#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cblas.h"

#include <time.h>
#include <sys/time.h>
// #define NCols 16
// #define Nrows 4

#define ROWS 10000//m
#define COLS 10000 // n

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
  long matrixsize=ROWS*COLS;
  float *matLow = malloc(sizeof(float) * matrixsize);
  float *matUp = malloc(sizeof(float) * matrixsize);

    float  vecy[COLS], vecx[COLS];

    int i,j,k;
    long l=0;
    for (i=0;i<ROWS;i++){
         //k=i+1;
        for (j=0;j<COLS;j++){
            if (j<=i)
               matLow[l]= ((i+j)%9)+1;
            else
               matLow[l]= 0;
            if (j<i)
                matUp[l]=0;
            else
                matUp[l]= ((i+j)%9)+1;
            l++;
          }
        vecx[i]=(i%9)+1;
        vecy[i]=(i%9)+1;
    }
/*
    printf ( "\nA:\n");
    l=0;
    for (k = 0; k < matrixsize; k++){

          if (l%15==0)
          printf("\n");
          printf(" %.4f",  matUp[k]);
          l++;
        }

        l=0;
        printf ( "\nb:\n");
        for (k = 0; k < ROWS; k++){

              printf(" %.4f",  vecx[k]);
            }
*/
/*
    char buffer[5024] ;
    char *record,*line;
    int i=0,j=0,n=0;

    FILE *fstream = fopen("../data/symLowSq1000.csv","r");
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

       //printf("%s",record) ;
       matLow[n] = atoi(record) ;
       record = strtok(NULL,",");
       n++;
      }
    ++i;
  }
  fclose(fstream);
  printf("Hello1\n");

  FILE *fstream1 = fopen("../data/symUpSq1000.csv","r");
  if(fstream1 == NULL)   {
     printf("\n file opening failed ");
     return -1 ;
  }

  while((line=fgets(buffer,sizeof(buffer),fstream1))!=NULL)
  {
  record = strtok(line,",");
  j=0;
  while(record != NULL)
    {

     //printf("%s",record) ;
     matUp[n] = atoi(record) ;
     record = strtok(NULL,",");
     n++;
    }
  ++i;
}

fclose(fstream1);




  FILE *fstream2 = fopen("../data/vecX1000.csv","r");
    if(fstream2 == NULL)   {
       printf("\n file opening failed ");
       return -1 ;
    }
    int k=0;
    while((line=fgets(buffer,sizeof(buffer),fstream2))!=NULL)
    {
        vecx[k] = atoi(line) ;
        ++k ;
    }
    fclose(fstream2);
*/

      long t1, t2;

    float a = 1.0, b=1.0;
    float y[COLS] ;
    int incx = 1;
    int incy = 1;
    int m=0;
    int ldA=ROWS;


        // TRMV
        t1=getMicrotime();
        cblas_strmv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit,  COLS,  matLow, ldA, vecx, incx);// changes matLow
         t2=getMicrotime();
         printf("TRMV Lower done at: %ld microseconds\n", t2-t1);

         t1=getMicrotime();

         cblas_strmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit,  COLS,   matUp, ldA, vecx, incx);

         t2=getMicrotime();
         printf("TRMV Upper done at: %ld microseconds\n", t2-t1);

         // TRSV
         t1=getMicrotime();
         cblas_strsv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit,  COLS, matLow, ldA, vecx, incx); // changes A
          t2=getMicrotime();
          printf("TRSV Lower done at: %ld microseconds\n", t2-t1);

          t1=getMicrotime();

          cblas_strsv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit,  COLS,   matUp, ldA, vecx, incx); // changes A

          t2=getMicrotime();
          printf("TRSV Upper done at: %ld microseconds\n", t2-t1);

          // for(int z = 0; z < COLS; z++) {
          //   free(matLow[z]);
          // }
          // free(matLow);
          // for(int z1 = 0; z1 < COLS; z1++) {
          //   free(matUp[z1]);
          // }
          // free(matUp);
  return 0 ;
}
