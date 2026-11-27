#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: Focused
//

void init_style_focused_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xff0000));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_focused_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_focused_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_focused(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_focused_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_focused(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_focused_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_focused,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_focused,
    };
    remove_style_funcs[styleIndex](obj);
}