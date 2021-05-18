
/*********************
*      INCLUDES
*********************/
#include "../../my_apps.h"

/*********************
*      DEFINES
*********************/


/**********************
*      TYPEDEFS
**********************/
static lv_style_t style;

static void custom_apply_cb(lv_theme_t* th, lv_obj_t* obj, lv_theme_style_t name)
{
    lv_style_list_t* list;

    switch (name) {
    case LV_THEME_BTN:
        list = lv_obj_get_style_list(obj, LV_BTN_PART_MAIN);
        _lv_style_list_add_style(list, &style);
        break;
    }
}

/**
 * @brief create a custom theme based on the currently active built-in theme.
 * @param  
*/
void my_theme_test(void)
{
    /*Get the current theme It will be the base of the custom theme*/
    lv_theme_t* base_theme = lv_theme_get_act();

    static lv_theme_t custom_theme;
    lv_theme_copy(&custom_theme, base_theme);
    lv_theme_set_apply_cb(&custom_theme, custom_apply_cb);
    lv_theme_set_base(&custom_theme, base_theme);


    lv_style_init(&style);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, custom_theme.color_primary);

}

void my_theme_test2(void)
{
    static lv_style_t style_btn;
    static lv_style_t style_btn_red;

    /*create a simple button style*/
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 10);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_bg_grad_dir(&style_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    lv_style_set_bg_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_SILVER);
    /*add border*/
    lv_style_set_border_width(&style_btn, LV_STATE_DEFAULT, 2);
    lv_style_set_border_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    /*Different border color in focused state*/
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, LV_COLOR_BLUE);
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

    lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /*make the button smaller when pressed*/
    lv_style_set_transform_height(&style_btn, LV_STATE_PRESSED, -5);
    lv_style_set_transform_width(&style_btn, LV_STATE_PRESSED, -10);

    static lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

    //lv_style_set_transition_prop_1(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    //lv_style_set_transition_prop_2(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    //lv_style_set_transition_time(&style_btn, LV_STATE_DEFAULT, 100);
    
    lv_style_set_transition_path(&style_btn, LV_STATE_DEFAULT, &path);

    /*Create a red style. Change only some colors.*/
    lv_style_init(&style_btn_red);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_MAROON);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_MAROON);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_RED);
    lv_style_set_text_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /*create button 1*/
    lv_obj_t* btn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn, 10, 10);
    lv_obj_set_size(btn, 120, 50);
    lv_obj_reset_style_list(btn, LV_BTN_PART_MAIN);
    lv_obj_add_style(btn, LV_BTN_PART_MAIN, &style_btn);

    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t* btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn2, 10, 80);
    lv_obj_set_size(btn2, 120, 50);

    lv_obj_reset_style_list(btn2, LV_BTN_PART_MAIN);
    lv_obj_add_style(btn2, LV_BTN_PART_MAIN, &style_btn);
    lv_obj_add_style(btn2, LV_BTN_PART_MAIN, &style_btn_red);
    lv_obj_set_style_local_radius(btn2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);

    lv_obj_t* label2 = lv_label_create(btn2, NULL);
    lv_label_set_text(label2, "Button 2");

}


