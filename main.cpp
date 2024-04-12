#include "ClassMatrix.h"
int main()
{
    Matrix<int> matrix1;
    matrix1.Print();
    std::string FileName;
    std::cout << "Enter the name of file (MatrixExample.txt)";
    std::cin >>FileName;
    Matrix<double> matrix2(FileName); //Reading matrix from file
    matrix2.Print();
    matrix1.WriteToAFile(); //Writing matrix to file
    std::cout << "Matrix multiplication: " << std::endl;
    (matrix1 * matrix2).Print();
    std::cout << "Multiplying a matrix by a number: " << std::endl;
    (matrix1 * 3).Print();
    std::cout << "Subtraction of matrices: " << std::endl;
    (matrix1 - matrix2).Print();
    std::cout << "Sum of matrices: " << std::endl;
    (matrix1 + matrix2).Print();
    std::cout << "Comparison of matrices: " << std::endl;
    std::cout << (matrix1 == matrix2) << std::endl;
    std::cout << "Elementary transformation of the first type: " << std::endl;
    matrix1.FirstElementaryTransformation(0, 1);
    matrix1.Print();
    std::cout << "Elementary transformation of the second type: " << std::endl;
    matrix1.SecondElementaryTransformation(0, 2);
    matrix1.Print();
    std::cout << "Elementary transformation of the third type: " << std::endl;
    matrix1.ThirdElementaryTransformation(0, 2, 1);
    matrix1.Print();
    std::cout << "Matrix determinant: " << std::endl;
    std::cout << matrix1.Determinant()<<std::endl;
    std::cout << "Inverse matrix: " << std::endl;
    (!matrix1).Print();
    std::cout <<"Matrix assignment"<<std::endl;
    Matrix matrix3=matrix2;
    matrix3.Print();
    std::cout <<"Null matrix"<<std::endl;
    Matrix matrix4=Matrix<int>::InitializationByZeros(3,4);
    matrix4.Print();
    std::cout <<"Matrix of units"<<std::endl;
    Matrix matrix5=Matrix<int>::InitializationByUnits(4,5);
    matrix5.Print();
}
