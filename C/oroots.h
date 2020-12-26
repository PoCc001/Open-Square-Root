/**
* Copyright Johannes Kloimb�ck 2020.
* Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE or copy at
* https://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef OROOTS_H
#define OROOTS_H

#include "osqrt.h"
#include "ocbrt.h"

#ifndef STRICT
#define STRICT 1
#endif

#ifndef CHECK_SPECIAL_CASES
#define CHECK_SPECIAL_CASES 1
#endif

#ifndef SUBNORMAL_NUMBERS
#define SUBNORMAL_NUMBERS 1
#endif

#if STRICT == 1
typedef double corr_t;
#else
typedef long double corr_t;
#endif

typedef union {
	double d;
	unsigned long long ull;
} double_ull;

#define DOUBLE_EXP_MASK_1 0b10000000000
#define DOUBLE_EXP_MASK_2 0b1111111111
#define DOUBLE_MANTISSA_MASK 0b1111111111111111111111111111111111111111111111111111ULL
#define DOUBLE_NAN 0x7fffffffffffffffULL
#define DOUBLE_EXP_MASK_3 0b11111111111
#define LOG_2 0.6931471805599453
#define E 2.718281828459045

inline unsigned int leading_zeros_ull(const unsigned long long *val) {
	unsigned int max_length = sizeof(*val) * 8;
	for (unsigned int i = max_length; i > 0; --i) {
		if (*val & (1ULL << (i - 1))) {
			return i;
		}
	}

	return 0;
}

inline unsigned int leading_zeros_ui(const unsigned int *val) {
	unsigned int max_length = sizeof(*val) * 8;
	for (unsigned int i = max_length; i > 0; --i) {
		if (*val & (1ULL << (i - 1))) {
			return i;
		}
	}

	return 0;
}

extern double oroot(double, int);

#endif