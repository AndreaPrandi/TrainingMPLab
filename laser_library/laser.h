#ifndef LASER_H
#define LASER_H

void Laser_Init(void);
void Laser_SingleMeasurement(void);
void Laser_ContinuousMeasurement(void);
void Laser_Stop(void);
void Laser_SetFrequency(uint8_t frequency);
uint8_t Laser_ReadData(void);
float Laser_GetDistance(void);
void Laser_SetStartPoint(uint8_t point);
void Laser_SetRange(uint16_t range);
void Laser_SetResolution(uint8_t resolution);
void Laser_StartOnPower(bool start);

#endif /* LASER_H */
