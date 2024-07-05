
#ifndef CAN_MESSAGES_H
#define CAN_MESSAGES_H

#include <stdint.h>

#define CAN_ID_Auto 291

typedef struct {
    uint8_t Speed;  // Start bit: 0, Length: 8 bits
    uint8_t rpm;  // Start bit: 8, Length: 8 bits
} CAN_Auto;

#endif // CAN_MESSAGES_H
