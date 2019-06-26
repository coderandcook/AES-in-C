#include <stdio.h>

#define TEST_EQUAL(x, y) if ((x) != (y)) printf("ERR " #x "!=" #y "\n");

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int main()
{
	TEST_EQUAL(add(3, 5), 3 + 5);
	TEST_EQUAL(sub(3, 5), 3 - 5);
}
