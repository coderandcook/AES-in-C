#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#pragma once

struct key32{
  uint32_t block[4];
};
struct expKey32{
  uint32_t block[44];
};

int isEqualState(const struct state2 *s1, const struct state2 *s2);
int isEqualEkey(const struct expKey32 *ekey1, const struct expKey32 *ekey2);
int isEqualBlock(const uint32_t *x1, const uint32_t *x2);

void clearEkey(struct expKey32 *ekey);
void clearKey32(struct key32 *key);

uint32_t updateRcon(uint32_t rc);
uint32_t RotWord32(uint32_t x);
uint32_t SubWord32(uint32_t x);

void transposeEkey(struct expKey32 *ekey);

void KeyExpansion(const struct key32 *key, struct expKey32 *ekey);

void printKey(struct key32 *key);
void printExpkey(struct expKey32 *ekey);
//uint32_t SubWord32b(uint32_t x);
//uint32_t SubRot32(uint32_t x, uint32_t rc);
//void transposeKey(struct key32 *key);
