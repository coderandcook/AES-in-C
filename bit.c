#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit.h"

//division by shifts

uint8_t add_bit8(uint8_t x, uint8_t y){//addition for SubBytes, InvSubBytes
  return x^y;
}
uint32_t add_bit32(uint32_t x, uint32_t y){
  return x^y;
}
uint16_t sub_bit16(uint16_t x, uint16_t y){
  return x^y;
}
uint32_t sub_bit32(uint32_t x, uint32_t y){
  return x^y;
}
int find_deg16(uint16_t x){
  int count=0;
  while(x>0){
    x = x>>1;
    count++;
  }
  if(count<1) return count;
  return count-1;
}

uint8_t mod_bit(uint16_t x){

  uint16_t m = 0x011b;
  while(x>0xff){
    //uint16_t temp = x;
    int deg_x = find_deg16(x);
    int deg_m = find_deg16(m);
    while(deg_x>deg_m){//to reach the same degree
      m = m<<1;
      deg_m = find_deg16(m);
    }
    x = sub_bit16(x,m);
    m = 0x011b;
  }
  return x;
}

uint8_t sub_bit2(uint8_t x, uint8_t y){
  uint8_t res=0;
  uint8_t t_x = x;
  uint8_t t_y = y;
  int c=0;
  //uint8_t prev_x=0;
  while(t_x>0){
    uint8_t temp = 0;
    if((t_x&1)==0 && (t_y&1)==1){
      uint8_t prev_x = t_x;
      int count=0;
      while((prev_x&1)==0){
        prev_x = prev_x>>1;
        count++;
      }
      prev_x &=0;
      while(count>0){
        prev_x = prev_x<<1;
        if(count>1)prev_x ^=1;
        count--;
      }
      t_x = prev_x;
      temp = 1;
    }
    else{
      temp = (t_x&1)^(t_y&1);
    }
    res ^= temp<<c;
    c++;
    t_y = t_y>>1;
    t_x = t_x>>1;
  }
  return res;
}

uint8_t xtime(uint8_t x){
  uint16_t t = x<<1;
  if(t&0x100) t^=0x11b;
  return t;
}

uint8_t mul(uint8_t x, uint8_t y){
  uint8_t final = 0;
  //start from 0th digit in x
  for(int i=0; i<8; i++){
    uint8_t ty = y;//for each 1 in x, shift ty and add
    if((x>>i)&1){//shift ty
      for(int k=0; k<i; k++) ty = xtime(ty);
      final ^= ty;
    }
  }
  return final;
}

int isEqual8(uint8_t x, uint8_t y){
  return x==y;
}

int findDeg(uint16_t a){
  for(int i=0; i<16; i++){
    uint8_t temp = a>>(15-i);
    if(temp==1) return 15-i;
  }
  return 0;
}
uint8_t div2(uint8_t divisor, uint16_t dividend, uint8_t *remainder){//returns quotient
  int deg0 = findDeg(dividend);
  int deg1 = findDeg(divisor);
  int q=0;
  while(deg1<=deg0){
    //printf("deg0-deg1 = %d    dividend = %x\n",deg0-deg1,dividend);
    *remainder = dividend^(divisor<<(deg0-deg1));
    dividend = *remainder;
    q ^= 1<<(deg0-deg1);
    deg0 = findDeg(dividend);
  }
  return q;
}

uint8_t mulInverse(uint8_t a, uint16_t m){// m = 0x11b;
  if(a==0 || a==1) return a;
  uint8_t q = 0;
  uint8_t remainder = 0;
  uint8_t aux[10] = {0};
  aux[0] = 0; aux[1] = 1;
  int count=2;

  while(remainder!=1){
    q = div2(a,m,&remainder);
    //printf("remainder = %x\n",remainder);

    m = a;
    a = remainder;
    aux[count] = mul(q,aux[count-1])^aux[count-2];
    //printf("aux[%d] = %x  q*aux[%d] = %x   aux[%d] = %x\n\n",count,aux[count],count-1,q*aux[count-1],count-2,aux[count-2]);
    count++;
  }
  return aux[count-1];
}
