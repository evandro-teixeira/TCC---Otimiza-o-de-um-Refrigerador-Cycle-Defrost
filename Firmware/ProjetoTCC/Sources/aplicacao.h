/*
 * aplicacao.h
 */
/*************************************************************************************
#ifndef APLICACAO_H_
#define APLICACAO_H_
#endif /* APLICACAO_H_ */
/**************************************************************************************/
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */

/***************************************************************************************************
Prototipo das Funções
****************************************************************************************************/
int  		channel_ADC(uint8 adc);
int  		converte_mili_volt(int dado);
void  		temperatura(uint16 t);
void 		Tensao_RMS(void);
void 		partida_motor(void);
void 		Tempo_PWM(uint8 tensao, uint8 freq);
void 		MCU_init(void);
void        read_ch(void);
void        PWM(uint8 canal);
void 		Controle_PWM(uint8 estado);
void        Led(void);
void        safe_transition(void);
void        key_processes(void);
void 		Application_Control(void);
void        PID(uint16 position, float temperature);
void 		aplicacao(void);
void        BackLight(uint8 cor); 
void        motor_starting(void);
void        pass_parameters(void);
