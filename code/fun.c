#include "headfile.h"
int r37_value,r38_value;
char text_line2[20];
char text_line3[20];
char text_line4[20];
char text_line5[20];
char text_line6[20];
char text_line7[20];
char text_line8[20];
char text_line9[20];
char texted[20];
int b1_lock;
int led8_state_r37;
int led8_state_r38;
int b1_state,b1_laststate;
int r37_state,r37_laststate,r38_state,r38_laststate;
void led_show(uint8_t led,uint8_t mode){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
	if (mode){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8 << (led - 1),GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8 << (led - 1),GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
}
void b1_scan(){
	b1_state = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	if (b1_state == 0 && b1_laststate == 1){
		b1_lock ++;
		b1_lock %=2;
	}
	b1_laststate = b1_state;
}
void r37_adc_detect(){
	if (b1_lock == 0){
		HAL_ADC_Start(&hadc2);
		r37_value = HAL_ADC_GetValue(&hadc2);
	}
	if (r37_value < 273){
		r37_state = 0;
		led8_state_r37 = 1;
	}else if (r37_value < 546){
		r37_state = 1;
		led8_state_r37 = 1;
	}else if (r37_value < 819){
		r37_state = 2;
		led8_state_r37 = 1;
	}else if (r37_value < 1092){
		r37_state = 3;
		led8_state_r37 = 0;
	}else if (r37_value < 1365){
		r37_state = 4;
		led8_state_r37 = 0;
	}else if (r37_value < 1638){
		r37_state = 5;
		led8_state_r37 = 0;
	}else if (r37_value < 1911){
		r37_state = 6;
		led8_state_r37 = 0;
	}else if (r37_value < 2184){
		r37_state = 7;
		led8_state_r37 = 0;
	}else if (r37_value < 2457){
		r37_state = 8;
		led8_state_r37 = 0;
	}else if (r37_value < 2730){
		r37_state = 9;
		led8_state_r37 = 0;
	}else if (r37_value < 3003){
		r37_state = 10;
		led8_state_r37 = 0;
	}else if (r37_value < 3276){
		r37_state = 11;
		led8_state_r37 = 0;
	}else if (r37_value < 3549){
		r37_state = 12;
		led8_state_r37 = 1;
	}else if (r37_value < 3822){
		r37_state = 13;
		led8_state_r37 = 1;
	}else if (r37_value < 4095){
		r37_state = 14;
		led8_state_r37 = 1;
	}
	if (r37_laststate != r37_state){
		//LCD_Clear(Black);
	}
	r37_laststate = r37_state;
}
void r38_adc_detect(){
	if (b1_lock == 0){
		HAL_ADC_Start(&hadc1);
		r38_value = HAL_ADC_GetValue(&hadc1);
	}
	if (r38_value < 273){
		r38_state = 0;
		led8_state_r38 = 1;
	}else if (r38_value < 546){
		r38_state = 1;
		led8_state_r38 = 1;
	}else if (r38_value < 819){
		r38_state = 2;
		led8_state_r38 = 1;
	}else if (r38_value < 1092){
		r38_state = 3;
		led8_state_r38 = 0;
	}else if (r38_value < 1365){
		r38_state = 4;
		led8_state_r38 = 0;
	}else if (r38_value < 1638){
		r38_state = 5;
		led8_state_r38 = 0;
	}else if (r38_value < 1911){
		r38_state = 6;
		led8_state_r38 = 0;
	}else if (r38_value < 2184){
		r38_state = 7;
		led8_state_r38 = 0;
	}else if (r38_value < 2457){
		r38_state = 8;
		led8_state_r38 = 0;
	}else if (r38_value < 2730){
		r38_state = 9;
		led8_state_r38 = 0;
	}else if (r38_value < 3003){
		r38_state = 10;
		led8_state_r38 = 0;
	}else if (r38_value < 3276){
		r38_state = 11;
		led8_state_r38 = 0;
	}else if (r38_value < 3549){
		r38_state = 12;
		led8_state_r38 = 1;
	}else if (r38_value < 3822){
		r38_state = 13;
		led8_state_r38 = 1;
	}else if (r38_value < 4095){
		r38_state = 14;
		led8_state_r38 = 1;
	}
	if (r38_laststate != r38_state){
		//LCD_Clear(Black);
	}
	r38_laststate = r38_state;
}


void lcd_show(){
	uint16_t temp = GPIOC->ODR;
	sprintf(texted,"       ANGLE");
	LCD_DisplayStringLine(Line0,(uint8_t *)texted);
	sprintf(texted,"    R37      R38");
	LCD_DisplayStringLine(Line1,(uint8_t *)texted);
	if (r37_state == 0){
		if (r38_state !=0 && r38_state !=14){
			sprintf(text_line2,"  *                 ");
		}else if (r38_state == 0 ){
			sprintf(text_line2,"  *        +        ");
		}else if (r38_state == 14 ){
			sprintf(text_line2,"  *              +  ");
		}
		LCD_DisplayStringLine(Line2,(uint8_t *)text_line2);
	}
	if (r37_state == 14){
		if (r38_state !=0 && r38_state !=14){
			sprintf(text_line2,"        *            ");
		}else if (r38_state == 0 ){
			sprintf(text_line2,"        *  +         ");
		}else if (r38_state == 14 ){
			sprintf(text_line2,"        *        +  ");
		}
		LCD_DisplayStringLine(Line2,(uint8_t *)text_line2);
	}
	if (r37_state != 0 && r37_state !=14){
		if (r38_state == 0 ){
			sprintf(text_line2,"           +        ");
		 }else if (r38_state == 14 ){
			sprintf(text_line2,"                 +  ");
		}else{
			sprintf(text_line2,"                    ");
		}
		LCD_DisplayStringLine(Line2,(uint8_t *)text_line2);
	}
	//Line2
	
	if (r37_state == 1){
		if (r38_state !=1 && r38_state !=13){
			sprintf(text_line3," *                   ");
		}else if (r38_state == 1 ){
			sprintf(text_line3," *        +          ");
		}else if (r38_state == 13 ){
			sprintf(text_line3," *                +  ");
		}
		LCD_DisplayStringLine(Line3,(uint8_t *)text_line3);
	}
	if (r37_state == 13){
		if (r38_state !=1 && r38_state !=13){
			sprintf(text_line3,"         *          ");
		}else if (r38_state == 1 ){
			sprintf(text_line3,"         *+         ");
		}else if (r38_state == 13 ){
			sprintf(text_line3,"         *        + ");
		}
		LCD_DisplayStringLine(Line3,(uint8_t *)text_line3);
	}
	if (r37_state != 1 && r37_state !=13){
		if (r38_state == 1 ){
			sprintf(text_line3,"          +         ");
		 }else if (r38_state == 13 ){
			sprintf(text_line3,"                  + ");
		}else{
			sprintf(text_line3,"                      ");
		}
		LCD_DisplayStringLine(Line3,(uint8_t *)text_line3);
	}
	//Line3
	
	if (r37_state == 2){
		if (r38_state !=2 && r38_state !=12){
			sprintf(text_line4,"*                   ");
		}else if (r38_state == 2 ){
			sprintf(text_line4,"*        +          ");
		}else if (r38_state == 12 ){
			sprintf(text_line4,"*                  +");
		}
		LCD_DisplayStringLine(Line4,(uint8_t *)text_line4);
	}
	if (r37_state == 12){
		if (r38_state !=2 && r38_state !=12){
			sprintf(text_line4,"          *         ");
		}else if (r38_state == 2 ){
			sprintf(text_line4,"         +*         ");
		}else if (r38_state == 12 ){
			sprintf(text_line4,"          *        +");
		}
		LCD_DisplayStringLine(Line4,(uint8_t *)text_line4);
	}
	if (r37_state != 2 && r37_state !=12){
		if (r38_state == 2 ){
			sprintf(text_line4,"         +          ");
		 }else if (r38_state == 12 ){
			sprintf(text_line4,"                   +");
		}else{
			sprintf(text_line4,"                    ");
		}
		LCD_DisplayStringLine(Line4,(uint8_t *)text_line4);
	}
	//Line4
	
	if (r37_state == 3){
		if (r38_state !=3 && r38_state !=11){
			sprintf(text_line5,"*    -        =     ");
		}else if (r38_state == 3 ){
			sprintf(text_line5,"*    -   +    =     ");
		}else if (r38_state == 11 ){
			sprintf(text_line5,"*    -        =    +");
		}
		LCD_DisplayStringLine(Line5,(uint8_t *)text_line5);
	}
	if (r37_state == 11){
		if (r38_state !=3 && r38_state !=11){
			sprintf(text_line5,"     -    *   =     ");
		}else if (r38_state == 3 ){
			sprintf(text_line5,"     -   +*   =     ");
		}else if (r38_state == 11 ){
			sprintf(text_line5,"     -    *   =    +");
		}
		LCD_DisplayStringLine(Line5,(uint8_t *)text_line5);
	}
	if (r37_state != 3 && r37_state !=11){
		if (r38_state == 3 ){
			sprintf(text_line5,"     -   +    =     ");
		 }else if (r38_state == 11 ){
			sprintf(text_line5,"     -        =    +");
		}else{
			sprintf(text_line5,"     -        =     ");
		}
		LCD_DisplayStringLine(Line5,(uint8_t *)text_line5);
	}
	//Line5
	
	if (r37_state == 4){
		if (r38_state !=4 && r38_state !=10){
			sprintf(text_line6,"*                   ");
		}else if (r38_state == 4 ){
			sprintf(text_line6,"*        +          ");
		}else if (r38_state == 10 ){
			sprintf(text_line6,"*                  +");
		}
		LCD_DisplayStringLine(Line6,(uint8_t *)text_line6);
	}
	if (r37_state == 10){
		if (r38_state !=4 && r38_state !=10){
			sprintf(text_line6,"          *         ");
		}else if (r38_state == 4 ){
			sprintf(text_line6,"         +*         ");
		}else if (r38_state == 10 ){
			sprintf(text_line6,"          *        +");
		}
		LCD_DisplayStringLine(Line6,(uint8_t *)text_line6);
	}
	if (r37_state != 4 && r37_state !=10){
		if (r38_state == 4 ){
			sprintf(text_line6,"         +          ");
		 }else if (r38_state == 10 ){
			sprintf(text_line6,"                   +");
		}else{
			sprintf(text_line6,"                    ");
		}
		LCD_DisplayStringLine(Line6,(uint8_t *)text_line6);
	}
	//Line6
	
	if (r37_state == 5){
		if (r38_state !=5 && r38_state !=9){
			sprintf(text_line7," *                   ");
		}else if (r38_state == 5 ){
			sprintf(text_line7," *        +          ");
		}else if (r38_state == 9 ){
			sprintf(text_line7," *                +  ");
		}
		LCD_DisplayStringLine(Line7,(uint8_t *)text_line7);
	}
	if (r37_state == 9){
		if (r38_state !=5 && r38_state !=9){
			sprintf(text_line7,"         *          ");
		}else if (r38_state == 5 ){
			sprintf(text_line7,"         *+         ");
		}else if (r38_state == 9 ){
			sprintf(text_line7,"         *        + ");
		}
		LCD_DisplayStringLine(Line7,(uint8_t *)text_line7);
	}
	if (r37_state != 5 && r37_state !=9){
		if (r38_state == 5 ){
			sprintf(text_line7,"          +         ");
		 }else if (r38_state == 9 ){
			sprintf(text_line7,"                  + ");
		}else{
			sprintf(text_line7,"                      ");
		}
		LCD_DisplayStringLine(Line7,(uint8_t *)text_line7);
	}
	//Line7
	
	if (r37_state == 6){
		if (r38_state !=6 && r38_state !=8){
			sprintf(text_line8,"  *                 ");
		}else if (r38_state == 6 ){
			sprintf(text_line8,"  *        +        ");
		}else if (r38_state == 8 ){
			sprintf(text_line8,"  *              +  ");
		}
		LCD_DisplayStringLine(Line8,(uint8_t *)text_line8);
	}
	if (r37_state == 8){
		if (r38_state !=6 && r38_state !=8){
			sprintf(text_line8,"        *            ");
		}else if (r38_state == 6 ){
			sprintf(text_line8,"        *  +         ");
		}else if (r38_state == 8 ){
			sprintf(text_line8,"        *        +  ");
		}
		LCD_DisplayStringLine(Line8,(uint8_t *)text_line8);
	}
	if (r37_state != 6 && r37_state !=8){
		if (r38_state == 6 ){
			sprintf(text_line8,"           +        ");
		 }else if (r38_state == 8 ){
			sprintf(text_line8,"                 +  ");
		}else{
			sprintf(text_line8,"                    ");
		}
		LCD_DisplayStringLine(Line8,(uint8_t *)text_line8);
	}
	//Line8
	
	if (r37_state == 7){
		if (r38_state !=7 && r38_state !=7){
			sprintf(text_line9,"     *               ");
		}else if (r38_state == 7 ){
			sprintf(text_line9,"     *        +      ");
		}
		LCD_DisplayStringLine(Line9,(uint8_t *)text_line9);
	}
	if (r37_state != 7){
		if (r38_state == 7 ){
			sprintf(text_line9,"              +      ");
		}else{
			sprintf(text_line9,"                     ");
		}
		LCD_DisplayStringLine(Line9,(uint8_t *)text_line9);
	}
	//Line9
	GPIOC->ODR = temp;
	if (b1_lock){
		led_show(1,1);
	}else{
		led_show(1,0);
	}
	if (b1_lock == 0 && (led8_state_r37 || led8_state_r38)){
		led_show(8,1);
	}else{
		led_show(8,0);
	}
}
