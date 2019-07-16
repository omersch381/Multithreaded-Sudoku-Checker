#include "constants.h"
#ifndef MAINQ2_H_
#define MAINQ2_H_

#define SUDOKU_NUMBERS 9
#define NTHREADS       3
#define ARRAYSIZE     27
int checkRow2(int mat[ROWS_SIZE][COLS_SIZE], int numberRow, int cols);
int checkCulumn2(int mat[ROWS_SIZE][COLS_SIZE], int rows, int numberCol);
int checkSubMatrix2(int mat[ROWS_SIZE][COLS_SIZE], int rowStart, int colStart);
void scanMatrixFromUser2();
void scanMatrixFromFile2(char* argv1);
int func1();
int func2();
int func3();
int func4();
int func5();
int func6();
int func7();
int func8();
int func9();
int func10();
int func11();
int func12();
int func13();
int func14();
int func15();
int func16();
int func17();
int func18();
int func19();
int func20();
int func21();
int func22();
int func23();
int func24();
int func25();
int func26();
int func27();

typedef int(*funcArray)(); //declare typedef of functions

typedef struct {
	int id; // thread id
	funcArray *funcs; // shared array of functions
	int *sum; //shared answer for sum of all elemnts
	pthread_mutex_t *mutex; // mutex to synchronize a write to sum
} ThreadParam;

#endif /* MAINQ2_H_ */
