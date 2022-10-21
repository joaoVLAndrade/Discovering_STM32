/*
 * app.h
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#ifndef APP_H_
#define APP_H_

#include <stdbool.h>

void app_init(void);
void app_loop(void);
void app_switch_0_interrupt(void);
void app_box_set_full(bool state);

#endif /* APP_H_ */
