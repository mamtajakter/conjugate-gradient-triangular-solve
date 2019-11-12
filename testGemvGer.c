#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cblas.h"

#include <time.h>
#include <sys/time.h>
// #define NCols 16
// #define Nrows 4

#define ROWS 10000 //m
#define COLS 10000 // n

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{

  //long matrixsize=ROWS*COLS;
  float *mat = malloc(sizeof(float) * (ROWS*COLS));

    float  vecy[COLS], vecx[COLS];

    int i,j,k;
    long l=0;
    for (i=0;i<ROWS;i++){
        for (j=0;j<COLS;j++){

          mat[l]= ((i+j)%9) +1;
          l++;

          }
          vecx[i]= (i % 9)+1;
          vecy[i]= (i % 9)+1;

    }

  /*  printf ( "\nA:\n");
    l=0;
    for (k = 0; k < ROWS*COLS; k++){

          if (l%15==0)
          printf("\n");
          printf(" %.4f",  mat[k]);
          l++;
        }

        l=0;
        printf ( "\nb:\n");
        for (k = 0; k < ROWS; k++){

              printf(" %.4f",  vecx[k]);
            }*/


/*
    char buffer[1024] ;
    char *record,*line;
    int i=0,j=0,n=0;

    FILE *fstream = fopen("../data/symSq1000.csv","r");
    if(fstream == NULL)   {
       printf("\n file opening failed ");
       return -1 ;
    }
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
    record = strtok(line,",");
    j=0;
    while(record != NULL)
      {
       //printf("Hello\n");
       mat[n] = atoi(record) ;
       record = strtok(NULL,",");
       n++;
      }
    ++i;
  }
  fclose(fstream);

printf("Hoolah") ;

  FILE *fstream1 = fopen("../data/vecX1000.csv","r");
    if(fstream1 == NULL)   {
       printf("\n file opening failed ");
       return -1 ;
    }
    int k=0;
    while((line=fgets(buffer,sizeof(buffer),fstream1))!=NULL)
    {
        vecx[k] = atoi(line) ;
        vecy[k] = atoi(line) ;
        ++k ;
    }
    fclose(fstream1);
*/
    long t1, t2;
    float a = 1.0, b=1.0;
    float y[COLS] ;
    int incx = 1;
    int incy = 1;
    int m=0;
    int ldA=ROWS;//ldA is major stride—number of rows (if colwise) or cols (if rowwise) of
        //parent matrix A. Useful for submatrices.

        t1=getMicrotime();
        cblas_sgemv(CblasRowMajor, CblasNoTrans, COLS, ROWS, a, mat, ldA, vecx, incx, b, vecy, incy);
        t2=getMicrotime();
        printf("GEMV done at: %ld microseconds\n", t2-t1);
              /*  for (i= 0; i< COLS; i++)
                    printf(" %1.0f, ", vecy[i]) ;*/

         // GER
         t1=getMicrotime();
         cblas_sger(CblasRowMajor, ROWS, COLS, a, vecx, incx, vecy, incy, mat, ldA);// cahnges y
         t2=getMicrotime();
         printf("GER done at: %ld microseconds\n", t2-t1);
         //printf("ger done\n");
        /* for (i= 0; i< ROWS*COLS; i++)
             printf(" %1.0f, ", mat[i]) ;*/

  return 0 ;
}
