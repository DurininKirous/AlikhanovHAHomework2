/*#include <iostream>
#include <cmath>
#include <fstream>
#include "ClassMatrix.h"












template<typename T>
bool operator !=(int a, Matrix<T> First)
{

    Matrix NewMatrix(First.GetLines(), First.GetColumns());
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            if (i == j) {
                *(*(NewMatrix.GetMatrix()+i)+i) += a;
            }
        }
    }
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            if (*(*(First.GetMatrix()+i)+j) != *(*(NewMatrix.GetMatrix()+i)+j)) {
                return true;
            }
        }
    }
    return false;
}
template<typename T>
bool operator ==(int a, Matrix<T> First)
{
    Matrix NewMatrix(First.GetLines(), First.GetColumns());
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            if (i == j) {
                *(*(NewMatrix.GetMatrix()+i)+i) += a;
            }
        }
    }
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            if (*(*(First.GetMatrix()+i)+j) != *(*(NewMatrix.GetMatrix()+i)+j)) {
                return false;
            }
        }
    }
    return true;
}*/
