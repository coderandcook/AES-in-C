#include <stdio.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "div_generic.h"
#include "SubBytes2.h"

#define TEST_EQUAL(x, y) if ((x) != (y)) printf("ERR " #x "!=" #y "\n");
#define TEST_ASSERT(x) if (!(x)) printf("ERR " #x "\n");
#define TEST_DIV_GENERIC(x) if(!(x)) printf("ERR " #x "\n");
#define TEST_MULPOLY(x) if(!(x)) printf("ERR" #x "\n");
#define TEST_CROSSMUL(x) if(!(x)) printf("ERR" #x "\n");


int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

void test_crossMul(){
	int exp[]= {1,0,0,0,1,1,1,0};
	int input[] = {1,1,0,0,1,0,1,0};
	int output[8]; clear(output);
	crossMul(input, output);

	TEST_CROSSMUL(isEqualPoly(output, exp));
}

void test_mulPoly(){
	int exp[] = {1,1,0,0,1,0,0,0};
	int poly1[] = {1,1,1,1,1,0,0,0};
	int poly2[] = {1,1,0,0,1,0,1,0};
	mulPoly(poly1, poly2);

	TEST_MULPOLY(isEqualPoly(poly1, exp));
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
	TEST_DIV_GENERIC(isEqualPoly(q, exp_q));
	TEST_DIV_GENERIC(isEqualPoly(remainder, exp_rem));

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
	TEST_EQUAL(add(3, 5), 3 + 5);
	TEST_EQUAL(sub(3, 5), 3 - 5);

	test_addPoly();
	test_div_generic();
	test_mulPoly();
	test_crossMul();
}
