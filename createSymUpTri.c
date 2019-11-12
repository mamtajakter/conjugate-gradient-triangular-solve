#include<stdio.h>

#include <stdlib.h>
#include<string.h>

#define ROWS 100 //m
#define COLS 100 // n
void create_marks_csv(char *filename,int **a,int n,int m){

printf("\n Creating %s.csv file",filename);

FILE *fp;

int i,j;

filename=strcat(filename,".csv");

fp=fopen(filename,"w+");

//fprintf(fp,"Student Id, Physics, Chemistry, Maths");

for(i=0;i<m;i++){
     for(j=0;j<n;j++){
         if (j<i)
            fprintf(fp,",");
         else
              {
               if (j== n-1)
                  fprintf(fp,"%d",a[i][j]);
               else
                    fprintf(fp,"%d,",a[i][j]);
               }
        }
    fprintf(fp,"\n");
    //fprintf(fp,"\n%d",i+1);
    }


fclose(fp);

printf("\n %sfile created",filename);

}

int main(){

  int **a = malloc(sizeof(int*) * ROWS);
  for(int w = 0; w < ROWS; w++) {
    a[w] = malloc(sizeof(int) * (ROWS-w));
  }

    int i,j,k;

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

return 0;

}
