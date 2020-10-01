// Copyright (C) 2020-2020 Michael Kuyper. All rights reserved.
// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

// to be included from board.h

// -------------------------------------------
#if defined(CFG_wsms130_board)

// Use the SX1276
#define BRD_sx1276_radio
#define BRD_sck_mosi_pulldown

// GPIOs connected to the SX1276
#define GPIO_RST        BRD_GPIO(PORT_B, 10)       // PB10
#define GPIO_DIO0       BRD_GPIO(PORT_B, 11)       // PB11
#define GPIO_DIO1       BRD_GPIO(PORT_C, 13)       // PC13
#define GPIO_DIO2       BRD_GPIO(PORT_B, 9)        // PB9
#define GPIO_DIO3       BRD_GPIO(PORT_B, 4)        // PB4
#define GPIO_DIO4       BRD_GPIO(PORT_B, 3)        // PB3
#define GPIO_DIO5       BRD_GPIO(PORT_A, 15)       // PA15

// SPI bus connection to the SX1276
#define BRD_RADIO_SPI   2                          // SPI2
#define GPIO_NSS        BRD_GPIO(PORT_B, 12)       // PB12
#define GPIO_SCK        BRD_GPIO_AF(PORT_B, 13, 0) // PB13, alternate function 0
#define GPIO_MISO       BRD_GPIO_AF(PORT_B, 14, 0) // PB14, alternate function 0
#define GPIO_MOSI       BRD_GPIO_AF(PORT_B, 15, 0) // PB15, alternate function 0

// Antenna switch
#define GPIO_TX         BRD_GPIO(PORT_A, 0)
#define GPIO_RX         BRD_GPIO_EX(PORT_A, 1, BRD_GPIO_ACTIVE_LOW)

// Enabled USART peripherals
#define BRD_USART       (BRD_USART1)

// USART1
#define BRD_USART1_DMA  BRD_DMA_CHANS(2,3)
#define GPIO_USART1_TX  BRD_GPIO_AF(PORT_A, 9,  4)  // PA9,  alternate function 4
#define GPIO_USART1_RX  BRD_GPIO_AF(PORT_A, 10, 4)  // PA10, alternate function 4

// Debug USART
#define BRD_DBG_UART    BRD_USART1_PORT

// Personalization UART
#define BRD_PERSO_UART  BRD_USART1_PORT
#define GPIO_PERSO_DET  GPIO_USART1_RX

// LED
#define GPIO_LED0       BRD_GPIO(PORT_B, 5)
#define BRD_LED_BLUE    GPIO_LED0

// Hall sensor (Door/Window)
#define GPIO_HALL       BRD_GPIO(PORT_A, 3)

// Power
#define GPIO_LSW        BRD_GPIO(PORT_A, 5) // battery load switch (diconnect battery from super caps)
#define GPIO_SSW        BRD_GPIO(PORT_B, 1) // sensor board load switch
#define GPIO_PSW        BRD_GPIO(PORT_A, 8) // voltage divider load switch
#define BRD_ADC_TEMP    2                   // PA2, channel 2
#define BRD_ADC_VBAT    8                   // PB0, channel 8

#endif
