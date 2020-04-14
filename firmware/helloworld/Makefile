TOPDIR := ../../basicmac

TARGET := wsms130

VARIANTS := eu868 us915 hybrid simul

REGIONS.simul := eu868
TARGET.simul := unicorn

FAM_MAKEFILES += ../common/target.mk

CFLAGS += -Os
CFLAGS += -g
CFLAGS += -Wall -Wno-main

SVCS += app

DEFS += -DSVC_FWMAN_TEST # enable test key function in fwman service
DEFS += -DSVC_FWMAN_PUBKEY=fwman_testkey
DEFS += -DSVC_FWMAN_CURVE=uECC_secp256r1

DEFS += -DDEBUG_RX
DEFS += -DDEBUG_TX

LMICCFG += eeprom_keys
LMICCFG += eeprom_region
LMICCFG += DEBUG
LMICCFG += extapi

include $(TOPDIR)/projects/projects.gmk

ifeq (simul,$(VARIANT))
test: build-$(VARIANT)/$(PROJECT).hex
	PYTHONPATH=$${PYTHONPATH}:$(TOPDIR)/tools/pylora:$(TOPDIR)/unicorn/simul \
		   $(TOPDIR)/unicorn/simul/lwtest.py \
		   -r EU868 \
		   -v -d -t \
		   $(TESTOPTS) \
		   $(BL)/build/boards/$(BL_BRD)/bootloader.hex \
		   $<
endif


.PHONY: test
