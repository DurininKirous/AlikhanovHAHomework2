#include <string>
class Matrix {
private:
    int lines;
    int columns;
    double** matrix;
public:
    void Print();
    void Init();
    void WriteToAFile();
    void Comprassion(const Matrix Second); //Сравнение матриц на основе перегруженных операторов
    void FirstElementaryTransformation(int FirstLine, int SecondLine);
    void SecondElementaryTransformation(int ChangeLine, int MultiPlier);
    void ThirdElementaryTransformation(int TakeLine, int MultiPlier, int ChangeLine);
    double Determinant();
    void Transposition();
    int GetLines();
    int GetColumns();
    double** GetMatrix();
    Matrix();
    Matrix(int lines, int columns, double** matrix); //Собрать матрицу из уже существующих элементов
    Matrix(int lines, int columns); //Собрать нулевую матрицу из lines*columns элементов 
    Matrix(const Matrix& p);
    Matrix(const Matrix p, int line, int column); //Собрать матрицу на основе переданной, но в которой вычеркнуты строка line и столбец column
    Matrix(char* FileName); //Собрать матрицу из файла, нужно передать имя файла (Уже существует файл MatrixExample.txt, но можно создать свою)
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
Matrix operator * (int a, Matrix First);
bool operator !=(int a, Matrix First);
bool operator ==(int a, Matrix First);
