// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#include "lmic.h"
#include "tabs/tabs.h"

uint32_t tabs_minutes (void) {
    return osticks2sec(os_getXTime()) / 60;
}
