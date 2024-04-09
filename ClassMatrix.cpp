#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include "ClassMatrix.h"
void Matrix::Print() 
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
void Matrix::Init() 
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
void Matrix::WriteToAFile()
{
    char FileName[128];
    std::cout << "Введите имя файла для вывода:";
    std::cin >> FileName;
    FileName[strcspn(FileName, "\n")] = '\0';
    FILE* write = NULL;
    fopen(FileName, "w");
    for (int i = 0; i < lines; i++) {
        fprintf(write, "%s", "[");
        for (int j = 0; j < columns; j++) {
            if (j != columns - 1) { fprintf(write, "%g ", *(*(matrix + i) + j)); }
            else { fprintf(write, "%g", *(*(matrix + i) + j)); }
        }
        fprintf(write, "%s", "]\n");
    }
    fclose(write);
}
void Matrix::Comprassion(const Matrix Second)
{
    if (*this == Second) {
        std::cout << "Они одинаковы!\n";
    }
    else if (*this != Second) {
        std::cout << "Они неодинаковы!\n";
    }
}
void Matrix::FirstElementaryTransformation(int FirstLine, int SecondLine)
{
    double tmp;
    for (int i = 0; i < columns; i++) {
        tmp = *(*(matrix+FirstLine)+i);
        *(*(matrix + FirstLine) + i) = *(*(matrix + SecondLine) + i);
        *(*(matrix + SecondLine) + i) = tmp;
    }
}
void Matrix::SecondElementaryTransformation(int ChangeLine, int MultiPlier)
{
    for (int i = 0; i < columns; i++) {
        *(*(matrix + ChangeLine) + i) *= MultiPlier;
    }
}
void Matrix::ThirdElementaryTransformation(int TakeLine, int MultiPlier, int ChangeLine)
{
    for (int i = 0; i < columns; i++) {
        *(*(matrix + ChangeLine) + i) += *(*(matrix + TakeLine) + i) * MultiPlier;
    }
}
double Matrix::Determinant()
{
    Matrix& p = *this;
    double det = 0;
    if (lines != columns) 
    {
        std::cout << "Определитель не существует для неквадратной матрицы\n";
        return 0;
    }
    else {
        if ((columns-p.columns) ==  columns-1) 
        { 
            return *(*(p.matrix)); 
        }
        for (int i = 0; i < p.columns; i++) 
        {
            Matrix NewMatrix(p, 0, i);
            det += *(*(p.matrix)+i) * pow(-1, i + 2)* NewMatrix.Determinant();
        }
        return det;
    }
}
void Matrix::Transposition()
{
    double tmp;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < i; j++) {
            tmp = *(*(matrix + i) + j);
            *(*(matrix+i)+j) = *(*(matrix + j) + i);
            *(*(matrix + j) + i) = tmp;
        }
    }
}
int Matrix::GetLines() 
{
    return lines;
}
int Matrix::GetColumns() 
{
    return columns;
}
double** Matrix::GetMatrix() 
{
    return matrix;
}
Matrix::Matrix() 
{
    int lines, columns;
    std::cout << "Введите количество строк:"; std::cin >> lines;
    std::cout << "Введите количество столбцов:"; std::cin >> columns;
    this->lines = lines;
    this->columns = columns;
    matrix = new double* [lines];
    for (int i = 0; i < lines; i++)
    {
        *(matrix+i) = new double[columns];
    }
    Init();
}
Matrix::Matrix(int lines, int columns, double **OtherMatrix)
{
    this->lines = lines;
    this->columns = columns;
    double** matrix = new double*[lines];
    for (int i = 0; i < lines; i++)
    {
        *(matrix + i) = new double[columns];
    }
    for (int i=0;i<lines;i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            *(*(matrix + i) + j) = *(*(OtherMatrix + i) + j);
        }
    }
    this->matrix = matrix;
}
Matrix::Matrix(int lines, int columns) 
{
    this->lines = lines;
    this->columns = columns;
    double** matrix = new double* [lines];
    for (int i = 0; i < lines; i++)
    {
        *(matrix+i) = new double[columns];
    }
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *(*(matrix + i) + j) = 0;
        }
    }
    this->matrix = matrix;
}
Matrix::Matrix(const Matrix &p)
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
Matrix::Matrix(const Matrix p, int line, int column) 
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
Matrix::Matrix(char *FileName)
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
Matrix::~Matrix() 
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
Matrix Matrix:: operator * (int a)
{
    Matrix ReturnMatrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            *(*(ReturnMatrix.matrix+i)+j)=*(*(matrix + i) + j) * a;
        }
    }
    return ReturnMatrix;
}
bool Matrix:: operator !=(int a)
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
bool Matrix::operator ==(int a)
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
Matrix operator * (int a, Matrix First)
{
    for (int i = 0; i < First.GetLines(); i++) {
        for (int j = 0; j < First.GetColumns(); j++) {
            *(*(First.GetMatrix() + i) + j) *= a;
        }
    }
    return Matrix{ First.GetLines(),First.GetColumns(),First.GetMatrix() };
}
bool operator !=(int a, Matrix First)
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
bool operator ==(int a, Matrix First)
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
