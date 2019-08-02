#pragma once
#include <stdio.h>

//uint8_t InvSubBytes_b(uint8_t x);
//uint8_t InvSubBytes_table(uint8_t x);
uint32_t InvSubWord32(uint32_t x);
//uint32_t InvSubWord32b(uint32_t x);

void InvSubBytes(struct state2 *s);
