/*
 * led7SEG.h
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */

#ifndef INC_LED7SEG_H_
#define INC_LED7SEG_H_

#include "global.h"

extern int led_1;
extern int led_2;
extern int stat_led_1;
extern int stat_led_2;
extern int road_1_flag;
extern int road_2_flag;

void display7SEG(int count_1, int count_2);
void countdownLED();
void update7SEG();

#endif /* INC_LED7SEG_H_ */
