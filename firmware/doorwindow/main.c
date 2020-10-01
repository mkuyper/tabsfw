// Copyright (C) 2020-2020 Michael Kuyper. All rights reserved.
// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#include "lmic.h"
#include "lwmux/lwmux.h"

#include "tabs/tabs.h"
#include "eefs/eefs.h"
#include "uexti/uexti.h"
#include "svcdefs.h"

typedef struct {
    uint32_t interval;  // minimum send interval (sec)
} dwconfig;

static struct {
    bool open;          // current sensor state (open/closed)
    uint32_t total;     // total events counted since last reboot
    uint32_t last;      // time of last event (in minutes)
    ostime_t next;      // time of next uplink (can be max. ~18h in future!)
    osjob_t* job;       // pointer to job (reusing init job!)
    dwconfig cfg;       // persistent configuration
} state;

// 16c6e6bb749241e0-327793d5
static const uint8_t UFID_DW_CONFIG[12] = { 0xe0, 0x41, 0x92, 0x74, 0xbb, 0xe6, 0xc6, 0x16, 0xd5, 0x93, 0x77, 0x32 };

const char* dw_eefs_fn (const uint8_t* ufid) {
    if( memcmp(ufid, UFID_DW_CONFIG, sizeof(UFID_DW_CONFIG)) == 0 ) {
        return "io.tabs.dwconfig";
    }
    return NULL;
}

void dw_cfg_load (void) {
    if( eefs_read(UFID_DW_CONFIG, &state.cfg, sizeof(dwconfig)) != sizeof(dwconfig) ) {
        state.cfg.interval = 360 * 60;
    }
    eefs_save(UFID_DW_CONFIG, &state.cfg, sizeof(dwconfig));
}

static bool tx (lwm_txinfo* txinfo) {
    txinfo->data[0] = state.open ? TABS_PL_STATUS_BTN0 : 0;
    txinfo->data[1] = 0; // TODO - battery
    txinfo->data[2] = 0; // TODO - temperature
    os_wlsbf2(txinfo->data + 3, tabs_minutes() - state.last);
    os_wlsbf3(txinfo->data + 5, state.total);
    txinfo->dlen = 8;
    txinfo->port = TABS_PORT_DOORWINDOW;
    return true;
}

void app_dl (int port, unsigned char* data, int dlen, unsigned int flags) {
    debug_printf("DL[%d]: %h\r\n", port, data, dlen);
}

static void check_uplink (osjob_t* job) {
    static lwm_job lj;
    ostime_t now = os_getXTime();
    if( (state.next - now) <= 0 ) {
        lwm_request_send(&lj, 0, tx);
        state.next += sec2osticks(state.cfg.interval);
    }
    os_setApproxTimedCallback(state.job, state.next, check_uplink);
}

static void trigger_uplink (void) {
    state.next = os_getTime();
    check_uplink(NULL);
}

static void hall_update (void) {
    bool open = pio_get(GPIO_HALL);
    if( state.open == open ) {
        // state didn't change -- missed an event
        state.total += 2;
    } else {
        state.open = open;
        state.total += 1;
    }
    state.last = tabs_minutes();
    debug_printf("%s total=%d\r\n", state.open ? "open  " : "closed", state.total);
    trigger_uplink();
}

static void hall_debounce (osjob_t* job) {
    hall_update();
}

// initialize the hall sensor
static void hall_init (osjob_t* job) {
    static int step;
    switch( step) {
        case 0:
            // power the sensor board
            pio_set(GPIO_SSW, 1);
            // configure the hall sensor input pin
            pio_set(GPIO_HALL, PIO_INP_HIZ);
            // wait a little
            os_setTimedCallback(job, os_getTime() + ms2osticks(500), hall_init);
            break;
        case 1:
            // read current state
            state.open = pio_get(GPIO_HALL);
            // arm the interrupt
            uexti_config(GPIO_HALL, true, true);
            uexti_enable(GPIO_HALL, true);
            // trigger first uplink
            trigger_uplink();
            break;
        default:
            ASSERT(0);
    }
    step += 1;
}

void hall_irq (unsigned int* mask) {
    static osjob_t job;
    if( *mask & (1 << PIO_IRQ_LINE(GPIO_HALL)) ) {
        os_setTimedCallback(&job, os_getTime() + ms2osticks(5), hall_debounce);
        *mask &= ~(1 << PIO_IRQ_LINE(GPIO_HALL));
    }
}

bool app_main (osjob_t* job) {
    state.job = job;
    hall_init(job);
    lwm_setmode(LWM_MODE_NORMAL);
    return true;
}
