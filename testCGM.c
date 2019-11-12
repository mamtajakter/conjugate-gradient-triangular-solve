
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "cblas.h"

#define SIZE 10000

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
    printf("Hello");
    long matrixsize=SIZE*SIZE;
    float A[matrixsize],  b[SIZE], x[SIZE], bTemp[SIZE] ;

        int i=0,j=0,k=0,m=0;

        long l=0;
        for (i=0;i<SIZE;i++){
            for (j=0;j<SIZE;j++){

              A[l]= ((i+j)%9) +1;
              l++;

              }
              // b[i]= (i % 9)+1;
              b[i]= 1.0;
              x[i] = b[i];
              bTemp[i] = b[i];
        }
/*
    printf ( "\nCheck A:");
    for (k = 0; k < SIZE*SIZE; k++) {
         printf("%.4f\n", A[k]);
     }
    printf ( "\nCheck B:");
    for (k = 0; k < SIZE; k++) {
         printf("%.4f\n", b[k]);
     }
*/
//===========================conjugateGradientSolver==================================

      long t1, t2;
      t1=getMicrotime();

      float TOLERANCE = 1.0e-10,alpha=1.0,beta=0.0,nrm2=0.0, s=0.0, ry = 0.0, t = 0.0, rz=0.0, bb=0.0;
      int incx = 1, incy = 1, ldA=SIZE;

      float rr[SIZE], r[SIZE], rTemp[SIZE], y[SIZE], z[SIZE];

      cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, alpha, (float*) A, ldA, x, incx, beta, rr, incy);//  rr=A*x

      cblas_saxpy (SIZE, -alpha, (float*) rr, 1,  (float*) bTemp, 1); // bTemp=b-rr
      for (m = 0; m < SIZE; m++) {
            r[m]=bTemp[m];// r= bTemp
      }
      nrm2=cblas_snrm2 (SIZE, (float*) r, 1);// nrm2= norm (r)

      int n = SIZE, count=0;

       if (nrm2<TOLERANCE){
         count=n;
       }

       for (m = 0; m < SIZE; m++) {
             rTemp[m]=r[m];// rTemp=r
       }
       cblas_sscal(SIZE, -alpha, (float*) rTemp, 1 );// rTemp=-r


       for (m = 0; m < SIZE; m++) {
             y[m]=rTemp[m];// y= rTemp
       }

       cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, alpha, (float*) A, ldA, (float*) y, incx, beta, z, incy);// z=A*y

       s = cblas_sdot (SIZE, (float*) y, 1,  (float*) z, 1);//s=y*z

       ry = cblas_sdot (SIZE, (float*) r, 1,  (float*) y, 1);//ry=r*y
      //  if (s<TOLERANCE)
      //     s=TOLERANCE;
       t = ry/s;//t=ry/s

       cblas_saxpy (SIZE, t, (float*) y, 1,  (float*) x, 1); // x= x+t*y

       while (count<n){

         cblas_saxpy (SIZE, -t, (float*) z, 1,  (float*) r, 1); // r= r-t*z

         nrm2=cblas_snrm2 (SIZE, (float*) r, 1);// nrm2= norm (r)

          if (nrm2<TOLERANCE)
            break;

          // if (s<TOLERANCE)
          //      s=TOLERANCE;

          rz = cblas_sdot (SIZE, (float*) r, 1,  (float*) z, 1);//rz=r*z


          bb = rz/s;

          cblas_sscal(SIZE, bb, (float*) y, 1 );// y=bb*y

          cblas_saxpy (SIZE, -alpha, (float*) r, 1,  (float*) y, 1); // y= y-r

          cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, alpha, (float*) A, ldA, (float*) y, incx, beta, z, incy);// z=A*y


          s = cblas_sdot (SIZE, (float*) y, 1,  (float*) z, 1);//s=y*z


          ry = cblas_sdot (SIZE, (float*) r, 1,  (float*) y, 1);//ry=r*y
          // if (s<TOLERANCE)
          //    s=TOLERANCE;
          t = ry/s;//t=ry/s
          cblas_saxpy (SIZE, t, (float*) y, 1,  (float*) x, 1); // x= x+t*y

          count++;
       }

       t2=getMicrotime();
       /*
       printf ( "\nX:");
       for (m = 0; m < SIZE; m++) {
            printf("%.4f\n", x[m]);
        }
        */
       printf("Time taken: %ld microseconds\n", t2-t1);

  }
