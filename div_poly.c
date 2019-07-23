#include <stdio.h>
#include <math.h>
#include "div_poly.h"

#include "div_generic.h"

//arrays are assumed to be length of 8
void div8(const int *dividend, const int *divisor, int *q, int *remainder){
  div_generic(dividend, 8, divisor, q, remainder);
}

void clear8(int *poly){
  clear_generic(poly, 8);
}
//copies poly to poly2
void copy8(const int *src, int *dst){
  copy_generic(src, dst, 8);
}
/*
int findDeg(const int *poly){
  int result = findDeg_generic(poly, 8);
  return result;
}*/

//use new quotient from updateQ
/*
void updateRemainder(int *remainder, const int *divisor, int new_q){
  updateRemainder_generic(remainder, 8, remainder, divisor, new_q);
}
*/

/*
void printPoly(const int *poly){
  printPoly_generic(poly, 8);
}*/
