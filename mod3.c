//use array of struct for division data (dividend, divisor, q, remainder) for each division operation
//use the constructed array to make a, b, m, c
#include <stdio.h>
#include <math.h>
//#include "div_poly.c"
//#include "poly.c"
#include "div_poly.h"
#include "poly.h"
#include "div_generic.h"

//q is no longer in the signature
//sets inverse of 8bit poly
int mulInverse(const int *m, const int *poly, int *inverse){
  int polyInt = 0;
  int i, n=0;
  int nextDividend[8], nextDivisor[8];
  int remainderInt = 0;
  int a[8], b[8], mo[8], c[8], t[8];
  int pre_b[] = {0,0,0,0,0,0,0,1}, pre_c[] = {0,0,0,0,0,0,0,0};
  int result=0;
  struct div{//a set of dividend, divisor, quotient, remainder
    int m[9];
    int dividend[8];
    int divisor[8];
    int q[8];
    int remainder[8];
    //int num[4][8];
    //dividend, divisor, quotient, remainder
  };
  struct div arr[10];

  polyInt = getInt(poly);
  if(polyInt==0){
    copy_generic(poly, inverse, 8);
    return 0;
  }
  else if(polyInt==1){
    copy_generic(poly, inverse, 8);
    return 1;
  }



  for(i=0; i<10; i++) copy_generic(m, arr[i].m, 9);//for each arr[n].m copy m
  clear_generic(arr[0].q, 8);
  clear_generic(arr[0].remainder, 8);
  copy_generic(poly, arr[0].divisor, 8);
  //
  div_generic(arr[0].m, 9, arr[0].divisor, arr[0].q, arr[0].remainder);
  //div_big(arr[0].m, arr[0].divisor, arr[0].q, arr[0].remainder);
  copy_generic(arr[0].divisor, nextDividend, 8);
  copy_generic(arr[0].remainder, nextDivisor, 8);
  remainderInt = getInt(arr[0].remainder);
  n++;

  while(remainderInt!=1){
    copy_generic(nextDivisor, arr[n].divisor, 8);
    copy_generic(nextDividend, arr[n].dividend, 8);
    clear8(arr[n].q);
    div8(arr[n].dividend, arr[n].divisor, arr[n].q, arr[n].remainder);
    copy_generic(arr[n].divisor, nextDividend, 8);
    copy_generic(arr[n].remainder, nextDivisor, 8);
    remainderInt = getInt(arr[n].remainder);
    //printf("n=%d  remainder=%d\n", n, remainderInt);
    n++;
  }

  /*
  //debugging purpose
  for(i=0; i<10; i++){
    printf("n=%d\n", i);
    //dividend(ignore n=0 dividend)
    printf("dividend: ");
    for(k=0; k<8; k++) printf("%d", arr[i].dividend[k]);
    //divisor
    printf("\ndivisor: ");
    for(k=0; k<8; k++) printf("%d", arr[i].divisor[k]);
    //q
    printf("\nq: ");
    for(k=0; k<8; k++) printf("%d", arr[i].q[k]);
    //remainder
    printf("\nremainder: ");
    for(k=0; k<8; k++) printf("%d", arr[i].remainder[k]);
    printf("\n");
  }
  */
  n--;


  while(n>=0){
    //set a
    copy_generic(arr[n].divisor, a, 8);
    //set b
    copy_generic(arr[n].q, t, 8);
    //mulPoly(t, pre_b);
    mul2(t,pre_b);

    addPoly(t, pre_c);

    copy_generic(t, b, 8);
    //set mo
    copy_generic(arr[n].dividend, mo, 8);
    //set c
    copy_generic(pre_b, c, 8);

    //set pre_b and pre_c
    copy_generic(b, pre_b, 8);
    copy_generic(c, pre_c, 8);

    /*debugging purpose
    printf("n = %d\n", n);
    printf("a: ");
    for(i=0; i<8; i++) printf("%d", a[i]);
    printf("\nb: ");
    for(i=0; i<8; i++) printf("%d", b[i]);
    printf("\nmo: ");
    for(i=0; i<8; i++) printf("%d", mo[i]);
    printf("\nc: ");
    for(i=0; i<8; i++) printf("%d", c[i]);
    printf("\n\n");
    */

    n--;
  }
  for(i=0; i<8; i++) inverse[i] = b[i];

  result = getInt(b);

  return result;
}

/*
int mod(int *m, int *poly, int poly_size, int *byte){
  int new_q = 0, rDeg = 0, dDeg = 0, bValue=0;
  int i;

  rDeg = findDeg_generic(poly,poly_size);
  dDeg = findDeg_generic(m,9);
  new_q = rDeg - dDeg;

  //make it a loop
  //update remainder
  if(new_q>=0) updateRemainder_generic2(poly,poly_size, m,9,new_q,byte);
  else{
    //transfer result
    for(i=7; i>=0; i--) byte[i] = poly[i+poly_size-1-7];
  }

  bValue = getInt(byte);
  return bValue;
}
*/
void mod2(const int *poly, int poly_size, int *res){
  //convert poly into length 15 array
  int temp[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int i;
  int rDeg,dDeg=8;
  int m[] = {1,0,0,0,1,1,0,1,1};
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

/*
int mod8(int *poly, int poly_size, int *byte){
  int m[] = {1,0,0,0,1,1,0,1,1};
  return mod(m,poly,poly_size,byte);
}*/

int xtime(int *poly){
  int multiplier[] = {0,0,0,0,0,0,1,0};
  mul2(poly,multiplier);
  return getInt(poly);
}
