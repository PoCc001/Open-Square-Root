/**
* Copyright Johannes Kloimb�ck 2020.
* Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE or copy at
* https://www.boost.org/LICENSE_1_0.txt)
*/

#include "osqrt.h"
#include <stdbool.h>

double osqrt(const double a) {
#if CHECK_SPECIAL_CASES != 0
	if (a < 0.0) {
		double nan;
		get_nan(&nan);
		return nan;
	}

	if (a == 0.0 || a != a) {
		return a;
	}
#endif

	double_ull val;
	val.d = a;

	int exponent = (int)(val.ull >> 52);
	
#if SUBNORMAL_NUMBERS != 0
	bool is_sub_normal = !exponent;
#endif

	exponent -= 1024;
	exponent >>= 1;
	exponent += 1024;

	unsigned long long mantissa = val.ull & DOUBLE_MANTISSA_MASK;

#if SUBNORMAL_NUMBERS != 0
	if (is_sub_normal) {
		int sub_normal_exponent = leading_zeros_ull(&mantissa) - 11;
		sub_normal_exponent >>= 1;
		exponent = ~(sub_normal_exponent) + 1;
		exponent &= DOUBLE_EXP_MASK_3;
	}
#endif

	double_ull guess;
	guess.ull = (unsigned long long)(exponent) << 52;

	for (int i = 0; i < 3; ++i) {
		guess.d += (a / guess.d);
		guess.ull -= 0x10000000000000ULL;
	}
	
	double guesst2 = guess.d + (a / guess.d);

	corr_t diff = ((corr_t)(guess.d) * (corr_t)guess.d) - (corr_t)a;
	diff /= guesst2;
	guess.d -= (double)(diff);
	
	return guess.d;
}