#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "div_generic.h"
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "MixColumns.h"

#define TEST_EQUAL(x, y) if ((x) != (y)) printf("ERR " #x "!=" #y "\n");
#define TEST_ASSERT(x) if (!(x)) printf("ERR " #x "\n");
int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}


void test_mixcolumns(){
	uint8_t column[4];
	struct state* s1=newState();
	s1->block[0][0] = 0x00;
	s1->block[0][1] = 0x02;
	s1->block[0][2] = 0x04;
	s1->block[0][3] = 0x06;

	s1->block[1][0] = 0x02;
	s1->block[1][1] = 0x04;
	s1->block[1][2] = 0x06;
	s1->block[1][3] = 0x00;

	s1->block[2][0] = 0x04;
	s1->block[2][1] = 0x06;
	s1->block[2][2] = 0x00;
	s1->block[2][3] = 0x02;

	s1->block[3][0] = 0x06;
	s1->block[3][1] = 0x00;
	s1->block[3][2] = 0x02;
	s1->block[3][3] = 0x04;

	setColumns(s1,0,column);
}

void test_shiftrows(){

	struct state* s1 = newState();
	s1->block[0][0] = 0x00;
	s1->block[0][1] = 0x02;
	s1->block[0][2] = 0x04;
	s1->block[0][3] = 0x06;

	s1->block[1][0] = 0x02;
	s1->block[1][1] = 0x04;
	s1->block[1][2] = 0x06;
	s1->block[1][3] = 0x00;

	s1->block[2][0] = 0x04;
	s1->block[2][1] = 0x06;
	s1->block[2][2] = 0x00;
	s1->block[2][3] = 0x02;

	s1->block[3][0] = 0x06;
	s1->block[3][1] = 0x00;
	s1->block[3][2] = 0x02;
	s1->block[3][3] = 0x04;

	struct state* s2 = newState();
	s2->block[0][0] = 0x00;
	s2->block[0][1] = 0x02;
	s2->block[0][2] = 0x04;
	s2->block[0][3] = 0x06;

	s2->block[1][0] = 0x00;
	s2->block[1][1] = 0x02;
	s2->block[1][2] = 0x04;
	s2->block[1][3] = 0x06;

	s2->block[2][0] = 0x00;
	s2->block[2][1] = 0x02;
	s2->block[2][2] = 0x04;
	s2->block[2][3] = 0x06;

	s2->block[3][0] = 0x00;
	s2->block[3][1] = 0x02;
	s2->block[3][2] = 0x04;
	s2->block[3][3] = 0x06;

	ShiftRows(s2);

	TEST_ASSERT(isEqualState(s1, s2));
}

void test_SubBytes(){
	int exp2[] = {0,0,0,1,0,0,0,1};
	int input[] = {1,1,1,0,0,0,1,1};
	int res[8]; clear(res);
	SubBytes(input, res);
	TEST_ASSERT(isEqualPoly(res, exp2));
}


void test_crossMul(){
	int exp[]= {1,0,0,0,1,1,1,0};
	int input[] = {1,1,0,0,1,0,1,0};
	int multiplier[] = {1,1,1,1,1,0,0,0};
	int output[8]; clear(output);
	crossMul(input, multiplier, output);

	TEST_ASSERT(isEqualPoly(output, exp));
}

void test_div_generic(){
	int m[] = {1,0,0,0,1,1,0,1,1};
	int poly[] = {0,1,0,1,0,0,1,1};
	int remainder[8]; clear(remainder);
	int q[8]; clear(q);
	//int dividend[8]; clear(dividend);

	int exp_q[] = {0,0,0,0,0,1,0,1};
	int exp_rem[] = {0,0,0,0,0,1,0,0};
	div_generic(m, 9, poly, q, remainder);
	//clear(q);
	TEST_ASSERT(isEqualPoly(q, exp_q));
	TEST_ASSERT(isEqualPoly(remainder, exp_rem));

}
void test_mul(){
	int exp[] = {1,1,0,0,1,0,0,1};
	int poly1[] = {0,0,1,1,1,1,0,1};
	int poly2[] = {0,0,0,0,0,1,0,1};
	mulPoly(poly1, poly2);
	TEST_ASSERT(isEqualPoly(poly1, exp));
}


void test_addPoly(){
	int poly1[] = {0,0,0,1,0,1,0,0};
	int poly2[] = {0,0,1,0,1,0,0,0};
	int expected[] = {0,0,1,1,1,1,0,0};
	addPoly(poly1, poly2);
	TEST_ASSERT(isEqualPoly(poly1, expected));
}

int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);
	//test_shiftrows();

	test_mixcolumns();
}
