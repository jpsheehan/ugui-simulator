#include <stdio.h>

#include "example.h"
#include "simulator.h"

#define MAX_OBJECTS 10

UG_GUI *gui;

UG_WINDOW window_1 ;
UG_BUTTON button_1 ;
UG_BUTTON button_2 ;
UG_BUTTON button_3 ;
UG_TEXTBOX textbox_1 ;
UG_OBJECT obj_buff_wnd_1 [MAX_OBJECTS] ;

void window_1_callback ( UG_MESSAGE* msg )
{
    printf("window_1 Callback!\n");
}

void example_run(UG_GUI* t_gui)
{
    gui = t_gui;
    // . . .
    /* Create the window */
    UG_WindowCreate( &window_1 , obj_buff_wnd_1 , MAX_OBJECTS, window_1_callback ) ;
    /* Modify the window t i t l e */
    UG_WindowSetTitleText( &window_1 , "uGUI Demo Window" ) ;
    UG_WindowSetTitleTextFont( &window_1 , &FONT_12X20 ) ;
    /* Create some buttons */
    UG_ButtonCreate( &window_1 , &button_1 , BTN_ID_0 , 10 , 10 , 110 , 60 ) ;
    UG_ButtonCreate( &window_1 , &button_2 , BTN_ID_1 , 10 , 80 , 110 , 130 ) ;
    UG_ButtonCreate( &window_1 , &button_3 , BTN_ID_2 , 10 , 150 , 110 , 200 ) ;
    /* Label the buttons */
    UG_ButtonSetFont( &window_1 , BTN_ID_0 , &FONT_12X20 ) ;
    UG_ButtonSetText( &window_1 , BTN_ID_0 , "Button\nA" ) ;
    UG_ButtonSetFont( &window_1 , BTN_ID_1 , &FONT_12X20 ) ;
    UG_ButtonSetText( &window_1 , BTN_ID_1 , "Button\nB" ) ;
    UG_ButtonSetFont( &window_1 , BTN_ID_2 , &FONT_12X20 ) ;
    UG_ButtonSetText( &window_1 , BTN_ID_2 , "Button\nC" ) ;
    /* Create a Textbox */
    UG_TextboxCreate( &window_1 , &textbox_1 , TXB_ID_0 , 120 , 10 , 310 , 200 ) ;
    UG_TextboxSetFont( &window_1 , TXB_ID_0 , &FONT_12X16 ) ;
    UG_TextboxSetText( &window_1 , TXB_ID_0 ,
    "This is just \na very simple\nwindow to\ndemonstrate\nsome basic\nfeatures of uGUI!" ) ;
    UG_TextboxSetForeColor( &window_1 , TXB_ID_0 , C_BLACK ) ;
    UG_TextboxSetAlignment( &window_1 , TXB_ID_0 , ALIGN_CENTER ) ;
    /* Finally , show the window */
    UG_WindowShow( &window_1 ) ;

    // run the simulator
    simulator_loop();
}
