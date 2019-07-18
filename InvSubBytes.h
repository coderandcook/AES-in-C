#pragma once
#include <stdio.h>

int InvSubBytes(const int *input, int *output);
void InvSubState(const struct state *input, struct state *output);

uint8_t InvSubBytes_b(uint8_t x);
void InvSubState_b(struct state *input, struct state *output);
