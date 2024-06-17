/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33EV256GM106
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <stdio.h>
#include "mcc_generated_files/system.h"
#include "SSD1322_OLED_lib/SSD1322_API.h"
#include "SSD1322_OLED_lib/SSD1322_GFX.h"
#include "SSD1322_OLED_lib/SSD1322_HW_Driver.h"
#include "mcc_generated_files/delay.h"
#include "FreeMono12pt7b.h"
#include "mcc_generated_files/pin_manager.h"
#include "gb110256x56.h"
#include "Bertone256x35.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/can1.h"

/*
                         Main application
 */
bool SendCANMessage(uint32_t msgId, uint8_t *data, uint8_t dataLength) {
    CAN_MSG_OBJ canMessage;

    if (dataLength > 8) {
        return false; // Data length exceeds maximum CAN data length
    }

    canMessage.msgId = msgId;
    canMessage.field.frameType = CAN_FRAME_DATA;
    canMessage.field.idType = CAN_FRAME_STD;
    canMessage.field.dlc = dataLength;
    canMessage.data = data;

    return CAN1_Transmit(CAN_PRIORITY_HIGH, &canMessage) == CAN_TX_MSG_REQUEST_SUCCESS;
}

int main(void) {
    SYSTEM_Initialize();
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();
   // CAN1_OperationModeSet(CAN_CONFIGURATION_MODE);
    // Imposta altre configurazioni specifiche qui
   //CAN1_OperationModeSet(CAN_INTERNAL_LOOPBACK_MODE);
     SSD1322_API_init();
  
     uint8_t frame_buffer[8192] = {0};
     select_font(&FreeMono12pt7b);
    TMR1_Start();
    TMR2_Start();
       char text1[5];  // Crea un buffer per la stringa del primo byte
       char text2[5];  // Crea un buffer per la stringa del secondo byte
    uint8_t messageData[1] = {56};
    
      fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, bertone256x35, 0, 15, 256, 35);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(5000);
        
          fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, gb110256x56, 0, 0, 256, 56);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(5000);

    

        led1_Toggle();

        // Disegnare alcune forme di base sul buffer
        fill_buffer(frame_buffer, 0x00);
        draw_rect(frame_buffer, 10, 10, 100, 50, 0x0F);  // Rettangolo
        draw_text(frame_buffer, "Ciao Mondo", 10, 20, 0x0F);

        draw_text(frame_buffer, "ciao mondo", 100, 50, 15);
        led2_Toggle();
        send_buffer_to_OLED(frame_buffer, 0, 0);

        DELAY_milliseconds(5000);
        led3_Toggle();

    while (1) {
        // Send a CAN message
      
            // Check if a message has been received
            if (CAN1_ReceivedMessageCountGet() > 0) {
                CAN_MSG_OBJ receivedMsg;
                uint8_t receivedData[8];
                receivedMsg.data = receivedData;

                if (CAN1_Receive(&receivedMsg)) {
                    if (receivedMsg.msgId == 0x123) {
                       fill_buffer(frame_buffer, 0x00);
                      
                        draw_text(frame_buffer, "velocita", 10, 20, 0x0F);
                        sprintf(text1, "%d", receivedMsg.data[0]);  // Correct
                        draw_text(frame_buffer, text1, 10, 40, 0x0F);  // Posizione e luminosità possono essere aggiustate
                        draw_text(frame_buffer, "rpm", 150, 20, 15);
                        sprintf(text2, "%d", receivedMsg.data[1]);  // Correct
                        draw_text(frame_buffer, text2, 180, 40, 0x0F);  // Posizione e luminosità possono essere aggiustate
                        led2_Toggle();
                        send_buffer_to_OLED(frame_buffer, 0, 0);
                        SendCANMessage(12, messageData, sizeof(messageData));  // Invia il messaggio CAN
                    }
                }
            }
            else{
                led2_Toggle();   // Turn off LED3 if the ID doesn't match

            }
        if (TMR1_GetElapsedThenClear()) {
           SendCANMessage(12, messageData, sizeof(messageData));  // Invia il messaggio CAN
        }

        
    }
        
    return 0;
}

