#pragma once

#include <stdint.h>
#include "timer.h"

static uint32_t idle_timer = 0; // time since last keypress in milliseconds

void idle_timer_init(void){
    if (idle_timer == 0){
        idle_timer = timer_read32();
    }
}

void idle_timer_reset(void){
    idle_timer = timer_read32();
}

bool idle_timer_check(uint32_t limit){
    return timer_elapsed32(idle_timer) >= limit;
}