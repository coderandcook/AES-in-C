//use array of struct for division data (dividend, divisor, q, remainder) for each division operation
//use the constructed array to make a, b, m, c
#include <stdio.h>
#include <math.h>
#include "div_poly.c"
#include "poly.c"

//q is no longer in the signature
int mod(int *m, int *poly, int *inverse);

/*
int main(){
  int i;
  int m[] = {1,0,0,0,1,1,0,1,1};
  //test1 -> 11001010
  int poly[] = {0,1,0,1,0,0,1,1};
  int q[] = {0,0,0,0,0,0,0,0};
  int remainder[] = {0,0,0,0,0,0,0,0};
  int inverse[8]; clear(inverse);
  int result = 0;
  result = mod(m, poly, q, remainder, inverse);
  printf("result = %d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d",inverse[i]);
  printf("\n\n");

  //test2 -> 00011100
  int poly2[] = {1,1,1,1,1,1,1,1};
  clear(q); clear(remainder); clear(inverse); result = 0;
  result = mod(m, poly2, q, remainder, inverse);
  printf("result=%d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d",inverse[i]);
  printf("\n\n");

  //test3 -> 10001101
  int poly3[] = {0,0,0,0,0,0,1,0};
  clear(q); clear(remainder); clear(inverse); result = 0;
  result = mod(m, poly3, q, remainder, inverse);
  printf("result=%d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d",inverse[i]);
  printf("\n\n");

  //test4 -> 00000000
  int poly4[] = {0,0,0,0,0,0,0,0};
  clear(q); clear(remainder); clear(inverse); result = 0;
  result = mod(m, poly4, q, remainder, inverse);
  printf("result=%d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d", inverse[i]);
  printf("\n\n");

  //test5 -> 00000000
  int poly5[] = {0,0,0,0,0,0,0,1};
  clear(q); clear(remainder); clear(inverse); result = 0;
  result = mod(m, poly5, q, remainder, inverse);
  printf("result=%d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d", inverse[i]);
  printf("\n\n");

}*/

int mod(int *m, int *poly, int *inverse){
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

  polyInt = setInt(poly);
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
  remainderInt = setInt(arr[0].remainder);
  n++;

  while(remainderInt!=1){
    copy_generic(nextDivisor, arr[n].divisor, 8);
    copy_generic(nextDividend, arr[n].dividend, 8);
    clear(arr[n].q);
    div8(arr[n].dividend, arr[n].divisor, arr[n].q, arr[n].remainder);
    copy_generic(arr[n].divisor, nextDividend, 8);
    copy_generic(arr[n].remainder, nextDivisor, 8);
    remainderInt = setInt(arr[n].remainder);
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
    mulPoly(t, pre_b);
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

  result = setInt(b);
  return result;
}
