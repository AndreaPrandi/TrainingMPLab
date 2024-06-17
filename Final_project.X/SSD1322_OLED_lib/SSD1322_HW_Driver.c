/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.c
 *
 * \brief Hardware dependent functions for SSD1322 OLED display.
 *
 * This file contains functions that rely on hardware of used MCU. In this example functions
 * are filled with STM32F411RE hardware implementation. To use this library on any other MCU
 * you just have to provide its hardware implementations of functions from this file and higher
 * level functions should work without modification.
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

//=================== Include hardware HAL libraries =====================//


 // Include per l'SPI driver
#include "../mcc_generated_files/pin_manager.h"
#include "../mcc_generated_files/delay.h"
#include "SSD1322_GFX.h"
#include "SSD1322_API.h"
#include "../SSD1322_OLED_lib/SSD1322_HW_Driver.h"


//====================== CS (Chip Select) pin configuration ========================//

// CS pin (RA0) high
void SSD1322_HW_drive_CS_high() {
    LATAbits.LATA0 = 1; // Configura il pin RA0 per CS
}

// CS pin (RA0) low
void SSD1322_HW_drive_CS_low() {
    LATAbits.LATA0 = 0; // Configura il pin RA0 per CS
}

//====================== RESET pin configuration ========================//

// RESET pin (RA1) high
void SSD1322_HW_drive_RESET_high() {
    LATAbits.LATA1 = 1; // Configura il pin RA1 per RESET
}

// RESET pin (RA1) low
void SSD1322_HW_drive_RESET_low() {
    LATAbits.LATA1 = 0; // Configura il pin RA1 per RESET
}

//====================== D/C (Data/Command) pin configuration ========================//

// D/C pin (RA9) high
void SSD1322_HW_drive_DC_high() {
    LATAbits.LATA9 = 1; // Configura il pin RA9 per Data/Command
}

// D/C pin (RA9) low
void SSD1322_HW_drive_DC_low() {
    LATAbits.LATA9 = 0; // Configura il pin RA9 per Data/Command
}

//====================== SPI Send Byte function for SPI1 ========================//
/*
void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit) {
    // Assicurati che la configurazione dei pin per SPI (RA4 e RC3) sia corretta
    TRISAbits.TRISA4 = 0; // RA4 come output per SDIN
    TRISCbits.TRISC3 = 0; // RC3 come output per SCLK

    SPI1BUF = byte_to_transmit;   
    DELAY_milliseconds(10);// Invia il byte
    while(!SPI1STATbits.SPIRBF);       // Attendi che la trasmissione sia completata
    uint8_t temp = SPI1BUF;            // Leggi il buffer per resettare il flag
}
*/

void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit) {
    // Invia il byte utilizzando la funzione SPI1_Exchange8bit, che ? una routine bloccante.
    uint8_t received_byte = SPI1_Exchange8bit(byte_to_transmit);

    // Non ? necessario attendere il buffer di ricezione, ma leggiamo SPI1BUF per resettare il flag di trasmissione.
    //(void)received_byte; // Opzionale: se vuoi ignorare il byte ricevuto.
    }


void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size) {
    for (uint32_t i = 0; i < array_size; i++) {
        SSD1322_HW_SPI_send_byte(array_to_transmit[i]);
    }
}

//====================== Delay function ========================//

void SSD1322_HW_msDelay(uint32_t milliseconds) {
    for (uint32_t i = 0; i < milliseconds; i++) {
        DELAY_milliseconds(1);  // Funzione di ritardo definita per il tuo compilatore
    }
}