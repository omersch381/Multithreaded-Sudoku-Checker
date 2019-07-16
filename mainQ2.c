#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include "mainQ2.h"

//Gadi told us that it is ok to put those variables as global variables even though that we could just pass them in the struct
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int finished = 0;
int matrix[ROWS_SIZE][COLS_SIZE];
void *do_work(void *param) {
	int *sum, result = 0;
	funcArray *funcs;
	pthread_mutex_t *mutex;

	// Thread array, mutex and global sum
	funcs = ((ThreadParam *) param)->funcs;
	mutex = ((ThreadParam *) param)->mutex;
	sum = ((ThreadParam *) param)->sum;

	while (finished < ARRAYSIZE) {
		if (pthread_mutex_lock(mutex) != 0)
			perror("Mutex didn't Lock #1");
		if (finished >= ARRAYSIZE) {
			if (pthread_cond_signal(&cond) != 0)
				perror("Mutex Didn't Signal #1");
			if (pthread_mutex_unlock(mutex) != 0)
				perror("Mutex Didn't Unlock #1");
			return NULL;
		}
		result = funcs[finished]();
		*sum += result;
		finished = finished + 1;
		if (pthread_mutex_unlock(mutex) != 0)
			perror("Mutex Didn't Unlock #2");
	}
	pthread_exit(NULL);
}
int main(int argc, char* argv[]) {

	int i, status, sum = 0;
	if (argc < 2) {
		scanMatrixFromUser2();
	} else {
		scanMatrixFromFile2(argv[1]);

	}
	funcArray func[ARRAYSIZE] = { &func1, &func2, &func3, &func4, &func5,
			&func6, &func7, &func8, &func9, &func10, &func11, &func12, &func13,
			&func14, &func15, &func16, &func17, &func18, &func19, &func20,
			&func21, &func22, &func23, &func24, &func25, &func26, &func27 }; //make array func of type funcArray
	ThreadParam params[NTHREADS];
	pthread_t threads[NTHREADS];
	pthread_mutex_t sum_mutex;
	if (pthread_mutex_init(&sum_mutex, NULL) != 0)
		perror("Mutex Initialization Failed");
	for (i = 0; i < NTHREADS; i++) {
		params[i].funcs = func;
		params[i].id = i;
		params[i].sum = &sum;
		params[i].mutex = &sum_mutex;
		status
				= pthread_create(&threads[i], NULL, do_work,
						(void *) &params[i]);
		if (status != 0)
			printf("\npthread creation failed with thread num #%d\n", i);
	}

	if (pthread_mutex_lock(&sum_mutex) != 0)
		perror("Mutex Didn't Lock");

	while (finished < ARRAYSIZE)
		if (pthread_cond_wait(&cond, &sum_mutex) != 0)
			perror("Conditional Didn't Wait");

	if (pthread_mutex_unlock(&sum_mutex) != 0)
		perror("Mutex Didn't Unlsock");
	printf(sum == ARRAYSIZE ? "solution is legal\n" : "solution is not legal\n");
	for (i = 0; i < NTHREADS; i++)
		if (pthread_join(threads[i], NULL) == -1)
			perror("pthread_join error");

	/* Clean up and exit */
	if (pthread_mutex_destroy(&sum_mutex) != 0)
		perror("Mutex Destroy Failed");
	pthread_exit(NULL);
}
void scanMatrixFromUser2() {
	int i, j;
	printf("Please Enter The Matrix - (int - enter - int without spaces):\n");
	for (i = 0; i < ROWS_SIZE; i++)
		for (j = 0; j < COLS_SIZE; j++)
			scanf("%d", &matrix[i][j]);
}
void scanMatrixFromFile2(char* argv1) {
	int i, j;
	char* fileName = NULL;
	FILE* f;
	fileName = argv1;
	if (!(f = fopen(fileName, "r")))
		perror("File Open Failed");
	for (i = 0; i < ROWS_SIZE; i++)
		for (j = 0; j < COLS_SIZE; j++)
			fscanf(f, "%d", &matrix[i][j]);
	if (fclose(f) != 0)
		perror("File Closure Failed");
}

int func1() {
	return checkRow2(matrix, 1, 9);
}

int func2() {
	return checkRow2(matrix, 2, 9);
}

int func3() {
	return checkRow2(matrix, 3, 9);
}
int func4() {
	return checkRow2(matrix, 4, 9);
}

int func5() {
	return checkRow2(matrix, 5, 9);
}

int func6() {
	return checkRow2(matrix, 6, 9);
}
int func7() {
	return checkRow2(matrix, 7, 9);
}
int func8() {
	return checkRow2(matrix, 8, 9);
}
int func9() {
	return checkRow2(matrix, 0, 9);
}
int func10() {
	return checkCulumn2(matrix, 9, 0);
}

int func11() {
	return checkCulumn2(matrix, 9, 1);
}

int func12() {
	return checkCulumn2(matrix, 9, 2);
}
int func13() {
	return checkCulumn2(matrix, 9, 3);
}

int func14() {
	return checkCulumn2(matrix, 9, 4);
}

int func15() {
	return checkCulumn2(matrix, 9, 5);
}
int func16() {
	return checkCulumn2(matrix, 9, 6);
}
int func17() {
	return checkCulumn2(matrix, 9, 7);
}
int func18() {
	return checkCulumn2(matrix, 9, 8);
}
int func19() {
	return checkSubMatrix2(matrix, 0, 0);
}

int func20() {
	return checkSubMatrix2(matrix, 0, 3);
}

int func21() {
	return checkSubMatrix2(matrix, 0, 6);
}
int func22() {
	return checkSubMatrix2(matrix, 3, 0);
}

int func23() {
	return checkSubMatrix2(matrix, 3, 3);
}

int func24() {
	return checkSubMatrix2(matrix, 3, 6);
}
int func25() {
	return checkSubMatrix2(matrix, 6, 0);
}
int func26() {
	return checkSubMatrix2(matrix, 6, 3);
}
int func27() {
	return checkSubMatrix2(matrix, 6, 6);
}

int checkRow2(int mat[ROWS_SIZE][COLS_SIZE], int numberRow, int cols) {
	int i, j;
	int result;
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

int checkCulumn2(int mat[ROWS_SIZE][COLS_SIZE], int rows, int numberCol) {
	int i, j;
	int result;
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
int checkSubMatrix2(int mat[ROWS_SIZE][COLS_SIZE], int rowStart, int colStart) {
	int i, x, y, result, rowEnd = rowStart + 2, colEnd = colStart + 2;
	for (i = 0; i < SUDOKU_NUMBERS; i++) {
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
