#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void create_matrix(FILE *file, int n, int m){ //Function to create a n x m matrix;

  fprintf(file, "Matrix %d x %d \n", n, m); //Write the matrix size;
  fprintf(file, "\n");

  for(int i = 0; i<n; i++){
    for(int j = 0; j < m; j++){
      fprintf(file, "%d ", rand() % 10); //Write random numbers (0 - 10) to the matrix file;
    }
    fprintf(file, "\n");
  }
}

int main(int argc, char *argv[]){

  void create_matrix(FILE *file, int n, int m);

  srand(time(NULL)); //Initialization for the rand() function;

  int n1, m1, n2, m2;

  n1 = atoi(argv[1]); //Matrix 1 rows;
  m1 = atoi(argv[2]); //Matrix 1 columns;
  n2 = atoi(argv[3]); //Matrix 2 rows;
  m2 = atoi(argv[4]); //Matrix 2 columns;

  FILE *file1, *file2; //Creating the matrixes;
  file1 = fopen("Matrix_1.txt","w");
  file2 = fopen("Matrix_2.txt","w");

  create_matrix(file1, n1, m1); //Creating matrix 1;
  create_matrix(file2, n2, m2); //Creating matrix 2;

  //Closing the files;
  fclose(file1);
  fclose(file2);

  return 0;
}