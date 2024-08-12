#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "main.h"

void CAN_Filter_Init(void);

void CAN_SendStdData(CAN_HandleTypeDef *hcan, uint16_t T_Id, uint8_t *T_Data);
uint16_t CAN_ReadStdData(CAN_HandleTypeDef *hcan, uint8_t *R_Data);
void CAN_Process(uint8_t *R_Data);

#endif
