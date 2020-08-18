//
// Original source: https://www.cs.unm.edu/~mueen/MASS.cpp
// Acknowledging the work of Mueen and his team:
// Abdullah Mueen, Yan Zhu, Michael Yeh, Kaveh Kamgar, Krishnamurthy Viswanathan, Chetan Kumar Gupta and Eamonn Keogh (2015), The Fastest Similarity Search Algorithm for Time Series Subsequences under Euclidean Distance, URL: http://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html
//
// This code runs on a ESP32 with n=1024 and m=128 in ~25 ms
//
#ifndef __MASS_H__
#define __MASS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <fft.h>

struct tMassStruct;
typedef struct tMassStruct tMass;

tMass * mass_init(unsigned n, unsigned m);
void mass_terminate(tMass ** h);
void mass_findNN(tMass * h, float * x, float * y, float * dist);

#ifdef __cplusplus
}
#endif

#endif /* __MASS_H__ */
