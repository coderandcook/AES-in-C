#pragma once
int mulInverse(const int *m, const int *poly, int *inverse);
void mod(const int *poly, int poly_size, int *res);
int xtime(int *poly);

void byteToPoly(uint8_t x, int *poly);
//void polyToByte()
uint8_t mulInverse_b(uint8_t x);
