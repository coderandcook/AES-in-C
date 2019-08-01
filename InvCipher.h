#pragma once
#include "ShiftRows2.h"

void invCipher32(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey);
//void invCipher32b(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey);
