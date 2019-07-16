#ifndef MAINQ1_H_
#define MAINQ1_H_

#define NUM_OF_THREADS 27
int checkMatrixFromFile(char* fileName);
void *threadFunction(void*);

void transformFromCharsToIntQuestion1(const char* sudokuFromInputFromInput,
		char* suduku);
void ToMatrix(char* sudokuFromFile, int matrix[ROWS_SIZE][COLS_SIZE]);
int checkRow(int mat[ROWS_SIZE][COLS_SIZE], int numberRow, int cols);
int checkCulumn(int mat[ROWS_SIZE][COLS_SIZE], int rows, int numberCol);
int checkSubMatrix(int mat[ROWS_SIZE][COLS_SIZE], int rowStart, int colStart);
int checkAllRows(int mat[ROWS_SIZE][COLS_SIZE], int rows, int cols);
int checkAllColumns(int mat[ROWS_SIZE][COLS_SIZE], int rows, int cols);
int checkAllSubMatrix(int mat[ROWS_SIZE][COLS_SIZE]);
int checkSubMatrix(int mat[ROWS_SIZE][COLS_SIZE], int rowStart, int colStart);
int results[NUM_OF_THREADS];
int matrix[ROWS_SIZE][COLS_SIZE];
void scanMatrixFromUser();
void scanMatrixFromFile(char* argv1);
struct thread_data {
	int thread_id;
};

#endif /* MAINQ1_H_ */
