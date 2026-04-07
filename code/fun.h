#ifndef _fun_h
#define _fun_h
#include "stm32g4xx.h"                  // Device header
void led_show(uint8_t led,uint8_t mode);
void lcd_show(void);
void b1_scan(void);
void r37_adc_detect(void);
void r38_adc_detect(void);
#endif
