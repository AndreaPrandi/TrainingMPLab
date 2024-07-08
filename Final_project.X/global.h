#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>
#include <stdbool.h> // Aggiungi questa linea per definire il tipo 'bool'

// Variabile globale per i dati del messaggio CAN
extern uint8_t globalMessageData[8];
extern volatile uint8_t speed;
extern volatile uint8_t rpm;
extern volatile bool drawImageFlag;
extern volatile bool drawBertone;
extern uint8_t immaginebuffer[];
extern volatile bool drawExtImg;
extern volatile bool image_complete;
extern volatile uint8_t x_image;
extern volatile uint8_t y_image;
extern volatile uint16_t length;
extern volatile uint8_t height;
#define CAN_ID_AUTO 0x123
typedef struct {
    uint8_t Speed;
    uint8_t rpm;
} Auto_t;



#endif
