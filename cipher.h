#pragma once
// inputs/outputs message as 4*4 bytes, input expkey(already expanded)
void cipher(const uint8_t *in, uint8_t *out, const struct expKey *ekey);
void cipher_b(const uint8_t *in, uint8_t *out, const struct expKey *ekey);
void cipher32(const uint32_t *in, uint32_t *out, struct expKey32 ekey);
void cipher32_b(const uint32_t *in, uint32_t *out, struct expKey32 ekey);
