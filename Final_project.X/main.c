
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
CAN_TX_MSG_REQUEST_STATUS SendCANMessage(uint32_t msgId, uint8_t *data, uint8_t dataLength) {
    CAN_MSG_OBJ canMessage;

    if (dataLength > 8) {
        return false; // Data length exceeds maximum CAN data length
    }

    canMessage.msgId = msgId;
    canMessage.field.frameType = CAN_FRAME_DATA;
    canMessage.field.idType = CAN_FRAME_STD;
    canMessage.field.dlc = dataLength;
    canMessage.data = data;

    return CAN1_Transmit(CAN_PRIORITY_HIGH, &canMessage) ;
}

int main(void) {
    SYSTEM_Initialize();
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();
   // CAN1_OperationModeSet(CAN_CONFIGURATION_MODE);
    // Imposta altre configurazioni specifiche qui
   //CAN1_OperationModeSet(CAN_INTERNAL_LOOPBACK_MODE);
     SSD1322_API_init();
     CAN_TX_MSG_REQUEST_STATUS dati;
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
        DELAY_milliseconds(500);
        
          fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, gb110256x56, 0, 0, 256, 56);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(500);

    

        led1_Toggle();

    while (1) {
        // Send a CAN message
      
            // Check if a message has been received
            if (CAN1_ReceivedMessageCountGet() > 0) {
                CAN_MSG_OBJ receivedMsg;
                uint8_t receivedData[8];
                receivedMsg.data = receivedData;

                if (CAN1_Receive(&receivedMsg)) {
                   // DELAY_milliseconds(100);
                    if (receivedMsg.msgId == 0x123) {
                       fill_buffer(frame_buffer, 0x00);
                      
                      
                        sprintf(text1, "Velocita: %d", receivedMsg.data[0]);  // Correct
                        draw_text(frame_buffer, text1, 10, 20, 0x0F);  // Posizione e luminositï¿½ possono essere aggiustate
                        sprintf(text2, "rpm: %d", receivedMsg.data[1]);  // Correct
                        draw_text(frame_buffer, text2, 10, 50, 0x0F);  // Posizione e luminositï¿½ possono essere aggiustate
                        led2_Toggle();
                        send_buffer_to_OLED(frame_buffer, 0, 0);
                        dati=SendCANMessage(12, messageData, sizeof(messageData));  // Invia il messaggio CAN
                        //DELAY_milliseconds(100);
                        led2_Toggle();   // Turn off LED3 if the ID doesn't match

                    }
                }
            }
            else{
                
               
                dati=SendCANMessage(45, messageData, sizeof(messageData));  // Invia il messaggio CAN
                DELAY_milliseconds(100);
                led2_Toggle();   // Turn off LED3 if the ID doesn't match
                

            }
       if (TMR1_GetElapsedThenClear()) {
          SendCANMessage(42, messageData, sizeof(messageData));  // Invia il messaggio CAN
        }

        
    }
        
    return 0;
}

