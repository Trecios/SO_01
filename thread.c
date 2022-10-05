
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
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

void *elementMultiplication(void* argument){ //Function to multiply the elements of the matrix;

  int *auxElements = (int *)argument;
  int *resultElement = (int*)malloc(sizeof(int));
  
  int elementOfMatrixC = 0;
  int columnOfMatrix1 = auxElements[0];

  for(int i = 1; i <= columnOfMatrix1; i++){
    elementOfMatrixC += auxElements[i]*auxElements[i+columnOfMatrix1];
  }

  *resultElement = elementOfMatrixC;
   
  pthread_exit(resultElement);

}

void matrixMultiplication(int* auxElements, int rows1, int columns1, int rows2, int columns2, int matrix1[LIM][LIM], int matrix2[LIM][LIM], pthread_t *threads,  double timeMeasured, int count){ //Function to multipky the matrixes using threads;

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
           
      pthread_create(&threads[count++], NULL, elementMultiplication, (void*)(auxElements));
    }
  }

  end = time(NULL);
  timeMeasured = (double) (end - start);

}

void resultMatrixSaveFiles(FILE* file, pthread_t *threads, int maxSize, int columns2, double timeMeasured){ //Function to save the result matrix file;

  for(int i = 0; i < maxSize; i++){
    void *resultElementFromThread;
        
    pthread_join(threads[i], &resultElementFromThread);
                   
    int *resultElement = (int *)resultElementFromThread;

    fprintf(file, "%d ", *resultElement);

    if ((i + 1) % columns2 == 0){
      fprintf(file, "\n");
    }
  }

  fprintf(file, "%f", timeMeasured);

  fclose(file);

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
  int count = 0;
  int* auxElements = NULL;
  pthread_t *threads;

  threads = (pthread_t*)malloc(maxSize*sizeof(pthread_t));

  if(columns1 == rows2){
    matrixMultiplication(auxElements,  rows1,  columns1,  rows2,  columns2, matrix1,  matrix2, threads, timeMeasured, count);
  }else{
    printf("Incompatible matrixes\n");
  }

  file = fopen("Matriz_3_thread.txt","w");
  fprintf(file,"%d %d\n", rows1, columns2);
  resultMatrixSaveFiles(file, threads, maxSize, columns2, timeMeasured);

  free(auxElements);
  free(threads);

  return 0;
}