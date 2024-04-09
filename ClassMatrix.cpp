#include <iostream>
#include <cmath>
#include <fstream>
#include "ClassMatrix.h"
template<typename T>
void Matrix<T>::Print()
{
    for (int i = 0; i < lines; i++)
    {
        std::cout << "[";
        for (int j = 0; j < columns; j++)
        {
            if (j != columns - 1) { std::cout << *(*(matrix+i)+j) << " "; }
            else { std::cout << *(*(matrix + i) + j); }
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}
template<typename T>
void Matrix<T>::Init()
{
    std::cout << "Заполните матрицу!\n";
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cin >> *(*(matrix + i) + j);
        }
    }
}
template<typename T>
void Matrix<T>::WriteToAFile()
{
    std::string FileName;
    std::cout << "Enter the name of file:";
    std::cin >> FileName;
    FileName[FileName.find("\n")] = '\0';
    std::ofstream out;
    out.open(FileName);
    for (int i = 0; i < lines; i++) {
        out <<"[";
        for (int j = 0; j < columns; j++) {
            out <<matrix[i][j];
            if (j == columns - 1) { out <<"]"; }
        }
        out <<"]";
    }
    out.close();
}
template<typename T>
void Matrix<T>::FirstElementaryTransformation(int FirstLine, int SecondLine)
{
    T tmp;
    for (int i = 0; i < columns; i++) {
        tmp = matrix[FirstLine][i];
        matrix[FirstLine][i] = matrix[SecondLine][i];
        matrix[SecondLine][i] = tmp;
    }
}
template<typename T>
void Matrix<T>::SecondElementaryTransformation(int ChangeLine, T MultiPlier)
{
    for (int i = 0; i < columns; i++) {
        matrix[ChangeLine][i] *= MultiPlier;
    }
}
template<typename T>
void Matrix<T>::ThirdElementaryTransformation(int TakeLine, T MultiPlier, int ChangeLine)
{
    for (int i = 0; i < columns; i++) {
        matrix[ChangeLine][i] += matrix[TakeLine][i] * MultiPlier;
    }
}
template<typename T>
double Matrix<T>::Determinant()
{
    Matrix& p = *this;
    double det = 0;
    if (lines != columns) 
    {
        std::cout << "There is no determinant for such a matrix\n";
        return 0;
    }
    else {
        if ((columns-p.columns) ==  columns-1) 
        { 
            return p.matrix[0][0];
        }
        for (int i = 0; i < p.columns; i++) 
        {
            Matrix NewMatrix(p, 0, i);
            det += p.matrix[0][i] * pow(-1, i + 2)* NewMatrix.Determinant();
        }
        return det;
    }
}
template<typename T>
void Matrix<T>::Transposition()
{
    double tmp;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < i; j++) {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}
template<typename T>
int Matrix<T>::GetLines()
{
    return lines;
}
template<typename T>
int Matrix<T>::GetColumns()
{
    return columns;
}
template<typename T>
T** Matrix<T>::GetMatrix()
{
    return matrix;
}
template<typename T>
Matrix<T>::Matrix()
{
    int lines, columns;
    std::cout << "Enter the number of lines:"; std::cin >> lines;
    std::cout << "Enter  the number of columns:"; std::cin >> columns;
    this->lines = lines;
    this->columns = columns;
    matrix = new T* [lines];
    for (int i = 0; i < lines; i++)
    {
        *matrix[i] = new T[columns];
    }
    Init();
}
template<typename T>
Matrix<T>::Matrix(int lines, int columns, T **OtherMatrix)
{
    this->lines = lines;
    this->columns = columns;
    T** matrix = new T*[lines];
    for (int i = 0; i < lines; i++)
    {
        matrix[i] = new T[columns];
    }
    for (int i=0;i<lines;i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            matrix[i][j] = OtherMatrix[i][j];
        }
    }
    this->matrix = matrix;
}
template<typename T>
Matrix<T>::Matrix(int lines, int columns)
{
    this->lines = lines;
    this->columns = columns;
    T** matrix = new T* [lines];
    for (int i = 0; i < lines; i++)
    {
        matrix[i] = new T[columns];
    }
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = 0;
        }
    }
    this->matrix = matrix;
}
template<typename T>
Matrix<T>::Matrix(const Matrix &p)
{
    lines = p.lines;
    columns = p.columns;
    double** matrix = new double*[lines];
    for (int i = 0; i < lines; i++)
    {
        *(matrix + i) = new double[columns];
    }
    for (int i=0;i<lines;i++) 
    {
        for (int j = 0; j < columns; j++)
        {
            *(*(matrix + i) + j) = *(*((p.matrix) + i) + j);
        }
    }
    this->matrix = matrix;
}
template<typename T>
Matrix<T>::Matrix(const Matrix p, int line, int column)
{
    int k = 0;
    int m = 0;
    this->lines = p.lines - 1;
    this->columns = p.columns - 1;
    double** matrix = new double* [lines];
    for (int i = 0; i < lines; i++) {
        *(matrix+i) = new double[columns];
    }
    for (int i = 0; i < p.lines; i++) {
        m = 0;
        if (i != line) {
            for (int j = 0; j < p.columns; j++) {
                if (j != column) {
                    *(*(matrix + k) + m) = *(*(p.matrix + i) + j);
                    m += 1;
                }
            }
            k += 1;
        }
    }
    this->matrix = matrix;
}
template<typename T>
Matrix<T>::Matrix(std::string FileName)
{
    if (strchr(FileName, '\n') != NULL) 
    {
        FileName[strcspn(FileName, "\n")] = '\0';
    }
    FILE* file = NULL;
    fopen(FileName, "r");
    char line[128];
    int lines = 0, columns = 0;
    while (fgets(line, 128, file)) 
    {
        lines += 1;
    }
    if (strchr(line, '\n') != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
    }
    char* Symb = strtok(line, "[ ;]");
    if (Symb != NULL) { columns += 1; }
    while ((Symb = strtok(NULL, "[ ;]")) != NULL)
    {
        columns += 1;
    }
    double** matrix = new double* [lines];
    for (int i=0;i<lines;i++) 
    {
        *(matrix + i) = new double[columns];
    }
    int CurrLine = 0;
    int CurrColumn=0;
    fseek(file, 0, 0);
    while (fgets(line, 128, file)) 
    {
        CurrColumn = 0;
        Symb = strtok(line, "[ ;]");
        
        if (strchr(line, '\n') != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
        }
        *(*(matrix+CurrLine)+CurrColumn) = std::atof(Symb);
        CurrColumn = 1;
        while ((Symb = strtok(NULL, "[ ;]")) != NULL)
        {
            *(*(matrix + CurrLine) + CurrColumn) = std::atof(Symb);
            CurrColumn += 1;
        }
        CurrLine += 1;
    }
    this->lines = lines;
    this->columns = columns;
    double** cpmatrix = new double* [lines];
    for (int i = 0; i < lines; i++)
    {
        *(cpmatrix + i) = new double[columns];
    }
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *(*(cpmatrix + i) + j) = *(*((matrix) + i) + j);
        }
    }
    this->matrix = cpmatrix;
    fclose(file);
}
template<typename T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < lines; i++)
    {
        delete[] *(matrix+i);
    }
    delete[] matrix;
}
Matrix Matrix::operator + (Matrix Second)
{
    if (lines == Second.lines && columns == Second.columns) {
        Matrix ReturnMatrix(lines, columns);
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                *(*(ReturnMatrix.matrix+i)+j)=*(*(matrix + i) + j) + *(*(Second.matrix + i) + j);
            }
        }
        return ReturnMatrix;
    }
    else {
        std::cout << "Ошибка!Размеры матриц не соответствуют друг другу. Возвращаем пустую матрицу размером с матрицу слева.\n";
        return Matrix{ lines,columns };
    }
}
Matrix Matrix::operator - (Matrix Second)
{
    if (lines == Second.lines && columns == Second.columns) {
        Matrix ReturnMatrix(lines, columns);
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                *(*(ReturnMatrix.matrix+i)+j)=*(*(matrix + i) + j) - *(*(Second.matrix + i) + j);
            }
        }
        return ReturnMatrix;
    }
    else {
        std::cout << "Ошибка!Размеры матриц не соответствуют друг другу. Возвращаем пустую матрицу размером с матрицу слева.\n";
        return Matrix{ lines,columns };
    }
}
Matrix Matrix::operator * (Matrix Second)
{
    double element;
    if (columns == Second.lines) {
        Matrix NewMatrix(lines, Second.columns);
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < Second.columns; j++) {
                element = 0;
                for (int k = 0; k < columns; k++) {
                    element += *(*(matrix + i) + k) * *(*(Second.matrix + k) + j);
                }
                *(*(NewMatrix.matrix + i) + j) = element;
            }
        }
        return Matrix{ lines,Second.columns,NewMatrix.matrix };
    }
    else {
        std::cout << "Ошибка!Размеры матриц не подходят друг к другу для умножения. Возвращаем пустую матрицу размером с матрицу слева.\n";
        return Matrix{ lines,columns };
    }
}
bool Matrix::operator != (Matrix Second)
{
    if (lines == Second.lines && columns == Second.columns) {
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                if (*(*(matrix + i) + j) != *(*(Second.matrix + i) + j)) {
                    return true;
                }
            }
        }
        return false;
    }
    else {
        return true;
    }
}
bool Matrix::operator == (Matrix Second)
{
    if (lines == Second.lines && columns == Second.columns) {
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                if (*(*(matrix + i) + j) != *(*(Second.matrix + i) + j)) {
                    return false;
                }
            }
        }
        return true;
    }
    else {
        return false;
    }
}
Matrix Matrix::operator ! ()
{
    Matrix AlgebraicAdditions(lines, columns);
    double det = this->Determinant();
    if (det == 0||(lines!=columns)) 
    { 
        std::cout << "Обратной матрицы для вашей матрицы нет! Возвращаем нулевую матрицу." << std::endl;
        return { lines,columns }; 
    }
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {
            Matrix Addition(*this, i, j);
            *(*(AlgebraicAdditions.matrix + i) + j) = pow(-1, i + j) * Addition.Determinant() / det;
        }
    }
    AlgebraicAdditions.Transposition();
    return Matrix{ AlgebraicAdditions.lines,AlgebraicAdditions.columns,AlgebraicAdditions.matrix };
}
template<typename T>
Matrix<T> Matrix<T>:: operator * (int a)
{
    Matrix ReturnMatrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            *(*(ReturnMatrix.matrix+i)+j)=*(*(matrix + i) + j) * a;
        }
    }
    return ReturnMatrix;
}
template<typename T>
bool Matrix<T>:: operator !=(int a)
{
    Matrix NewMatrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == j) {
                *(*(NewMatrix.matrix+i)+i) += a;
            }
        }
    }
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(*(matrix+i)+j) != *(*(NewMatrix.GetMatrix()+i)+j)) {
                return true;
            }
        }
    }
    return false;
}
template<typename T>
bool Matrix<T>::operator ==(int a)
{
    Matrix NewMatrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == j) {
                *(*(NewMatrix.matrix + i) + i) += a;
            }
        }
    }
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(*(matrix + i) + j) != *(*(NewMatrix.matrix + i) + j)) {
                return false;
            }
        }
    }
    return true;
}
template<typename T>
Matrix<T> operator * (int a, Matrix<T> First)
{
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            *(*(First.GetMatrix() + i) + j) *= a;
        }
    }
    return Matrix{ First.GetLines(),First.GetColumns(),First.GetMatrix() };
}
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
}
