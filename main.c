/*
 * SOS.c
 *
 * Created: 3/11/2020 9:52:12 AM
 * Author : MENA
 */ 




#include "SOS.h"
#include "avr/interrupt.h"
#include "Timer.h"
#include "LCD.h"
#include "softwareDelay.h"
#include "pushButton.h"
extern uint8_t init_done ;
/**=========================================================================*
 *								Defines & Globals							*
 *==========================================================================*/
/*

// #define TRANSMIT_MAX 255
// #define RECEIVE_MAX  255
// #define ENTER_KEY	 0x0D
// 
// BCM_cfg_s BCM1;
// UART_cfg UART1;
// 
// uint8_t rxBuffer[RECEIVE_MAX];
// uint8_t txBuffer[TRANSMIT_MAX];
// 
// volatile uint8_t a_index        = ZERO;
// volatile uint8_t msg_len        = ZERO;
// volatile uint8_t g_TxBuffer_Len = ZERO;
// volatile uint8_t g_UART_TXindex = ZERO;
// volatile uint8_t BCM_sending    = FALSE;
*/


/**=========================================================================*
 *							TMU TASKS				                    	*
 *==========================================================================*/

uint8_t counter = 0 ;


 void buttonstate(void){
	 En_buttonStatus_t state = FALSE ;
	
	 pushButtonGetStatus( BTN_0 , &state );
	  if(state == TRUE){
		  DDRD = 0x0F ;
		  PORTD ^= 0x0F ;
	  }
	//  pushButtonGetStatus(BTN_1 , &state );

	 
 }
 
  void buttonstate2(void){
	  En_buttonStatus_t state = FALSE ;
	  pushButtonGetStatus(BTN_1 , &state );
	  if(state == TRUE){
		  DDRD = 0x0F ;
		  PORTD ^= 0x0F ;
	  }
	   

	  
  }
 
 void buttomInit(void){
	  pushButtonInit(BTN_0);
	//  pushButtonInit(BTN_1);


 }
 
  void buttomInit2(void){
	 // pushButtonInit(BTN_0);
	  pushButtonInit(BTN_1);

  }
  
 
void lcdInit(void){
	
	LCD_init();
	
}

void sendstring(void){
	if (init_done==TRUE)
	{
		/* to excute the display string once*/
	//	if ( counter == ZERO_VALUE )
	//	{
			LCD_displayString("13222");
			//counter++;
		//}
	}
}

/*

/ **=========================================================================*
 *							BCM Notification Functions						*
 *==========================================================================* /

/ * TX Completion Notification Routine * /
void txnotify(enum_BcmStatus st)
{
	BCM_sending = FALSE ;
	g_UART_TXindex = ZERO;
	BCM_DeInit(&BCM1);
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
}
	
/ * RX Completion Notification Routine * /
void rxnotify(enum_BcmStatus st)
{	
	BCM_Get_msgLEN(& msg_len );
	UART_Write(rxBuffer[a_index++]);
}

/ **=========================================================================*
 *							UART TX / RX ISR Handlers						*
 *==========================================================================* /

/ * UART Reception Completion ISR Handler* /
void UART_ISR_RXcbf(void)
{
	if (BCM_sending==FALSE)
	{
		if(g_UART_TXindex < TRANSMIT_MAX)
		{
			txBuffer[g_UART_TXindex++] = UART_Read();
			if(txBuffer[g_UART_TXindex-1] == ENTER_KEY)
			{
				BCM_Send(txBuffer, g_UART_TXindex, &BCM1, txnotify);
				g_UART_TXindex = ZERO;
			}
		}
		else
		{
			BCM_Send(txBuffer, g_UART_TXindex, &BCM1, txnotify);
			BCM_sending = TRUE;
			g_UART_TXindex = ZERO;	
		}
	}
	
}

/ * UART Transmission Completion ISR Handler * /
void UART_ISR_TXcbf(void)
{
	if(a_index < msg_len)
	{	
		UART_Write(rxBuffer[a_index++]);	
	}
	else if(a_index == msg_len)
	{
		UART_Write('\n');
		a_index++;
	}
	else
	{
		a_index = ZERO;
	}
}

/ **=========================================================================*
 *					BCM Applications For ECU1 & ECU2						*
 *==========================================================================* /

void ECU1_Application(void)
{
	/ *-------------[ BCM Initialization ]-------------* /
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
	
	/ *-------------[ UART Initialization ]-------------* /
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_RX;
	UART1.uartInterrupts = OnRx;
	UART_SetRX(UART_ISR_RXcbf);
	UART_Init(&UART1);
	
	/ *-------------[ SUPER LOOP ]-------------* /
	while (1)
	{
		BCM_Tx_Dispatcher();
	}
}

void ECU2_Application(void)
{
	/ *-------------[ BCM Initialization ]-------------* /
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Rx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
	BCM_Setup_RxBuffer(&BCM1, RECEIVE_MAX, rxBuffer, rxnotify);
	
	/ *-------------[ UART Initialization ]-------------* /
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_TX;
	UART1.uartInterrupts = OnTx;
	UART_SetTX(UART_ISR_TXcbf);
	UART_Init(&UART1);
	
	/ *-------------[ SUPER LOOP ]-------------* /
	while (1)
	{
		BCM_Rx_Dispatcher();
	}
}
*/

/**=========================================================================*
 *								Main Function								*
 *==========================================================================*/

int main(void)
{
	//ECU2_Application();
	//ECU1_Application();
	
/**=========================================================================*
 *								SOS TEST CODE								*
 *==========================================================================*/
	
	
	sei();
	
	SOS_Cfg_s SOS_cfg1 ;
	SOS_cfg1.Timer_channel = SOS_TIMER_CH2 ;
	SOS_cfg1.SOS_Reselution = reselution_one_mili ;
	
	SOS_Init(&SOS_cfg1);
	
	/*SOS_tsak_s SOS_task1 ;
	SOS_task1.delay_time = 1 ;
	SOS_task1.Priority = 9 ;
	SOS_task1.Ptr_FunctionCall = toggle1;
	SOS_task1.Task_ID = 1 ;
	SOS_task1.SOS_mode = PERIODIC ;
	

	SOS_Create_Task(&SOS_task1) ;
	
	SOS_tsak_s SOS_task2 ;
	SOS_task2.delay_time = 1 ;
	SOS_task2.Priority = 2 ;

	SOS_task2.Ptr_FunctionCall = toggle3;
	SOS_task2.Task_ID = 2;
	SOS_task2.SOS_mode = PERIODIC ;
	
	SOS_Create_Task(&SOS_task2) ;
	*/
	

	
	SOS_tsak_s SOS_init ;
	SOS_init.delay_time = 3 ;
	SOS_init.Priority = 1 ;
	
	SOS_init.Ptr_FunctionCall = lcdInit;
	SOS_init.Task_ID = 5 ;
	SOS_init.SOS_mode = PERIODIC ;
	
	SOS_Create_Task(&SOS_init) ;
	
	
	SOS_tsak_s SOS_lcd_send ;
	SOS_lcd_send.delay_time = 3 ;
	SOS_lcd_send.Priority = 2 ;
	
	SOS_lcd_send.Ptr_FunctionCall = sendstring;
	SOS_lcd_send.Task_ID = 4 ;
	SOS_lcd_send.SOS_mode = PERIODIC ;
	
	SOS_Create_Task(&SOS_lcd_send) ;
	
	
	SOS_tsak_s SOS_Button_init ;
	SOS_Button_init.delay_time = 1 ;
	SOS_Button_init.Priority = 1 ;
	
	SOS_Button_init.Ptr_FunctionCall = buttomInit;
	SOS_Button_init.Task_ID = 5 ;
	SOS_Button_init.SOS_mode = ONESHOT ;
	
	SOS_Create_Task(&SOS_Button_init) ;
	
	
	SOS_tsak_s SOS_Button_get_state ;
	SOS_Button_get_state.delay_time = 1 ;
	SOS_Button_get_state.Priority = 3 ;
	
	SOS_Button_get_state.Ptr_FunctionCall = buttonstate;
	SOS_Button_get_state.Task_ID = 4 ;
	SOS_Button_get_state.SOS_mode = PERIODIC ;
	
	SOS_Create_Task(&SOS_Button_get_state) ;
	
	
		
		SOS_tsak_s SOS_Button_init2 ;
		SOS_Button_init2.delay_time = 1 ;
		SOS_Button_init2.Priority = 1 ;
		
		SOS_Button_init2.Ptr_FunctionCall = buttomInit2;
		SOS_Button_init2.Task_ID = 5 ;
		SOS_Button_init2.SOS_mode = ONESHOT ;
		
		//SOS_Create_Task(&SOS_Button_init2) ;
		
		
		SOS_tsak_s SOS_Button_get_state2 ;
		SOS_Button_get_state2.delay_time = 1 ;
		SOS_Button_get_state2.Priority = 4 ;
		
		SOS_Button_get_state2.Ptr_FunctionCall = buttonstate2;
		SOS_Button_get_state2.Task_ID = 4 ;
		SOS_Button_get_state2.SOS_mode = PERIODIC ;
		
		//SOS_Create_Task(&SOS_Button_get_state2) ;
		
	
	
    while (1) 
    {
		SOS_Run();
    }
	
	
}
