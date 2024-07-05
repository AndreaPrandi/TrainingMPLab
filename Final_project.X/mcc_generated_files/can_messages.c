
#include "can_messages.h"

void decode_CAN_Auto(CAN_Auto* msg, const uint8_t* data) {
    msg->Speed = (data[0] >> 0) & ((1 << 8) - 1);
    msg->rpm = (data[1] >> 0) & ((1 << 8) - 1);
}

void encode_CAN_Auto(const CAN_Auto* msg, uint8_t* data) {
    data[0] |= (msg->Speed & ((1 << 8) - 1)) << 0;
    data[1] |= (msg->rpm & ((1 << 8) - 1)) << 0;
}

