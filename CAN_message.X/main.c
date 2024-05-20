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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/delay.h"
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
    CAN1_OperationModeSet(CAN_CONFIGURATION_MODE);
    // Imposta altre configurazioni specifiche qui
    CAN1_OperationModeSet(CAN_LOOPBACK_MODE);

    uint8_t messageData[8] = {0x15, 0x2A, 0x37, 0x4C, 0x5B, 0x6E, 0x7D, 0x8F};

    while (1) {
        // Send a CAN message
        //SendCANMessage(0x123, messageData, sizeof(messageData));
            // Check if a message has been received
            if (CAN1_ReceivedMessageCountGet() > 0) {
                CAN_MSG_OBJ receivedMsg;
                uint8_t receivedData[8];
                receivedMsg.data = receivedData;

                if (CAN1_Receive(&receivedMsg)) {
                    if (receivedMsg.msgId == 0x123) {
                        led3_Toggle();  // Turn on LED3 on receiving the message
                    } else {
                        led2_Toggle();   // Turn off LED3 if the ID doesn't match
                    }
                }
            }
            else{
                led2_Toggle();   // Turn off LED3 if the ID doesn't match

            }
        DELAY_milliseconds(1000);
    }
        
    return 0;
}

