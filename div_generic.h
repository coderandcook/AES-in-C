#include <stdlib.h>
//void setByte(int *poly, uint8_t byte);
//uint8_t getByte(int *poly);

void copy_generic(const int *poly, int *poly2, int size);
void clear_generic(int *poly, int size);
void copy_generic2(const int *poly1, int poly1_size, int *poly2, int poly2_size);
void print_generic(const int *poly, int size);
int findDeg_generic(const int *poly, int size);
int updateQ_generic(int *quotient, const int reDeg, const int dDeg);
void updateRemainder_generic(const int *remainder, int remainder_size, int *remainder_new, const int *divisor, int new_q);
void updateRemainder_generic2(int *remainder, int remainder_size, const int *divisor, int divisor_size, int new_q, int *rem_new);
void updateRem3(int *remainder, const int *divisor, int new_q);
void div_generic(const int *dividend, int dividend_size, const int *divisor, int *q, int *remainder);
//void div_generic2(int *dividend,int dividend_size,int *q,int *remainder);
