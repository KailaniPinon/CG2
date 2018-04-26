#pragma once

class Matrix {
public:
	void MyMatrix();
	void MakeIdentity();
	Matrix Transposed();
	void Transpose();

public:
	float mArr[4][4] = {0 , 0};
};