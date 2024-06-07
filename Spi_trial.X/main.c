#include "mcc_generated_files/system.h"
#include "C:\Users\aprandi\Desktop\SSD1322_OLED_library-master\SSD1322_OLED_lib\SSD1322_API.h"
#include "C:\Users\aprandi\Desktop\SSD1322_OLED_library-master\SSD1322_OLED_lib\SSD1322_GFX.h"
#include "mcc_generated_files/delay.h"
#include  "FreeMono12pt7b.h"
#include "mcc_generated_files/pin_manager.h"
#include "tom_and_jerry.h"
#include "gb110256x56.h"
#include "Bertone256x35.h"
/*
                         Main application
 */
int main(void)
{

   SYSTEM_Initialize();
  
    // Inizializzazione del display SSD1322
    SSD1322_API_init();
    //select_font(&FreeMono12pt7b);
    // Buffer per il frame buffer del display
    uint8_t frame_buffer[8192] = {0};

    // Riempire il buffer con il colore nero (tutti i pixel spenti)
   
    // Ciclo infinito
    while (1)
    {
        
        fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, gb110256x56, 0, 0, 256,56 );
        send_buffer_to_OLED(frame_buffer, 0, 0);
        DELAY_milliseconds(5000);
        fill_buffer(frame_buffer, 0x00);
        draw_bitmap_4bpp(frame_buffer, bertone256x35, 0, 0, 256,35 );
        send_buffer_to_OLED(frame_buffer, 0, 0); 
        DELAY_milliseconds(5000);
        led1_Toggle();
        // Disegnare alcune forme di base sul buffer
        fill_buffer(frame_buffer, 0x00);
        draw_rect(frame_buffer, 10, 10, 100, 50, 0x0F);  // Rettangolo
       //draw_line(frame_buffer, 10, 10, 100, 50, 0x0F);  // Linea diagonale
        //draw_circle(frame_buffer, 60, 30, 20, 0x0F);     // Cerchio
        draw_text(frame_buffer, "Ciao Mondo", 10, 20, 0x0F);
        // Inviare il buffer al display OLED
        // now let's try to write some text with a font
		// first thing to do is font selection
		select_font(&FreeMono12pt7b);
		// now text will we written with that font
		draw_text(frame_buffer, "ciao mondo", 100, 50, 15);
		// send a frame buffer to the display
		
        led2_Toggle();
        send_buffer_to_OLED(frame_buffer, 0, 0);
        // Aggiungi qui il codice principale del stuo programma
        DELAY_milliseconds(5000);
          led3_Toggle();
    }

    return 1;
}
