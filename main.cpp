#include "RenderGameLoop.h"
//#include "Matrix.h"

int main(){
//
//	Matrix m;
//
//	m.mArr[1][0] = 3;
//	m.mArr[1][2] = 3;
//	m.mArr[0][2] = 3;
////	matrix.mArr[1][3] = 3;
//
//	m.Transpose();

	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}

	BeginRenderingLoop();

	return EXIT_WITH_SUCCESS;
}