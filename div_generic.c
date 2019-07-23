//division, assuming array length of 9 for m
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "div_generic.h"

void clear_generic(int *poly, int size){
  int i;
  for(i=0; i<size; i++) poly[i] = 0;
}

//copy poly1 to poly2(accounts different sizes for poly1 and poly2)
void copy_generic2(const int *src, int src_size, int *dst, int dst_size){
  int diff;
  int i;

  clear_generic(dst,dst_size);
  if(src_size>=dst_size){
    diff = src_size-dst_size;
    for(i=src_size-1; i>=diff; i--) dst[i-diff]=src[i];
  }
  else{
    diff = dst_size-src_size;
    for(i=dst_size-1; i>=diff; i--) dst[i] = src[i-diff];
  }
}
void copy_generic(const int *src, int *dst, int size){
  copy_generic2(src,size,dst,size);
}

void printPoly_generic(const int *poly, int size){
  int i;
  for(i=0; i<size; i++) printf("%d", poly[i]);
  printf("\n");
}
int findDeg_generic(const int *poly, int size){
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
void updateRemainder_generic(const int *remainder, int remainder_size, int *remainder_new, const int *divisor, int new_q){
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
/*
//for any length of divisor, any length of remainder
void updateRemainder_generic2(int *remainder, int remainder_size, const int *divisor, int divisor_size, int new_q, int *rem_new){
  int i,t;
  int temp[remainder_size]; clear_generic(temp,remainder_size);
  int diff = remainder_size-divisor_size;
  //printf("diff: %d\nnew_q: %d\n",diff,new_q);

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
*/
void updateRem3(int *remainder, const int *divisor, int new_q){
  //make an empty rem array to store quotient*divisor
  int temp[15]; clear_generic(temp,15);
  int t=0;
  //shift divisor by new_q
  int i;
  for(i=14-new_q; i>=14-8-new_q; i--) temp[i] = divisor[i-(14-8-new_q)];

  for(i=0; i<15; i++){
    t = remainder[i]-temp[i];
    if(t==-1) remainder[i] = 1;
    else remainder[i] = t%2;
  }
}
//consider div() with divisor of length 9 ->mod
void div_generic(const int *dividend, int dividend_size, const int *divisor, int *q, int *remainder){
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
