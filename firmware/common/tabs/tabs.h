// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#ifndef _tabs_h_
#define _tabs_h_

#include <stdint.h>

// ------------------------------------------------
// Standard payloads

enum {
    TABS_PL_STATUS_BTN0         = (1 << 0),
    TABS_PL_STATUS_BTN1         = (1 << 1),

    TABS_PL_STATUS_FAULT2       = (1 << 2),
    TABS_PL_STATUS_FAULT1       = (1 << 3),
    TABS_PL_STATUS_FAULT0       = (1 << 4),
};

enum {
    TABS_PORT_CONFIG            = 204,  /* 0xcc */

    TABS_PORT_DOORWINDOW        = 100,
    TABS_PORT_MOTION            = 102,
    TABS_PORT_AIRQ              = 103,
    TABS_PORT_POSITION          = 136,
    TABS_PORT_BUTTON            = 147,
};


// ------------------------------------------------
// Shared convenience functions

uint32_t tabs_minutes (void);

#endif
