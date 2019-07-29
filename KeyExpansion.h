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
void setKey2(struct key *k, const uint8_t *keyarray);

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
void clearEkey(struct expKey32 *ekey);
void setKey32(struct key32 *key, const uint8_t *keyarray);
void clearKey32(struct key32 *key);
void printKey32(struct key32 key);
void printExpkey32(struct expKey32 ekey);

uint32_t updateRcon32(uint32_t rc);
uint32_t RotWord32(uint32_t x);
uint32_t SubWord32(uint32_t x);//SubBytes operation
uint32_t SubRot32(uint32_t x, uint32_t rc);



union u32{
  uint32_t x[4];
  uint8_t b[4][4];
  uint8_t b2[16];
};
int isSmallEndian(struct key key);
void setU32(union u32 *u, struct key key);
void clearU32(union u32 *u);
void transEkey(struct key key, struct expKey ekey,struct expKey32 *ekey2);
//void KeyExpansion_b2(struct key key, struct expKey32 *ekey);
void KeyExpansion32(const struct key32 *key, struct expKey32 *ekey);
void KeyExpansion32_pre(struct key32 key, struct expKey32 *ekey);

void copyByte();


void transposeKey(struct key32 *key);
void transposeEkey(struct expKey32 *ekey);
