/*
 * SPI_CONFIG.h
 *
 *  Created on: Jul 17, 2021
 *      Author: zoldeyck
 */

#ifndef MCAL_SPI_SPI_CONFIG_H_
	#define MCAL_SPI_SPI_CONFIG_H_

	//num of channels and available channels
	#define NumOfSPIChannels 1
	#define SPIChannel_1 1

	//SPI Slave/Master Mode Select
	#define Slave 0
	#define Master 1
	#define SPI_Mode Master

	//PINS and PORTS
	#define SPI_PORT PORT_B
	#define SPI_SS_PIN 4
	#define SPI_MOSI_PIN 5
	#define SPI_MISO_PIN 6
	#define SPI_SCK_PIN 7

	//Available slaves
	#define TheMaster 0
	#define NumOfSPISlaves 1
	#define SlaveID_1 1
	#define SlaveID_1_Port SPI_PORT
	#define SlaveID_1_Pin SPI_SS_PIN

	//SPI Clock Modes
	#define Mode_0 0
	#define Mode_1 1
	#define Mode_2 2
	#define Mode_3 3
	#define SPI_ClockMode Mode_1

	//SPI PreScalar
	#define CPU_Freq_DivideBy_2		0x4
	#define CPU_Freq_DivideBy_4		0x0
	#define CPU_Freq_DivideBy_8		0x5
	#define CPU_Freq_DivideBy_16	0x1
	#define CPU_Freq_DivideBy_32	0x6
	#define CPU_Freq_DivideBy_64	0x2
	#define CPU_Freq_DivideBy_128	0x3
	#define SPI_Freq CPU_Freq_DivideBy_128

	//SPI Data Order Select
	#define MSB_First 0
	#define LSB_First 1
	#define SPI_DataOrder MSB_First

	//Bits and masks of control register
	#define ResgisterDefaultVal 0
	#define ClockSelectBit_0_BIT 0
	#define ClockSelectBit_0_MSK 1
	#define ClockSelectBit_1_BIT 1
	#define ClockSelectBit_1_MSK 2
	#define ClockPhase_BIT 2
	#define ClockPhase_MSK 4
	#define ClockPolarity_BIT 3
	#define ClockPolarity_MSK 8
	#define MasterSlaveModeSelect_BIT 4
	#define MasterSlaveModeSelect_MSK 16
	#define DataOrder_BIT 5
	#define DataOrder_MSK 32
	#define SPIEnable_BIT 6
	#define SPIEnable_MSK 64
	#define InterruptEnable_BIT 7
	#define InterruptEnable_MSK 128

	//Bits and masks of Status register
	#define ClockSelectBit_2_BIT 0
	#define ClockSelectBit_2_MSK 1
	#define WriteCollisionFlag_BIT 6
	#define WriteCollisionFlag_MSK 64
	#define InterruptFlag_BIT 7
	#define InterruptFlag_MSK 128

	//SPI Errors
	#define OperationSuccess 0
	#define Unavailable_SPI_Channel 1
	#define Slave_Still_InService 2
	#define Non_Existant_Slave 3
	#define WriteCollisionOccurs 4
	#define OperationFail 5
	#define SelectedSPIModeUnavailable 6
	#define OperationStarted 255



#endif /* MCAL_SPI_SPI_CONFIG_H_ */
