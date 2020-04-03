#include <iostream>
using namespace std;

void fillArrays(__int8* a, __int8* b, __int8* c, __int16* d);

__int16* process(__int8* a, __int8* b, __int8* c, __int16* d);


int main() {
	__int8 a[8], b[8], c[8];
	__int16 d[8];

	fillArrays(a, b, c, d);

	cout << "By loop: ";
	__int16 arr[8];
	for (int i = 0; i < 8; i++) {
		arr[i] = (a[i] - b[i]) * (c[i] - d[i]);
		cout << arr[i] << " "; 
	}
	cout << endl << endl;

	__int16* res = process(a, b, c, d);

	cout << "By function: ";
	for (int i = 0; i < 8; i++) cout << (int)res[i] << " ";
	cout << endl;

	delete res;
	return 0;
}


void fillArrays(__int8* a, __int8* b, __int8* c, __int16* d) {
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		a[i] = rand() % 254 - 50;
		b[i] = rand() % 254 - 50;
		c[i] = rand() % 254 - 50;
		d[i] = rand() % (256 * 256 - 1) - (256 * 128);
	}
}

__int16* process(__int8* a, __int8* b, __int8* c, __int16* d) {
	__int8 arr_a[8];
	__int8 arr_b[8];
	__int8 arr_c[8];
	__int16 arr_d[8];
	__int16 res[8];

	for (int i = 0; i < 8; i++) arr_a[i] = a[i];
	for (int i = 0; i < 8; i++) arr_b[i] = b[i];
	for (int i = 0; i < 8; i++) arr_c[i] = c[i];
	for (int i = 0; i < 8; i++) arr_d[i] = d[i];

	_asm {
		movq		mm0,		arr_a
		psubb		mm0,		arr_b
		
		punpcklbw	mm1,		mm0
		psraw		mm1,		8
		punpckhbw	mm2,		mm0
		psraw		mm2,		8


		movq		mm0,		arr_c
		punpcklbw	mm3,		mm0
		psraw		mm3,		8
		punpckhbw	mm4,		mm0
		psraw		mm4,		8

		movq		mm5,		arr_d
		movq		mm6,		arr_d + 8

		psubw		mm3,		mm5
		psubw		mm4,		mm6


		pmullw		mm1,		mm3
		pmullw		mm2,		mm4


		movq		res,		mm1
		movq		res + 8,	mm2
	}

	__int16* p_res = new __int16[8];
	for (int i = 0; i < 8; i++) p_res[i] = res[i];

	return p_res;
}