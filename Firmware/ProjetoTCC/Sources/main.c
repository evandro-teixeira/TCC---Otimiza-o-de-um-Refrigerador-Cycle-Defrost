/*************************************************************************************************************
 *
 * Projeto: Trabalho de Conclusão de Curso - OTIMIZAÇÃO DE UM REFRIGERADOR CYCLO DEFROST
 * Autor: Evandro Teixeira, Gerson Stein, Guilherme Martino
 * 
 *************************************************************************************************************/
#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include <stdio.h>
#include <math.h>
#include "define.h"
#include "externa.h"
#include "aplicacao.h"
#include "Timer.h"
#include "LCD.h"
#include "types.h"
#include "Controle_LCD.h"
/****************************************************************************************************/
#ifdef __cplusplus
extern "C"
#endif
/****************************************************************************************************
Prototipo da Função
****************************************************************************************************/
void MCU_init(void); //Incializa MCU
/****************************************************************************************************
variavel global
****************************************************************************************************/
uint8 controle_inicial = 0;
/****************************************************************************************************
LOOP PRINCIPAL 
****************************************************************************************************/
void main(void) 
{
  //Incializa perifericos do MCU	
  MCU_init();	
  //Inicializa função do display de LCD 
  lcd_ini(display_8x5|_2_linhas,display_ligado|cursor_desligado|cursor_fixo);//Função Display LCD
  //Habilita tela inicia do Display
  Tela_inicial();
  //Desliga Rele 
  RELE = OFF;		    	
  //Inicia o motor no estado desligado
  Flag_Motor_ON = FALSE;
  //Inicia o Loop Inifito
  for(;;)
  { 
	//antes de iniciar o controle é feita medida temperatura
	if(controle_inicial < 6)
	{	
		// Set a saida do inversor de frequencia para zero volt
		HIN_1 = OFF;
		LIN_1 = ON;
		HIN_2 = OFF;
		LIN_2 = ON;
		// Realiza aquisição e calculo da tensão do ADC
		Tensao_RMS();
		// Realiza o calculo da temperatura
		temperatura(temp_mV);
		// SeT Flag para sair da rotina de repouso
		Flag_Overflow_Repouso = TRUE;
		// Incremente variavel de controle
		controle_inicial++;
	}
	else
	{
		//inicia rotina de controle do display 
		Atualiza_LCD();			   //Maq. de Estado Display LCD  
		//Inicia aplicação/controle 
		Application_Control();	    //Maq. de Estado Aplicação 
	}		
	//Tensao_RMS();
	//temperatura(temp_mV);
	//Controle_PWM(ON);		
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
    /* loop forever */
    /* please make sure that you never leave main */
  }
}
/****************************************************************************************************
****************************************************************************************************/
