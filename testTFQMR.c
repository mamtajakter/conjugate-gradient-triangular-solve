
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "cblas.h"

#define SIZE 4

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
    printf("Hello");
    long matrixsize=SIZE*SIZE;
    float A[matrixsize],  b[SIZE], x[SIZE], bTemp[SIZE], r[SIZE], y1[SIZE], w[SIZE], vec0[SIZE], d[SIZE]  ;

        int i=0,j=0;

        long l=0;
        for (i=0;i<SIZE;i++){
            for (j=0;j<SIZE;j++){

              A[l]= ((i+j)%9) +1;
              l++;

              }
              // b[i]= (i % 9)+1;
              b[i]= 1.0;
              x[i] = 0.0;
              bTemp[i] = 1.0;

              r[i]= 1.0;
              w[i] = 1.0;
              y1[i] = 1.0;

              vec0[i] = 0.0;
              d[i] = 0.0;

        }
        printf ( "\nCheck A:");
    for (i = 0; i < SIZE*SIZE; i++) {
         printf("%.4f\n", A[i]);
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

        // A: matrix 
        // b, x, bTemp: unit vector 

      long t1, t2;
      t1=getMicrotime();

      float TOLERANCE = 1.0e-10,alpha=1.0,beta=0.0,nrm2=0.0, s=0.0, ry = 0.0, t = 0.0, rz=0.0, bb=0.0, theta = 0.0, eta =0.0, m=0.0, tau, rho, rhon;
      int incx = 1, incy = 1, ldA=SIZE, k=0, kmax=100;

      float v[SIZE], vTemp[SIZE], u1[SIZE],u2[SIZE], uTemp[SIZE],y2[SIZE], z[SIZE], dTemp[SIZE], yTemp[SIZE];

      //v = gemv' a y1
      cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, alpha, (float*) A, ldA, y1, incx, beta, v, incy);//  v=A*y1

      cblas_scopy(SIZE, v, 1, u1, 1);// u1= v

      theta = 0.0;
      eta = 0.0;

      tau=cblas_snrm2 (SIZE, (float*) r, 1);// tau = nrm2 r
      rho = tau * tau;

      m = 0.0;

      float sigma, c;

      while (k < kmax)
      {
          k++;

          //sigma =  dot r' v' 
          sigma = cblas_sdot (SIZE, (float*) r, 1,  (float*) v, 1);//sigma = r*v
          alpha = rho / sigma;
          j=1;
          m = 2 * k - 2 + j;
          // ww' = axpy ((negate 1) * alpha)  u1' w'
          cblas_saxpy (SIZE, -alpha, (float*) u1, 1,  (float*) w, 1); // w=w-alpha*u1
          
          //dd' = axpy (theta' * theta' * eta'/ alpha) d' y1'
          cblas_scopy(SIZE, d, 1, dTemp, 1);// dTemp = d
          cblas_sscal(SIZE, theta * theta * eta / alpha, (float*) dTemp, 1 );// dTemp = =(theta' * theta' * eta'/ alpha)*dTemp
          cblas_saxpy (SIZE, 1, (float*) y1, 1,  (float*) dTemp, 1); // dTemp = y1+ (theta' * theta' * eta'/ alpha)*d
          cblas_scopy(SIZE, dTemp, 1, d, 1);// d = dTemp
          
          //ttheta' = (nrm2 ww') / tau'
          nrm2 = cblas_snrm2 (SIZE, (float*) w, 1);
          theta = nrm2 / tau;
          //c = 1 / sqrt (1 + ttheta' * ttheta') 
          c = 1 / sqrt (1 + theta * theta) ;
          // ttau' = tau' * ttheta' * c 
          tau = tau * theta * c;
          // eeta' = c * c * alpha 
          eta = c * c * alpha;
          //xx' = axpy eeta'  dd' x'
          cblas_saxpy (SIZE, eta, (float*) d, 1,  (float*) x, 1); // x=x+ eta*d
          

          if (tau*sqrt(m+1) <= TOLERANCE){
            break;
          }
          j=2;
          //yy2 = axpy ((negate 1) * alpha)  v' y1'
          cblas_scopy(SIZE, y1, 1, y2, 1);// y2 = y1
          cblas_saxpy (SIZE, -alpha, (float*) v, 1,  (float*) y2, 1); // y2 = y2 -alpha*v

          //uu2 = gemv' a yy2
          cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, 1.0, (float*) A, ldA, y2, incx, 0.0, u2, incy);//  u2=A*y2

          m = 2 * k - 2 + j;

          // ww' = axpy ((negate 1) * alpha)  u2' w'
          cblas_saxpy (SIZE, -alpha, (float*) u2, 1,  (float*) w, 1); // w=w-alpha*u1
          
          //dd' = axpy (theta' * theta' * eta'/ alpha) d' y2'
          cblas_scopy(SIZE, d, 1, dTemp, 1);// dTemp = d
          cblas_sscal(SIZE, theta * theta * eta / alpha, (float*) dTemp, 1 );// dTemp = =(theta' * theta' * eta'/ alpha)*dTemp
          cblas_saxpy (SIZE, 1, (float*) y2, 1,  (float*) dTemp, 1); // dTemp = y2+ dTemp
          cblas_scopy(SIZE, dTemp, 1, d, 1);// d = dTemp
          
          //ttheta' = (nrm2 ww') / tau'
          nrm2 = cblas_snrm2 (SIZE, (float*) w, 1);
          theta = nrm2 / tau;
          //c = 1 / sqrt (1 + ttheta' * ttheta') 
          c = 1 / sqrt (1 + theta * theta) ;
          // ttau' = tau' * ttheta' * c 
          tau = tau * theta * c;
          // eeta' = c * c * alpha 
          eta = c * c * alpha;
          //xx' = axpy eeta'  dd' x'
          cblas_saxpy (SIZE, eta, (float*) d, 1,  (float*) x, 1); // x=x+ eta*d

          if (tau*sqrt(m+1) <= TOLERANCE){
            break;
          }

          //rhon = dot r' ww
          rhon = cblas_sdot (SIZE, (float*) r, 1,  (float*) w, 1);//rhon=r*w
          beta = rhon / rho;
          rho = rhon;
          //yy1 = axpy beta yy2 ww
          cblas_scopy(SIZE, y2, 1, yTemp, 1);// yTemp = y2
          cblas_sscal(SIZE, beta, (float*) yTemp, 1 );// yTemp = beta*yTemp
          cblas_saxpy (SIZE, 1, (float*) w, 1,  (float*) yTemp, 1); // yTemp = y1+ yTemp
          cblas_scopy(SIZE, yTemp, 1, y1, 1);// y1 = yTemp
          
          //u1 = gemv' a yy1
          cblas_sgemv(CblasRowMajor, CblasNoTrans, SIZE, SIZE, 1.0, (float*) A, ldA, y1, incx, 0.0, u1, incy);//  u1=A*y1

          //uTemp = u2 + beta * v
          cblas_scopy(SIZE, u2, 1, uTemp, 1);// uTemp = u2
          cblas_saxpy (SIZE, beta, (float*) v, 1,  (float*) uTemp, 1); // uTemp = uTemp+ beta* v
          
          // v = u1 + beta * uTemp  
          cblas_scopy(SIZE, u1, 1, v, 1);// v = u1
          cblas_saxpy (SIZE, beta, (float*) uTemp, 1,  (float*) v, 1); // v = v+ beta* uTemp
  
          
      }

 

       t2=getMicrotime();
       
       printf ( "\nX:");
       for (i = 0;i < SIZE; i++) {
            printf("%.4f\n", x[i]);
        }
        
       printf("Time taken: %ld microseconds\n", t2-t1);

  }
