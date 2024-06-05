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
#include "C:\Users\aprandi\MPLABXProjects\Spi_trial.X\mcc_generated_files\pin_manager.h"
#include "../SSD1322_OLED_lib/SSD1322_HW_Driver.h"

//====================== CS pin low ========================//
/**
 *  @brief Drives CS (Chip Select) pin of SPI interface low.
 *
 *  CS pin may be also signed as "SS" or "NSS"
 */
void SSD1322_HW_drive_RESET_low() {
    LATBbits.LATB0 = 0; // Esempio, usa il pin RB0 per RESET
}

void SSD1322_HW_drive_RESET_high() {
    LATBbits.LATB0 = 1; // Esempio, usa il pin RB0 per RESET
}

void SSD1322_HW_drive_CS_low() {
    LATBbits.LATB1 = 0; // Esempio, usa il pin RB1 per CS
}

void SSD1322_HW_drive_CS_high() {
    LATBbits.LATB1 = 1; // Esempio, usa il pin RB1 per CS
}

void SSD1322_HW_drive_DC_low() {
    LATBbits.LATB2 = 0; // Esempio, usa il pin RB2 per DC
}

void SSD1322_HW_drive_DC_high() {
    LATBbits.LATB2 = 1; // Esempio, usa il pin RB2 per DC
}

void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit) {
    SPI2BUF = byte_to_transmit;        // Invia il byte
    while(!SPI2STATbits.SPIRBF);       // Attendi che la trasmissione sia completata
    uint8_t temp = SPI2BUF;            // Leggi il buffer per resettare il flag
}

void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size) {
    for (uint32_t i = 0; i < array_size; i++) {
        SSD1322_HW_SPI_send_byte(array_to_transmit[i]);
    }
}
void SSD1322_HW_msDelay(uint32_t milliseconds) {
    for (uint32_t i = 0; i < milliseconds; i++) {
        __delay_ms(1);  // Funzione di ritardo definita per il tuo compilatore
    }
}
