#include <stdlib.h>
#include <stdint.h>
#pragma once

struct key32{
  uint32_t block[4];
};
struct expKey32{
  uint32_t block[44];
};
//uint32_t Rcon;
void clearEkey(struct expKey32 *ekey);
void setKey32(struct key32 *key, const uint8_t *keyarray);
void clearKey32(struct key32 *key);
void printKey32(struct key32 key);
void printExpkey32(struct expKey32 *ekey);

uint32_t updateRcon32(uint32_t rc);
uint32_t RotWord32(uint32_t x);
uint32_t SubWord32(uint32_t x);//SubBytes operation
uint32_t SubRot32(uint32_t x, uint32_t rc);

void KeyExpansion32(const struct key32 *key, struct expKey32 *ekey);

void transposeKey(struct key32 *key);
void transposeEkey(struct expKey32 *ekey);
