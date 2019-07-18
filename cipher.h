#pragma once
// inputs/outputs message as 4*4 bytes, input expkey(already expanded)
void cipher(const uint8_t *in, uint8_t *out, const struct expKey *ekey);
void cipher_b(const uint8_t *in, uint8_t *out, const struct expKey *ekey);
