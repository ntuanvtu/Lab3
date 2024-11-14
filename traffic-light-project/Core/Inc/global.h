/*
 * global.h
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "fsm.h"
#include "led7SEG.h"

#define redTimer        6000
#define greenTimer      3000
#define yellowTimer     2000

#define RED             0
#define YELLOW          1
#define GREEN           2
#define INIT            3
#define MAN_RED        100
#define MAN_YELLOW     200
#define MAN_GREEN      300

#define RED_GREEN       150
#define RED_YELLOW      250
#define GREEN_RED       350
#define YELLOW_RED      450

#define MODIFY          10
#define AUTOMATIC       20

extern int status;
extern int status1;
extern int status2;
extern int status3;

extern int TimerModify[3];
extern int setTraffic[3];

#endif /* INC_GLOBAL_H_ */

