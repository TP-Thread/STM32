#ifndef CHASSIS_TASK_H
#define CHASSIS_TASK_H

#include "main.h"
#include "cmsis_os.h"

#define PI 3.1415926f

#define W_L 0.4f // 轮距，单位：m
#define W_R 0.05f

void chassis_task(void *argument);

void Vehicle_Speed(float V, float W);

#endif
