/*
 * SPI.c
 *
 *  Created on: Jul 17, 2021
 *      Author: zoldeyck
 */
#include "../../INFRASTRUCTURE/STD_types.h"
#include "../../INFRASTRUCTURE/Bit Operations.h"
#include "../DIO/DIO.h"
#include "SPI.h"

void static (*SPI_TX_Complete_callback)(void)=NULL_PTR;

void __vector_12(void)__attribute__((signal,used));//TX_complete

uint8_t SPI_Init(uint8_t SpiNumber) {
	uint8_t ErrRetVal = OperationStarted;
	uint8_t Dummy = 0;
	if (SpiNumber <= NumOfSPIChannels) {
		WRITE_REG(SPI_ControlReg, ResgisterDefaultVal);
		switch (SPI_Mode) {
		case Master:
			/*SPI Master Mode*/
			MODIFY_REG(SPI_ControlReg, MasterSlaveModeSelect_MSK,
					Master<<MasterSlaveModeSelect_BIT);
			/*SPI PIN Initialization*/
			DIO_SetPinDirection(SPI_PORT, SPI_SS_PIN, PIN_OUTPUT);
			DIO_WritePin(SPI_PORT, SPI_SS_PIN,PIN_HIGH);
			DIO_SetPinDirection(SPI_PORT, SPI_SCK_PIN, PIN_OUTPUT);
			DIO_SetPinDirection(SPI_PORT, SPI_MOSI_PIN, PIN_OUTPUT);
			/*selecting the clock mode*/
			MODIFY_REG(SPI_ControlReg, ClockPhase_MSK,
					READ_BIT(SPI_ClockMode,0)<<ClockPhase_BIT);
			MODIFY_REG(SPI_ControlReg, ClockPolarity_MSK,
					READ_BIT(SPI_ClockMode,1)<<ClockPolarity_BIT);
			/*Setting the Data Order*/
			MODIFY_REG(SPI_ControlReg, DataOrder_MSK,
					SPI_DataOrder<<DataOrder_BIT);
			/*Set SPI Clock Frequency*/
			MODIFY_REG(SPI_StatusReg, ClockSelectBit_2_MSK,
					READ_BIT(SPI_Freq,2)<<ClockSelectBit_2_BIT);
			MODIFY_REG(SPI_ControlReg, ClockSelectBit_1_MSK,
					READ_BIT(SPI_Freq,1)<<ClockSelectBit_1_BIT);
			MODIFY_REG(SPI_ControlReg, ClockSelectBit_0_MSK,
					READ_BIT(SPI_Freq,0)<<ClockSelectBit_0_BIT);
			/*clearing flags*/
			Dummy = READ_BIT(SPI_StatusReg,WriteCollisionFlag_BIT);
			Dummy = READ_BIT(SPI_StatusReg,InterruptFlag_BIT);
			Dummy = READ_REG(SPI_DataReg);
			/*enable SPI Module*/
			SET_BIT(SPI_ControlReg, SPIEnable_BIT);
			ErrRetVal = OperationSuccess;
			break;
		case Slave:
			/*SPI Slave Mode*/
			MODIFY_REG(SPI_ControlReg, MasterSlaveModeSelect_MSK,
					Slave<<MasterSlaveModeSelect_BIT);
			/*SPI PIN Initialization*/
			DIO_SetPinDirection(SPI_PORT, SPI_MISO_PIN, PIN_OUTPUT);
			/*selecting the clock mode*/
			MODIFY_REG(SPI_ControlReg, ClockPhase_MSK,
					READ_BIT(SPI_ClockMode,0)<<ClockPhase_BIT);
			MODIFY_REG(SPI_ControlReg, ClockPolarity_MSK,
					READ_BIT(SPI_ClockMode,1)<<ClockPolarity_BIT);
			/*Setting the Data Order*/
			MODIFY_REG(SPI_ControlReg, DataOrder_MSK,
					SPI_DataOrder<<DataOrder_BIT);
			/*Set SPI Clock Frequency*/
			/*not necessary as we are in slave case*/
			/*clearing flags*/
			Dummy = READ_BIT(SPI_StatusReg, WriteCollisionFlag_BIT);
			Dummy = READ_BIT(SPI_StatusReg, InterruptFlag_BIT);
			Dummy = READ_REG(SPI_DataReg);
			/*removing garbage from slave Data register*/
			SPI_DataReg='\0';
			/*enable SPI Module*/
			SET_BIT(SPI_ControlReg, SPIEnable_BIT);
			ErrRetVal = OperationSuccess;
			break;
		default:
			/*error selected SPI mode is unavailable*/
			ErrRetVal = SelectedSPIModeUnavailable;
		}
	} else {
		/*error out of spi channels range.*/
		ErrRetVal = Unavailable_SPI_Channel;
	}
	return ErrRetVal;
}

uint8_t SPI_TransmitChar(uint8_t SpiNumber, uint8_t TxChar, uint8_t slave_CH) {
	uint8_t ErrRetVal = OperationStarted;
	uint8_t dummy = 0;
	uint8_t Data=0 ;
	switch (SPI_Mode) {
	case Master:
		if (slave_CH <= NumOfSPISlaves) {
			/*pulling slave select down*/
			DIO_WritePin(SlaveID_1_Port, SlaveID_1_Pin, PIN_LOW);
			/*making data available in the shift register (transmitting start)*/
			WRITE_REG(SPI_DataReg, TxChar);
			/*checking for write collision*/
			if (READ_BIT(SPI_StatusReg, WriteCollisionFlag_BIT)) {
				ErrRetVal = WriteCollisionOccurs;
				dummy = READ_REG(SPI_DataReg);
				/*flag is cleared*/
			} else {
				ErrRetVal = OperationSuccess;
			}

		} else {
			ErrRetVal = Non_Existant_Slave;
		}
		break;
	case Slave:
		DIO_ReadPin(SlaveID_1_Port, SlaveID_1_Pin,&Data);
		if (!Data) {
			/*making data available in the shift register*/
			WRITE_REG(SPI_DataReg, TxChar);
			/*checking for write collision*/
			if (READ_BIT(SPI_StatusReg, WriteCollisionFlag_BIT)) {
				ErrRetVal = WriteCollisionOccurs;
				dummy = READ_REG(SPI_DataReg);
				/*flag is cleared*/
			} else {
				ErrRetVal = OperationSuccess;
			}
		} else {
			ErrRetVal = OperationFail;
		}
		break;
	}
	return ErrRetVal;
}

uint8_t SPI_ReceiveChar(uint8_t SpiNumber, ptr_uint8_t RxData, uint8_t slave_CH) {
	uint8_t ErrRetVal = OperationStarted;
	switch (SPI_Mode) {
	case Master:
		if (slave_CH <= NumOfSPISlaves) {
			/*check that transmission is completed*/
			if ((READ_BIT(SPI_StatusReg, InterruptFlag_BIT))) {
				/*Read Data from data_register*/
				*RxData = SPI_DataReg;
				DIO_WritePin(SlaveID_1_Port, SlaveID_1_Pin, PIN_HIGH);
				ErrRetVal = OperationSuccess;
			} else {
				ErrRetVal = OperationFail;
			}
		} else {
			/*error out of spi channels range.*/
			ErrRetVal = Unavailable_SPI_Channel;
		}
		break;
	case Slave:
		if ((READ_BIT(SPI_StatusReg, InterruptFlag_BIT))) {
			*RxData = SPI_DataReg;
			ErrRetVal = OperationSuccess;
		} else {
			ErrRetVal = OperationFail;
		}
		break;
	}
	return ErrRetVal;
}

uint8_t SPI_DataExchange (uint8_t SpiNumber, uint8_t TxChar, ptr_uint8_t RxData, uint8_t slave_CH)
{
	uint8_t RETVAL = OperationStarted;
	switch(SPI_Mode){
	case Master:
		SPI_TransmitChar(SPIChannel_1, TxChar, SlaveID_1);
		while(SPI_ReceiveChar(SPIChannel_1, RxData, SlaveID_1) != OperationSuccess) ;
		RETVAL = OperationSuccess;
		break;
	case Slave:
//		while (SPI_ReceiveChar(SPIChannel_1, RxData, SlaveID_1)	!= OperationSuccess);
//		while (SPI_TransmitChar(SPIChannel_1, TxChar, SlaveID_1) != OperationSuccess);
		while (SPI_TransmitChar(SPIChannel_1, TxChar, SlaveID_1) != OperationSuccess);
		while (SPI_ReceiveChar(SPIChannel_1, RxData, SlaveID_1)	!= OperationSuccess);
		RETVAL = OperationSuccess;
		break;
	}
	return RETVAL;
}

uint8_t SPI_TransmitString(uint8_t SpiNumber, ptr_uint8_t TxString,
uint8_t slave_CH) {
	uint8_t ErrRetVal = OperationStarted;
	uint8_t iterator = 0;
	uint8_t Dummy = 0;
	while(iterator <= 255)
	{
		if (*TxString == '\0') {
			ErrRetVal = OperationSuccess;
			SPI_TransmitChar(SPIChannel_1, '\0', SlaveID_1);
			while(!(READ_BIT(SPI_StatusReg, InterruptFlag_BIT)));
			break;
		} else {
			SPI_TransmitChar(SPIChannel_1, *TxString, SlaveID_1);
			while(!(READ_BIT(SPI_StatusReg, InterruptFlag_BIT)));
			iterator++;
			TxString++;
		}
	}
	return ErrRetVal;
}

uint8_t SPI_ReceiveString(uint8_t SpiNumber, ptr_uint8_t RxString,uint8_t slave_CH)
{
	uint8_t ErrRetVal = OperationStarted;
	uint8_t* RxStringAddress=RxString;
	uint8_t iterator = 0;
	uint8_t Dummy = 0;
	while (1) 
	{
		SPI_TransmitChar(SPIChannel_1,*RxString,SlaveID_1);
		while(!(SPI_StatusReg & 0x80));
		*RxString = SPI_DataReg;
		dummy_delay();
		if(*RxString == '\0')
		{
			break;
		}		
		RxString++;
	}
}

uint8_t SPI_EnableInterrupt(uint8_t SpiNumber)
{
	uint8_t ErrRetVal = OperationStarted;
	/*Enable Global Interrupt*/
	SET_BIT(STATUS_REG, 7);
	/*Enable Local Interrupt*/
	MODIFY_REG(SPI_ControlReg,
			InterruptEnable_MSK,
			InterruptEnable_MSK);
	ErrRetVal = OperationSuccess;
	return ErrRetVal;
}

uint8_t SPI_DisableInterrupt(uint8_t SpiNumber)
{
	uint8_t ErrRetVal = OperationStarted;
	CLEAR_BIT(SPI_ControlReg, InterruptEnable_BIT);
	ErrRetVal = OperationSuccess;
	return ErrRetVal;
}

uint8_t SPI_Set_TX_CompleteCallback(uint8_t SpiNumber,void(*callBack)(void))
{
	uint8_t ErrRetVal = 0;
		if (callBack != NULL_PTR)
			SPI_TX_Complete_callback = callBack;
		return ErrRetVal;
}

void __vector_12(void)
{
	if (SPI_TX_Complete_callback != NULL_PTR)
		SPI_TX_Complete_callback();
}
