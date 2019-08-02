#pragma once
#include "ShiftRows2.h"

void InvCipher(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey);
//void invCipher32b(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey);
