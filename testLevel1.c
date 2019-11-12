/*
gcc cbals_functions.c -lcblas
./a.out
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cblas.h"
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define COLS 1000000
#define ROWS 1000000

//float mat[ROWS], vec[ROWS];
float *vecX[ROWS], *vecY[ROWS];

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(int argc, char *argv[])
{

  float  vecy[COLS], vecx[COLS];

  int i,j,k;
  long l=0;
  for (i=0;i<ROWS;i++){
       k=i+1;
      vecx[i]=k%9;
      vecy[i]=k%9;
  }

    float alpha=1.0, beta=1.0,param[5]={2,2,2,2,2}, c=0.5f, s=0.866f;
    float ap=0, bp=2,ccp,ssp;
    float *a=&ap,*b=&bp, *cc=&ccp, *ss=&ssp;
    float dot,asum,amax,amin,nrm2,znrm2;
    float d1p=1000000000, d2p=1,x1p=-2,x2p=4, *paramg[5];
    float *d1=&d1p, *d2=&d2p, *x1=&x1p, x2=4;


    for (int m = 0; m < ROWS; m++) {
        vecX[m]=&vecx[m];
        vecY[m]=&vecy[m];
    }
    long t1,t2;
/*
    // COPY
    t1= getMicrotime();
    cblas_scopy (ROWS,  *vecX, 1,  *vecY, 1);
    t2=getMicrotime();
    printf("COPY: %ld\n", t2-t1 );

    // SWAP
    t1= getMicrotime();
    cblas_sswap (ROWS,  *vecX, 1,  *vecY, 1);
    t2=getMicrotime();
    printf("SWAP: %ld\n", t2-t1 );
*/
    // AXPY
    t1= getMicrotime();
    cblas_saxpy (ROWS, alpha, *vecX, 1,  *vecY, 1);
    t2=getMicrotime();
    printf("AXPY: %ld\n", t2-t1 );
/*
    // SCAL
    t1= getMicrotime();
    cblas_sscal(ROWS,alpha, *vecX, 1 );
    t2=getMicrotime();
    printf("SCAL: %ld\n", t2-t1 );

    // DOT
    t1= getMicrotime();
    dot=cblas_sdot (ROWS, *vecX, 1,  *vecY, 1);
    t2=getMicrotime();
    printf("DOT: %ld\n", t2-t1 );

    // NRM2
    t1= getMicrotime();
    nrm2=cblas_snrm2 (ROWS, *vecX, 1);
    t2=getMicrotime();
    printf("NRM2: %ld\n", t2-t1 );

    // ASUM
    t1= getMicrotime();
    asum=cblas_sasum (ROWS, *vecX, 1);
    t2=getMicrotime();
    printf("ASUM: %ld\n", t2-t1 );

    // I_AMAX
    t1= getMicrotime();
    amax=cblas_isamax (ROWS, *vecX, 1);
    t2=getMicrotime();
    printf("I_AMAX: %ld\n", t2-t1 );

    // ROT
    t1= getMicrotime();
    cblas_srot(ROWS,*vecX, 1,  *vecY, 1,c,s);
    t2=getMicrotime();
    printf("ROT: %ld\n", t2-t1 );

    // ROTM
    t1= getMicrotime();
    cblas_srotm(ROWS,  *vecX, 1,  *vecY, 1, param);
    t2=getMicrotime();
    printf("ROTM: %ld\n", t2-t1 );
*/
    t1= getMicrotime();
    cblas_saxpy (ROWS, beta, *vecX, 1,  *vecY, 1);
    cblas_saxpy (ROWS, alpha, *vecY, 1,  *vecX, 1);
    t2=getMicrotime();
    printf("AXPYAXPY: %ld\n", t2-t1 );

    // cblas_srotg((float*) a, (float*) b, (float*) cc,(float*)  ss);
    // cblas_srotmg( (float*) d1,(float*) d2, (float*) x1, x2p, *paramg);

    return 0 ;
}
