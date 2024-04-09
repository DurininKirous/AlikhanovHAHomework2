#include <string>
template <typename T>
class Matrix {
private:
    int lines;
    int columns;
    T** matrix;
public:
    void Print();
    void Init();
    void WriteToAFile();
    void FirstElementaryTransformation(int FirstLine, int SecondLine);
    void SecondElementaryTransformation(int ChangeLine, T MultiPlier);
    void ThirdElementaryTransformation(int TakeLine, T MultiPlier, int ChangeLine);
    double Determinant();
    void Transposition();
    int GetLines();
    int GetColumns();
    T** GetMatrix();
    Matrix();
    Matrix(int lines, int columns, T** matrix); //Собрать матрицу из уже существующих элементов
    Matrix(int lines, int columns); //Собрать нулевую матрицу из lines*columns элементов 
    Matrix(const Matrix& p);
    Matrix(const Matrix p, int line, int column); //Собрать матрицу на основе переданной, но в которой вычеркнуты строка line и столбец column
    Matrix(std::string FileName); //Собрать матрицу из файла, нужно передать имя файла (Уже существует файл MatrixExample.txt, но можно создать свою)
    ~Matrix();
    Matrix operator + (Matrix Second);
    Matrix operator - (Matrix Second);
    Matrix operator * (Matrix Second);
    bool operator != (Matrix Second);
    bool operator == (Matrix Second);
    Matrix operator ! ();
    Matrix operator * (int a);
    bool operator !=(int a);
    bool operator ==(int a);
};
template<typename T>
Matrix<T> operator * (T a, Matrix<T> First);
template<typename T>
bool operator !=(int a, Matrix<T> First);
template<typename T>
bool operator ==(int a, Matrix<T> First);
