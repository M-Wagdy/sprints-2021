/* BCM_Interface.h
 *
 * Created: 8/24/2021
 *  Author: Ahmed Essam
 */
 #ifndef _BCM_INTERFACE_H_
 #define _BCM_INTERFACE_H_
/*-INCLUDES-------------------------------*/
#include "STD_TYPES.h"
#include "COMMProxy.h"
/*-MACROS---------------------------------*/
#define BCM_MAX_DATA_SIZE (uint16_t)1000
#define BCM_MIN_DATA_SIZE (uint16_t)1
/*BCM MODES*/
#define BCM_MODE_RX       (uint8_t)0
#define BCM_MODE_TX       (uint8_t)1
#define BCM_MODE_IDEAL    (uint8_t)2
/*BCM TX STATES*/
#define BCM_TXSTATE_PENDING (uint8_t)1
#define BCM_TXSTATE_SENDING (uint8_t)2

/*BCM RX STATES*/
#define BCM_RXSTATE_RECEIVING 	   (uint8_t)1
#define BCM_RXSTATE_CS 			   (uint8_t)2
#define BCM_RXSTATE_ERROR 		   (uint8_t)3
#define BCM_STATE_INVALID          (uint8_t)4

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_BCMTask_t{
    uint8_t             u8_BCMID;//BCM CMD
    uint8_t             u8_BCMMode;//To store the mode(Transmit/Receive)
    uint8_t             u8_BCMCS;//This var store the count of bytes
    uint8_t             u8_BCMState;//To store the state
    uint8_t             u8_BCMPacketCounter;//Counter for the packet
    uint16_t            u16_BCMByteCoounter;//Counter for the bytes
    uint16_t            u16_BCMSize;//Size of data
    ptr_uint8_t         ptr_BCMBuffer;//Array of the data
    Ptr_VoidFuncVoid_t  ptr_BCMCallBackFu;//Call back function

}STR_BCMTask_t;
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef STR_BCMTask_t*  ptr_STR_BCMTask_t;
/*-APIs DECLARATIONS------------------------*/
extern ERROR_STATE_t BCM_Send(uint8_t COMM_ID, uint16_t Size,ptr_uint8_t DataArr,Ptr_VoidFuncVoid_t TX_CBF);
extern ERROR_STATE_t BCM_Receive(uint8_t COMM_ID,uint16_t Size,ptr_uint8_t DataArr,Ptr_VoidFuncVoid_t RX_CBF);
extern ERROR_STATE_t BCM_Get(uint8_t CH_ID,ptr_STR_BCMTask_t* Task);
extern ERROR_STATE_t BCM_SetState(uint8_t CH_ID,uint8_t CurrentState);
 #endif // _BCM_INTERFACE_H_
