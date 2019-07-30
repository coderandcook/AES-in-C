#pragma once
#include <stdlib.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"

int isEqualMessage(const uint8_t *x, const uint8_t *y);
void AddRoundKey32(struct state2 *s, const struct expKey32 *ekey, int i);
