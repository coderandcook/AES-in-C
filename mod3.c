//use array of struct for division data (dividend, divisor, q, remainder) for each division operation
//use the constructed array to make a, b, m, c
#include <stdio.h>
#include <math.h>
#include "div_poly.h"
#include "poly.h"
#include "div_generic.h"
#include "mod3.h"



void mod(const int *poly, int poly_size, int *res){
  //convert poly into length 15 array
  clear8(res);
  int temp[15]; clear_generic(temp,15);
  int rDeg,dDeg=8;
  int m[] = {1,0,0,0,1,1,0,1,1};
  int i;
  for(i=14; i>=15-poly_size; i--) temp[i] = poly[i-(15-poly_size)];

  rDeg = findDeg_generic(temp,15);
  //loop updateRem
  while(rDeg>=dDeg){
    updateRem3(temp,m,rDeg-dDeg);
    rDeg = findDeg_generic(temp,15);
  }
  //set res
  for(i=7; i>=0; i--){
    res[i] = temp[i+(14-7)];
  }
}



void byteToPoly(uint8_t x, int *poly){
  clear8(poly);
  int temp_x = x;
  //printf("temp_x = %d\n",temp_x);
  for(int i=0; i<8; i++){
    int t = pow(2,7-i)/1;
    poly[i] = temp_x/ t;
    temp_x -= t*poly[i];
  }
}
