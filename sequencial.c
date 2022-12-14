#include <stdio.h>
#include <time.h>
#define LIM 200

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

void matrixMultiplication(int rows1, int columns1, int rows2, int columns2, int rows3, int columns3, double timeMeasured, int matrix1[LIM][LIM], int matrix2[LIM][LIM], int matrix3[LIM][LIM]){ //Function to multiply two matrixes;

  time_t start, end;
  start = time(NULL);

  for(int i = 0; i < rows3; i++){ 
    for(int j = 0; j < columns3; j++){
      matrix3[i][j] = 0; //Guarantee that the number will start at 0;
      for(int k = 0; k < rows1; k++){
        matrix3[i][j] += matrix1[i][k]*matrix2[k][j]; //Matrix multiplication;
      }        
    }
  }
  
  end = time(NULL);
  timeMeasured = (double) (end - start);

}


void resultMatrixSaveFile(FILE* file, int rows, int columns, double timeMeasured, int matrix[LIM][LIM]){ //Function to save the result matrix file;

  if(file != NULL){

    fprintf(file,"%d %d\n", rows, columns);

    for(int i = 0; i < rows; i++){
      for(int j = 0; j < columns; j++){
        fprintf(file, "%d ", matrix[i][j]);
      }

    fprintf(file,"\n");

    }

    fprintf(file, "%f", timeMeasured);
    fclose(file);

  }else{

    printf("File Error");

  }
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
  int matrix3[LIM][LIM];

  int rows1, columns1, rows2, columns2, rows3, columns3;

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

  file = fopen("Matriz_3_sequential.txt","w");
  if(columns1 == rows2){

    rows3 = rows1; 
    columns3 = columns2;
    matrixMultiplication(columns1, rows2, rows1, columns2, rows3, columns3, timeMeasured, matrix1, matrix2, matrix3);
    printf("Matrix 3\n");
    resultMatrixSaveFile(file, rows3, columns3, timeMeasured, matrix3);

  }else{

    printf("Incompatible matrixes\n");

  }

  return 0;
}