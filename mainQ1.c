#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include "constants.h"
#include "mainQ1.h"
int matrix[ROWS_SIZE][COLS_SIZE];
int main(int argc, char* argv[]) {
	pthread_t threads[NUM_OF_THREADS];
	struct thread_data thread_data_array[NUM_OF_THREADS];
	int rc = 0, t;

	if (argc < 2)
		scanMatrixFromUser();
	else
		scanMatrixFromFile(argv[1]);

	// get data to threads
	for (t = 0; t < NUM_OF_THREADS; t++)
		thread_data_array[t].thread_id = t;

	// Launch threads and pass the thread id as a parameter
	for (t = 0; t < NUM_OF_THREADS; t++) {
		if ((rc = pthread_create(&threads[t], NULL, threadFunction,
				(void *) &thread_data_array[t]))) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	// Wait till all threads will finish their job
	for (t = 0; t < NUM_OF_THREADS; t++)
		pthread_join(threads[t], NULL);

	// Display Result of work Threads
	for (int i = 0; i < NUM_OF_THREADS; i++) {
		if (results[i] == 0) {
			printf("solution is not legal\n");
			pthread_exit(NULL);
			return 0;
		}
	}//else
	printf("solution is legal\n");
	/* Last thing that main() should do */
	pthread_exit(NULL);
	return 0;
}
void scanMatrixFromUser() {
	int i, j;
	printf("Please Enter The Matrix - (int - enter - int without spaces):\n");
	for (i = 0; i < ROWS_SIZE; i++)
		for (j = 0; j < COLS_SIZE; j++)
			scanf("%d", &matrix[i][j]);
}
void scanMatrixFromFile(char* argv1) {
	int i, j;
	FILE* f;
	char* fileName = argv1;
	if (!(f = fopen(fileName, "r")))
		perror("File Open Failed");
	for (i = 0; i < ROWS_SIZE; i++)
		for (j = 0; j < COLS_SIZE; j++)
			fscanf(f, "%d", &matrix[i][j]);
	if (fclose(f) != 0)
		perror("File Closure Failed");
}
void *threadFunction(void *thread_arg) {
	int taskid;
	struct thread_data *my_data;
	my_data = (struct thread_data *) thread_arg;
	taskid = my_data->thread_id;
	if (taskid < 9) {
		results[taskid] = checkRow(matrix, taskid, COLS_SIZE);
		//	   results[taskid] = 1;
	} else if (taskid >= 9 && taskid < 18) {
		int colToCheck = taskid - 9;
		results[taskid] = checkCulumn(matrix, ROWS_SIZE, colToCheck);
		//	 results[taskid] = 5;
	} else if (taskid >= 18 && taskid < NUM_OF_THREADS) {
		int rowToCheck = -1; // to get error id switch is not good
		int colToCheck = -1;
		switch (taskid) {
		case 18:
			rowToCheck = 0;
			colToCheck = 0;
			break;
		case 19:
			rowToCheck = 3;
			colToCheck = 0;
			break;
		case 20:
			rowToCheck = 6;
			colToCheck = 0;
			break;
		case 21:
			rowToCheck = 3;
			colToCheck = 0;
			break;
		case 22:
			rowToCheck = 3;
			colToCheck = 3;
			break;
		case 23:
			rowToCheck = 3;
			colToCheck = 6;
			break;
		case 24:
			rowToCheck = 6;
			colToCheck = 0;
			break;
		case 25:
			rowToCheck = 6;
			colToCheck = 3;
			break;
		case 26:
			rowToCheck = 6;
			colToCheck = 6;
			break;
		}

		results[taskid] = checkSubMatrix(matrix, rowToCheck, colToCheck);
	} else {
		perror("Invalid ThreadID!");
	}

	//	printf("Thread %d:  result: %d\n", taskid, results[taskid]);
	pthread_exit(NULL);
}

int checkMatrix(char* sudokuChars, char checkType) {
	int matrix[ROWS_SIZE][COLS_SIZE], res;
	ToMatrix(sudokuChars, matrix);
	res = 0;
	switch (checkType) {
	case 0:
		res = checkAllRows(matrix, ROWS_SIZE, COLS_SIZE);
		return res;
		break;
	case 1:
		res = checkAllColumns(matrix, ROWS_SIZE, COLS_SIZE);
		return res;
		break;
	case 2:
		res = checkAllSubMatrix(matrix);
		return res;
		break;
	}
	return res;
}
int checkRow(int mat[ROWS_SIZE][COLS_SIZE], int numberRow, int cols) {
	int i, j, result;
	for (i = 0; i < ROWS_SIZE; i++) {
		result = 0;
		for (j = 0; j < cols; j++)
			if (sudokuNumbers[i] == mat[numberRow][j])
				result = 1;
		if (result != 1)
			return 0;
	}
	return 1;
}
int checkAllRows(int mat[ROWS_SIZE][COLS_SIZE], int rows, int cols) {
	int i, result = 0;
	for (i = 0; i < rows; i++)
		result = checkRow(mat, i, cols);
	return result;
}

int checkCulumn(int mat[ROWS_SIZE][COLS_SIZE], int rows, int numberCol) {
	int i, j, result;
	for (i = 0; i < COLS_SIZE; i++) {
		result = 0;
		for (j = 0; j < rows; j++)
			if (sudokuNumbers[i] == mat[j][numberCol])
				result = 1;
		if (result != 1)
			return 0;
	}
	return 1;
}
int checkAllColumns(int mat[ROWS_SIZE][COLS_SIZE], int rows, int cols) {
	int i, result;
	for (i = 0; i < cols; i++)
		result = checkCulumn(mat, rows, i);
	return result;
}
int checkSubMatrix(int mat[ROWS_SIZE][COLS_SIZE], int rowStart, int colStart) {
	int i, x, y, result, rowEnd = rowStart + 2, colEnd = colStart + 2;
	for (i = 0; i < 9; i++) {
		result = 0;
		for (x = rowStart; x < rowEnd + 1; x++)
			for (y = colStart; y < colEnd + 1; y++)
				if (sudokuNumbers[i] == mat[x][y])
					result = 1;
		if (result != 1)
			return 0;
	}
	return 1;
}
int checkAllSubMatrix(int mat[ROWS_SIZE][COLS_SIZE]) {
	int i, result, rowToCheck, columnToCheck;
	rowToCheck = 0;
	columnToCheck = 0;
	for (i = 0; i < ROWS_SIZE; i++) {
		result = checkSubMatrix(mat, rowToCheck, columnToCheck);
		if (result == 0)
			return 0;
		else {
			columnToCheck += 3;
			if (columnToCheck > 6) {
				columnToCheck = 0;
				rowToCheck += 3;
			}
		}
	}
	return 1;
}
void ToMatrix(char* sudokuFromFile, int matrix[ROWS_SIZE][COLS_SIZE]) {
	int i, j, k;
	for (k = 0, i = 0; i < SUDOKU_NUMBERS; i++) {
		for (j = 0; j < SUDOKU_NUMBERS; j++) {
			matrix[i][j] = (int) (sudokuFromFile[k]);
			k++;
		}
	}
}

