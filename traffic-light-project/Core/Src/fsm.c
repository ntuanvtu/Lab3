/*
 * fsm.c
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */


/*
 * fsm.c
 *
 *  Created on: Oct 17, 2023
 *      Author: ProX
 */

#include "fsm.h"

void Red_Green() {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
}

void Red_Yellow() {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void Green_Red() {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void Yellow_Red() {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void trafficOff() {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void handleKeyInput(int index) {
    if (index == 0) {
        KeyReg1Counter++;

        if (KeyReg1Counter == 1 || KeyReg1Counter > 4) {
            KeyReg1Counter = 1;

            status = INIT;

            led_1 = setTraffic[RED] / 1000;
            led_2 = setTraffic[GREEN] / 1000;
            stat_led_1 = RED;
            stat_led_2 = GREEN;
            road_1_flag = 0;
            road_2_flag = 0;
            setTimer_LED(1000);
        } else if (KeyReg1Counter == 2 || KeyReg1Counter == 3|| KeyReg1Counter == 4) {
            setTimer3(500);
            trafficOff();
        }

    }
    else if (index == 1) {
        if (KeyReg1Counter == 2) {
            TimerModify[RED] += 1000;

            if (TimerModify[RED] > 9000) {
                TimerModify[RED] = 0;
            }
        }

        else if (KeyReg1Counter == 3) {
            TimerModify[YELLOW] += 1000;

            if (TimerModify[YELLOW] > 9000) {
                TimerModify[YELLOW] = 0;
            }
        }

        else if (KeyReg1Counter == 4) {
            TimerModify[GREEN] += 1000;

            if (TimerModify[GREEN] > 9000) {
                TimerModify[GREEN] = 0;
            }
        }
    }
    else if (index == 2) {
        if (KeyReg1Counter == 2) {
            KeyReg1Counter = 1;

            if (TimerModify[RED] - TimerModify[YELLOW] - 1000 > 0) {
                setTraffic[RED] = TimerModify[RED];
                setTraffic[GREEN] = setTraffic[RED] - setTraffic[YELLOW] - 1000;
                TimerModify[GREEN] = setTraffic[GREEN];
            }
        }

        else if (KeyReg1Counter == 3) {
            KeyReg1Counter = 1;

            if (TimerModify[YELLOW] + TimerModify[GREEN] + 1000 <= 9000) {
                setTraffic[YELLOW] = TimerModify[YELLOW];
                setTraffic[RED] = setTraffic[YELLOW] + setTraffic[GREEN] + 1000;
                TimerModify[RED] = setTraffic[RED];
                }
            }

            else if (KeyReg1Counter == 4) {
                KeyReg1Counter = 1;

                if (TimerModify[YELLOW] + TimerModify[GREEN] + 1000 <= 9000) {
                    setTraffic[GREEN] = TimerModify[GREEN];
                    setTraffic[RED] = setTraffic[YELLOW] + setTraffic[GREEN] + 1000;
                    TimerModify[RED] = setTraffic[RED];
                }
            }

        HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DOT1_GPIO_Port, DOT1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DOT2_GPIO_Port, DOT2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DOT3_GPIO_Port, DOT3_Pin, GPIO_PIN_RESET);

        status = INIT;

        led_1 = setTraffic[RED] / 1000;
        led_2 = setTraffic[GREEN] / 1000;
        stat_led_1 = RED;
        stat_led_2 = GREEN;
        road_1_flag = 0;
        road_2_flag = 0;
        setTimer_LED(1000);
    }
}

void fsm_run() {
    switch (status) {
        case INIT:
            Red_Green();

            status = RED_GREEN;

            break;

        case RED_GREEN:
            Red_Green();

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = MAN_RED;
            }

            if (road_2_flag == 1) {
                road_2_flag = 0;
                status = RED_YELLOW;
            }

            break;

        case RED_YELLOW:
            Red_Yellow();

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = MAN_RED;
            }

            if (road_1_flag == 1 && road_2_flag == 1) {
                road_1_flag = 0;
                road_2_flag = 0;
                status = GREEN_RED;
            }

            break;

        case GREEN_RED:
            Green_Red();

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = MAN_RED;
            }

            if (road_1_flag == 1) {
                road_1_flag = 0;
                status = YELLOW_RED;
            }

            break;

        case YELLOW_RED:
            Yellow_Red();

            if (isButtonPressed(0)) {
                status = MAN_RED;
            }

            if (road_1_flag == 1 && road_2_flag == 1) {
                road_1_flag = 0;
                road_2_flag = 0;
                status = RED_GREEN;
            }

            break;

        case MAN_RED:
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
                HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);

                setTimer3(500);
            }

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = MAN_YELLOW;
            }

            if (isButtonPressed(1)) {
                handleKeyInput(1);
            }

            if (isButtonPressed(2)) {
                handleKeyInput(2);
                status = RED_GREEN;
            }

            break;

        case MAN_YELLOW:
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin);
                HAL_GPIO_TogglePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin);

                setTimer3(500);
            }

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = MAN_GREEN;
            }

            if (isButtonPressed(1)) {
                handleKeyInput(1);
            }

            if (isButtonPressed(2)) {
                handleKeyInput(2);
                status = RED_GREEN;
            }

            break;

        case MAN_GREEN:
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
                HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);

                setTimer3(500);
            }

            if (isButtonPressed(0)) {
                handleKeyInput(0);
                status = RED_GREEN;
            }

            if (isButtonPressed(1)) {
                handleKeyInput(1);
            }

            if (isButtonPressed(2)) {
                handleKeyInput(2);
                status = RED_GREEN;
            }
    }
}
