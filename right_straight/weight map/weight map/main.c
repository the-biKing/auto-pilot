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

void writeMatrixToFile(const char* filename, int** matrix);
int hadamardSum(int staticMatrix[ROWS][COLS], int** mallocMatrix);
void matrixAdd(int src[ROWS][COLS], int** destination);
void matrixMinus(int src[ROWS][COLS], int** destination);


int main(void) {
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
	//allocate memory for weight map
	int** rightWeightMap = malloc(ROWS * sizeof(int*));
	int** straightWeightMap = malloc(ROWS * sizeof(int*));
	if (rightWeightMap == NULL || straightWeightMap == NULL) {
		printf("Memory allocation failed.\n");
		free(rightWeightMap);
		free(straightWeightMap);
		return 1;
	}
	for (int i = 0; i < ROWS; i++) {
		rightWeightMap[i] = malloc(COLS * sizeof(int));
		straightWeightMap[i] = malloc(COLS * sizeof(int));
		if (rightWeightMap[i] == NULL || straightWeightMap[i] == NULL) {
			printf("Memory allocation failed.\n");
			for (int j = 0; j < i; j++) {
				free(rightWeightMap[j]);
				free(straightWeightMap[j]);
			}
			free(rightWeightMap);
			free(straightWeightMap);
			return 1;
		}
	}
	//store wight map into allocated memory

	FILE* Rfile = fopen("rightWeightMap.txt", "r");
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (fscanf(Rfile, "%d", &rightWeightMap[i][j]) != 1) {
				printf("Error reading file.\n");
				fclose(Rfile);
				for (int i = 0; i < ROWS; i++) {
					free(rightWeightMap[i]);
				}
				free(rightWeightMap);
				for (int i = 0; i < ROWS; i++) {
					free(straightWeightMap[i]);
				}
				free(straightWeightMap);
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
				for (int i = 0; i < ROWS; i++) {
					free(straightWeightMap[i]);
				}
				free(straightWeightMap);
				for (int i = 0; i < ROWS; i++) {
					free(rightWeightMap[i]);
				}
				free(rightWeightMap);
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

	for (int i = 0; i < ROWS; i++) {
		free(rightWeightMap[i]);
		free(straightWeightMap[i]);
	}
	free(rightWeightMap);
	free(straightWeightMap);

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

void writeMatrixToFile(const char* filename, int **matrix) {
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

int hadamardSum(int staticMatrix[ROWS][COLS], int **mallocMatrix) {
	int sum = 0;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += staticMatrix[i][j] * mallocMatrix[i][j];
		}
	}

	return sum;
}

void matrixAdd(int src[ROWS][COLS], int **destination) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			destination[i][j] = src[i][j] + destination[i][j];
		}
	}
}
void matrixMinus(int src[ROWS][COLS], int **destination) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			destination[i][j] = destination[i][j] - src[i][j];
		}
	}
}