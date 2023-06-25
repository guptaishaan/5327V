#include "main.h"
#include <stdlib.h>

static lv_res_t firstauton(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  char mytext[64];

  sprintf(mytext, "Button 1 \n");
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);
  auton1();
  /* The button is released.
  * Make something here */
 

  return LV_RES_OK; /*Return OK if the button is not deleted*/

}

static lv_res_t secondauton(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  char mytext[64];

  sprintf(mytext, "Button 2 \n");
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);
  auton2();

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t thirdauton(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  char mytext[64];

  sprintf(mytext, "Button 3\n");
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}


void gui(void) {

 /*Create a title label*/
 lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
 lv_label_set_text(label, "Select a Button");
 lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

 /*Create a normal button*/
 static lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
 lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
 lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
 lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
 lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, firstauton);

 /*Add a label to the button*/
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Auton 1");

 /*Copy the button and set toggled state. (The release action is copied too)*/
 static lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
 lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
 // lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
 lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
 lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, secondauton);

 /*Add a label to the toggled button*/
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Auton 2");

 /*Copy the button and set inactive state.*/
 static lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
 lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 10);
 //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
 lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
 lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, thirdauton);

 /*Add a label to the inactive button*/
 label = lv_label_create(btn3, NULL);
 lv_label_set_text(label, "Auton 3");
}
