/*za
 * button.c
 *
 *  Created on: Nov 12, 2024
 *      Author: ngoct
 */

/*
 * button.c
 *
 *  Created on: Oct 23, 2023
 *      Author: ProX
 */
#include "button.h"

int button_flag[3] = {0, 0, 0};
int KeyReg1Counter = 1;

static int KeyReg0[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
static int KeyReg1[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
static int KeyReg2[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

static int KeyReg3[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

static int TimerForKeyPress[3] = {100, 100, 100};

void subKeyProcess(int index) {
    button_flag[index] = 1;
}

int isButtonPressed(int index) {
    if (button_flag[index]) {
        button_flag[index] = 0;
        return 1;
    }
    return 0;
}

void getKeyInput() {
    for (int i = 0; i < 3; i++) {
        KeyReg0[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg2[i];

        if (i == 0) KeyReg2[i] = HAL_GPIO_ReadPin(Button_1_GPIO_Port, Button_1_Pin);
        if (i == 1) KeyReg2[i] = HAL_GPIO_ReadPin(Button_2_GPIO_Port, Button_2_Pin);
        if (i == 2) KeyReg2[i] = HAL_GPIO_ReadPin(Button_3_GPIO_Port, Button_3_Pin);

        if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg3[i] != KeyReg2[i]) {
                KeyReg3[i] = KeyReg2[i];

                if (KeyReg2[i] == PRESSED_STATE) {
                    subKeyProcess(i);
                    TimerForKeyPress[i] = 100;
                }
            } else {
                TimerForKeyPress[i]--;
                if (TimerForKeyPress[i] == 0) {
                    if (KeyReg2[i] == PRESSED_STATE) {
                        subKeyProcess(i);
                    }

                    TimerForKeyPress[i] = 100;
                }
            }
        }
    }

}
