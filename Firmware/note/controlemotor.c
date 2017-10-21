/*****************************************************************************************
 * Definições dos Port do PWM 
 * e definição do Port do Rele
 ******************************************************************************************/
#define HIN_1 				PTCD_PTCD1
#define LIN_1 				PTCD_PTCD0
#define HIN_2 				PTCD_PTCD4
#define LIN_2 				PTCD_PTCD3
#define RELE                PTBD_PTBD7
/*****************************************************************************************/




/*****************************************************************************************
 * Função de controla o PWM
 * possui uma maquina de estado gerenciar a geração do PWM
 ******************************************************************************************/
void Controle_PWM(uint8 estado, uint8 target_tensao,uint8 target_freq)
{
   /*
	* Montor Ligado
	*/
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
   /*
	* Motor Desligado
	*/
	//Coloca o Drive em alta impedancia
	else
	{
		HIN_1 = OFF;
		LIN_1 = OFF;
		HIN_2 = OFF;
		LIN_2 = OFF;
	}
}
/*****************************************************************************************/



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
/*****************************************************************************************/




/*****************************************************************************************
*     Interrupt handler : isrVtpm1ovf
*     Description : User interrupt service routine. 
*     Parameters  : None
*     Returns     : Nothing
 ******************************************************************************************/
__interrupt void isrVtpm1ovf(void)
{
  /* Write your interrupt code here ... */
	TPM1SC;
	TPM1SC_TOF = 0;
	//inicia a contagem
	if(Flag_Start_TPM1 == TRUE)
	{
		contador_TPM1++;
		if(contador_TPM1 >= timer)
		{
			contador_TPM1      = FALSE;
			Flag_Overflow_TPM1 = TRUE;
			Flag_Start_TPM1    = FALSE;
		}
	}
	
}
/*****************************************************************************************/



/*****************************************************************************************
*     Interrupt handler : isrVtpm2ovf
*     Description : User interrupt service routine. 
*     Parameters  : None
*     Returns     : Nothing
 ******************************************************************************************/
__interrupt void isrVtpm2ovf(void)
{
  /* Write your interrupt code here ... */
	TPM2SC;
	TPM2SC_TOF = 0;	
	//controle do inversor
	// É necessario que essa rotina execute no tempo da interrupção
	if(Flag_Start_PWM == TRUE)
	{
		Controle_PWM(ON,Tensao,Frequencia);
	}
	else 
	{
		Controle_PWM(OFF,OFF,OFF);
	}
}