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
    long matrixsize=0;
    matrixsize=COLS * (COLS+1)/2;

    float *matLow = malloc(sizeof(float) * matrixsize);
    float *matUp = malloc(sizeof(float) * matrixsize);

    float vecy[COLS], vecx[COLS];

    int i,j,k,ll;
    long l=0;
    for (i=0;i<ROWS;i++){
         //k=i+1;
        for (j=0;j<COLS;j++){
            if (l<matrixsize){
              if (j<=i){
                matLow[l]= ((i+j)%9)+1;
                l++;
              }

              else
                 ll= 0;
            }
          }
        vecx[i]=(i%9)+1;
        vecy[i]=(i%9)+1;
    }
    l=0;
    k=0;
    for (i=0;i<ROWS;i++){
         //k=i+1;
        for (j=0;j<COLS;j++){
            if (l<matrixsize){
              if (j>=i){
                matUp[l]= ((i+j)%9)+1;
                l++;
              }

              else
                 ll= 0;
            }
          }
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
    char buffer[1024] ;
    char *record,*line;
    int i=0,j=0,n=0;

    FILE *fstream = fopen("../data/symLowTri1000.csv","r");
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
   //
    ++i;
  }
  //printf("end\n");
  fclose(fstream);
printf("Hello");



  FILE *fstream1 = fopen("../data/symUpTri1000.csv","r");
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
        vecy[k] = atoi(line) ;
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


        // SYMV
         t1=getMicrotime();
         cblas_ssymv(CblasRowMajor, CblasLower, COLS, a, matLow, ldA, vecx, incx, b, vecy, incy);// cahnges y
         t2=getMicrotime();
         printf("SYMV Lower done at: %ld microseconds\n", t2-t1);
/*
         t1=getMicrotime();
         cblas_ssymv(CblasRowMajor, CblasUpper, COLS, a,  matUp, ldA, vecx, incx, b, vecy, incy);
         t2=getMicrotime();
         printf("SYMV Upper done at: %ld microseconds\n", t2-t1);
*/
         // SYR
          t1=getMicrotime() ;
          //printf("t1: %ld \n", t1);
          cblas_ssyr(CblasRowMajor,  CblasLower, COLS, a, vecx, incx,  matLow, ldA);// cahnges A

          t2=getMicrotime() ;
          //printf("t2: %ld \n", t2);
          //long t3=t2-t1;
          printf("SYR Lower done at: %ld microseconds\n", t2-t1);

/*
          t1=getMicrotime();
          cblas_ssyr(CblasRowMajor,  CblasUpper, COLS, a, vecx, incx, matUp, ldA);// cahnges A
          t2=getMicrotime();
          printf("SYR Upper done at: %ld microseconds\n", t2-t1);
*/

           // SYR2
           t1=getMicrotime();
           cblas_ssyr2(CblasRowMajor,  CblasLower, COLS, a, vecx, incx, vecy, incy, matLow, ldA);
           t2=getMicrotime();
           printf("SYR2 Lower done at: %ld microseconds\n", t2-t1);
/*
           t1=getMicrotime();
           cblas_ssyr2(CblasRowMajor,  CblasUpper, COLS, a, vecx, incx, vecy, incy, matUp, ldA);
           t2=getMicrotime();
           printf("SYR2 Upper done at: %ld microseconds\n", t2-t1);
*/
  return 0 ;
}
