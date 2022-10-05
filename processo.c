#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define LIM 100

void readMatrix(FILE* file, int matrix[LIM][LIM], int matrix1, int matrix2){ //Function to read a matrix file;

  if(file != NULL) {

    for(int i = 0; i < matrix1; i++) {
      for(int j = 0; j < matrix2; j++) {
        fscanf(file, "%d", &matrix[i][j]);
      }
    }

    fclose(file);

  }else{

    printf("File Error");

  }
}

int elementMultiplication(int* auxElements){ //Function to multiply the elements of the matrix;

    int elementOfMatrix3 = 0;
    int columnOfMatrix1 = auxElements[0];
    for(int i = 1; i <= columnOfMatrix1; i++){
        elementOfMatrix3 += auxElements[i]*auxElements[i+columnOfMatrix1];
    }

   return elementOfMatrix3;
   
}

void matrixMultiplication(int* auxElements, int rows1, int columns1, int rows2, int columns2, int matrix1[LIM][LIM], int matrix2[LIM][LIM], pid_t* processos, FILE* file, int maxSize, double timeMeasured){ //Function to multipky the matrixes using processes;

  fprintf(file,"%d %d\n", rows1, columns2);

  time_t start, end;
  start = time(NULL);

  for(int i = 0; i < rows1; i++){
    for(int j = 0; j < columns2; j++){
                
      auxElements = (int *)malloc((20)*sizeof(int));

      auxElements[0] = columns1;

      for(int k = 0; k < columns1; k++){
        auxElements[k+1] = matrix1[i][k];
      }
      for(int k = 0; k < rows2; k++){
        auxElements[k+columns1+1] = matrix2[k][j];
      }

			int resultElement = elementMultiplication(auxElements);

			fprintf(file,"%d ", resultElement);
             
		}

		fprintf(file,"\n");

  }

  end = time(NULL);
  timeMeasured = (double) (end - start);
  fprintf(file, "%f", timeMeasured);

}


void printMatrix(int rows, int columns, int matrix[LIM][LIM]){ //Function to print a matrix;

  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
             
        printf("%d ",matrix[i][j]);

    }

    printf("\n");

  }
}

int main(int argc, char *argv[]){

  FILE * file;

  int matrix1[LIM][LIM];
  int matrix2[LIM][LIM];

  int rows1, columns1, rows2, columns2;

  double timeMeasured;

  file = fopen(argv[1], "r");
  fscanf(file, "Matrix %d x %d", &rows1, &columns1);
  readMatrix(file, matrix1, rows1, columns1);

  file = fopen(argv[2], "r");
  fscanf(file, "Matrix %d x %d", &rows2, &columns2);
  readMatrix(file, matrix2, rows2, columns2);

  printf("Matrix 1\n");  
  printMatrix(rows1, columns1, matrix1);

  printf("Matrix 2\n"); 
  printMatrix(rows2, columns2, matrix2);   


  int maxSize = rows1*columns2;
  pid_t processes[maxSize];
  file = fopen("Matrix_3_process.txt","w");
    
  int count = 0;
  int* auxElements = NULL;
  if(rows1 == columns2){
  	for(int i = 0; i < maxSize; i++){
    	processes[i] = fork();
      if(processes[count] == 0){
        matrixMultiplication(auxElements,  rows1,  columns1,  rows2,  columns2, matrix1,  matrix2, processes, file, maxSize, timeMeasured);
        exit(0);
      }else{
      	pid_t status = wait(NULL);
      	exit(0);
      }
    }

  }else{
    printf("Incompatible matrixes\n");
  }

  fclose(file);
  free(auxElements);
	return 0;
}