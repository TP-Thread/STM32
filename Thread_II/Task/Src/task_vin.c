/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.0
 * @日  期  2024-02-20
 * @内  容  测量电压
 ******************************************************************************
 */

#include "task_vin.h"

/**
 * @brief	vin 任务,测量电压
 * @param	argument: NULL
 */
void vin_task(void const *argument)
{

  VOL_ScaleSet();

  while (1)
  {
    printf("Voltage: %-3.1f\n", VIN_GetVal());
    osDelay(10000);
  }
}
