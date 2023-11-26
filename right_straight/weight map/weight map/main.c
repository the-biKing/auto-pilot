#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include "..\..\..\Rmatrix_data.h"
#include "..\..\..\Smatrix_data.h"

#define STRAIGHTPICNUMBER 8
#define RIGHTPICNUMBER 6

#define ROWS 128
#define COLS 128

#define TURNRIGHT 1
#define GOSTRAIGHT 2
#define STRAIGHTBIAS 0
#define RIGHTBIAS 0

void writeMatrixToFile(const char* filename, int matrix[ROWS][COLS]);
int hadamardSum(int matrix1[ROWS][COLS], int matrix2[ROWS][COLS]);
void matrixAdd(int src[ROWS][COLS], int destination[ROWS][COLS]);
void matrixMinus(int src[ROWS][COLS], int destination[ROWS][COLS]);


int main(void) {
	int rightWeightMap[128][128];
	int straightWeightMap[128][128];
	int rightResult;
	int straightResult;
	int* straight[STRAIGHTPICNUMBER] = { 
		matrixS1,
		matrixS2,
		matrixS3,
		matrixS4,
		matrixS5,
		matrixS6,
		matrixS7,
		matrixS8 
	};
	int *right[RIGHTPICNUMBER] = { 
		matrixR1,
		matrixR2,
		matrixR3,
		matrixR4,
		matrixR5,
		matrixR6
	};
	int calculatedTime=0;
RECALCULATE:
	calculatedTime = calculatedTime + 1;
	FILE* Rfile = fopen("rightWeightMap.txt", "r");
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (fscanf(Rfile, "%d", &rightWeightMap[i][j]) != 1) {
				printf("Error reading file.\n");
				fclose(Rfile);
				return 1;
			}
		}
	}
	fclose(Rfile);
	FILE* Sfile = fopen("straightWeightMap.txt", "r");
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (fscanf(Sfile, "%d", &straightWeightMap[i][j]) != 1) {
				printf("Error reading file.\n");
				fclose(Sfile);
				return 1;
			}
		}
	}
	fclose(Sfile);
	//do the manipulation here
	int correctNum=0;
	for (int i = 0;i < RIGHTPICNUMBER;i++) {
		rightResult = hadamardSum(right[i], rightWeightMap);
		if (rightResult > RIGHTBIAS) {
			//correct
			correctNum++;
		}
		else {
			//wrong
			matrixAdd(right[i], rightWeightMap);
		}
		straightResult = hadamardSum(right[i], straightWeightMap);
		if (straightResult > STRAIGHTBIAS) {
			//wrong
			matrixMinus(right[i], straightWeightMap);
		}
		else {
			//correct
			correctNum++;
		}
	}
	for (int i = 0;i < STRAIGHTPICNUMBER;i++) {
		rightResult = hadamardSum(straight[i], rightWeightMap);
		if (rightResult > RIGHTBIAS) {
			//wrong
			matrixMinus(straight[i], rightWeightMap);
		}
		else {
			//correct
			correctNum++;
		}
		straightResult = hadamardSum(straight[i], straightWeightMap);
		if (straightResult > STRAIGHTBIAS) {
			//correct
			correctNum++;
		}
		else {
			//wrong
			matrixAdd(straight[i], straightWeightMap);
		}
	}
	writeMatrixToFile("rightWeightMap.txt", rightWeightMap);
	writeMatrixToFile("straightWeightMap.txt", straightWeightMap);
	if (correctNum < 2*(STRAIGHTPICNUMBER + RIGHTPICNUMBER)) {
		goto RECALCULATE;
	}
	else if (calculatedTime > 2000) {
		printf("can't find correct map after 2000 iteration");
		return 1;
	}
	else {
		printf("correct weight map found after %d iterations", calculatedTime);
		return 0;
	}

	return 0;
}

void writeMatrixToFile(const char* filename, int matrix[ROWS][COLS]) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}
	// Write the matrix data to the file
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			fprintf(file, "%d ", matrix[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

int hadamardSum(int matrix1[ROWS][COLS], int matrix2[ROWS][COLS]) {
	int sum = 0;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += matrix1[i][j] * matrix2[i][j];
		}
	}

	return sum;
}

void matrixAdd(int src[ROWS][COLS], int destination[ROWS][COLS]) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			destination[i][j] = src[i][j] + destination[i][j];
		}
	}
}
void matrixMinus(int src[ROWS][COLS], int destination[ROWS][COLS]) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			destination[i][j] = destination[i][j] - src[i][j];
		}
	}
}