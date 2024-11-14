/*
 * button.h
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int KeyReg1Counter;
extern int TimerModify[3];
extern int setTraffic[3];

void handleKeyInput();
void subKeyProcess();
int isButtonPressed(int index);
void getKeyInput();

#endif /* INC_BUTTON_H_ */
