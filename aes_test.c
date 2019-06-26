#include <stdio.h>
#include "poly.h"

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
}
