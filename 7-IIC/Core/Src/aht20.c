/*
 * aht20.c
 *
 *  Created on: Jun 24, 2025
 *      Author: s5566
 */

#include "aht20.h"

#define AHT20_ADDRESS 0x70

uint8_t readBuffer[6] = {0};

void AHT20_init(){
	uint8_t readBuffer;
	HAL_Delay(40);
	HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
	if((readBuffer & 0x08) == 0x00){
		uint8_t sendBuffer[3] = { 0xBE, 0x08, 0x00};
		HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);

	}
}

void AHT20_Read(float *Temp, float *Humi){
	uint8_t sendBuffer[3] = { 0xAC, 0x33, 0x00};
	uint8_t readBuffer[6] = {0};


	HAL_I2C_Master_Transmit_IT(&hi2c1, AHT20_ADDRESS, sendBuffer, 3);
	HAL_Delay(75);
	HAL_I2C_Master_Receive_IT(&hi2c1, AHT20_ADDRESS, readBuffer, 6);

	if( (readBuffer[0] & 0x80) == 0x00 ){
		uint32_t data = 0;
		data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
		*Humi = data * 100.0f / (1<<20);

		data = (((uint32_t)readBuffer[3] & 0x0F ) << 16) + ((uint32_t)readBuffer[4] << 8) + ((uint32_t)readBuffer[5]);
		*Temp = data * 200.0f / (1<<20) - 50;
	}
}

void AHT20_Measure(){
	static uint8_t sendBuffer[3] = { 0xAC, 0x33, 0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, AHT20_ADDRESS, sendBuffer, 3);
}

void AHT20_get(){
	HAL_I2C_Master_Receive_IT(&hi2c1, AHT20_ADDRESS, readBuffer, 6);
}

void AHT20_Analysis(float *Temp, float *Humi){
	if( (readBuffer[0] & 0x80) == 0x00 ){
		uint32_t data = 0;
		data = ((uint32_t)readBuffer[3] >> 4) + ((uint32_t)readBuffer[2] << 4) + ((uint32_t)readBuffer[1] << 12);
		*Humi = data * 100.0f / (1<<20);

		data = (((uint32_t)readBuffer[3] & 0x0F ) << 16) + ((uint32_t)readBuffer[4] << 8) + ((uint32_t)readBuffer[5]);
		*Temp = data * 200.0f / (1<<20) - 50;
	}
}





