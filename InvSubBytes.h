#pragma once
#include <stdio.h>

uint8_t InvSubBytes_b(uint8_t x);
uint8_t InvSubBYtes_table(uint8_t x);
void InvSubState32(struct state2 *s);
