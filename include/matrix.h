
#ifndef MATRIX_H
#define MATRIX_H

#include <array.h>
#include <vector>
#include "math.h"

using std::vector;

/** \brief Matrix class
 *  \author Astromis
 * \param [in] raw Number of raws
 * \param [in] columns Number of columns
 * \return [Matrix rawsXcolumns size]
 *
 */

template<class T1>
class Matrix : public Array<T1>
{
    template <class F1>
    friend ostream &operator<< (ostream &, const Matrix<F1> &); // перегруженный оператор вывода

    template <class F1>
    friend istream &operator>> (istream &, Matrix<F1> &); // перегруженный оператор ввода

    template<class F1>
    friend Matrix<F1> operator+(F1 ,Matrix<F1> &);

    template<class F1>
    friend Matrix<F1> operator-(F1 ,Matrix<F1> &);

    template<class F1>
    friend Matrix<F1> operator*(F1 ,Matrix<F1> &);

    template<class F1>
    friend Matrix<F1> operator/(F1 ,Matrix<F1> &);

    template<class F1>
    friend Matrix<F1> operator+(Matrix<F1> &, F1);

    template<class F1>
    friend Matrix<F1> operator-(Matrix<F1> &, F1);

    template<class F1>
    friend Matrix<F1> operator*(Matrix<F1> &, F1);

    template<class F1>
    friend Matrix<F1> operator/(Matrix<F1> &, F1);


private:



public:
    Array<T1> *ArrayPtr; // указатель на матрицу типа Array
    int raws; /**< Raws matrix */
    int columns;
    Matrix();// конструктор по умолчанию
    Matrix(int, int ); // конструктор с параметрами
    Matrix( Matrix &matrixToCopy ); // конструктор копии
    ~Matrix(); // десструктор класса Matrix

    vector<int> getSize() const; // возвратить количество объектов типа Array
    Array<T1> *getArrayPtr() const; // вернуть указатель на объект типа Array
    Array<T1> &operator[] (int ); // перегруженная операция взятия индекса
    void setMatrix(); // заполнение матрицы
    void getMatrix(); // вывод матрицы

    void T();
    void fill_rand(const T1 a, const T1 b);
    void fill_normal(float mean,float std);
    void resize_matrix(int raw, int column);
    void fill_one();
    void fill_diag();


    Matrix<T1> activation();

    int *search(const int key) const; // поиск по ключу

    //element-wise operations
    Matrix operator*(const Matrix &right);
    Matrix operator+ (const Matrix &right);
    Matrix operator- (const Matrix &right);
    Matrix operator/ (const Matrix &right);

    Matrix operator+= (const Matrix &right);

    Matrix dot(const Matrix &b);
    Matrix transpose();
    Matrix<T1> concat( Matrix &b, char mode);

    void save(const char * path);

    const Matrix &operator= (const Matrix &right); // оператор присваивания
    bool operator== (const Matrix &right) const;// оператор сравнения

    Matrix<T1> slice_raw(int raw, int col);
    Matrix<T1> slice_col(int raw, int col);
    Matrix<T1> slice_mat(int st_raw, int end_raw, int st_col, int end_col);

};


#endif // MATRIX_H


//#include "matrix.h"
#include <vector>
//#include "array.h"
#include <iomanip>
#include <iostream>
#include <fstream>

using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin
using std::endl;
 // для манипулятора setw
using std::setw;   // пространство имен std для setw
using std::vector;
#include <cstdlib>

template<class T1>
void Matrix<T1>::save(const char* path)
{
    FILE *myfile;
    char  a[1];
    int pream[2];
    a[0] = '\n';

    myfile = fopen (path, "w");
    if(myfile == NULL)
    {
        cout<<"Cannot open file.";
        exit(1);
    }
    pream[0]=raws;pream[1]=columns;
    //writing quantity of raws and columns
    fwrite(pream, sizeof(int), 2, myfile);
    fwrite(a, sizeof(char), 1, myfile);
    //writing values by raws and columns
    for(int i=0;i<raws;i++)
    {
        fwrite(ArrayPtr[i].getPtr(), sizeof(int), 2, myfile);
        fwrite(a, sizeof(char), 1, myfile);

    }
}

template<class T1>
void Matrix<T1>::fill_one()
{
    for(int i=0;i<raws;i++)
        for(int j=0;j<columns;j++)
            ArrayPtr[i][j] = 1;

}

template<class T1>
void Matrix<T1>::fill_diag()
{
    int i=0,j=0;
    while(i<raws && j<columns)
    {
        ArrayPtr[i][j] = 1;
        i++;
        j++;
    }
}

template<class T1>
Matrix<T1> Matrix<T1>::concat(Matrix &b, char mode)
{

    if(mode == 'c')
    {
        if(raws != b.raws)
        {
            cout<<"Incompatable raws";
            exit(1);
        }
        Matrix<T1> res(raws, (columns + b.columns));
        for(int i=0;i<raws;i++)
        {
            for(int j=0;j<columns;j++)
            {
                res[i][j] = ArrayPtr[i][j];
            }
        }
        //cout<<res;
        for(int i=0;i<raws;i++)
            for(int j=columns;j<(columns + b.columns);j++)

                res[i][j] = b[i][j-columns];
        cout<<res;
        return res;
    }
    else
    {
        cout<<columns<<" "<<b.columns;
        if(columns != b.columns)
        {
            cout<<"Incompatable columns";
            exit(1);
        }
        Matrix<T1> res(raws + b.raws,columns);
        for(int i=0;i<raws;i++)
        {
            for(int j=0;j<columns;j++)
            {
                res[i][j] = ArrayPtr[i][j];
            }
        }
        //cout<<res;
        for(int i=raws;i<(raws + b.raws);i++)
            for(int j=0;j<columns;j++)

                res[i][j] = b[i-raws][j];
        cout<<res;
        return res;
    }
}

template<class T1>
Matrix<T1>::Matrix() // конструктор по умолчанию
{
    raws = 5; // по умолчанию размер матрицы = 10 объектам типа Array
    columns = 5;
    ArrayPtr = new Array<T1> [raws]; // выделить место в памяти для матрицы

}

template<class T1>
Matrix<T1>::Matrix(int rawsSize, int columnsSize) // конструктор с параметрами
{
    raws = (rawsSize > 0 ? rawsSize : 5); // количество строк
    columns =  (columnsSize > 0 ? columnsSize : 5);

    ArrayPtr = new Array<T1> [raws]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
        ArrayPtr[ix].setSize(columns); // количество столбцов

}

template<class T1>
Matrix<T1>::Matrix(  Matrix &matrixToCopy ) // конструктор копии
    :raws(matrixToCopy.raws)              // инициализатор размера массива
{
    int tmpcolumn = matrixToCopy.columns;
    ArrayPtr = new Array<T1> [raws]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
        ArrayPtr[ix].setSize(tmpcolumn); // количество столбцов

    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < tmpcolumn; jx++)
            {
                ArrayPtr[ix][jx] = matrixToCopy[ix][jx];// заполняем матрицу значениями матрицы matrixToCopy
            }
}


template<class T1>
Matrix<T1>::~Matrix() // десструктор класса Matrix
{
   delete  [] ArrayPtr; // освободить память, удалив матрицу
}

/*
vector<int> Matrix::getSize() const// возвратить количество элементов матрицы
{
    vector<int> matSize(2);
    matSize[0] = raws;
    matSize[1] = columns;
    return matSize;
}*/

template<class T1>
Array<T1> *Matrix<T1>::getArrayPtr() const
{
    return ArrayPtr;
}

template<class T1>
// перегруженный оператор взятия индекса
Array<T1> &Matrix<T1>::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= raws)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ArrayPtr[subscript]; // возврат ссылки на элемент массива
}

template<class T1>
void Matrix<T1>::setMatrix() // заполнение массива
{
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            cin >> ArrayPtr[ix][jx]; // ввод элементов матрицы с клавиатуры
}

template<class T1>
void Matrix<T1>::getMatrix() // вывод массива
{
    for (int ix = 0; ix < raws; ix++)
    {
        for (int jx = 0; jx < columns; jx++)
            cout << setw(5) << ArrayPtr[ix][jx]; // вывод элементов матрицы на экран
        cout << std::endl;
    }

    cout << std::endl; // новая строка
}

template<class T1>
int *Matrix<T1>::search(const int key) const // поиск по ключу
{
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            if ( key == ArrayPtr[ix][jx] ) // поиск по ключу
                return (&ArrayPtr[ix][jx]);             // позиция искомого элемента

    return NULL;
}

template<class T1>
Matrix<T1> Matrix<T1>::operator+ (const Matrix &right)
//element-wise sum
{
    if (raws != right.raws || columns != right.columns)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

    Matrix result(raws, columns);
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            result.ArrayPtr[ix][jx] = ArrayPtr[ix][jx] + right.ArrayPtr[ix][jx];

    return result; // вернуть сумму
}

template<class T1>
Matrix<T1> Matrix<T1>::operator- (const Matrix &right)
//element-wise substruction
{
    if (raws != right.raws || columns != right.columns)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

    Matrix result(raws, columns);
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            result.ArrayPtr[ix][jx] = ArrayPtr[ix][jx] - right.ArrayPtr[ix][jx];

    return result; // вернуть сумму
}

template<class T1>
Matrix<T1> Matrix<T1>::operator*(const Matrix &right)
//element-wise multiplication of matrixes
{
    if (raws != right.raws || columns != right.columns)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < columns; j++)
    {
        result[i][j] = ArrayPtr[i][j] * right.ArrayPtr[i][j];

    }
    return result;

}

template<class T1>
Matrix<T1> Matrix<T1>::operator/(const Matrix &right)
//element-wise dividing of matrixes
{
    if (raws != right.raws || columns != right.columns)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < columns; j++)
    {
        result[i][j] = ArrayPtr[i][j] / right.ArrayPtr[i][j];

    }
    return result;

}

template<class T1>
void Matrix<T1>::T()
{
    Matrix tmp = *this;
    int tmpraw = raws;
    int tmpcolumn = columns;
    //cout<<this->raws<<" "<<this->columns<<endl;
    delete  [] ArrayPtr;
    ArrayPtr = new Array<T1> [tmpcolumn];

    for (int ix = 0; ix < tmpcolumn; ix++){ // перераспределяем выделенную память
        ArrayPtr[ix].setSize(tmpraw); // количество столбцов
    }
    raws = tmpcolumn;
    columns = tmpraw;
    //cout<<this->raws<<" "<<this->columns<<endl;
    for(int i = 0;i<tmpraw;i++){
        for(int j = 0; j<tmpcolumn;j++){
            ArrayPtr[j][i] = tmp[i][j];
        }
    }
}

template<class T1>
Matrix<T1> Matrix<T1>::transpose()
{

    Matrix tmp(columns,raws);

    //cout<<this->raws<<" "<<this->columns<<endl;
    for(int i = 0;i<raws;i++){
        for(int j = 0; j<columns;j++){
            tmp[j][i] = ArrayPtr[i][j];
        }
    }
    return tmp;
}

template<class T1>
Matrix<T1> Matrix<T1>::operator+= (const Matrix &right)
{
    if (raws != right.raws || columns != right.columns)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

//    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            ArrayPtr[ix][jx] = ArrayPtr[ix][jx] + right.ArrayPtr[ix][jx];

    return *this; // вернуть сумму
}

template<class T1>
const Matrix<T1> &Matrix<T1>::operator= (const Matrix &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {

        if (raws != right.raws || columns != right.columns)
        {
            delete [] ArrayPtr; // освободить пространство
            raws = right.raws; // установить нужный размер матрицы
            columns = right.columns;
            ArrayPtr = new Array<T1> [right.raws]; // выделить память под копируемый массив

            for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
                ArrayPtr[ix].setSize(right.columns); // количество столбцов
         }

        for (int ix = 0; ix < raws; ix++)
            for (int jx = 0; jx < columns; jx++)
                ArrayPtr[ix][jx] = right.ArrayPtr[ix][jx]; // скопировать массив
    }

    return *this; // разрешает множественное присваивание, например x = t = e
}

template<class T1>
bool Matrix<T1>::operator== (const Matrix &right) const// оператор сравнения
{
    if (raws != right.raws || columns != right.columns)
        return false; // матрицы с разным количеством элементов

    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            if (ArrayPtr[ix][jx] != right.ArrayPtr[ix][jx])
                return false; // матрицы не равны

    return true; // матрицы равны
}

template<class T1>
void Matrix<T1>::fill_rand(const T1 a, const T1 b)
{
    for(int i=0;i<raws;i++)
    {
        ArrayPtr[i].fill_rand(a,b);
    }
}

template<class T1>
void Matrix<T1>::fill_normal(float mean,float std)
{
    for(int i=0;i<raws;i++)
    {
        ArrayPtr[i].fill_normal(mean,std);
    }

}

template<class T1>
Matrix<T1> Matrix<T1>::slice_raw(int raw, int col)
{
    Matrix<T1> res(1,columns - col);
    for(int i=col; i <columns;i++)
    {
        res[0][i-col]=ArrayPtr[raw][i];
    }
    return res;

}

template<class T1>
Matrix<T1> Matrix<T1>::slice_col(int raw, int col)
{
    Matrix<T1> res(raws - raw,1);
    for(int i=raw; i <raws;i++)
    {
        res[i-raw][0]=ArrayPtr[i][col];
    }
    return res;

}

template<class T1>
Matrix<T1> Matrix<T1>::slice_mat(int st_raw, int end_raw, int st_col, int end_col)
{
    Matrix<T1> res(end_raw-st_raw, end_col-st_col);
    for(int i=st_raw;i<end_raw;i++)
        for(int j=st_col;j<end_col;j++)
            res[i-1][j-1] = ArrayPtr[i][j];
    return res;
}

template<class T1>
void Matrix<T1>::resize_matrix(int raw, int column)
{
    //add coping values for generealize method;
    raws = raw;
    columns =  column;
    delete [] ArrayPtr;
    ArrayPtr = new Array<T1> [raws]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
        ArrayPtr[ix].setSize(columns); // количество столбцов
}

template<class T1>
Matrix<T1> Matrix<T1>::activation()
{
    Matrix<float> res(raws,columns);

    for(int i=0;i<raws;i++)
    {
        for(int j=0;j<columns;j++)
        {
            res[i][j] = 1/(1+exp(-ArrayPtr[i][j]));
        }
    }
    return res;
}

template<class T1>
Matrix<T1> Matrix<T1>::dot(const Matrix &b)
{
     if(columns != b.raws){
        cout<<"Incompatable sizes of matrixes."<<std::endl;
        exit(1);
    }
    Matrix result(raws,b.columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < b.columns; j++)
    {
        result[i][j] = 0;
        for(int k = 0; k < b.raws; k++)
            result.ArrayPtr[i][j] += ArrayPtr[i][k] * b.ArrayPtr[k][j];
    }
    return result;
}

//----------------------------------

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator+(T1 left,Matrix<T1> &right)
{
    Matrix<T1> res;
    for(int i=0;i<right.raws;i++)
        for(int j=0;j<right.columns;j++)
            res[i][j] = left + right[i][j];
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator-(T1 left,Matrix<T1> &right)
{
    Matrix<T1> res;
    for(int i=0;i<right.raws;i++)
        for(int j=0;j<right.columns;j++)
            res[i][j] = left - right[i][j];
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator*(T1 left,Matrix<T1> &right)
{
    Matrix<T1> res;
    for(int i=0;i<right.raws;i++)
        for(int j=0;j<right.columns;j++)
            res[i][j] = left * right[i][j];
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator/(T1 left,Matrix<T1> &right)
{
    Matrix<T1> res;
    for(int i=0;i<right.raws;i++)
        for(int j=0;j<right.columns;j++)
            res[i][j] = left / right[i][j];
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator+(Matrix<T1> &left, T1 right)
{
    Matrix<T1> res;
    for(int i=0;i<left.raws;i++)
        for(int j=0;j<left.columns;j++)
            res[i][j] = left[i][j] + right;
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator-(Matrix<T1> &left, T1 right)
{
    Matrix<T1> res;
    for(int i=0;i<left.raws;i++)
        for(int j=0;j<left.columns;j++)
            res[i][j] = left[i][j] - right;
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator*(Matrix<T1> &left, T1 right)
{
    Matrix<T1> res;
    for(int i=0;i<left.raws;i++)
        for(int j=0;j<left.columns;j++)
            res[i][j] = left[i][j] * right;
    return res;
}

template<class T1> //why are both variants T1 and F1 fi?
Matrix<T1> operator/(Matrix<T1> &left, T1 right)
{
    Matrix<T1> res;
    for(int i=0;i<left.raws;i++)
        for(int j=0;j<left.columns;j++)
            res[i][j] = left[i][j] / right;
    return res;
}

template<class T1>
// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Matrix<T1> &obj)
{
    for (int ix = 0; ix < obj.raws; ix++)
    {
        for (int jx = 0; jx < obj.columns; jx++)
        {
            output << setw(10) // под каждое число выделяется 5 позиций
                   << obj.ArrayPtr[ix][jx];
        }
        cout << std::endl;
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

template<class T1>
// перегруженный оператор ввода, для заполнения матрицы с клавиатуры
istream &operator>> (istream & input, Matrix<T1> &obj)
{
    for (int ix = 0; ix < obj.raws; ix++)
        for (int jx = 0; jx < obj.columns; jx++)
            input >> obj.ArrayPtr[ix][jx]; // заполняем матрицу

    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}
