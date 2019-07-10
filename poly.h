#pragma once

void setPoly(int num, int *poly);
//int setInt(int *bin);
int getInt(const int *poly);

void addPoly(int *poly, const int *poly2);
void addPoly_generic(const int *poly1, int poly1_size, const int *poly2, int poly2_size, int *output);
void subPoly(int *poly, const int *poly2);//necessary?
void mul2(int *poly, const int *poly2);
int isEqualPoly(const int *poly1, const int *poly2);
