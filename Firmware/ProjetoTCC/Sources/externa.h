/*
 * externa.h
 */
/*************************************************************************************
#ifndef EXTERNA_H_
#define EXTERNA_H_
#endif /* EXTERNA_H_ */
/*************************************************************************************/
#include "types.h"
//#include "externa.h"
 		  
extern uint8 	 	motor_on;	
extern uint8 	 	motor_off;	
extern uint8 	 	controle_estado;
extern uint16  	 	t_OFF;		 // variavel que controla o tempo off do PWM
extern uint16  	 	t_ON;		 // variavel que controla o tempo on do PWM
//extern uint16  	t_vcc;      // variavel que controla qtd de pulso para determinar tensão RMS 
extern uint32 		number;
extern uint8	 	channel;
extern uint16 	 	read_adc;
extern uint16 		resultado;
extern int       	tensao_adc;
extern float 	 	valor_freq;
extern float 	 	periodo;
extern char 		LCD_LINHA_1[17];//		= 	"                ";
extern char 		LCD_LINHA_2[17];// 		= 	"                ";
extern uint8		erro;
extern uint16		timer;
extern uint16  	    temp_mV;
extern float 		temp;
extern uint16 		posicao_termo; 	
extern uint8 		estado_LCD; 
extern uint8  		backlight;
extern int16        temperature;  
extern int 			converte_mili_volt(int dado);

extern bool  		Flag_ch1;		// Indica o estado da chave 1 - SETUP
extern bool  		Flag_ch2;		// Indica o estado da chave 2 - INCREMENTO +
extern bool  		Flag_ch3;		// Indica o estado da chave 3 - INCREMENTO -
extern bool  		Flag_ch4;		// Indica o estado da chave 4 - ENTER
extern bool 		Flag_Overflow_TPM2;
extern bool 		Flag_Overflow_TPM1;
extern bool 		Flag_Start_TPM1;
extern bool         Flag_Overflow_CH; 
extern bool         Flag_Start_Contador_CH;
extern bool         Flag_Start_Contador_LCD;
extern bool         Flag_Overflow_LCD;
extern bool   		Flag_Start_PWM;
extern bool         Flag_Motor_ON; 
extern bool         Flag_Overflow_Motor;      
extern bool         Flag_Start_Contador_Motor;
extern bool    		Flag_Start_Repouso   ;  
extern bool    		Flag_Overflow_Repouso;
//extern int channel_ADC(uint8 adc);
//extern int temperatura(uint16 t);

