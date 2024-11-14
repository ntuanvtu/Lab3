/*
 * led7SEG.c
 *
 *  Created on: 17 thg 10, 2023
 *      Author: ProX
 */

#include "led7SEG.h"

int led_1 = 6;
int led_2 = 3;
int stat_led_1 = RED;
int stat_led_2 = GREEN;
int road_1_flag = 0, road_2_flag = 0;

void countDownLED() {
    display7SEG(led_1, led_2);

    if (timer_LED_flag == 1) {
        led_1--;
        led_2--;

        if (led_1 < 0) {
            road_1_flag = 1;

            switch (stat_led_1) {
                case RED:
                    stat_led_1 = GREEN;
                    led_1 = setTraffic[GREEN] / 1000;
                    break;
                case YELLOW:
                    stat_led_1 = RED;
                    led_1 = setTraffic[RED] / 1000;
                    break;
                case GREEN:
                    stat_led_1 = YELLOW;
                    led_1 = setTraffic[YELLOW] / 1000;
                    break;
            }
        }

        if (led_2 < 0) {
            road_2_flag = 1;

            switch (stat_led_2) {
                case RED:
                    stat_led_2 = GREEN;
                    led_2 = setTraffic[GREEN] / 1000;
                    break;
                case YELLOW:
                    stat_led_2 = RED;
                    led_2 = setTraffic[RED] / 1000;
                    break;
                case GREEN:
                    stat_led_2 = YELLOW;
                    led_2 = setTraffic[YELLOW] / 1000;
                    break;
            }
        }

        setTimer_LED(1000);
    }
}

int tempCounter;
int timer1, timer2;

void update7SEG() {
    if (status == INIT || status == RED_GREEN || status == RED_YELLOW || status == GREEN_RED || status == YELLOW_RED) {
        countDownLED();
    } else {
        if (KeyReg1Counter == 1) {
            status = INIT;
        }

        else if (KeyReg1Counter == 2) {
            tempCounter = TimerModify[RED];
        }

        else if (KeyReg1Counter == 3) {
            tempCounter = TimerModify[YELLOW];
        }

        else if (KeyReg1Counter == 4) {
            tempCounter = TimerModify[GREEN];
        }

        timer1 = KeyReg1Counter;        // Display MODE
        timer2 = tempCounter / 1000;    // Display value

        display7SEG(timer1, timer2);

    }
}

void display7SEG(int count_1, int count_2){
	uint32_t num_1[10] = {0x0001, 0x004F, 0x0012, 0x0006, 0x004C, 0x0024, 0x0020, 0x000F, 0x0000, 0x0004};
	uint32_t num_2[10] = {0x0080, 0x2780, 0x0900, 0x0300, 0x2600, 0x1200, 0x1000, 0x0780, 0x0000, 0x0200};
	GPIOB->ODR = num_1[count_1] | num_2[count_2];
}
