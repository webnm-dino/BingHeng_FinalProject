#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_CURRENT_PAGE = 0,
    FLOW_GLOBAL_VARIABLE_ARC_VALUE = 1,
    FLOW_GLOBAL_VARIABLE_TIMER_VALUE = 2,
    FLOW_GLOBAL_VARIABLE_TIMER_RUNNING = 3,
    FLOW_GLOBAL_VARIABLE_WATER_COUNT = 4,
    FLOW_GLOBAL_VARIABLE_WATER_GOAL = 5,
    FLOW_GLOBAL_VARIABLE_HABIT_BREATH_STATUS = 6,
    FLOW_GLOBAL_VARIABLE_HABIT_WATER_STATUS = 7,
    FLOW_GLOBAL_VARIABLE_HABIT_RUN_STATUS = 8,
    FLOW_GLOBAL_VARIABLE_GROUP_REMOVE_ALL_OBJS = 9
};

// Native global variables

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/