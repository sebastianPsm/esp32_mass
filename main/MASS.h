//
// Original source: https://www.cs.unm.edu/~mueen/MASS.cpp
// Acknowledging the work of Mueen and his team:
// Abdullah Mueen, Yan Zhu, Michael Yeh, Kaveh Kamgar, Krishnamurthy Viswanathan, Chetan Kumar Gupta and Eamonn Keogh (2015), The Fastest Similarity Search Algorithm for Time Series Subsequences under Euclidean Distance, URL: http://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html
//
// This code runs on a ESP32 with n=1024 and m=128 in ~13 ms
//                                n=2048           in ~26 ms
//
#ifndef __MASS_H__
#define __MASS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <fft.h>

struct tMassStruct;
typedef struct tMassStruct tMass;

struct tMassStruct {
    float * x;
    unsigned n;

    float * y;
    float * dist;
    unsigned m;

    float *z;
    float *cx;
    float *cx2;
    float *cy;
    float *cy2;

    fft_config_t * fft_plan_X;
    fft_config_t * fft_plan_Y;
    fft_config_t * fft_plan_Z;
};

tMass * mass_init(unsigned n, unsigned m);
void mass_terminate(tMass ** h);
void mass_findNN(tMass * h, float * x, float * y, float * dist);
void multiply_x_and_y(tMass * h, float * z);

#ifdef __cplusplus
}
#endif

#endif /* __MASS_H__ */