/*
 * BCM.c
 *
 * Created: 8/24/2021
 *  Author: Ahmed Essam & Rehab
 */
/*-INCLUDES-------------------------------*/
#include"BCM.h"
/*-MACROS-------------------------------*/
#define CMD_INDEX       (uint8_t)0
#define SIZE_INDEX      (uint8_t)1
#define DATA_INDEX      (uint8_t)2
#define CS_INDEX        (uint8_t)3

#define PACKET_SIZE     (uint8_t)4

#define CMD_SIZE      	(uint8_t)1
#define FRAME_SIZE      (uint8_t)2
#define CS_SIZE      	(uint8_t)1



/*-LOCAL FUNCTIONS PROTOTYPES----------------------------*/
static ERROR_STATE_t BCM_Init(void);
static ERROR_STATE_t BCM_InitPacket(uint8_t COMM_ID,uint8_t COMM_Mode);
static void BCM_UART_TXCBF(void);
static void BCM_SPI_TXCBF(void);
static void BCM_I2C_TXCBF(void);

static void BCM_UART_RXCBF(uint8_t Data);
static void BCM_SPI_RXCBF(uint8_t Data);
static void BCM_I2C_RXCBF(uint8_t Data);
/*- GLOBAL EXTERN VARIABLES-------------------------------*/
extern uint8_t au8_BCM_UsedCH[COMM_NUMBERS];
/*- GLOBAL STATIC VARIABLES-------------------------------*/
static uint16_t gu16_CSCounter=ZERO;
static uint8_t gau8_CSTemp[COMM_NUMBERS]={ZERO};
static ERROR_STATE_t IsInit=NOT_INIT;//This var stores INIT if the BCM_Init is return ERROR_OK
static ptr_uint8_t aptr_Packet[COMM_NUMBERS][PACKET_SIZE];//This arr stores the arrs of the packets
static uint8_t au8_InitPacketFlag[COMM_NUMBERS]={NOT_INIT,NOT_INIT,NOT_INIT};
static uint16_t au16_Packet_sizes[COMM_NUMBERS][PACKET_SIZE]=
																{
																	{CMD_SIZE,FRAME_SIZE,ZERO,CS_SIZE},
																	{CMD_SIZE,FRAME_SIZE,ZERO,CS_SIZE},
																	{CMD_SIZE,FRAME_SIZE,ZERO,CS_SIZE}
																};//This arr stores the size of every element of the packet
static ptr_STR_BCMTask_t aptr_Task[COMM_NUMBERS]={NULL_PTR,NULL_PTR,NULL_PTR};//This arr stores pointers to tasks structure
/*- LOCAL FUNCTIONS IMPLEMENTATION------------------------*/
static void BCM_UART_TXCBF(void)
{
    aptr_Task[COMM_UART_CH]->u8_BCMState=BCM_TXSTATE_SENDING;
    //BCM_SetState(COMM_UART_CH,BCM_TXSTATE_SENDING);
}

static void BCM_SPI_TXCBF(void)
{
    aptr_Task[COMM_SPI_CH]->u8_BCMState=BCM_TXSTATE_SENDING;
    //BCM_SetState(COMM_SPI_CH,BCM_TXSTATE_SENDING);
}

static void BCM_I2C_TXCBF(void)
{
    aptr_Task[COMM_I2C_CH]->u8_BCMState=BCM_TXSTATE_SENDING;
    //BCM_SetState(COMM_I2C_CH,BCM_TXSTATE_SENDING);
}

static void BCM_UART_RXCBF(uint8_t Data)
{
    uint8_t u8_FrameCounter;
    switch (aptr_Task[COMM_UART_CH]->u8_BCMState)
    {
        case BCM_RXSTATE_RECEIVING:
            (aptr_Packet[COMM_UART_CH][aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter])[aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter]=Data;

            (aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter)++;
				
			if(DATA_INDEX==u8_FrameCounter)
			{
				gau8_CSTemp[COMM_UART_CH]+=Data;
			}
			else
			{
				/*Do Nothing*/
			}
            if((au16_Packet_sizes[COMM_UART_CH][aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_UART_CH]->u8_BCMState=BCM_RXSTATE_CS;
                }
                else if(DATA_INDEX==u8_FrameCounter)
                {
                    if( (au16_Packet_sizes[COMM_UART_CH][DATA_INDEX]) > (aptr_Task[COMM_UART_CH]->u16_BCMSize) )
                    {
                        aptr_Task[COMM_UART_CH]->u8_BCMState=BCM_RXSTATE_ERROR;

                    }
                    else
                    {
                        aptr_Task[COMM_UART_CH]->u16_BCMSize=au16_Packet_sizes[COMM_UART_CH][DATA_INDEX];
                    }
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        case BCM_RXSTATE_ERROR:

            (aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter)++;

            if((au16_Packet_sizes[COMM_UART_CH][aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_UART_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_UART_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_UART_CH]->u8_BCMMode=BCM_MODE_IDEAL;
                    au8_InitPacketFlag[COMM_UART_CH]=NOT_INIT;
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        default:
            break;
    }
}

static void BCM_SPI_RXCBF(uint8_t Data)
{
    uint8_t u8_FrameCounter;
    switch (aptr_Task[COMM_SPI_CH]->u8_BCMState)
    {
        case BCM_RXSTATE_RECEIVING:
            (aptr_Packet[COMM_SPI_CH][aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter])[aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter]=Data;

            (aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter)++;
			
			if(DATA_INDEX==u8_FrameCounter)
			{
				gau8_CSTemp[COMM_SPI_CH]+=Data;
			}
			else
			{
				/*Do Nothing*/
			}
            if((au16_Packet_sizes[COMM_SPI_CH][aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_SPI_CH]->u8_BCMState=BCM_RXSTATE_CS;
                }
                else if(DATA_INDEX==u8_FrameCounter)
                {
                    if(au16_Packet_sizes[COMM_SPI_CH][DATA_INDEX]>aptr_Task[COMM_SPI_CH]->u16_BCMSize)
                    {
                        aptr_Task[COMM_SPI_CH]->u8_BCMState=BCM_RXSTATE_ERROR;

                    }
                    else
                    {
                        aptr_Task[COMM_SPI_CH]->u16_BCMSize=au16_Packet_sizes[COMM_SPI_CH][DATA_INDEX];
                    }
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        case BCM_RXSTATE_ERROR:

            (aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter)++;

            if((au16_Packet_sizes[COMM_SPI_CH][aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_SPI_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_SPI_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_SPI_CH]->u8_BCMMode=BCM_MODE_IDEAL;
                    au8_InitPacketFlag[COMM_SPI_CH]=NOT_INIT;
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        default:
            break;
    }
}

static void BCM_I2C_RXCBF(uint8_t Data)
{
    uint8_t u8_FrameCounter;
    switch (aptr_Task[COMM_I2C_CH]->u8_BCMState)
    {
        case BCM_RXSTATE_RECEIVING:
            (aptr_Packet[COMM_I2C_CH][aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter])[aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter]=Data;

            (aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter)++;

			if(DATA_INDEX==u8_FrameCounter)
			{
				gau8_CSTemp[COMM_I2C_CH]+=Data;
			}
			else
			{
				/*Do Nothing*/
			}
            if((au16_Packet_sizes[COMM_I2C_CH][aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_I2C_CH]->u8_BCMState=BCM_RXSTATE_CS;
                }
                else if(DATA_INDEX==u8_FrameCounter)
                {
                    if(au16_Packet_sizes[COMM_I2C_CH][DATA_INDEX]>aptr_Task[COMM_I2C_CH]->u16_BCMSize)
                    {
                        aptr_Task[COMM_I2C_CH]->u8_BCMState=BCM_RXSTATE_ERROR;

                    }
                    else
                    {
                        aptr_Task[COMM_I2C_CH]->u16_BCMSize=au16_Packet_sizes[COMM_I2C_CH][DATA_INDEX];
                    }
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        case BCM_RXSTATE_ERROR:

            (aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter)++;

            if((au16_Packet_sizes[COMM_I2C_CH][aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter])==(aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter))
            {
                (aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter)++;
                (aptr_Task[COMM_I2C_CH]->u16_BCMByteCoounter)=ZERO;
                u8_FrameCounter=(aptr_Task[COMM_I2C_CH]->u8_BCMPacketCounter);
                if(PACKET_SIZE==u8_FrameCounter)
                {
                    aptr_Task[COMM_I2C_CH]->u8_BCMMode=BCM_MODE_IDEAL;
                    au8_InitPacketFlag[COMM_I2C_CH]=NOT_INIT;
                }
                else
                {
                    //DO NOTHING
                }
            }
            else
            {
                //DO NOTHING
            }
            break;
        default:
            break;
    }
}

static ERROR_STATE_t BCM_Init(void)
{
    ERROR_STATE_t u8_ErrorState = ERROR_OK;
    /*Check if the BCM had been init before*/
    if(NOT_INIT==IsInit)
    {
        uint8_t InitCounter;
        /*This for loop to init all the used comm channel */
        for(InitCounter=ZERO;InitCounter<COMM_NUMBERS;InitCounter++)
        {
            /*Check if the the channel is enabled*/
            if(ENABLE==au8_BCM_UsedCH[InitCounter])
            {
                /*Init the comm channel */
                while(ERROR_OK!=COMMProxy_Init(InitCounter));
                if(NULL_PTR==aptr_Task[InitCounter])
                {
                    /*Assign the address of the task structure to the pointer*/
                    /*IF YES MAKE IT POINT TO THE TASK*/
                    BCM_Get(InitCounter,&aptr_Task[InitCounter]);
                }
            }
            else
            {
                //DO NOTHING
            }
        }
        /*set call back functions*/
        COMMProxy_SetTxCallback(COMM_UART_CH,BCM_UART_TXCBF);
        COMMProxy_SetTxCallback(COMM_SPI_CH,BCM_SPI_TXCBF);
		COMMProxy_SetTxCallback(COMM_I2C_CH,BCM_I2C_TXCBF);

        COMMProxy_SetRxCallback(COMM_UART_CH,BCM_UART_RXCBF);
        COMMProxy_SetRxCallback(COMM_SPI_CH,BCM_SPI_RXCBF);
		COMMProxy_SetRxCallback(COMM_I2C_CH,BCM_I2C_RXCBF);
        /*set the init flag*/
        IsInit=INIT;
    }
    else
    {
        u8_ErrorState=ERROR_NOK;
    }
    /*Return state */
    return u8_ErrorState;
}
static ERROR_STATE_t BCM_InitPacket(uint8_t COMM_ID,uint8_t COMM_Mode)
{
    ERROR_STATE_t u8_ErrorState = ERROR_OK;
    if(COMM_ID>=COMM_NUMBERS)
    {
        u8_ErrorState = ERROR_NOK;
    }
    else
    {
        switch(COMM_Mode)
        {
            case BCM_MODE_TX:
                aptr_Packet[COMM_ID][SIZE_INDEX]=(ptr_uint8_t)&(aptr_Task[COMM_ID]->u16_BCMSize);
                au16_Packet_sizes[COMM_ID][DATA_INDEX]=aptr_Task[COMM_ID]->u16_BCMSize;
                break;
            case BCM_MODE_RX:
                aptr_Packet[COMM_ID][SIZE_INDEX]=(ptr_uint8_t)&(au16_Packet_sizes[COMM_ID][DATA_INDEX]);
				gau8_CSTemp[COMM_ID]=ZERO;
                break;
            default:
                break;

        }
        aptr_Packet[COMM_ID][CMD_INDEX]=&aptr_Task[COMM_ID]->u8_BCMID;
        aptr_Packet[COMM_ID][DATA_INDEX]=aptr_Task[COMM_ID]->ptr_BCMBuffer;
        aptr_Packet[COMM_ID][CS_INDEX]=&(aptr_Task[COMM_ID]->u8_BCMCS);

    }
    return u8_ErrorState;
}
/*- APIs IMPLEMENTATION-----------------------------------*/
extern void BCM_TxMainFunction(void)
{
    uint8_t u8_ChCounter=ZERO;
    if(NOT_INIT==IsInit)
    {
       BCM_Init();
    }
    else
    {
        //DO NOTHING
    }
    if(INIT==IsInit)
    {
        for(u8_ChCounter=ZERO;u8_ChCounter<COMM_NUMBERS;u8_ChCounter++)
        {
            if(DISABLE==au8_BCM_UsedCH[u8_ChCounter])
            {
                continue;
            }
            else
            {
                if(BCM_MODE_TX==aptr_Task[u8_ChCounter]->u8_BCMMode)
                {
                    /*CHECK IF THE POINTER TO TASK IS NULL*/
                    if(NOT_INIT==au8_InitPacketFlag[u8_ChCounter])
                    {
                        /*IF YES MAKE IT POINT TO THE TASK*/
                        au8_InitPacketFlag[u8_ChCounter]=INIT;
                        BCM_InitPacket(u8_ChCounter,BCM_MODE_TX);

                    }
                    else
                    {
                        //DO NOTHING
                    }
                    switch (aptr_Task[u8_ChCounter]->u8_BCMState)
                    {
                        case BCM_TXSTATE_SENDING:
                            //SEND PACKET(COMMAND,SIZE,DATA,SC)
                            aptr_Task[u8_ChCounter]->u8_BCMState=BCM_TXSTATE_PENDING;
							COMMProxy_Send(u8_ChCounter,(aptr_Packet[u8_ChCounter][aptr_Task[u8_ChCounter]->u8_BCMPacketCounter])[aptr_Task[u8_ChCounter]->u16_BCMByteCoounter]);
                            (aptr_Task[u8_ChCounter]->u16_BCMByteCoounter)++;
                            if((au16_Packet_sizes[u8_ChCounter][aptr_Task[u8_ChCounter]->u8_BCMPacketCounter])==(aptr_Task[u8_ChCounter]->u16_BCMByteCoounter))
                            {
                                (aptr_Task[u8_ChCounter]->u8_BCMPacketCounter)++;
                                (aptr_Task[u8_ChCounter]->u16_BCMByteCoounter)=ZERO;
                                if(PACKET_SIZE==(aptr_Task[u8_ChCounter]->u8_BCMPacketCounter))
                                {
                                    aptr_Task[u8_ChCounter]->u8_BCMMode=BCM_MODE_IDEAL;
                                    (aptr_Task[u8_ChCounter]->ptr_BCMCallBackFu)();
                                    au8_InitPacketFlag[u8_ChCounter]=NOT_INIT;
                                }
                                else
                                {
                                    //DO NOTHING
                                }
                            }
                            else
                            {
                                //DO NOTHING
                            }

                            break;
                        case BCM_TXSTATE_PENDING:
                            //WAIT THE ISR TO CHANGE IT BACK TO SENDING
                            break;
                        default:
                            //ERROR
                            break;
                    }
                }
                else
                {
                    //DO NOTHING
                }
            }
        }
    }
}
extern void BCM_RxMainFunction(void)
{
    uint8_t u8_ChCounter=ZERO;
    if(NOT_INIT==IsInit)
    {
       BCM_Init();
    }
    else
    {
        //DO NOTHING
    }
    if(INIT==IsInit)
    {
        for(u8_ChCounter=ZERO;u8_ChCounter<COMM_NUMBERS;u8_ChCounter++)
        {
            if(DISABLE==au8_BCM_UsedCH[u8_ChCounter])
            {
                continue;
            }
            else
            {
                if(BCM_MODE_RX==aptr_Task[u8_ChCounter]->u8_BCMMode)
                {
                    /*CHECK IF THE POINTER TO TASK IS NULL*/
                    if(NOT_INIT==au8_InitPacketFlag[u8_ChCounter])
                    {
                        /*IF YES MAKE IT POINT TO THE TASK*/
                        au8_InitPacketFlag[u8_ChCounter]=INIT;
                        BCM_InitPacket(u8_ChCounter,BCM_MODE_RX);

                    }
                    else
                    {
                        //DO NOTHING
                    }
                    switch (aptr_Task[u8_ChCounter]->u8_BCMState)
                    {
                        case BCM_RXSTATE_RECEIVING:
                            /*Waiting*/
                            break;
                        case BCM_RXSTATE_CS:
                            /*Checking Sum*/
                            aptr_Task[u8_ChCounter]->u8_BCMMode=BCM_MODE_IDEAL;
                            au8_InitPacketFlag[u8_ChCounter]=NOT_INIT;
							
                            if((aptr_Task[u8_ChCounter]->u8_BCMCS)==gau8_CSTemp[u8_ChCounter])
                            {
                                (aptr_Task[u8_ChCounter]->ptr_BCMCallBackFu)();
                            }
                            else
                            {
                                /*Do Nothing*/
                            }
                            break;
                        case BCM_RXSTATE_ERROR:
                            /*Error*/
                            break;
                        default:
                            //ERROR
                            break;
                    }
                }
                else
                {
                    //DO NOTHING
                }
            }
        }
    }
}
