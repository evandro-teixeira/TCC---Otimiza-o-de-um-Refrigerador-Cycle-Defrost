/*
 * define.h
 */
/*
#ifndef DEFINE_H_
#define DEFINE_H_
#endif // DEFINE_H_ 
*/
/***************************************************************************************************
Definições dos Port do PWM 
****************************************************************************************************/
/*
#define PWM_1 PTCD_PTCD0
#define PWM_2 PTCD_PTCD1
#define PWM_3 PTCD_PTCD3
#define PWM_4 PTCD_PTCD4
*/
/***************************************************************************************************

****************************************************************************************************/
#define PARADO   			1      
#define READ_CH				2
#define TEMPERATURA         3
#define DECISION            4
#define MOTOR_CONTROL       5
#define DISPLAY             6

#define PARTIDA_MOTOR 		2
#define MOTOR_ON 			3
#define MOTOR_OFF 			4

#define ON     				1
#define OFF    				0

#define RED					1
#define BLUE				2
#define GREEN				3
#define Linha_1				1
#define Linha_2				2 
// Lista de erro
#define ERRO_DISPLAY        1
//DEFINIÇOES DO PORT RELÉ
/*
#define RELE 				PTED_PTED2
//Definições do Port's push buttom  
#define CH_1 				PTDD_PTDD6
#define CH_2 				PTDD_PTDD7
#define CH_3 				PTED_PTED0
#define CH_4 				PTED_PTED1
//Definições Do Port Back Light LCD
#define BACKLIGHT_BLUE 		PTFD_PTFD6
#define BACKLIGHT_GREEN 	PTFD_PTFD7
#define BACKLIGHT_RED  		PTGD_PTGD0
//definições dos Port do PWM
#define HIN_1 				PTDD_PTDD2
#define LIN_1 				PTDD_PTDD3
#define HIN_2 				PTDD_PTDD4
#define LIN_2 				PTDD_PTDD5
*/
#define CH_1 				PTCD_PTCD6
#define CH_2 				PTCD_PTCD5
#define CH_3 				PTCD_PTCD7
#define CH_4 				PTDD_PTDD2

//Botões de teste prototipo
#define SW_1                PTAD_PTAD6


#define BACKLIGHT_BLUE 		PTDD_PTDD6
#define BACKLIGHT_RED  		PTDD_PTDD7

#define HIN_1 				PTCD_PTCD1
#define LIN_1 				PTCD_PTCD0
#define HIN_2 				PTCD_PTCD4
#define LIN_2 				PTCD_PTCD3
/*
#define HIN_1 PTAD_PTAD1
#define LIN_1 PTAD_PTAD2
#define HIN_2 PTAD_PTAD3
#define LIN_2 PTAD_PTAD1
*/
#define RELE                PTBD_PTBD7

#define LED_1 				PTAD_PTAD4
#define LED_2 				PTAD_PTAD5


