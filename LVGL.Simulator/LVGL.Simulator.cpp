/*
 * PROJECT:   LVGL ported to Windows Desktop
 * FILE:      LVGL.Windows.Desktop.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
#include "lv_examples/lv_examples.h"
#include "my_apps/my_apps.h"
#include "FLT/FLT_Entry.h"
#include "lv_drivers/win32drv/win32drv.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

int main()
{
    lv_init();

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        LV_HOR_RES_MAX,
        LV_VER_RES_MAX,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    /*
     * Demos, benchmarks, and tests.
     *
     * Uncomment any one (and only one) of the functions below to run that
     * item.
     */
    //first_app_examples();
    //my_style_test();
    //my_style_test2();
    //my_style_test3();
    //my_style_test4();
    //my_style_test5();
    //my_style_test6();
    //my_style_test10();
    //my_style_test8();
    //my_theme_test2();
    //vending_machine();
    FLT_Entry();
    //lv_demo_widgets();
    //lv_demo_benchmark();
    //lv_demo_keypad_encoder();
    //lv_demo_printer();
    //lv_demo_stress();
    //lv_ex_get_started_1();
    //lv_ex_get_started_2();
    //lv_ex_get_started_3();

    //lv_ex_style_1();
    //lv_ex_style_2();
    //lv_ex_style_3();
    //lv_ex_style_4();
    //lv_ex_style_5();
    //lv_ex_style_6();
    //lv_ex_style_7();
    //lv_ex_style_8();
    //lv_ex_style_9();
    //lv_ex_style_10();
    //lv_ex_style_11();
    //lv_ex_win_1();
    //lv_ex_msgbox_2();

    /*
     * There are many examples of individual widgets found under the
     * lv_examples/src/lv_ex_widgets directory.  Here are a few sample test
     * functions.  Look in that directory to find all the rest.
     */
     //lv_ex_arc_1();
     //lv_ex_cpicker_1();
     //lv_ex_gauge_1();
     //lv_ex_img_1();
     //lv_ex_tileview_1();

    while (!lv_win32_quit_signal)
    {
        lv_task_handler();
        Sleep(10);
    }

    return 0;
}
