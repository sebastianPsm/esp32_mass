//
// Original source: https://www.cs.unm.edu/~mueen/MASS.cpp
// Acknowledging the work of Mueen and his team:
// Abdullah Mueen, Yan Zhu, Michael Yeh, Kaveh Kamgar, Krishnamurthy Viswanathan, Chetan Kumar Gupta and Eamonn Keogh (2015), The Fastest Similarity Search Algorithm for Time Series Subsequences under Euclidean Distance, URL: http://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html
//
// This code runs on a ESP32 with n=1024 and m=128 in ~13 ms
//                                n=2048           in ~26 ms
//
#include "MASS.h"

#define REAL (2*idx+0)
#define IMAG (2*idx+1)

void multiply_x_and_y(tMass * h, float * z);
void zNorm(const float * x, int n, float * y);

tMass * mass_init(unsigned n, unsigned m) {
    if(n <= m) return NULL;

    tMass * h = (tMass *) malloc(sizeof(tMass));
    h->n = n;
    h->m = m;

    h->x = (float *) malloc(sizeof(float) * n);
    h->y = (float *) malloc(sizeof(float) * m); 
    h->dist = (float *) malloc(sizeof(float) * n);
    h->z = (float *) malloc(sizeof(float) * 2 * n);

    h->cx = (float *) malloc(sizeof(float) * (n+1));
    h->cx2 = (float *) malloc(sizeof(float) * (n+1));
    h->cy = (float *) malloc(sizeof(float) * (m+1));
    h->cy2 = (float *) malloc(sizeof(float) * (m+1));

    h->fft_plan_X = fft_init(2*n, FFT_COMPLEX, FFT_FORWARD, NULL, NULL);
    h->fft_plan_Y = fft_init(2*n, FFT_COMPLEX, FFT_FORWARD, NULL, NULL);
    h->fft_plan_Z = fft_init(2*n, FFT_COMPLEX, FFT_BACKWARD, NULL, NULL);

    assert(h->fft_plan_X);
    assert(h->fft_plan_Y);
    assert(h->fft_plan_Z);

    return h;
}
void mass_terminate(tMass ** h) {
    free((*h)->x);
    free((*h)->y);
    free((*h)->dist);
    free((*h)->z);

    free((*h)->cx);
    free((*h)->cx2);
    free((*h)->cy);
    free((*h)->cy2);

    fft_destroy((*h)->fft_plan_X);
    fft_destroy((*h)->fft_plan_Y);
    fft_destroy((*h)->fft_plan_Z);

    free(*h);
    *h = NULL;
}
void mass_findNN(tMass * h, float * x, float * y, float * dist) {
    unsigned idx;

    //Normalize
    zNorm(x, h->n, h->x);
    zNorm(y, h->m, h->y);

    //Compute the cumulative sums
    h->cx[0] = h->cx2[0] = h->cy[0] = h->cy2[0] = 0.0;
    for(idx = 1 ; idx <= h->n; idx++) {
        h->cx[idx] = h->cx[idx-1] + h->x[idx-1];
        h->cx2[idx] = h->cx2[idx-1] + h->x[idx-1] * h->x[idx-1];
        if(idx <= h->m) {
            h->cy[idx] = h->cy[idx-1] + h->y[idx-1];
            h->cy2[idx] = h->cy2[idx-1] + h->y[idx-1] * h->y[idx-1];
        }
    }
    
    //Compute the multiplication numbers
    multiply_x_and_y(h, h->z);
    
    //y Stats
    float sumy = h->cy[h->m];
    float sumy2 = h->cy2[h->m];
    float meany = sumy/h->m;
    float sigmay = (sumy2/h->m) - meany*meany;
    sigmay = sqrt(sigmay);

    // validated

    //The Search
    for(idx = 0 ; idx < (h->n - h->m + 1) ; idx++) {
        float sumxy = h->z[h->m - 1 + idx];
        float sumx = h->cx[idx + h->m] - h->cx[idx]; // Sum of x of every subsequences of length m
        float sumx2 = h->cx2[idx + h->m] - h->cx2[idx]; // Sum of x^2 of every subsequences of length m
        float meanx = sumx/h->m; // Mean of every subsequences of length m
        float sigmax = sqrt((sumx2 / h->m) - meanx*meanx); // Standard deviaiton of every subsequences of length m

        float c = ( sumxy - h->m*meanx*meany ) / ( h->m*sigmax*sigmay );
        dist[idx] = sqrt(2 * h->m * (1-c));
    }
}
void zNorm(const float * x, int n, float * y) {
    float ex = 0, ex2 = 0;

    for(unsigned idx = 0 ; idx < n ; idx++ ) {
        ex += x[idx];
        ex2 += x[idx] * x[idx];
    }
    float mean = ex / n;
    float std = ex2 / n;
    std = sqrt(std - mean * mean);
    for(unsigned idx = 0 ; idx < n ; idx++ )
        y[idx] = (x[idx]-mean) / std;
}
void multiply_x_and_y(tMass * h, float * z) {
    for(unsigned idx = 0; idx < 2*h->n; idx++) {
        h->fft_plan_X->input[IMAG] = 0;
        h->fft_plan_Y->input[IMAG] = 0;
        h->fft_plan_X->input[REAL] = (idx < h->n) ? (h->x[idx]) : 0;
        h->fft_plan_Y->input[REAL] = (idx < h->m) ? (h->y[h->m-idx-1]) : 0;
    }

    fft_execute(h->fft_plan_X);    
    fft_execute(h->fft_plan_Y);

    for(unsigned idx = 0 ; idx < 2*h->n; idx++) {
        h->fft_plan_Z->input[REAL] = h->fft_plan_X->output[REAL]*h->fft_plan_Y->output[REAL] - h->fft_plan_X->output[IMAG]*h->fft_plan_Y->output[IMAG];
        h->fft_plan_Z->input[IMAG] = h->fft_plan_X->output[IMAG]*h->fft_plan_Y->output[REAL] - h->fft_plan_X->output[REAL]*h->fft_plan_Y->output[IMAG];
    }

    fft_execute(h->fft_plan_Z);

    for(unsigned idx = 0; idx < 2*h->n; idx++)
        z[idx] = h->fft_plan_Z->output[REAL]/(2*h->n);    
}