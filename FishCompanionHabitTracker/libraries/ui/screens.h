#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_HOME = 1,
    SCREEN_ID_HYDRATE = 2,
    SCREEN_ID_BREATHWORK_TIME = 3,
    SCREEN_ID_BREATHWORK_START = 4,
    SCREEN_ID_BREATHWORK_FINISH = 5,
    SCREEN_ID_RUN = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *home;
    lv_obj_t *hydrate;
    lv_obj_t *breathwork_time;
    lv_obj_t *breathwork_start;
    lv_obj_t *breathwork_finish;
    lv_obj_t *run;
    lv_obj_t *hydrate_btn;
    lv_obj_t *happy_mode;
    lv_obj_t *neutral_mode;
    lv_obj_t *sad_mode;
    lv_obj_t *run_btn;
    lv_obj_t *breathe_btn;
    lv_obj_t *obj0;
    lv_obj_t *watercounter;
    lv_obj_t *total;
    lv_obj_t *hydratebtn;
    lv_obj_t *obj1;
    lv_obj_t *breathtime;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *runbtn;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
} objects_t;

extern objects_t objects;

void create_screen_home();
void tick_screen_home();

void create_screen_hydrate();
void tick_screen_hydrate();

void create_screen_breathwork_time();
void tick_screen_breathwork_time();

void create_screen_breathwork_start();
void tick_screen_breathwork_start();

void create_screen_breathwork_finish();
void tick_screen_breathwork_finish();

void create_screen_run();
void tick_screen_run();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Groups

typedef struct _groups_t {
    lv_group_t *HomeWidgets;
    lv_group_t *GroupRemoveAllObjs;
    lv_group_t *HydrateWidgets;
    lv_group_t *BreathworkTimeWidgets;
    lv_group_t *BreathworkStartWidgets;
    lv_group_t *BreathworkFinishWidgets;
    lv_group_t *RunWidget;
} groups_t;

extern groups_t groups;

void ui_create_groups();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/

//testinggasdasdasdasasdasd