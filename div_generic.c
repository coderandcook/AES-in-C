//division, assuming array length of 9 for m
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
void setPoly(struct state *s, int row, int col, int *poly){
  int i;
  uint8_t num = s->block[row][col];
  int t = 0;
  int temp;
  for(i=0; i<8; i++){
    temp = pow(2,i+1)/1;
    poly[7-i] = num%temp;
    num = num/temp;
  }
}


//take out an element from state, convert it to poly
uint8_t setByte(struct state *s, int row, int col){
  uint8_t result = s->block[row][col];
  return result;
}
//convert array of int (0 or 1) into uint8_t number
uint8_t getByte(int *poly){
  uint8_t result=0x00;
  int temp=0;
  int i;
  for(i=7; i>=0; i--){
    temp = pow(2,i)/1;
    result += poly[i]*temp;
  }
  return result;
}
*/

void copy_generic(int *poly, int *poly2, int size){
  int i;
  for(i=0; i<size; i++) poly2[i] = poly[i];
}
void clear_generic(int *poly, int size){
  int i;
  for(i=0; i<size; i++) poly[i] = 0;
}
void print_generic(int *poly, int size){
  int i;
  for(i=0; i<size; i++) printf("%d", poly[i]);
  printf("\n");
}
int findDeg_generic(int *poly, int size){
  int i;
  for(i=0; i<size; i++){
    if(poly[i]==1) return size-1-i;
  }
  return -1;
}
//updates quotient, and returns degree of added quotient
int updateQ_generic(int *quotient, int reDeg, int dDeg){
  int new_q = reDeg-dDeg;
  if(new_q<0) return -1;
  quotient[7-new_q]++;

  quotient[7-new_q] = quotient[7-new_q]%2;
  return new_q;
}

//assumes divisor length is less than 9
void updateRemainder_generic(int *remainder, int remainder_size, int *remainder_new, int *divisor, int new_q){
  int i, t;
  int temp[remainder_size]; clear_generic(temp, remainder_size);

  for(i=0; i<remainder_size-new_q; i++){//shift divisor by new_q to make temp
    temp[i]=divisor[i+new_q-(remainder_size-8)];
  }
  for(i=0; i<8; i++){//subtract temp from remainder
    t=remainder[i+(remainder_size-8)]-temp[i+(remainder_size-8)];
    if(t>=0) t = t%2;
    else if(t==-1) t=1;
    remainder_new[i]=t;
  }
}
//for any length of divisor, any length of remainder
void updateRemainder_generic2(int *remainder, int remainder_size, int *divisor, int divisor_size, int new_q, int *rem_new){
  int i,t;
  int temp[remainder_size]; clear_generic(temp,remainder_size);
  int diff = remainder_size-divisor_size;

  for(i=0; i<remainder_size-new_q; i++){
    temp[i] = divisor[i+new_q-diff];
  }
  for(i=0; i<remainder_size; i++){
    t = remainder[i]-temp[i];
    if(t>=0) t = t%2;
    else if(t==-1)t=1;
    remainder[i] = t;
  }

  for(i=7; i>=0; i--){
    rem_new[i] = remainder[i+remainder_size-1-7];
  }

}

//consider div() with divisor of length 9 ->mod
void div_generic(int *dividend, int dividend_size, int *divisor, int *q, int *remainder){
  int count=0;
  int rDeg=0, dDeg=0, new_q=0;
  int rem_temp[9]; clear_generic(rem_temp, 9);

  if(dividend_size==9){
    copy_generic(dividend, rem_temp, 9);
    rDeg = findDeg_generic(rem_temp, 9);
  }
  else{
    copy_generic(dividend, remainder, 8);
    rDeg = findDeg_generic(dividend, 8);
  }
  dDeg = findDeg_generic(divisor, 8);

  while(rDeg>=dDeg){
    new_q = updateQ_generic(q, rDeg, dDeg);
    if(rDeg==8 && count==0){
      updateRemainder_generic(rem_temp, 9, remainder, divisor, new_q);
    }
    else{
      updateRemainder_generic(remainder, 8, remainder, divisor, new_q);
    }
    rDeg = findDeg_generic(remainder, 8);
    count++;
  }
}
