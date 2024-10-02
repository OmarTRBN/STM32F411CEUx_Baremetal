// main.c

#include "stm32f4xx.h"
#include "stm32_omar.h"

#define LEDPIN PC13

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

void initMPU6050() {
    char data;

    // Wake up MPU6050 (Power Management 1 register)
    data = 0x00;
    I2C_burstWrite(MPU6050_ADDR, 0x6B, 1, &data);

    // Configure clock source (Power Management 1 register)
    data = 0x01;  // Set clock source to PLL with X axis gyroscope reference
    I2C_burstWrite(MPU6050_ADDR, 0x6B, 1, &data);

    // Configure gyroscope full scale range (Gyroscope Configuration register)
    data = 0x08;  // Set full scale range to ±500 degrees/second
    I2C_burstWrite(MPU6050_ADDR, 0x1B, 1, &data);

    // Configure accelerometer full scale range (Accelerometer Configuration register)
    data = 0x08;  // Set full scale range to ±4g
    I2C_burstWrite(MPU6050_ADDR, 0x1C, 1, &data);

    // Configure digital low pass filter (Configuration register)
    data = 0x03;  // Set DLPF to 44Hz (for both accel and gyro)
    I2C_burstWrite(MPU6050_ADDR, 0x1A, 1, &data);

    // Configure sample rate divider (Sample Rate Divider register)
    data = 0x07;  // Set sample rate to 1kHz / (1 + 7) = 125Hz
    I2C_burstWrite(MPU6050_ADDR, 0x19, 1, &data);

    // Disable interrupts (Interrupt Enable register)
    data = 0x00;
    I2C_burstWrite(MPU6050_ADDR, 0x38, 1, &data);
}

void readAccelData(int16_t* accelData) {
    char data[6];
    I2C_burstRead(MPU6050_ADDR, ACCEL_XOUT_H, 6, data);
    
    accelData[0] = (data[0] << 8) | data[1];  // X-axis
    accelData[1] = (data[2] << 8) | data[3];  // Y-axis
    accelData[2] = (data[4] << 8) | data[5];  // Z-axis
}



int main(void)
{
	initI2C1();
	initMPU6050();
	
	int16_t accelData[3];
	
	tim2_pa5_output_compare();

	while (1)
	{
		readAccelData(accelData);
		systickDelayMs(500);
	}
}