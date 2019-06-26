//division, assuming array length of 9 for m
#include <stdio.h>
#include <math.h>

void copy_generic(int *poly, int *poly2, int size);
void clear_generic(int *poly, int size);
void print_generic(int *poly, int size);
int findDeg_generic(int *poly, int size);
int updateQ_generic(int *quotient, int reDeg, int dDeg);
void updateRemainder_generic(int *remainder, int remainder_size, int *remainder_new, int *divisor, int new_q);
void div_generic(int *dividend, int dividend_size, int *divisor, int *q, int *remainder);

/*
int main(){
  int i;
  int new_q = 0;
  int m[] = {1,0,0,0,1,1,0,1,1};
  int poly[] = {0,1,0,1,0,0,1,1};
  int q[8], remainder[8];
  clear_generic(q,8); clear_generic(remainder, 8);
  int dividend[8];
  clear_generic(dividend, 8);

  new_q = updateQ_generic(q,8,6);
  //updateRemainder_big(m, dividend, poly, new_q);
  updateRemainder_generic(m, 9, dividend, poly, new_q);
  printf("first updated remainder: ");
  for(i=0; i<8; i++) printf("%d", dividend[i]);
  printf("\n");
  new_q = updateQ_generic(q, 6, 6);
  updateRemainder_generic(dividend, 8, dividend, poly, new_q);

  printf("q: ");
  for(i=0; i<8; i++) printf("%d", q[i]);
  printf("\nnew remainder: ");
  for(i=0; i<8; i++) printf("%d", dividend[i]);
  printf("\n\n");

  int m2[] = {1,0,0,0,1,1,0,1,1};
  int poly2[] = {0,1,0,1,0,0,1,1};
  int q2[8], remainder2[8]; clear_generic(q2, 8); clear_generic(remainder2, 8);
  div_generic(m2, 9, poly2, q2, remainder2);
  printf("new remainder: ");
  for(i=0; i<8; i++) printf("%d", remainder2[i]);
  printf("\nnew quotient: ");
  for(i=0; i<8; i++) printf("%d", q2[i]);
  printf("\n\n");

  int dividend2[] = {0,0,0,0,0,1,0,0};
  int divisor[] = {0,0,0,0,0,0,1,1};
  int quotient[8]; clear_generic(quotient, 8);
  int rem[8]; clear_generic(rem, 8);
  div_generic(dividend2, 8, divisor, quotient, rem);
  printf("new remainder: ");
  for(i=0; i<8; i++) printf("%d", rem[i]);
  printf("\nnew quotient: ");
  for(i=0; i<8; i++) printf("%d", quotient[i]);//edit quotient part
  printf("\n\n");
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
  int i;
  int new_q = reDeg-dDeg;
  if(new_q<0) return -1;
  quotient[7-new_q]++;

  quotient[7-new_q] = quotient[7-new_q]%2;
  return new_q;
}


void updateRemainder_generic(int *remainder, int remainder_size, int *remainder_new, int *divisor, int new_q){
  int i, t;
  int temp[remainder_size]; clear_generic(temp, remainder_size);
  for(i=0; i<remainder_size-new_q; i++){
    temp[i]=divisor[i+new_q-(remainder_size-8)];
  }
  for(i=0; i<8; i++){
    t=remainder[i+(remainder_size-8)]-temp[i+(remainder_size-8)];
    if(t>=0) t = t%2;
    else if(t==-1) t=1;
    remainder_new[i]=t;
  }

}
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
