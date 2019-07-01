#include <stdio.h>
#include "KeyExpansion.h"

struct Rcon* newRcon(){
  struct Rcon* rc = (struct Rcon*)malloc(sizeof(struct Rcon));
  int i;
  for(i=0; i<4; i++) rc->byte[i] = 0;
  return rc;
}

void updateRcon(struct Rcon *rc, int i, int Nk){
  //uint8_t temp=Nk;
  uint8_t temp = i/Nk;
  rc->byte[0] = temp;

}
