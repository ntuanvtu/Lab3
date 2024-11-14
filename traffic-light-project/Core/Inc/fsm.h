/*
 * fsm.h
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"

extern int timer1, timer2;

void Red_1_On();
void Yellow_1_On();
void Green_1_On();
void Red_2_On();
void Yellow_2_On();
void Green_2_On();

void trafficOff();
void handleKeyInput(int index);

void fsm_run();

#endif /* INC_FSM_H_ */

