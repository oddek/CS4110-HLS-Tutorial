

#include "fir.h"

#define N 3

//Modified example by Prof. Young-kyu Choi
void fir( const uint8_t input, uint8_t* output )
{
#pragma HLS INTERFACE mode=s_axilite port=fir
#pragma HLS INTERFACE mode=s_axilite port=input
#pragma HLS INTERFACE mode=s_axilite port=output

	const float coef = 1.0f/3.0f;
	static float shift_reg[N];
	float acc = 0;

	for (int8_t i = N - 1; i > 0; i--)
	{
		shift_reg[i] = shift_reg[i - 1];
		acc += shift_reg[i] * coef;
	}
	acc += input * coef;
	shift_reg[0] = (float)input;
	*output = (uint8_t)(acc+0.5f);
}
