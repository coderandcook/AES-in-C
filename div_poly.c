#include <stdio.h>
#include <math.h>
#include "div_generic.c"

/*
int main(){
  int i;

  int m[] = {1,0,0,0,1,1,0,1,1};
  int poly[] = {0,1,0,1,0,0,1,1};

  int q[8]; clear(q);
  int rem[8]; clear(rem);
  int q2[8]; clear(q2);
  int rem2[8]; clear(rem2);

  div_generic(m, 9, poly, q, rem);

  div(poly, rem, q2, rem2);

  printf("q: ");
  for(i=0; i<8; i++) printf("%d", q[i]);
  printf("\nrem: ");
  for(i=0; i<8; i++) printf("%d", rem[i]);

  printf("\nq2: ");
  for(i=0; i<8; i++) printf("%d", q2[i]);
  printf("\nrem2: ");
  for(i=0; i<8; i++) printf("%d", rem2[i]);

  printf("\n");

}
*/

//arrays are assumed to be length of 8
void div(int *dividend, int *divisor, int *q, int *remainder){
  div_generic(dividend, 8, divisor, q, remainder);
  /*
  int rDeg=0, dDeg=0, new_q=0;
  copy_generic(dividend, remainder, 8);
  rDeg = findDeg_generic(remainder, 8);
  dDeg = findDeg_generic(divisor, 8);
  while(rDeg>=dDeg){
    new_q = updateQ_generic(q, rDeg, dDeg);
    updateRemainder_generic(remainder, 8, remainder, divisor, new_q);
    rDeg = findDeg_generic(remainder, 8);
  }
  */
  //in the end, q and remainder is updated
}

void clear(int *poly){
  clear_generic(poly, 8);
}
//copies poly to poly2
void copy(int *poly, int *poly2){
  copy_generic(poly, poly2, 8);
}
int findDeg(int *poly){
  int result = findDeg_generic(poly, 8);
  return result;
}
//use new quotient from updateQ
void updateRemainder(int *remainder, int *divisor, int new_q){
  updateRemainder_generic(remainder, 8, remainder, divisor, new_q);
  /*
  int i,t;
  int temp[] = {0,0,0,0,0,0,0,0};
  //to make temp, shift divisor by degree of quotient
  for(i=0; i<8-new_q; i++){
    temp[i]=divisor[i+new_q];
  }
  for(i=0; i<8; i++){
    t = remainder[i]-temp[i];
    //change t
    if(t>=0) t=t%2;
    else if(t==-1) t=1;
    remainder[i]=t;
  }*/
}
void printPoly(int *binary){
  print_generic(binary, 8);
}
