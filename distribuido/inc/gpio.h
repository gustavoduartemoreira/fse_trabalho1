#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>


#define L_01 18
#define L_02 23
#define AC 24
#define PR 25

#define Spres 7
#define Sfum 1
#define Sjan 12
#define Spor 16

#ifndef GPIO_H_
#define GPIO_H_

void gpio_init();
void toggle(int item, int state);
void* gpio_handler();
void desliga_tudo();

#endif /* GPIO_H_ */