#include<iostream>
#include<stdlib.h>
#include<fstream>

#define SIZEMAX 10

using namespace std;

void resetRowAndColMatrix(int[SIZEMAX][SIZEMAX], int[SIZEMAX][SIZEMAX], int);
void setRow(int[SIZEMAX][SIZEMAX], int, int);
void setCol(int[SIZEMAX][SIZEMAX], int, int);
void howManySquare(int[SIZEMAX][SIZEMAX], int[SIZEMAX][SIZEMAX], int, fstream &, int);

void main() {

	char inputChar;
	int dotNumber, lineNumber, rowMatrix[SIZEMAX][SIZEMAX], colMatrix[SIZEMAX][SIZEMAX];
	int tempI, tempJ, i, problemNumber;

	fstream inputDataFile, outputDataFile;
		
	inputDataFile.open("input.txt", ios::in);
	if (!inputDataFile)
	{
		cout << "\nError: The file from which the data will be imported was not found!" << endl << endl << endl;
		exit(0);
	}

	outputDataFile.open("output.txt", ios::out);
	if (!outputDataFile)
	{
		cout << "\nError: There was a problem printing the file!" << endl << endl << endl;
		exit(0);
	}

	   	 
	problemNumber = 1;
	while (!inputDataFile.eof()) {
				
		inputDataFile >> dotNumber;
		resetRowAndColMatrix(rowMatrix, colMatrix, dotNumber);
		inputDataFile >> lineNumber;
				
		for (i = 0; i < lineNumber; i++) {
			inputDataFile >> inputChar;
			if (inputChar == 'H') {
				inputDataFile >> tempI;
				inputDataFile >> tempJ;
				setRow(rowMatrix, tempI - 1, tempJ - 1);

			}
			if (inputChar == 'V') {
				inputDataFile >> tempJ;
				inputDataFile >> tempI;
				setCol(colMatrix, tempI - 1, tempJ - 1);

			}
		}
		
		howManySquare(rowMatrix, colMatrix, dotNumber, outputDataFile, problemNumber);
		problemNumber++;
	}
	


	inputDataFile.close();
	outputDataFile.close();

	cout << "\nAll transactions have been successfully completed. Please check the output file!";

	cout << endl << endl << endl << endl;
	system("pause");
}


void resetRowAndColMatrix(int rowMatrix[SIZEMAX][SIZEMAX], int colMatrix[SIZEMAX][SIZEMAX], int sizeOfGameBoard) {
	int i, j;
	for (i = 0; i < sizeOfGameBoard; i++) {
		for (j = 0; j < sizeOfGameBoard; j++) {
			rowMatrix[i][j] = 0;
			colMatrix[i][j] = 0;
		}
	}
}
void setRow(int rowMatrix[SIZEMAX][SIZEMAX], int tempI, int tempJ) {
	rowMatrix[tempI][tempJ] = 1;
}
void setCol(int colMatrix[SIZEMAX][SIZEMAX], int tempI, int tempJ) {
	colMatrix[tempI][tempJ] = 1;
}
void howManySquare(int rowMatrix[SIZEMAX][SIZEMAX], int colMatrix[SIZEMAX][SIZEMAX], int dotNumber, fstream &outputDataFile, int problemNumber) {
	int i, j, k, squareSize = 1, squareCounter[SIZEMAX], flagOfSquare, counterN, newFlag;

	for (i = 0; i < dotNumber; i++) {
		squareCounter[i] = 0;
	}



	for (k = 0; k < squareSize; k++) {
		for (i = 0; i < dotNumber; i++) {
			for (j = 0; j < dotNumber; j++) {
				flagOfSquare = 1;
				for (counterN = 0; counterN < squareSize; counterN++) {
					if (rowMatrix[i][j + counterN] != 1 || rowMatrix[i + squareSize][j + counterN] != 1 || colMatrix[i + counterN][j] != 1 || colMatrix[i + counterN][j + squareSize] != 1) {
						flagOfSquare = 0;
						break;
					}
				}
				if (flagOfSquare == 1) {
					squareCounter[squareSize]++;
				}
			}
		}
		squareSize++;
		if (squareSize == dotNumber)
			break;
	}


	outputDataFile << "Problem #" << problemNumber << endl << "----------" << endl;

	for (i = 0; i < dotNumber; i++) {
		if (squareCounter[i] != 0) {
			newFlag = 1;
			break;
		}
		else
			newFlag = 0;
	}

	if (newFlag == 0)
		outputDataFile << "No completed squares can be found!" << endl << endl;
	else {
		for (i = 0; i < dotNumber; i++) {
			if (squareCounter[i] != 0) {
				outputDataFile << squareCounter[i] << " square(s) of size " << i << "." << endl;
			}
		}
		outputDataFile << endl;
	}
}
