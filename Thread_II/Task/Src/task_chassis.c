/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.2
 * @日  期  2024-03-05
 * @内  容  底盘控制任务
 ******************************************************************************
 */

#include "task_chassis.h"

extern float Roll, Pitch, Yaw; // 欧拉角 单位 rad

float Yaw_PID[3] = {10000, 0, 0};
static PID yaw_pid;
float expect_yaw;

/**
 * @brief	底盘任务
 * @param	argument: 空
 */
void chassis_task(void *argument)
{
    // 遥控器初始化
    SBUS_Init();
    // CAN过滤器配置
    CAN_Filter_Init();

    int32_t speedSet_L, speedSet_R;

    uint8_t speed_Data[8];

    PID_Init(&yaw_pid, Yaw_PID, 2000, 2000); // yaw角PID初始化
    expect_yaw = Yaw;

    while (1)
    {
        // 切换为陆行模式
        if (SBUS_CH.CH6 > 1500)
        {
            if ((SBUS_CH.CH3 > 950) && (SBUS_CH.CH3 < 1050) && (SBUS_CH.CH1 > 950) && (SBUS_CH.CH1 < 1050))
            {
                Motor_stop(0x141);
                Motor_stop(0x142);
            }
            else
            {
                if ((SBUS_CH.CH3 > 700) && (SBUS_CH.CH3 < 1300))
                {
                    if ((SBUS_CH.CH1 > 700) && (SBUS_CH.CH1 < 1300))
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) - (SBUS_CH.CH1 - 1000)) * 28.6;
                        speedSet_R = ((SBUS_CH.CH3 - 1000) + (SBUS_CH.CH1 - 1000)) * 28.6;
                    }
                    else
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) * 28.6 - (SBUS_CH.CH1 - 1000) * 286);
                        speedSet_R = ((SBUS_CH.CH3 - 1000) * 28.6 + (SBUS_CH.CH1 - 1000) * 286);
                    }
                }
                else
                {
                    if ((SBUS_CH.CH1 > 700) && (SBUS_CH.CH1 < 1300))
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) * 286 - (SBUS_CH.CH1 - 1000) * 28.6);
                        speedSet_R = ((SBUS_CH.CH3 - 1000) * 286 + (SBUS_CH.CH1 - 1000) * 28.6);
                    }
                    else
                    {
                        speedSet_L = -((SBUS_CH.CH3 - 1000) - (SBUS_CH.CH1 - 1000)) * 286;
                        speedSet_R = ((SBUS_CH.CH3 - 1000) + (SBUS_CH.CH1 - 1000)) * 286;
                    }
                }
            }

            Motor_speed(0x141, speedSet_L);
            Motor_speed(0x142, speedSet_R);
        }
        else
        {
            Motor_stop(0x141);
            Motor_stop(0x142);
        }

        // Motor_torque(0x142, 580);
        // Motor_speed(0x142, -100000);
        // printf("CH3:%d\n",SBUS_CH.CH3);
        // printf("Yaw:%.2f\n",Yaw);
        Motor_state2(0x141, speed_Data);
        Motor_state2(0x142, speed_Data);
        vTaskDelay(10);
    }
}

// void chassis_task(void const * argument)
//{
//     uint32_t xLastWakeTime = xTaskGetTickCount();

//    while (1)
//    {
//		//此任务以10ms运行一次
//		vTaskDelayUntil( &xLastWakeTime, 10);

//		Drive_Motor(Vector_S.Move_X, Vector_S.Move_Y, Vector_S.Move_W);

//        Motor_speed(0x141, speedSet_L);
//        Motor_speed(0x142, speedSet_R);
//    }
//}

/**
 * @brief	差速车运动学逆解，根据三轴目标速度计算各车轮目标转速
 * @param  X和Z轴方向的目标运动速度 m/s	rad/s
 */
void Vehicle_Speed(float V, float W)
{
    int32_t speedSet_L, speedSet_R;

    // 运动学逆解
    speedSet_L = 100 * (V - W * W_L / 2.0f) * 180 / (W_R * PI); // 计算出左轮的目标速度dps
    speedSet_R = 100 * (V + W * W_L / 2.0f) * 180 / (W_R * PI); // 计算出右轮的目标速度dps

    Motor_speed(0x141, speedSet_L);
    Motor_speed(0x142, speedSet_R);
}
