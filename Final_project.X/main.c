
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
#include "global.h"

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

      if (immaginebuffer == NULL) {
          led3_SetHigh();
           fill_buffer(frame_buffer, 0x00);
          draw_text(frame_buffer, "error memory allocation", 10, 20, 0x0F);  // Posizione e luminositï¿½ possono essere aggiustate
           send_buffer_to_OLED(frame_buffer, 0, 0);
          DELAY_milliseconds(5000);
    }
    uint8_t text1[15] ;
    uint8_t text2[15] ;
   uint8_t messageData[1] = {20};
    dati = SendCANMessage(22, messageData, sizeof(messageData));
        fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, bertone256x35, 0, 15, 256, 35);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(500);
        
        fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, gb110256x56, 0, 0, 256, 56);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(500);

        fill_buffer(frame_buffer, 0x00);
        sprintf(text1, "Velocita: %d", 0);  // Correct
        draw_text(frame_buffer, text1, 10, 20, 0x0F);  // Posizione e luminositï¿½ possono essere aggiustate
        sprintf(text2, "rpm: %d", 0);  // Correct
        draw_text(frame_buffer, text2, 10, 50, 0x0F);  // Posizione e luminositï¿½ possono essere aggiustate
        send_buffer_to_OLED(frame_buffer, 0, 0);
        
        fill_buffer(frame_buffer, 0x00);
     
        led1_Toggle();

    while (1) {
        
        if (drawImageFlag== true){
        
        
            fill_buffer(frame_buffer, 0x00);
            draw_bitmap_4bpp(frame_buffer, gb110256x56, 0, 0, 256, 56);
            send_buffer_to_OLED(frame_buffer, 0, 0);
            DELAY_milliseconds(500);
        }
            else if (drawBertone==true){
            fill_buffer(frame_buffer, 0x00);
            draw_bitmap_4bpp(frame_buffer, bertone256x35, 0, 15, 256, 35);
            send_buffer_to_OLED(frame_buffer, 0, 0);
            DELAY_milliseconds(500);  
           } else if (image_complete==true) {
              fill_buffer(frame_buffer, 0x00);
              draw_bitmap_4bpp(frame_buffer,immaginebuffer,0,0,256,35);
              send_buffer_to_OLED(frame_buffer, 0, 0);
              DELAY_milliseconds(500); 
              dati = SendCANMessage(22, messageData, sizeof(messageData));
               
            }
        
        else{
            
         fill_buffer(frame_buffer, 0x00);
         dati = SendCANMessage(48, messageData, sizeof(messageData));

        static uint8_t messageData[1] = {56};
        CAN_TX_MSG_REQUEST_STATUS dati;

        draw_rect_filled(frame_buffer, 10, 0, 250, 20, 0x00);
        sprintf(text1, "Velocita: %d", speed);
        draw_text(frame_buffer, text1, 10, 20, 0x0F);
      
        dati = SendCANMessage(22, messageData, sizeof(messageData));
        led1_Toggle();

        draw_rect_filled(frame_buffer, 10, 35, 250, 64, 0x00);
        sprintf(text2, "rpm: %d", rpm);
        draw_text(frame_buffer, text2, 10, 50, 0x0F);
        send_buffer_to_OLED(frame_buffer, 0, 0);
        dati = SendCANMessage(6, messageData, sizeof(messageData));
        led2_Toggle();
        
        }
    }
        
    return 0;
}

