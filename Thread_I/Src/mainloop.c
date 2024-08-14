/**			                                                    
  ******************************************************************************
  * @作  者  没PF的老亚瑟
  * @版  本  V1.0
  * @日  期  2022-12-30
  * @brief   控制函数
  *
  ******************************************************************************
  */
#include "mainloop.h"
#include "usbd_customhid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t bEP1_SendBuf[64] = { 0 };

/**
 * Main Loop Function
 */
void MainLoop(void)
{	
	if(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, bEP1_SendBuf, 64) == USBD_OK)
	{
		bEP1_SendBuf[0]++;
	}
	
	LED_B_Toggle();
	
	HAL_Delay(1000);
}
