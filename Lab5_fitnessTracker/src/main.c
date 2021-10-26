#include "I2C.h"
#include "inttypes.h"
#include <esp_task_wdt.h>
#include <esp_pm.h>
#include "math.h"
#include "circular_buffer.h"

#define sdaPin 33                 // kan behövas ändra på min
#define sclPin 32                 // kan behövas ändra på min
#define MPU6050_ADDR 0x68         // address
#define MPU6050_PWR_MGMT_1 0x6B   // register
#define MPU6050_SMPLRT_DIV 0x19   // register
#define MPU6050_WHO_AM_I 0x75     // register
#define MPU6050_TEMP_OUT_H 0x41   // temperatur-register
#define MPU6050_TEMP_OUT_L 0x42   // temperatur-register
#define MPU6050_ACCEL_XOUT_H 0x3B // accelerator x-axel-register
#define MPU6050_ACCEL_XOUT_L 0x3C // accelerator x-axel-register
#define MPU6050_ACCEL_YOUT_H 0x3D // accelerator y-axel-register
#define MPU6050_ACCEL_YOUT_L 0x3E // accelerator y-axel-register
#define MPU6050_ACCEL_ZOUT_H 0x3F // accelerator z-axel-register
#define MPU6050_ACCEL_ZOUT_L 0x40 // accelerator z-axel-register
#define MPU6050_Accel_Lsb 16384.f
#define taskPeriod 2000
#define BUFFER_SIZE 10
struct circularBuffer circularBuffer;
uint32_t accelMag;


void samplingTask(void *arg)
{
     TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        int16_t rawData = 0;
        uint8_t buffer;
   
        // read the axcels
        float xAccel, yAccel, zAccel;
        readI2C(MPU6050_ADDR, MPU6050_ACCEL_XOUT_L, &buffer, 1);
        rawData = buffer;
        readI2C(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, &buffer, 1);
        rawData |= ((int16_t)buffer) << 8;
        xAccel = (float)rawData;

        readI2C(MPU6050_ADDR, MPU6050_ACCEL_YOUT_L, &buffer, 1);
        rawData = buffer;
        readI2C(MPU6050_ADDR, MPU6050_ACCEL_YOUT_H, &buffer, 1);
        rawData |= ((int16_t)buffer) << 8;
        yAccel = (float)rawData;
        readI2C(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_L, &buffer, 1);
        rawData = buffer;
        readI2C(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_H, &buffer, 1);
        rawData |= ((int16_t)buffer) << 8;
        zAccel = (float)rawData;

        // calc magnitude and add to buffer
        accelMag = (uint32_t)sqrtf(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
        printf("xA: %.2f, yA: %.2f, zA: %.2f\n", xAccel, yAccel, zAccel);
        printf("Acceleration magnitude: %d \n", (int)accelMag);
        addElement(&circularBuffer, accelMag);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(taskPeriod));
    }
}

/*void stepsTask(void *arg)
{
} */

void app_main()
{

    esp_pm_config_esp32_t config = {
        .light_sleep_enable = true,
        .min_freq_mhz = 14,
        .max_freq_mhz = 80};

    esp_pm_configure(&config);

    initI2C(sdaPin, sclPin);
    writeI2C(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0);
    writeI2C(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 250);

    uint32_t *buffer_data = (uint32_t *)malloc(BUFFER_SIZE * sizeof(uint32_t)); // allokerar minne i datorn för arrayn
    initCircularBuffer(&circularBuffer, buffer_data, BUFFER_SIZE);

    xTaskCreate(samplingTask, "accelerationTask", 2048, NULL, 1, NULL); // kanske ta tillbaka sen
    // xTaskCreate(stepsTask, "stepsTask", 1024, NULL, 10, NULL);
   //free(buffer_data);
}

