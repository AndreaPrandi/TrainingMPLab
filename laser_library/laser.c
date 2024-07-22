#include "xc.h"
#include "laser.h"
#include "uart1.h"

/**
 * @brief Inizializza la comunicazione UART per il modulo laser.
 */
void Laser_Init(void) {
    UART1_Initialize();
}

/**
 * @brief Invia un comando per eseguire una misurazione singola.
 */
void Laser_SingleMeasurement(void) {
    UART1_Write(0x80);
    UART1_Write(0x06);
    UART1_Write(0x02);
    UART1_Write(0x78);
}

/**
 * @brief Invia un comando per avviare le misurazioni continue.
 */
void Laser_ContinuousMeasurement(void) {
    UART1_Write(0x80);
    UART1_Write(0x06);
    UART1_Write(0x03);
    UART1_Write(0x77);
}

/**
 * @brief Invia un comando per fermare il modulo laser.
 */
void Laser_Stop(void) {
    UART1_Write(0x80);
    UART1_Write(0x04);
    UART1_Write(0x02);
    UART1_Write(0x7A);
}

/**
 * @brief Imposta la frequenza di misurazione del modulo laser.
 * @param frequency La frequenza desiderata (es. 5, 10, 20 Hz).
 */
void Laser_SetFrequency(uint8_t frequency) {
    UART1_Write(0xFA);
    UART1_Write(0x04);
    UART1_Write(0x0A);
    UART1_Write(frequency);
    UART1_Write(0x00); // Example checksum, replace with actual if necessary
}

/**
 * @brief Legge un byte di dati dalla UART.
 * @return Il byte di dati ricevuto.
 */
uint8_t Laser_ReadData(void) {
    if (UART1_IsRxReady()) {
        return UART1_Read();
    }
    return 0; // Return 0 if no data is available
}

/**
 * @brief Ottiene la distanza misurata dal modulo laser.
 * @return La distanza in metri.
 */
float Laser_GetDistance(void) {
    uint8_t data[7];
    for (int i = 0; i < 7; i++) {
        data[i] = Laser_ReadData();
    }
    // Assuming the data format is ASCII and represents the distance in meters
    float distance = atof((char*)data);
    return distance;
}

/**
 * @brief Imposta il punto di partenza del modulo laser.
 * @param point Il punto di partenza desiderato (0 per l'inizio, 1 per la fine).
 */
void Laser_SetStartPoint(uint8_t point) {
    UART1_Write(0xFA);
    UART1_Write(0x04);
    UART1_Write(0x08);
    UART1_Write(point);
    UART1_Write(0x00); // Example checksum, replace with actual if necessary
}

/**
 * @brief Imposta la gamma del modulo laser.
 * @param range La gamma desiderata in metri.
 */
void Laser_SetRange(uint16_t range) {
    UART1_Write(0xFA);
    UART1_Write(0x04);
    UART1_Write(0x09);
    UART1_Write((range >> 8) & 0xFF);
    UART1_Write(range & 0xFF);
    UART1_Write(0x00); // Example checksum, replace with actual if necessary
}

/**
 * @brief Imposta la risoluzione del modulo laser.
 * @param resolution La risoluzione desiderata (es. 1mm o 0.1mm).
 */
void Laser_SetResolution(uint8_t resolution) {
    UART1_Write(0xFA);
    UART1_Write(0x04);
    UART1_Write(0x0C);
    UART1_Write(resolution);
    UART1_Write(0x00); // Example checksum, replace with actual if necessary
}

/**
 * @brief Imposta se il modulo laser deve avviare la misurazione all'accensione.
 * @param start Se true, avvia la misurazione all'accensione; altrimenti no.
 */
void Laser_StartOnPower(bool start) {
    UART1_Write(0xFA);
    UART1_Write(0x04);
    UART1_Write(0x0D);
    UART1_Write(start ? 0x01 : 0x00);
    UART1_Write(0x00); // Example checksum, replace with actual if necessary
}
