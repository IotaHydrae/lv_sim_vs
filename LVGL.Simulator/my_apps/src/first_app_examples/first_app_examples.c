#include "../../my_apps.h"

static void btn1_event_cb(lv_obj_t* btn, lv_event_t event)
{
    static uint8_t cnt = 0;
    if (event == LV_EVENT_CLICKED) {
        lv_obj_set_top(btn, true);
    }
    switch (event)
    {
    case LV_EVENT_CLICKED:
        
        cnt++;
        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t* label = lv_obj_get_child(btn, NULL);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

static void btn2_event_cb(lv_obj_t* btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        lv_obj_set_top(btn, true);
    }
}
/**
 * Create a button with a label and react on Click event.
 */
void first_app_examples(void)
{
    LV_IMG_DECLARE(pic1_alpha_800x480);
	/*Create a screen*/

	lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_obj_t* srceen_img = lv_img_create(scr, NULL);

    /*static lv_style_t style_screen_img0_main;
    lv_style_init(&style_screen_img0_main);

    lv_style_set_image_recolor(&style_screen_img0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_image_recolor_opa(&style_screen_img0_main, LV_STATE_DEFAULT, 0);
    lv_style_set_image_opa(&style_screen_img0_main, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(srceen_img, LV_IMG_PART_MAIN, &style_screen_img0_main);*/

    lv_obj_set_pos(srceen_img, 0, 0);
    //lv_obj_set_click(srceen_img, true);
    lv_obj_set_size(srceen_img, 800, 480);
    lv_img_set_src(srceen_img, &pic1_alpha_800x480);
    /*lv_img_set_pivot(srceen_img, 0, 0);
    lv_img_set_angle(srceen_img, 0);*/

	lv_scr_load(scr);																/*Load the screen*/
	
	/*Create 2 buttons*/
	lv_obj_t * btn1 = lv_btn_create(scr, NULL); 		/*Create a button on the screen*/
	lv_btn_set_fit(btn1, true);					/*Enable to automatically set the size according to the content*/
	lv_obj_set_pos(btn1, 60, 40);									/*Set the position of the button*/
    lv_obj_set_event_cb(btn1, btn1_event_cb);
	
	lv_obj_t * btn2 = lv_btn_create(scr, btn1); 		/*Copy the first button*/
	lv_obj_set_pos(btn2, 70, 60);							/*Set the position of the button*/
    lv_obj_set_event_cb(btn2, btn2_event_cb);
	/*Add labels to the buttons*/
	lv_obj_t * label1 = lv_label_create(btn1, NULL);		/*Create a label on the first button*/
	lv_label_set_text(label1, "Button 1");					/*Set the text of the label*/


	lv_obj_t * label2 = lv_label_create(btn2, NULL);		/*Create a label on the second button*/
	lv_label_set_text(label2, "Button 2");
    /*Set the text of the label*/

}
