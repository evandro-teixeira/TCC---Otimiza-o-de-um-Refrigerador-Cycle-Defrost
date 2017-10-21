/********************************************************************************************************
 * aplicacao.c
 * Aquivo que contem as rotina da aplicação do projeto
 ********************************************************************************************************/
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
/********************************************************************************************************************
Variaveis Globais
********************************************************************************************************************/
int16  		  		tensao_adc				=	0;
uint8               erro					=   0;
uint16				timer					=   0;
//int			  	Texto_LCD	      		= 	0;
//uint8 			motor_on		  		= 	0;	
//uint8 			motor_off		  		= 	0;	
uint8 				controle_estado 		= 	1;
//uint8 			fim_partida     		= 	0;
uint16              safe_time               =   0;      // tempo de segurança
uint16  			t_OFF				    = 	0; 		// variavel que controla o tempo off do PWM
uint16  			t_ON				    = 	0; 		// variavel que controla o tempo on do PWM
//uint16  			t_vcc           		= 	10;		// variavel que controla qtd de pulso para determinar tensão RMS 
uint32 				number 	  				= 	0;
uint16  			temp_mV					=	0;
//float 			valor_freq			  	= 	1.0;
//float 			periodo					=	0;
//uint16			periodo_us				=   0;
char 				LCD_LINHA_1[17] 		= 	"                ";
char 				LCD_LINHA_2[17] 		= 	"                ";
uint8 				linha 					= 	0;
uint16 				tempo_linha 			= 	0;
//uint16 			led						= 	0;
//char 				teste 					= 	0;
//char 				teste1 					= 	0;
uint16 				x1						=	0,
					x2						=	0,
					x3						=	0,		
					x4						=	0,
					x5						=	0; 
float 				temp 					= 	0.0;
int16               temperature             =   0;
uint8           	calc_rms 				= 	1;
uint8               state_PWM               =   1;
uint8               frequencia              =   60;
uint8               p_tensao                =   100;               
int16				target_temperature      =   0;		//variavel que sera feita a comparação com a temperatura atual
uint16 				posicao_termo 			=   1;      //   ||    que indica a posição do termoestato
uint8 				estado_LCD  			=   1;      // controla maquina de estado do lcd
uint8  				backlight               =   1;      // controla a cor do backligth 
uint8               inc_freq                =   40;     // Varaiavel de incremento da partida do motor - frequencia
uint8               inc_tensao              =   50;     // Varaiavel de incremento da partida do motor -  tensão
uint8               target_freq             =   40;
uint8               target_tensao           =   50;
/********************************************************************************************************
 * variavel de teste para o desenvolvimento da função de debounce
 ********************************************************************************************************/
uint16 teste_ch  = 0;  // 
uint16 teste_ch2 = 0;
uint16 teste_ch3 = 0;
uint16 teste_ch4 = 0;
/******************************************************************************************************************
*Flag
*obs.: Sao sinais de que adota 2 estados -  um elva para nivel logico 1 
*						   				 -  outro vela para o nivel logico 0 
***************************************************************************************************/
bool  	Flag_ch1 				  = FALSE;		// Indica o estado da chave 1 - SETUP
bool  	Flag_ch2 				  = FALSE;		// Indica o estado da chave 2 - INCREMENTO +
bool  	Flag_ch3 			 	  = FALSE;		// Indica o estado da chave 3 - INCREMENTO -
bool  	Flag_ch4 				  = FALSE;		// Indica o estado da chave 4 - ENTER
bool	Flag_Overflow_TPM2		  = FALSE;		// Indica que ouve estorou na contagem da interrupção TPM2
bool	Flag_Overflow_TPM1	      = FALSE;		// Indica que ouve estorou na contagem da interrupção TPM1
bool    Flag_Start_TPM1           = FALSE;
bool    Flag_Start_Contador_CH    = FALSE;
bool    Flag_Overflow_CH          = FALSE;
bool    Flag_Start_Contador_LCD   = FALSE;
bool    Flag_Overflow_LCD         = FALSE;
bool    Flag_Start_PWM            = FALSE;
bool    Flag_Motor_ON             = FALSE;
bool    Flag_Start_Motor          = FALSE;
bool    Flag_Overflow_Motor       = FALSE;
bool    Flag_Start_Contador_Motor = FALSE;
bool    Flag_Start_Repouso        = FALSE;      // Set Flag do contador do tempo de repouso - toda vez que  
bool    Flag_Overflow_Repouso     = FALSE;      // o motor for desligado é necessario esperar um determinado 
												// tempo para ser religado
/****************************************************************************************************
Função que de escolha do canal ADC
****************************************************************************************************/
int channel_ADC(uint8 adc)
{
	ADCSC1A_ADCHA = adc;
	channel = adc;
	return 1;
}
/****************************************************************************************************
Função que converte unidade do ADC para milivolts
****************************************************************************************************/
int converte_mili_volt(int dado)
{
	return (uint16) (((float)dado/4095)*3300) ;
}
/****************************************************************************************
 Função responsavel pela partida do motor 
***************************************************************************************/
void partida_motor(void)
{
	//rotina que controla a partida do motor
}
/****************************************************************************************
* Funsão Converte Tensão em Temperatura 
*****************************************************************************************/
void temperatura(uint16 t)
{
   //return (uint16)((float)(0.0307*t)-50);
   temp = (float)((0.0307*t)-45);
  /* if(t<=2100)
      temp = (float)((0.0332*t)-50.343);
   else if((t>2100) || (t<=2290))
      temp = (float)((0.0281*t)-10.20);
   else if(t > 2290)
      temp = (float)((0.0644*t)-160.2);   */
   temperature = (int16)temp;
}
/****************************************************************************************
* Calcula a tensão RMS do ADC
*****************************************************************************************/
void Tensao_RMS(void)
{   
	switch(calc_rms)
	{
		case 1:
		//realiza a primeira amostra de tensão
		channel_ADC(0x06);
		x1 			=(uint16)converte_mili_volt(read_adc);		
		calc_rms 	= 2;
		break;
		
		case 2:
		//Realiza a segunda amostra de tensão
		//delay_us(100);
		channel_ADC(0x06);
		x2 			= (uint16)converte_mili_volt(read_adc);
		calc_rms 	= 3;
		break;
		
		case 3:		
		//realiza a terceira amostra de tensão
		//delay_us(100);
		channel_ADC(0x06);
		x3 			= (uint16)converte_mili_volt(read_adc);
		calc_rms 	= 4;
		break;
		
		case 4:
		//realiza a quarta amostra de tensão
		//delay_us(100);
		channel_ADC(0x06);
		x4 			= (uint16)converte_mili_volt(read_adc);
		calc_rms 	= 5;
		break;
	
		case 5:
		//Realiza a quinta amostra de tensão
		//delay_us(100);
		channel_ADC(0x06);
		x5 			= (uint16)converte_mili_volt(read_adc);
		calc_rms 	= 6;
		break;
		
		case 6:
		//Calcula a tensão RMS
		temp_mV 	= (uint16)((x1+x2+x3+x4+x5)/5);
		temp_mV 	= (uint16)sqrt((temp_mV*temp_mV));
		calc_rms 	= 1;
		break;	
	}
}
/****************************************************************************************
Read Key
* obs:
* Se chave for precionada inicia contador que se encontra na interrupção TPM2
* se ao final da contagem o mesmo continua 
* a FLAG sera bacionada
*****************************************************************************************/
void read_ch(void)
{
	//testa chave 1
	//if(CH_1 == 0)
	if(CH_1 == 0)
	{ 
        LED_1 = ON;
        Flag_Start_Contador_CH = TRUE;        
		if((Flag_Overflow_CH == TRUE) && (CH_1 == 0))
		{	
			Flag_ch1 			= TRUE;
			Flag_Overflow_CH    = FALSE;
			LED_1 = OFF;
			teste_ch++;
		}		
	}
	//testa chave 2
	else if(CH_2 == 0)
	{
		Flag_Start_Contador_CH = TRUE;
		if((Flag_Overflow_CH == TRUE) && (CH_2 == 0))
		{	
			Flag_ch2 			= TRUE;
			Flag_Overflow_CH    = FALSE;
			teste_ch2++;
		}	
	}
	//testa chave 3
	else if(CH_3 == 0)
	{
		Flag_Start_Contador_CH = TRUE;
		if((Flag_Overflow_CH == TRUE) && (CH_3 == 0))
		{	
			Flag_ch3 			= TRUE;
			Flag_Overflow_CH    = FALSE;
			teste_ch3++;
		}	
	}
	//Testa chave 4
	else if(CH_4 == 0)
	{	
		Flag_Start_Contador_CH = TRUE;
		if((Flag_Overflow_CH == TRUE) &&(CH_4 == 0))
		{	
			Flag_ch4 			= TRUE;
			Flag_Overflow_CH    = FALSE;
			teste_ch4++;
		}	
	}
}
/*****************************************************************************************
 * Rotina de geração de PWM em hardware
 * rotina não adotada no projeto
*****************************************************************************************/
void PWM(uint8 canal)
{
	if(canal == 1)
	{
		//pwm1 PTD2
		/* ### Init_TPM init code */
		(void)(TPM1C0SC == 0U);              /* Channel 0 int. flag clearing (first part) */
		/* TPM1C0SC: CH0F=0,CH0IE=1,MS0B=1,MS0A=0,ELS0B=0,ELS0A=1 */
		TPM1C0SC = 0x64U;                    /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
		TPM1C0V = 0x1771U;                   /* Compare 0 value setting */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
		TPM1SC = 0x00U;                      /* Stop and reset counter */
		TPM1MOD = 0x2EE0U;                   /* Period value setting */
		(void)(TPM1SC == 0U);                /* Overflow int. flag clearing (first part) */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=1 */
		TPM1SC = 0x09U;                      /* Int. flag clearing (2nd part) and timer control register setting */
		/* ### */
	}
	else if(canal == 2)
	{
		//PWM 2 PTD3
		/* ### Init_TPM init code */
		(void)(TPM1C1SC == 0U);              /* Channel 0 int. flag clearing (first part) */
		/* TPM1C1SC: CH1F=0,CH1IE=1,MS1B=1,MS1A=0,ELS1B=0,ELS1A=1 */
		TPM1C1SC = 0x64U;                    /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
		TPM1C1V = 0x1771U;                   /* Compare 0 value setting */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
		TPM1SC = 0x00U;                      /* Stop and reset counter */
		TPM1MOD = 0x2EE0U;                   /* Period value setting */
		(void)(TPM1SC == 0U);                /* Overflow int. flag clearing (first part) */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=1 */
		TPM1SC = 0x09U;                      /* Int. flag clearing (2nd part) and timer control register setting */
		/* ### */
	}
	else if(canal == 3)
	{
		//PWM 3 PTD4
		/* ### Init_TPM init code */
		(void)(TPM1C2SC == 0U);              /* Channel 0 int. flag clearing (first part) */
		/* TPM1C2SC: CH2F=0,CH2IE=1,MS2B=1,MS2A=0,ELS2B=0,ELS2A=1 */
		TPM1C2SC = 0x64U;                    /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
		TPM1C2V = 0x1771U;                   /* Compare 0 value setting */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
		TPM1SC = 0x00U;                      /* Stop and reset counter */
		TPM1MOD = 0x2EE0U;                   /* Period value setting */
		(void)(TPM1SC == 0U);                /* Overflow int. flag clearing (first part) */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=1 */
		TPM1SC = 0x09U;                      /* Int. flag clearing (2nd part) and timer control register setting */
		/* ### */
	}
	else if(canal == 4)
	{
		//PWM 4 PTD5
		/* ### Init_TPM init code */
		(void)(TPM1C3SC == 0U);              /* Channel 0 int. flag clearing (first part) */
		/* TPM1C3SC: CH3F=0,CH3IE=1,MS3B=1,MS3A=0,ELS3B=0,ELS3A=1 */
		TPM1C3SC = 0x64U;                    /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
		TPM1C3V = 0x1771U;                   /* Compare 0 value setting */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
		TPM1SC = 0x00U;                      /* Stop and reset counter */
		TPM1MOD = 0x2EE0U;                   /* Period value setting */
		(void)(TPM1SC == 0U);                /* Overflow int. flag clearing (first part) */
		/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=1 */
		TPM1SC = 0x09U;                      /* Int. flag clearing (2nd part) and timer control register setting */
		/* ### */
	}
	else 
	{
		//Desliga PWM
		//(void)(TPM1C3SC == 0U);      
		TPM1C3SC = 0;
		TPM1C3V = 0;
		//TPM1SC = 0x00U;
		TPM1MOD = 0x2EE0U;
		//(void)(TPM1SC == 0U);
		//TPM1SC = 0x09U; 
	}
}

/*****************************************************************************************
 * Função de controle do motor
 * recebe o valor da tensão porcentagem (0 a 100%)
 *   ||       ||  da frequencia (0 a 120Hz) 
 * retorna t_on e t_off safe_time
*****************************************************************************************/
void Tempo_PWM(uint8 tensao, uint8 freq)
{
	float constante  = 0.0;
	uint32 periodo    = 0;
	//uint16 periodo_us   = 0;
	//float constante2 = 0.0;
	//calcula pi(semi-ciclo da senoide)
	//periodo = (float)((1/valor_freq)/2);
	//periodo 		= (float)(((float)(1/freq))/2);
	//calculo do periodo T = 1/f
	//é utilizado 1000000 converter em micro segundos
	periodo = (uint32)(1000000/freq);  //1000000
	periodo = (uint32)(periodo/2);
	//Converte o valor para micro segundos
	//periodo_us 		= (uint32)(periodo * 1000000);
	//calculo da constante de multiplicação
	constante 		= (float)((float)tensao/100);
	//constante2 		= (float)(1 - constante);
	//Descconta 2 mile segundos para o tempo segurança 
	//esse tempo é importante, pois é para evitar de colocar os transistor 
	//de potencia em curto (25%)
	safe_time       = (uint16)(((float)periodo * 0.25)/2);		
	periodo 		= ((uint16)periodo - safe_time);
	//calculo do tempo ON
	t_ON			= (uint16)(periodo * constante);
	//calculo do tempo OFF
	t_OFF 			= (uint16)((periodo - t_ON)/2);	
	//é necessario dividir por dois a interrupção é de micro segundos
	safe_time       = (uint16)(safe_time/2);
	t_ON            = (uint16)(t_ON/2);
	t_OFF           = (uint16)(t_OFF/2);
}
/*****************************************************************************************
 * Função de controla o PWM
 * possui uma maquina de estado gerenciar a geração do PWM
 * 
 ******************************************************************************************/
void Controle_PWM(uint8 estado)
{
	//state_PWM = estado;
	if(estado == TRUE)
	{
		switch(state_PWM)
		{	
			case 1:
				//Tempo_PWM(Tensao,Frequencia);
				Tempo_PWM(target_tensao,target_freq);
				state_PWM = 2;
			break;	
			//Inicia a geração dos pulsos
			//estado "safe_time"
			case 2:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = safe_time;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Alta Impedandia
				//Drive 2 : Alta Impedancia
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE  = ON;
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 3;
				}
			break;
		
			case 3:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_OFF;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em GND
				//Drive 2 : Saida em GND 
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE  = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 4;
				}			
			break;
		
			case 4:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_ON;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em VCC
				//Drive 2 : Saida em GND
				safe_transition();//
				HIN_1 = ON;
				LIN_1 = OFF;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 5;
				}			
	    	break;
		
			case 5:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_OFF;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em GND
				//Drive 2 : Saida em GND 
				safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE  = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 6;
				}
			break;
		
			case 6:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = safe_time;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em Alta Impedancia
				//Drive 2 : Saida em Alta Impedancia
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 7;
				}
			break;
		
			 
			case 7:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = safe_time;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em Alta Impedancia
				//Drive 2 : Saida em Alta Impedancia
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 8;
				}
				break;
					
		
			case 8:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_OFF;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em GND
				//Drive 2 : Saida em GND   
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE  = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 9;
				}
			break;
		
			case 9:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_ON;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em GND
				//Drive 2 : Saida em VCC
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = ON;
				LIN_2 = OFF;
				//RELE  = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 10;
				}
			break;
			
			case 10:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = t_OFF;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em GND
				//Drive 2 : Saida em GND   
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE = ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 11;
				}
			break;
			
			case 11:
				//repassa valor da variavel safe_timer para iniciar a contagem
				timer = safe_time;
				//SET contador 
				Flag_Start_TPM1 = TRUE;
				//SET os BIT de controle do diver IR3101
				//Drive 1 : Saida em Alta Impedancia
				//Drive 2 : Saida em Alta Impedancia
				//safe_transition();
				HIN_1 = OFF;
				LIN_1 = ON;
				HIN_2 = OFF;
				LIN_2 = ON;
				//RELE =  ON;
				//Checa se ouve Overflow no contador
				if(Flag_Overflow_TPM1 == TRUE)
				{
					Flag_Overflow_TPM1 = FALSE;
					state_PWM = 1;
				}
			break;
		}
	}
	//Coloca o Drive em alta impedancia
	else
	{
		HIN_1 = OFF;
		LIN_1 = OFF;
		HIN_2 = OFF;
		LIN_2 = OFF;
	}
}
/*****************************************************************************************
* Função para teste
******************************************************************************************/
void Led(void)
{ 
	LED_1 = ON;
	LED_2 = OFF;
	delay_us(1000000);
	LED_1 = OFF;
	LED_2 = ON;
	delay_us(1000000);
}
/*****************************************************************************************
*
******************************************************************************************/
void safe_transition(void)
{
	uint32 i = 0;
	HIN_1 = OFF;
	LIN_1 = OFF;
	HIN_2 = OFF;
	LIN_2 = OFF;
	//delay_us(50);
	//RELE = OFF;
	//delay_us(5000);
	//Força um atraso para alteração do bit de controle do drive de potencia
	for(i=0;i<8;i++);
}
/*****************************************************************************************
* Função para teste
******************************************************************************************/
/*void key_processes(void)
{
	if(Flag_ch1 == TRUE)
	{
		Flag_ch1 = FALSE;
	}
	if(Flag_ch2 == TRUE)
	{
		Flag_ch2 = FALSE;
	}
	if(Flag_ch3 == TRUE)
	{
		Flag_ch3 = FALSE;
	}
	if(Flag_ch4 == TRUE)
	{
		Flag_ch4 = FALSE;
	}
}*/
/*****************************************************************************************
* Essa função checa todos os parametros da aplicação e tomas as devidas decições 
******************************************************************************************/
void Application_Control(void)
{
	switch(controle_estado)
	{
		case PARADO:
			Tensao_RMS();
			controle_estado = TEMPERATURA;	
		break;
		
		case TEMPERATURA:
			temperatura(temp_mV);
			controle_estado = READ_CH;			
		break;
	
		case READ_CH:
			//key_processes();
			//as ações a respeito das leituras da chave estão função Controle_LCD
			controle_estado = DECISION;
		break;
		
		case DECISION:
			//if(temp target_temperature)
			PID(posicao_termo,temp);
			controle_estado = MOTOR_CONTROL;
		break;	
		
		case MOTOR_CONTROL:
			// Para ser ligado o motor é necessario tres condições 
			if((Flag_Motor_ON == FALSE) && (Flag_Start_Motor == TRUE) )//&& (Flag_Overflow_Repouso == TRUE))
			{			
		    	// rotina de partida do motor
				motor_starting();
				RELE = ON;
				Flag_Overflow_Repouso = FALSE;
			}
			pass_parameters();
			//Controle_PWM(ON);
			Flag_Start_PWM = TRUE;     
			controle_estado = PARADO; 
		break;	
	}
}
/********************************************************************************************************
*Função que decide de acordo com a posição do termostato que o usuario
*definiu no setup do equipamento e a temperatura atual do equipamento
*dados de entrada:
*	position      - posição do termostao
*	temperature   - temperatura atual
*dados de saida:
*   frequencia    - frequencia na qual o inversor de gerar
*   p_tensão      - define a tensão que deve ser gerada pelo inversor	
********************************************************************************************************/
void PID(uint16 position, float temperature)
{
	uint16 temperatura = 0;
	//converte a temperatura para numero intero e adiciona um off set de 3
	temperatura = (uint16)(3+temperature); 	
	//Maq. de Estado controle PID
	switch(position)
	{
		case 1:
			// se temperatura for menor do que -3ºC
			// desliga conpresssor
			if(temperatura <= 0)
			{
				RELE               =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;
				//frequencia       =   140;
				//p_tensao         =   100;
			}
			else if(temperatura > 0 && temperatura <= 1)
			{
				frequencia         =   114;
				p_tensao           =   80;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 1 && temperatura <= 2)
			{
				frequencia         =   114;
				p_tensao           =   82;		
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 2 && temperatura <= 3)
			{
				frequencia         =   117;
				p_tensao           =   84;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 3 && temperatura <= 4)
			{
				frequencia         =   120;
				p_tensao           =   86;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 4 && temperatura <= 5)
			{
				frequencia         =   123;
				p_tensao           =   88;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 5 && temperatura <= 6)
			{
				frequencia         =   126;
				p_tensao           =   90;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 6 && temperatura <= 7)
			{
				frequencia         =   128;
				p_tensao           =   92;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 7 && temperatura <= 8)
			{
				frequencia         =   131;
				p_tensao           =   94;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 8 && temperatura <= 9)
			{
				frequencia         =   134;
				p_tensao           =   96;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 9 && temperatura <= 10)
			{
				frequencia         =   137;
				p_tensao           =   98;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 10)
			{
				frequencia         =   140;
				p_tensao           =   100;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
		break;
		
		case 2:
			// se temperatura for menor do que -3ºC
			// desliga conpresssor
			if(temperatura <= 0)
			{
				RELE = OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;
				//frequencia       =   140;
				//p_tensao         =   100;
			}
			else if(temperatura > 0 && temperatura <= 1)
			{
				frequencia         =   84;
				p_tensao           =   80;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 1 && temperatura <= 2)
			{
				frequencia         =   89;
				p_tensao           =   82;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 2 && temperatura <= 3)
			{
				frequencia         =   95;
				p_tensao           =   84;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 3 && temperatura <= 4)
			{
				frequencia         =   100;
				p_tensao           =   86;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 4 && temperatura <= 5)
			{
				frequencia         =   106;
				p_tensao           =   88;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 5 && temperatura <= 6)
			{
				frequencia         =   112;
				p_tensao           =   90;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 6 && temperatura <= 7)
			{
				frequencia         =   117;
				p_tensao           =   92;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 7 && temperatura <= 8)
			{
				frequencia         =   123;
				p_tensao           =   94;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 8 && temperatura <= 9)
			{
				frequencia         =   128;
				p_tensao           =   96;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 9 && temperatura <= 10)
			{
				frequencia         =   134;
				p_tensao           =   98;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 10)
			{
				frequencia         =   140;
				p_tensao           =   100;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
		break;
		
		case 3:
			// se temperatura for menor do que -3ºC
			// desliga conpresssor
			if(temperatura <= 0)
			{
				RELE               =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;
				//frequencia       =   140;
				//p_tensao         =   100;
			}
			else if(temperatura > 0 && temperatura <= 1)
			{
				frequencia         =   56;
				p_tensao           =   80;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 1 && temperatura <= 2)
			{
				frequencia         =   64;
				p_tensao           =   82;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 2 && temperatura <= 3)
			{
				frequencia         =   72;
				p_tensao           =   84;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 3 && temperatura <= 4)
			{
				frequencia        =   81;
				p_tensao          =   86;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 4 && temperatura <= 5)
			{
				frequencia        =   89;
				p_tensao          =   88;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 5 && temperatura <= 6)
			{
				frequencia        =   98;
				p_tensao          =   90;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 6 && temperatura <= 7)
			{
				frequencia        =   106;
				p_tensao          =   92;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 7 && temperatura <= 8)
			{
				frequencia        =   114;
				p_tensao          =   94;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 8 && temperatura <= 9)
			{
				frequencia        =   123;
				p_tensao          =   96;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 9 && temperatura <= 10)
			{
				frequencia        =   131;
				p_tensao          =   98;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 10)
			{
				frequencia        =   140;
				p_tensao          =   100;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
		break;
		
		case 4:
			// se temperatura for menor do que -3ºC
			// desliga conpresssor
			if(temperatura <= 0)
			{
				RELE              =   OFF;
				Flag_Motor_ON     =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor  =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;				
				//frequencia       =   140;
				//p_tensao         =   100;
			}
			else if(temperatura > 0 && temperatura <= 1)
			{
				RELE               = OFF;
				Flag_Motor_ON      = FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE; 
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso = TRUE;				
				//frequencia       =   114;
				//p_tensao         =   80;
			}
			else if(temperatura > 1 && temperatura <= 2)
			{
				frequencia         =   40;
				p_tensao           =   82;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 2 && temperatura <= 3)
			{
				frequencia         =   50;
				p_tensao           =   84;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 3 && temperatura <= 4)
			{
				frequencia         =   61;
				p_tensao           =   86;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 4 && temperatura <= 5)
			{
				frequencia         =   72;
				p_tensao           =   88;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 5 && temperatura <= 6)
			{
				frequencia         =   84;
				p_tensao           =   90;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 6 && temperatura <= 7)
			{
				frequencia         =   95;
				p_tensao           =   92;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 7 && temperatura <= 8)
			{
				frequencia         =   106;
				p_tensao           =   94;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 8 && temperatura <= 9)
			{
				frequencia         =   117;
				p_tensao           =   96;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 9 && temperatura <= 10)
			{
				frequencia         =   128;
				p_tensao           =   98;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;;
			}
			else if(temperatura > 10)
			{
				frequencia         =   140;
				p_tensao           =   100;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
		break;
		
		case 5:
			// se temperatura for menor do que -3ºC
			// desliga conpresssor
			if(temperatura <= 0)
			{
				RELE               =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;				
				//frequencia       =   140;
				//p_tensao         =   100;
			}
			else if(temperatura > 0 && temperatura <= 1)
			{
				RELE               =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;				
				//frequencia       =   114;
				//p_tensao         =   80;
			}
			else if(temperatura > 1 && temperatura <= 2)
			{
				RELE               =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;				
				//frequencia       =   114;
				//p_tensao         =   82;			
			}
			else if(temperatura > 2 && temperatura <= 3)
			{
				RELE 		       =   OFF;
				Flag_Motor_ON      =   FALSE;
				// RESET Flag para ligar o motor
				Flag_Start_Motor   =   FALSE;
				// SET a Flag para contar o tempo de repouso
				Flag_Start_Repouso =   TRUE;				
				//frequencia       =   117;
				//p_tensao         =   84;
			}
			else if(temperatura > 3 && temperatura <= 4)
			{
				frequencia         =   42;
				p_tensao           =   86;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 4 && temperatura <= 5)
			{
				frequencia         =   56;
				p_tensao           =   88;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 5 && temperatura <= 6)
			{
				frequencia         =   70;
				p_tensao           =   90;
				// SET Flag para ligar o motor
				Flag_Start_Motor   =   TRUE;
			}
			else if(temperatura > 6 && temperatura <= 7)
			{
				frequencia        =   84;
				p_tensao          =   92;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 7 && temperatura <= 8)
			{
				frequencia        =   98;
				p_tensao          =   94;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 8 && temperatura <= 9)
			{
				frequencia        =   112;
				p_tensao          =   96;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 9 && temperatura <= 10)
			{
				frequencia        =   126;
				p_tensao          =   98;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
			else if(temperatura > 10)
			{
				frequencia        =   140;
				p_tensao          =   100;
				// SET Flag para ligar o motor
				Flag_Start_Motor  =   TRUE;
			}
		break;
		/*
		case 6:
		break;
		
		case 7:
		break;
		
		case 8:
		break;
		
		case 9:
		break;
		
		case 10:
		break;
		*/
		
	}
}
/*****************************************************************************************
*
******************************************************************************************/
/*
void aplicacao(void)
{
	switch(controle_estado)
	{
		case PARADO:
			controle_estado = READ_CH;	
		break;
		
		case READ_CH:
			//key_processes();
			controle_estado = 3;
			
		break;
	
		case 3:
			
		break;
	}
}
*/
/****************************************************************************************
Read Key
*****************************************************************************************/
/*void read_ch(void)
{
	uint8 lag = 0;
	//testa chave 1
	if(SW_1 == 0)
	{
		lag = 1; 
		LED_1 = 1;
		//delay_us(100);
		//Tempo debulse
		if(lag == 1 && CH_1 == 0)
		{	
			Flag_ch1 = 1;
			lag = 0;
		}	
	}
	//testa chave 2
	else if(CH_2 == 0)
	{
		lag = 1; 
		//delay_us(100);
		//Tempo debulse
		if(lag == 1 && CH_2 == 0)
		{	
			Flag_ch2 = 1;
			lag = 0;
		}	
	}
	//testa chave 3
	else if(CH_3 == 0)
	{
		lag = 1; 
		//delay_us(100);
		//Tempo debulse		
		/*if(lag == 1 && CH_2 == 0)
		{	
			Flag_ch2 = 1;
			lag = 0;
		}	
	}
	//Testa chave 4
	else if(CH_4 == 0)
	{
		lag = 1; 
		//delay_us(100);
		//Tempo debulse		
		if(lag == 1 && CH_4 == 0)
		{	
			Flag_ch4 = 1;
			lag = 0;
		}
	}
}
*/
/********************************************************************************************************
 * Rotina que aciona o backlight do display de lcd de acordo com 
 * a configuração setada pelo usuario no setup do equipamento
 ********************************************************************************************************/
void BackLight(uint8 cor)
{
	if(cor == RED)
	{
		BACKLIGHT_RED  = ON;
		BACKLIGHT_BLUE = OFF;
	}
	else if(cor == BLUE)
	{
		BACKLIGHT_BLUE = ON;
		BACKLIGHT_RED  = OFF;
	}
	else if(cor == GREEN)
	{
		BACKLIGHT_BLUE = ON;
		BACKLIGHT_RED  = OFF;
	}
	else//cor padrão
	{
		BACKLIGHT_BLUE = ON;
		BACKLIGHT_RED  = OFF;		
	}
}
/*******************************************************************************************************
*Função de controle de partida do motor
* ********************************************************************************************************/
void motor_starting(void)
{
	Flag_Start_Contador_Motor = TRUE;
	if(Flag_Overflow_Motor == TRUE)
	{
		Flag_Overflow_Motor = FALSE;
		inc_freq++;
		inc_tensao++;
		if(inc_freq >= frequencia)
		{
			inc_freq = frequencia;		
		}
		if(inc_tensao >= p_tensao)
		{
			inc_tensao = p_tensao;
		}
		if((inc_freq >= frequencia) && (inc_tensao >= p_tensao))
		{
			Flag_Motor_ON = TRUE;
			//atribui os valores iniciais
			inc_freq      = 40;
			inc_tensao    = 50; 
		}
	}
}
/*******************************************************************************************************
 * Função que repassa os valores alvo da tensão e frequencia
 ********************************************************************************************************/
void pass_parameters(void)
{
	// 
	if(Flag_Motor_ON == TRUE)
	{
		target_freq   = frequencia;
		target_tensao = p_tensao;
	}
	else
	{
		target_freq   = inc_freq;
		target_tensao = inc_tensao;	
	}
}
/*******************************************************************************************************
 * the end 
 ********************************************************************************************************/
