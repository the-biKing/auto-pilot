#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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
int hadamardSum(int staticMatrix[ROWS][COLS], int** mallocMatrix);

int main(void) {
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
	//store training data to pointer arrays so it's easier to iterate through them
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
	int rightResult = hadamardSum(right[0], rightWeightMap);
	printf("%d", rightResult);




	//free memory
	for (int i = 0; i < ROWS; i++) {
		free(rightWeightMap[i]);
		free(straightWeightMap[i]);
	}
	free(rightWeightMap);
	free(straightWeightMap);
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

int hadamardSum(int staticMatrix[ROWS][COLS], int **mallocMatrix) {
	int sum = 0;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += staticMatrix[i][j] * mallocMatrix[i][j];
		}
	}

	return sum;
}