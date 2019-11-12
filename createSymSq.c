#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define ROWS 10000 //m
#define COLS 10000 // n

void create_marks_csv(char *filename,int **a/*a[][COLS]*/,int n,int m){

printf("\n Creating %s.csv file",filename);

FILE *fp;

int i,j;

filename=strcat(filename,".csv");

fp=fopen(filename,"w+");

//fprintf(fp,"Student Id, Physics, Chemistry, Maths");

for(i=0;i<m;i++){
     for(j=0;j<n;j++){
          if (j== n-1)
              fprintf(fp,"%d",a[i][j]);
          else
                fprintf(fp,"%d,",a[i][j]);
       }
    fprintf(fp,"\n");
    }

fclose(fp);

printf("\n %sfile created",filename);

}

int main(){
  //printf("hi1\n");
    //int a[ROWS][COLS];
    int **a = malloc(sizeof(int*) * ROWS);
    for(int w = 0; w < ROWS; w++) {
      a[w] = malloc(sizeof(int) * COLS);
    }

    int i,j,k;
    //printf("hi\n");
    for (i=0;i<ROWS;i++){
         k=i+1;
        for (j=0;j<COLS;j++){
            a[i][j]= k+j;
          }
    }
    char str[100];

    printf("\n Enter the filename :");

    gets(str);

create_marks_csv(str,a,ROWS,COLS);

  for(int z = 0; z < ROWS; z++) {
    free(a[z]);
  }
  free(a);
return 0;

}
