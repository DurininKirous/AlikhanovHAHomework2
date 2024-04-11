#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
template <typename T>
T convert_to(const std::string &str)
{
    std::istringstream ss(str);
    T num;
    ss >> num;
    return num;
}
template <typename T>
class Matrix {
private:
    int lines;
    int columns;
    T** matrix;
public:
    void Print()
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
    };
    void Init()
    {
        std::cout << "Fill out the matrix!\n";
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                std::cin >> matrix[i][j];
            }
        }
    };
    void WriteToAFile()
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
    void FirstElementaryTransformation(int FirstLine, int SecondLine);
    void SecondElementaryTransformation(int ChangeLine, T MultiPlier);
    void ThirdElementaryTransformation(int TakeLine, T MultiPlier, int ChangeLine);
    double Determinant();
    void Transposition();
    int GetLines();
    int GetColumns();
    T** GetMatrix();
    Matrix()
    {
        std::cout << "Enter the number of lines:"; std::cin >> lines;
        std::cout << "Enter  the number of columns:"; std::cin >> columns;
        matrix = new T* [lines];
        for (int i = 0; i < lines; ++i)
        {
            matrix[i] = new T[columns];
        }
        Init();
    };
    Matrix(int lines, int columns, T** matrix); //Собрать матрицу из уже существующих элементов
    Matrix(int lines, int columns); //Собрать нулевую матрицу из lines*columns элементов 
    Matrix(const Matrix& p);
    Matrix(const Matrix p, int line, int column); //Собрать матрицу на основе переданной, но в которой вычеркнуты строка line и столбец column
    Matrix(std::string FileName)//Собрать матрицу из файла, нужно передать имя файла (Уже существует файл MatrixExample.txt, но можно создать свою)
    {
        if (FileName.find("\n") != std::string::npos)
        {
            FileName[FileName.find("\n")] = '\0';
        }
        std::fstream in;
        in.open(FileName);
        std::string line;
        std::string garb="[ ;]";
        int lines = 0, columns = 0;
        while (std::getline(in,line))
        {
            lines += 1;
        }
        /*if (line.find("\n") != std::string::npos)
        {
            line[line.find("\n")] = '\0';
        }*/
        std::stringstream ss(line);
        std::string token;
        while (ss >> token)
        {
                columns+=1;
        }
        ss.clear();
        T** matrix = new T* [lines];
        for (int i=0;i<lines;++i)
        {
            matrix[i] = new T[columns];
        }
        int CurrLine = 0;
        int CurrColumn=0;
        in.close();
        in.open(FileName);
        while (std::getline(in,line))
        {
            CurrColumn = 0;

            if (line.find("\n") != std::string::npos)
            {
                line[line.find("\n")] = '\0';
            }
            std::cout <<line<<std::endl;
            std::string empty;
            line.erase(line.find('['),line.find('[')+1);
            line.erase(line.find(']'),line.find(']'));
            ss.str(line);
            while (ss >> token)
            {
                matrix[CurrLine][CurrColumn]=(convert_to<double>(token));
                ++CurrColumn;
                //std::cout <<convert_to<T>(token)<<std::endl;
            }
            ++CurrLine;
            ss.clear();
        }
        this->lines = lines;
        this->columns = columns;
        this->matrix=matrix;
        /*T** cpmatrix = new T* [lines];
        for (int i = 0; i < lines; i++)
        {
            cpmatrix[i] = new T[columns];
        }
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cpmatrix[i][j] = matrix[i][j];
            }
        }
        this->matrix = cpmatrix;*/
        in.close();
    };
    ~Matrix()
    {
        for (int i = 0; i < lines; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
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
