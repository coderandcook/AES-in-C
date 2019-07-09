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
void setKey(struct key *k, uint8_t *bytes);
struct expKey *newekey();
struct word *newWord();
void setWord(struct key *key, int i, struct word *word);

struct Rcon* newRcon();
void updateRcon(struct Rcon *rc);

void RotWord(uint8_t *bytes);
//void SubWord(struct word *word1, struct word *word2);
void SubWord(uint8_t *word1, uint8_t *word2);
void SubRot(uint8_t *word1, uint8_t *word2, struct Rcon *rc);

int isEqualWord(uint8_t *word1, uint8_t *word2);
//generates expanded key
void KeyExpansion(struct key *key, struct expKey *ekey);
