/*
 * app.h
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_get_tick(void);
void app_loop(void);
void app_switch_0_interrupt(void);
void app_switch_1_interrupt(void);

#endif /* APP_H_ */
