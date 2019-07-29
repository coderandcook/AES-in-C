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


void test_cipher(){
	//int i,k;
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key,keyarray);
	//first four words must be the same as first four in key
	KeyExpansion(key, ekey);
	printekey(ekey,0,43);

	uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	//uint8_t in[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

	uint8_t out[16]; //clear_generic(out,16);
	uint8_t out2[16];

	cipher(in,out,ekey);
	int i;
	for(i=0; i<16; i++) printf("%x ",out[i]);
	printf("\n");

	invCipher(out,out2,ekey);
	printf("inv: ");
	for(i=0; i<16; i++) printf("%x ",out2[i]);
	printf("\n");
}


void bench_mark(){
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key,keyarray);
	//first four words must be the same as first four in key
	KeyExpansion(key, ekey);
	//printekey(ekey,0,43);

	uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	//uint8_t in[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

	uint8_t out[16],final[16];

	int N = 1000;
	clock_t begin = clock();
	for(int i=0; i<N; i++){
		cipher(in,out,ekey);
	}
	clock_t end = clock();
	printf("cipher(): %f usec\n", (end-begin)/(double)N/CLOCKS_PER_SEC*1e6);

	clock_t b = clock();
	for(int i=0; i<N; i++)invCipher(out,final,ekey);
	clock_t e = clock();
	printf("invCipher(): %f usec\n", (e-b)/(double)N/CLOCKS_PER_SEC*1e6);



	struct key *key2 = newKey(); //clearKey(key2);
	struct expKey *ekey2 = newekey();

	uint8_t keyarray2[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key2,keyarray2);
	KeyExpansion_b(key2, ekey2);

	uint8_t in2[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	uint8_t out2[16], final2[16];

	clock_t begin2 = clock();
	for(int i=0; i<N; i++)cipher_b(in2,out2,ekey2);
	clock_t end2 = clock();
	printf("cipher_b(): %f usec\n", (end2-begin2)/(double)N/CLOCKS_PER_SEC*1e6);

	clock_t b2 = clock();
	for(int i=0; i<N; i++)invCipher_b(out2,final2,ekey2);
	clock_t e2 = clock();
	printf("invCipher_b(): %f usec\n", (e2-b2)/(double)N/CLOCKS_PER_SEC*1e6);


}

void test_cipher2(){
	uint8_t keyarray1[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	uint8_t input1[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	uint8_t output1[16]; uint8_t temp_output1[16];

	uint8_t keyarray2[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	uint8_t input2[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	uint8_t output2[16]; uint8_t temp_output2[16];

	struct key *key1 = newKey(); setKey(key1,keyarray1);
	struct expKey *ekey1 = newekey(); KeyExpansion(key1,ekey1);
	cipher(input1,temp_output1,ekey1);
	uint8_t exp1[] = {0x39,0x25,0x84,0x1d,0x02,0xdc,0x09,0xfb,0xdc,0x11,0x85,0x97,0x19,0x6a,0x0b,0x32};

	TEST_ASSERT(isEqualMessage(exp1,temp_output1));
	/*
	int i;
	for(i=0; i<16; i++) printf("%x ",temp_output1[i]);
	printf("\n");*/
	invCipher(temp_output1,output1,ekey1);
	uint8_t exp2[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	TEST_ASSERT(isEqualMessage(exp2,output1));
	/*
	for(i=0; i<16; i++) printf("%x ",output1[i]);
	printf("\n");*/

	struct key *key2 = newKey(); setKey(key2,keyarray2);
	struct expKey *ekey2 = newekey(); KeyExpansion(key2,ekey2);
	cipher(input2,temp_output2,ekey2);
	uint8_t exp3[] = {0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a};
	TEST_ASSERT(isEqualMessage(exp3,temp_output2));
	/*
	for(i=0; i<16; i++) printf("%x ",temp_output2[i]);
	printf("\n");*/
	invCipher(temp_output2,output2,ekey2);
	uint8_t exp4[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	TEST_ASSERT(isEqualMessage(exp4,output2));
	/*
	for(i=0; i<16; i++) printf("%x ",output2[i]);
	printf("\n");*/
}

void test_sb(){
	int x[] = {1,1,1,0,1,1,1,1};
	int y[8]; clear8(y);
	SubBytes(x,y);
	for(int i=0; i<8; i++) printf("%d",y[i]);
	printf("\n\n");

	uint8_t test = 0x02;
	test = mulInverse_b(test);
	printf("test = %x\n\n\n",test);

	uint8_t x1 = 0xf8, y1 = 0xca;
	x1 = crossMul_b(y1,x1);
	printf("final result = %x\n\n\n",x1);

	uint8_t x2 = 0xa9;
	x2 = SubBytes_b(x2);
	printf("sb result: %x\n\n",x2);



	struct state s; clearState(&s);
	setState(0,0,0x19,&s);
	setState(0,1,0xa0,&s);
	setState(0,2,0x9a,&s);
	setState(0,3,0xe9,&s);

	setState(1,0,0x3d,&s);
	setState(1,1,0xf4,&s);
	setState(1,2,0xc6,&s);
	setState(1,3,0xf8,&s);

	setState(2,0,0xe3,&s);
	setState(2,1,0xe2,&s);
	setState(2,2,0x8d,&s);
	setState(2,3,0x48,&s);

	setState(3,0,0xbe,&s);
	setState(3,1,0x2b,&s);
	setState(3,2,0x2a,&s);
	setState(3,3,0x08,&s);

	printState(&s); printf("\n");


	struct state s2; clearState(&s2);
	SubState_b(&s,&s2);
	printState(&s2);
	printf("\n");

	ShiftRows2(&s2); printf("after ShiftRows2:\n");
	printState(&s2);
	printf("\n");

	MixColumns_b(&s2);
	printState(&s2);
	printf("\n");
}

void test_ke2(){
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key,keyarray);
	//first four words must be the same as first four in key
	KeyExpansion_b(key, ekey);
	printekey(ekey,0,43);
}
void test_c(){
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key,keyarray);
	KeyExpansion(key, ekey);
	//printekey(ekey,0,43);

	uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	//uint8_t in[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

	uint8_t out[16];
	cipher_b(in,out,ekey);


	struct key *key2 = newKey();
	struct expKey *ekey2 = newekey();

	uint8_t keyarray2[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key2,keyarray2);
	KeyExpansion(key2, ekey2);


	uint8_t in2[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	uint8_t out2[16];
	cipher_b(in2,out2,ekey2);
}

void test_invsb(){
	uint8_t x = 0xc5;
	uint8_t res = InvSubBytes_b(x);
	printf("res = %x\n",res);

	struct state s; clearState(&s);
	setState(0,0,0x7a,&s);
	setState(0,1,0x89,&s);
	setState(0,2,0x2b,&s);
	setState(0,3,0x3d,&s);

	setState(1,0,0x9f,&s);
	setState(1,1,0xd5,&s);
	setState(1,2,0xef,&s);
	setState(1,3,0xca,&s);

	setState(2,0,0x10,&s);
	setState(2,1,0xf5,&s);
	setState(2,2,0xfd,&s);
	setState(2,3,0x4e,&s);

	setState(3,0,0x27,&s);
	setState(3,1,0x0b,&s);
	setState(3,2,0x9f,&s);
	setState(3,3,0xa7,&s);

	printState(&s);printf("\n\n");

	struct state s2; clearState(&s2);
	InvSubState_b(&s,&s2);
	printState(&s2);




	clearState(&s);
	setState(0,0,0x7a,&s);
	setState(0,1,0x89,&s);
	setState(0,2,0x2b,&s);
	setState(0,3,0x3d,&s);

	setState(1,0,0xd5,&s);
	setState(1,1,0xef,&s);
	setState(1,2,0xca,&s);
	setState(1,3,0x9f,&s);

	setState(2,0,0xfd,&s);
	setState(2,1,0x4e,&s);
	setState(2,2,0x10,&s);
	setState(2,3,0xf5,&s);

	setState(3,0,0xa7,&s);
	setState(3,1,0x27,&s);
	setState(3,2,0x0b,&s);
	setState(3,3,0x9f,&s);

	InvShiftRows2(&s);
	printState(&s);

	printf("\n");
	clearState(&s);
	setState(0,0,0x7a,&s);
	setState(0,1,0x89,&s);
	setState(0,2,0x2b,&s);
	setState(0,3,0x3d,&s);

	setState(1,0,0xd5,&s);
	setState(1,1,0xef,&s);
	setState(1,2,0xca,&s);
	setState(1,3,0x9f,&s);

	setState(2,0,0xfd,&s);
	setState(2,1,0x4e,&s);
	setState(2,2,0x10,&s);
	setState(2,3,0xf5,&s);

	setState(3,0,0xa7,&s);
	setState(3,1,0x27,&s);
	setState(3,2,0x0b,&s);
	setState(3,3,0x9f,&s);

	InvMixColumns_b(&s);
	printState(&s);
}
void test_shifter(){
	uint32_t x = 0xffcc0000; //0xff 0xcc 0x00 0x00
	int num = 3;
	x = rshift32(x,num);
	printf("x = %x\n",x); //0xcc 0x00 0x00 0xff
}

void test_sr32(){
	struct state2 s; clearState2(&s);
	s.block[0] = 0xaabbccdd;
	s.block[1] = 0xaabbccdd;
	s.block[2] = 0xaabbccdd;
	s.block[3] = 0xaabbccdd;
	printState32(s);

	ShiftRows32(&s);
	printf("\n");
	printState32(s);
}

void test_ke32(){
	uint32_t rc = 0x80000000;
	rc = updateRcon32(rc);
	printf("rc = %x\n",rc);
	rc = updateRcon32(rc);
	printf("rc = %x\n",rc);


	uint32_t rtest = 0x09cf4f3c;
	rtest = RotWord32(rtest);
	printf("rtest = %x\n",rtest);


	uint32_t sw_test = 0xcf4f3c09;
	sw_test = SubWord32(sw_test);
	printf("sw_test = %x\n",sw_test);

	uint32_t t = 0x2a6c7605; rc = 0x02000000;
	t = SubRot32(t,rc);
	printf("t = %x\n\n",t);



}


void test_ke8(){
	struct key key; clearKey(&key);
	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(&key,keyarray);
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",key.block[i][k]);
		printf("\n");
	}printf("\n");


	union u32 u;
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) u.b[i][k] = key.block[i][k];
	}
	printf("now for small endian:\n");
	for(int i=0; i<4; i++) printf("%x\n",u.x[i]);

	union u32 u2;
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) u2.b[i][k] = key.block[i][3-k];
	}
	printf("\nnow for big endian (x):\n");
	for(int i=0; i<4; i++) printf("%x\n",u2.x[i]);
	printf("\nb:\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",u2.b[i][k]);
		printf("\n");
	}
}


void test_ke(){
	/*
	struct key key;
	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};

	setKey2(&key,keyarray);
	struct expKey32 ekey;
	//KeyExpansion_b2(key,&ekey);

	struct expKey ekey0;
	struct key key0;
	setKey(&key0,keyarray);
	KeyExpansion(&key0,&ekey0);
	//printekey(&ekey0,0,43);
	struct expKey32 ekey32;
	transEkey(key0,ekey0,&ekey32);
	for(int i=0; i<44; i++)printf("%x\n",ekey32.block[i]);

	printf("\n");
	KeyExpansion_b2(key0,&ekey);
	printf("\n");
	*/

	union u32 u; clearU32(&u);
	u.x[0] = 0x00112233;
	u.x[1] = 0x44556677;
	u.x[2] = 0x8899aabb;
	u.x[3] = 0xccddeeff;

	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",u.b[i][k]);
		printf("\n");
	}printf("\n");

	clearU32(&u);
	u.x[0] = htonl(0x00112233);
	u.x[1] = htonl(0x44556677);
	u.x[2] = htonl(0x8899aabb);
	u.x[3] = htonl(0xccddeeff);
	printf("htonl on u.x:\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",u.b[i][k]);
		printf("\n");
	}printf("\n");


	clearU32(&u);
	struct key key; clearKey(&key);
	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(&key,keyarray);
	printf("using setKey:\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",key.block[i][k]);
		printf("\n");
	}printf("\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) u.b[i][k] = key.block[i][k];
	}
	printf("x with setKey:\n");
	for(int i=0; i<4; i++) printf("%x\n",u.x[i]);
	printf("\n");

	clearU32(&u);
	setKey2(&key,keyarray);
	printf("using setKey2:\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) printf("%x ",key.block[i][k]);
		printf("\n");
	}printf("\n");
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++) u.b[i][k] = key.block[i][k];
	}
	printf("x with setKey2:\n");
	for(int i=0; i<4; i++) printf("%x\n",u.x[i]);
	printf("\n");

}

void test_keyexp32(){
	struct key32 key;
	struct expKey32 ekey;
	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey32(&key,keyarray);
	printf("\nkey:\n");
	printKey32(key); printf("\n");

	KeyExpansion32(key,&ekey);
	for(int i=0; i<44; i++) printf("%x\n",ekey.block[i]);
	printf("\n");
}

void test_addr32(){
	struct state s0; clearState(&s0);
	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	struct key key0;
	setKey(&key0,keyarray);
	for(int i=0; i<4; i++){
		for(int k=0; k<4; k++)printf("%x ",key0.block[i][k]);
		printf("\n");
	}


	struct state2 s; clearState2(&s);
	s.block[0] = 0x04e04828;
	s.block[1] = 0x66cbf806;
	s.block[2] = 0x8119d326;
	s.block[3] = 0xe59a7a4c;
	struct key32 key; clearKey32(&key);
	setKey32(&key,keyarray);
	printf("key:\n");
	for(int i=0; i<4; i++)printf("%x\n",key.block[i]);
	printf("\n");

	struct expKey32 ekey; clearEkey(&ekey);
	KeyExpansion32(key,&ekey);
	//for(int i=0; i<44; i++)printf("%x\n",ekey.block[i]);
	printExpkey32(ekey);

	AddRoundKey32(&s,ekey,4);
	printf("\nresult:\n");
	for(int i=0; i<4; i++)printf("%x\n",s.block[i]);
}
void test_mc2(){
	struct state2 s; clearState2(&s);
	s.block[0] = 0xd4e0b81e;
	s.block[1] = 0xbfb44127;
	s.block[2] = 0x5d521198;
	s.block[3] = 0x30aef1e5;

	MixColumns32(&s);
	for(int i=0; i<4; i++)printf("%x\n",s.block[i]);
}

void test_cipher32(){
	uint32_t in[] = {0x3243f6a8, 0x885a308d, 0x313198a2,0xe0370734};
	uint32_t out[4];

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	struct key32 key; clearKey32(&key);
	setKey32(&key,keyarray);

	struct expKey32 ekey; clearEkey(&ekey);
	KeyExpansion32(key,&ekey);

	int N = 1000;
	clock_t begin = clock();
	for(int i=0; i<N; i++)cipher32(in,out,ekey);
	clock_t end = clock();

	printf("Cipher32(): %f usec\n", (end-begin)/(double)N/CLOCKS_PER_SEC*1e6);

	printf("output array:\n");
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
}
void benchmark_keyexpansion(){
	struct key32 key; clearKey32(&key);
	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	struct expKey32 ekey;

	int N = 1000;
	clock_t begin = clock();
	for(int i=0; i<N; i++)KeyExpansion32_pre(key, &ekey);
	clock_t end = clock();
	printf("KeyExpansion32_pre(): %f usec\n", (end-begin)/(double)N/CLOCKS_PER_SEC*1e6);

	clock_t begin2 = clock();
	for(int i=0; i<N; i++)KeyExpansion32(key,&ekey);
	clock_t end2 = clock();
	printf("KeyExpansion32(): %f usec\n", (end2-begin2)/(double)N/CLOCKS_PER_SEC*1e6);
	//printExpkey32(ekey);




}

void test_rev(){
	struct state2 s; clearState2(&s);
	s.block[0] = 0xd4e0b81e;
	s.block[1] = 0xbfb44127;
	s.block[2] = 0x5d521198;
	s.block[3] = 0x30aef1e5;

	transposeState(&s);
	printf("transposed s:\n");
	for(int i=0; i<4; i++)printf("%x\n",s.block[i]);
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

void test_newke(){
	struct key32 key; clearKey32(&key);
	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	struct expKey32 ekey;

	KeyExpansion32(key,&ekey);
	printExpkey32(ekey);
}
void test_lshift32(){
	uint32_t x = 0x11223344;
	uint32_t t0 = lshift32(x,1);
	uint32_t t1 = lshift32(x,2);

	printf("t0=%x   t1=%x\n",t0,t1);
}
void test_mc32(){
	struct state2 s;
	s.block[0] = 0xd4bf5d30;
	s.block[1] = 0xe0b452ae;
	s.block[2] = 0xb84111f1;
	s.block[3] = 0x1e2798e5;


	MixColumns32(&s);
	for(int i=0; i<4; i++)printf("%x\n",s.block[i]);

	s.block[0] = 0xd4e0b81e;
	s.block[1] = 0xbfb44127;
	s.block[2] = 0x5d521198;
	s.block[3] = 0x30aef1e5;
	MixColumns32(&s);
	printf("original:\n");
	for(int i=0; i<4; i++)printf("%x\n",s.block[i]);
}

void test_cipher32b(){
	struct key32 key; clearKey32(&key);

	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;
	/*
	key.block[0] = 0x2b28ab09;
	key.block[1] = 0x7eaef7cf;
	key.block[2] = 0x15d2154f;
	key.block[3] = 0x16a6883c;*/

	struct expKey32 ekey;
	KeyExpansion32(key,&ekey);

	uint32_t in[] = {0x3243f6a8,0x885a308d,0x313198a2,0xe0370734};
	uint32_t out[4];
	cipher32_b(in,out,ekey);
	//for(int i=0; i<4; i++)printf("%x\n",out[i]);
}

void test_keTrans(){
	struct key32 key; clearKey32(&key);

	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	struct expKey32 ekey;
	KeyExpansion32(key,&ekey);

	for(int i=0; i<44; i++)printf("%x\n",ekey.block[i]);



	transposeKey(&key);
	printf("\nkey:\n");
	for(int i=0; i<4; i++)printf("%x\n",key.block[i]);


}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	bench_mark();
	/*
	test_cipher32();
	printf("\n");
	test_rev();
	printf("\n");
	test_assemble();
	printf("\n");
	test_addr32();
	printf("\n");
	*/
	test_newke();
	printf("\n");
	benchmark_keyexpansion();
	printf("\n");
	test_cipher32b();
	printf("\n");
	test_lshift32();
	printf("\n");
	test_mc32();
	printf("\n");
	test_keTrans();

	printf("\n");
	int test = 0;
	if(test) printf("if sees for 0\n");
	int test2 = 1;
	if(test2)printf("if sees for 1\n");
}
