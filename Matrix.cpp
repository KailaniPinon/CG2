#include "Matrix.h"


void Matrix::MyMatrix() {
	//MakeIdentity();
	Transpose();
}

void Matrix::MakeIdentity() {

	for (int i = 0; i < 4; ++i) {
	//i represent index of row
	//j represents index of column
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				mArr[j][i] = 1;
			}
		}
	}
	/*
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				arr[i][j] = (i == j) ? 1 : 0;
			}

		}
	}
	*/
}

void Matrix::Transpose() {
	for (int i = 0; i < 4; ++i) {
		//i represent index of column
		//j represents index of row
		for (int j = i; j < 4; ++j) {
			//every time we look thru a row, increment column value
			mArr[i][j] = mArr[0][i];

		}
	}
}

//TODO: Not working 
Matrix Matrix::Transposed() {
	Matrix transposed;

	for (int i = 0; i < 4; ++i) {
		//i represent index of column
		//j represents index of row
		for (int j = i; j < 4; ++j) {
		//every time we look thru a row, increment column value
			transposed.mArr[i][j] = mArr[0][i];

		}
	}
	return transposed;
/*
	float newArr[4][4] = { 0,0 };

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			arr[i][j] = newArr[j][i];
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			arr[i][j] = newArr[i][j];
		}
	}
*/
}

