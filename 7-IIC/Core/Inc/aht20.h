/*
 * aht20.h
 *
 *  Created on: Jun 24, 2025
 *      Author: s5566
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_

#include "i2c.h"

void AHT20_init();
void AHT20_Read(float *Temp, float *Humi);

void AHT20_Measure();

void AHT20_get();

void AHT20_Analysis(float *Temp, float *Humi);

#endif /* INC_AHT20_H_ */
