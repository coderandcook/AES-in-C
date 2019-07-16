#include <stdio.h>
#include <stdlib.h>

uint8_t add_bit(uint8_t x, uint8_t y){
  return x^y;
}
uint16_t sub_bit(uint16_t x, uint16_t y){
  return x^y;
}
int find_deg(uint16_t x){
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
    int deg_x = find_deg(x);
    int deg_m = find_deg(m);
    while(deg_x>deg_m){//to reach the same degree
      m = m<<1;
      deg_m = find_deg(m);
    }

    x = sub_bit(x,m);
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

//come back after editing mod_bit
uint8_t mul_bit(uint8_t x, uint8_t y){
  uint16_t res=0;
  uint8_t t_x = x;
  uint16_t t_y = y;

  while(t_x>0){
    if((t_x&1)==1) res^=t_y;
    t_x = t_x>>1;
    t_y = t_y<<1;
  }
  printf("res2 = %x\n",res);

  return mod_bit(res);
}



int isEqualW(uint8_t x, uint8_t y){
  return x==y;
}
