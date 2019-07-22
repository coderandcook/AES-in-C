#include <stdlib.h>
#include <stdint.h>
#pragma once

struct key{
 uint8_t block[4][4];
};
struct Rcon{//represents a word
  uint8_t bytes[4];
};
struct word{
  uint8_t w[4];
};
struct expKey{
  //44 words that hold 4bytes each
  //struct word word[44];
  uint8_t wordList[44][4];
};

struct key *newKey();
void clearKey(struct key *k);
void setKey(struct key *k, const uint8_t *words);
struct expKey *newekey();
struct word *newWord();
void setWord(const struct key *key, int i, struct word *word);

struct Rcon* newRcon();
void setRcon(struct Rcon *rc);
void updateRcon(struct Rcon *rc);

void RotWord(uint8_t *words);
//void SubWord(struct word *word1, struct word *word2);
void SubWord(const uint8_t *word1, uint8_t *word2);
void SubRot(uint8_t *word1, uint8_t *word2, const struct Rcon *rc);

int isEqualWord(const uint8_t *word1, const uint8_t *word2);

void printekey(const struct expKey *ekey, int startRow, int endRow);
//generates expanded key
void KeyExpansion(const struct key *key, struct expKey *ekey);

void updateRcon_b(struct Rcon *rc);
void SubWord_b(uint8_t *x, uint8_t *y);
void SubRot_b(uint8_t *x, uint8_t *y, const struct Rcon *rc);
void KeyExpansion_b(const struct key *key, struct expKey *ekey);

struct key32{
  uint32_t block[4];
};
struct expKey32{
  uint32_t block[44];
};
//uint32_t Rcon;

uint32_t updateRcon32(uint32_t rc);
uint32_t RotWord_b2(uint32_t x);
//uint32_t SubWord_b2(uint32_t x);//SubBytes operation
//uint32_t SubRot_b2();
