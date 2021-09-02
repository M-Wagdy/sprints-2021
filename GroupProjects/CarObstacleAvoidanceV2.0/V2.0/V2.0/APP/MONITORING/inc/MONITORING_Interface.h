/*
 * MONITORING_Interface.h
 *
 * Created: 8/16/2021 3:22:38 PM
 *  Author: zoldeyck
 */ 


#ifndef MONITORING_INTERFACE_H_
#define MONITORING_INTERFACE_H_

#include "LIB.h"

typedef struct STR_MONITOR_data_t{
	uint32_t u32_MONITOR_Xpos;
	uint32_t u32_MONITOR_Ypos;
	const uint8_t* u8_MONITOR_String;
	uint32_t* u32_MONITOR_Number;
} STR_MONITOR_data_t;

ERROR_STATE_t MONITOR_Set(STR_MONITOR_data_t * Data_To_Display);
ERROR_STATE_t MONITOR_Get(STR_MONITOR_data_t * Data_From_Display);


#endif /* MONITORING_INTERFACE_H_ */