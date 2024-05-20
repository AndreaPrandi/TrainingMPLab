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
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/tmr2.h"

/*
                         Main application
 */
int main(void)
{
    float Variabile_prova;
    extern uint16_t dutyCycle; 
    Variabile_prova=dutyCycle;
    dutyCycle=52;

    // initialize the device
    SYSTEM_Initialize();
    led1_SetLow();
    
    led2_SetHigh();
    led3_SetHigh();
    int adcResult =0; 
    int adcResultPercentage=0;
    float potenza_led=0;
    // Inizializza il Timer
    // Avvia il Timer
    TMR2_Start(); 
    while (1) 
    {
       
       
      
       
        ADC1_ChannelSelect(channel_AN19);
        
        ADC1_SoftwareTriggerEnable();  // Comincia a campionare
        DELAY_milliseconds(100);
        ADC1_SoftwareTriggerDisable(); // Termina il campionamento e inizia la conversione
        
        while (!ADC1_IsConversionComplete(channel_AN19));
        
        potenza_led=ADC1_ConversionResultGet(channel_AN19);
        
        
        
        adcResultPercentage=(int)((potenza_led/1023)*100);
         
        dutyCycle=adcResultPercentage;
        Variabile_prova=dutyCycle;
        
        
        
        
        
        // Resetta tutti i LED prima di impostarne uno specifico
       // led3_SetHigh();  // Imposta alto solo il LED 3 se adcResult > 80
       // DELAY_milliseconds(10);
        //led3_SetLow();
        //DELAY_milliseconds(30);
        
        
         /*
        if (adcResultPercentage > 80) {
            led1_SetLow();
            led2_SetLow();
            led3_SetHigh();  // Imposta alto solo il LED 3 se adcResult > 80
        } else if ( adcResultPercentage> 50) {
            led1_SetLow();
            led3_SetLow();
            led2_SetHigh();
        } else if (adcResultPercentage > 10) {
            led3_SetLow();
            led2_SetLow();
            led1_SetHigh();
        }
           */ 
        // Aggiungi un piccolo ritardo (esempio per XC16/ XC32)
        
          
       // DELAY_milliseconds(500);
    }
    return 1; 
}
/**
 End of File
*/

