#include "fir.h"

#define N 3

//Modified example by Prof. Young-kyu Choi
void fir( const uint8_t input, uint8_t* output )
{
#pragma HLS INTERFACE mode=s_axilite port=fir
#pragma HLS INTERFACE mode=s_axilite port=input
#pragma HLS INTERFACE mode=s_axilite port=output

	static uint8_t shift_reg[N];
	uint16_t acc = 0;

	for (int8_t i = N - 1; i > 0; i--)
	{
		shift_reg[i] = shift_reg[i - 1];
		acc += shift_reg[i];
	}

	shift_reg[0] = input;
	acc += shift_reg[0];

	//Divide by three
	*output = ((acc) * 0xAAAAAAABULL ) >> 33;
}
