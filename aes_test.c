#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "div_generic.h"
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "MixColumns.h"
#include "AddRoundKey3.h"
#include "KeyExpansion.h"
#include "cipher.h"
#include "InvShiftRows.h"
#include "InvSubBytes.h"
#include "InvMixColumns.h"
#include "InvCipher.h"
#include "shifter.h"
#include "bit.h"

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




void test_assemble(){
	uint32_t a = 0x11223344;
	uint32_t a0 = a>>24;
	uint32_t a1 = a>>16;
	uint32_t a2 = a>>8;
	uint32_t a3 = a;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
	a = 0;
	a0 = a0<<24;
	a1 = a1<<16;
	a2 = a2<<8;
	//a3 = a3;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
	a = a0|a1|a2|a3;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
}

void test_cipher32b(){
	struct key32 key; clearKey32(&key);

	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	struct expKey32 ekey;
	KeyExpansion32(&key,&ekey);
	//printExpkey32(&ekey);

	uint32_t in[] = {0x328831e0, 0x435a3137, 0xf6309807, 0xa88da234};

	uint32_t out[4];
	cipher32(in,out,ekey);
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
}

void test_cipher32(){
	uint32_t in[4];
	uint32_t out[4];

	struct expKey32 ekey;

	int N = 1000;

	in[0] = 0x328831e0;
	in[1] = 0x435a3137;
	in[2] = 0xf6309807;
	in[3] = 0xa88da234;

	struct key32 key;
	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;
	KeyExpansion32(&key,&ekey);

	clock_t begin2 = clock();
	for(int i=0; i<N; i++)cipher32(in,out,ekey);
	clock_t end2 = clock();

	printf("\ncipher32(): %f usec\n", (end2-begin2)/(double)N/CLOCKS_PER_SEC*1e6);
	printf("out:\n");
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
}

void test_mulinv(){
	uint8_t x = 0xff;
	uint16_t m = 0x11b;

	x = mulInverse(x,m);
	printf("x = %x\n",x);
}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);


	printf("\n");
	test_cipher32();
	printf("\n");
	test_mulinv();

}
