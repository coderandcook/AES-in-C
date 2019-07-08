#pragma once

void setPoly(int num, int *binary);
//int setInt(int *bin);
int getInt(int *poly);

void addPoly(int *binary, int *binary2);
void addPoly_generic(int *poly1, int poly1_size, int *poly2, int poly2_size, int *output);
void subPoly(int *binary, int *binary2);//necessary?
void mul2(int *poly, int *poly2);
int isEqualPoly(int *poly1, int *poly2);
