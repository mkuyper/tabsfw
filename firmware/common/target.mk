ifeq (wsms130,$(TARGET))
    MCU         := stm32l0
    LD_SCRIPTS  += $(BL)/src/arm/stm32lx/ld/STM32L0xxB.ld
    DEFS        += -DSTM32L0 -DSTM32L072xx
    DEFS        += -DCFG_wsms130_board
    DEFS        += -DBRD_IMPL_INC='"$(CURDIR)/../common/brd_wsms130.h"'
    OOCFGS	+= ../common/wsms130.cfg
    BL_BUILD	:= ../../bootloader/wsms130
endif
