
/*
#include "matrix.h"
#include <vector>
#include "array.h"
#include <iomanip>
#include <iostream>

using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin
using std::endl;
 // для манипулятора setw
using std::setw;   // пространство имен std для setw
using std::vector;
#include <cstdlib>

Matrix::Matrix() // конструктор по умолчанию
{
    raws = 10; // по умолчанию размер матрицы = 10 объектам типа Array
    columns = 10;
    ArrayPtr = new Array [raws]; // выделить место в памяти для матрицы
    for (int ix = 0; ix < raws; ix++) // обнуляем матрицу
        for (int jx = 0; jx < columns; jx++)
            ArrayPtr[ix][jx] = 0;
}

Matrix::Matrix(int rawsSize, int columnsSize) // конструктор с параметрами
{
    raws = (rawsSize > 0 ? rawsSize : 10); // количество строк
    columns =  (columnsSize > 0 ? columnsSize : 10);

    ArrayPtr = new Array [raws]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
        ArrayPtr[ix].setSize(columns); // количество столбцов

    for (int ix = 0; ix < raws; ix++) // обнуляем матрицу
        for (int jx = 0; jx < columns; jx++)
            ArrayPtr[ix][jx] = 0;
}

Matrix::Matrix(  Matrix &matrixToCopy ) // конструктор копии
    :raws(matrixToCopy.raws)              // инициализатор размера массива
{
    int tmpcolumn = matrixToCopy.columns;
    ArrayPtr = new Array [raws]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
        ArrayPtr[ix].setSize(tmpcolumn); // количество столбцов
    //cout<<"size: "<<size<<"column: "<<column<<endl;
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < tmpcolumn; jx++){
            //cout<<"ix: "<<ix<<", jx: "<<jx<<endl;
            ArrayPtr[ix][jx] = matrixToCopy[ix][jx];// заполняем матрицу значениями матрицы matrixToCopy
            }
}



Matrix::~Matrix() // десструктор класса Matrix
{
   delete  [] ArrayPtr; // освободить память, удалив матрицу
}

vector<int> Matrix::getSize() const// возвратить количество элементов матрицы
{
    vector<int> matSize(2);
    matSize[0] = raws;
    matSize[1] = columns;
    return matSize;
}

Array *Matrix::getArrayPtr() const
{
    return ArrayPtr;
}

// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Matrix &obj)
{
    for (int ix = 0; ix < obj.raws; ix++)
    {
        for (int jx = 0; jx < obj.columns; jx++)
        {
            output << setw(5) // под каждое число выделяется 5 позиций
                   << obj.ArrayPtr[ix][jx];
        }
        cout << std::endl;
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

// перегруженный оператор ввода, для заполнения матрицы с клавиатуры
istream &operator>> (istream & input, Matrix &obj)
{
    for (int ix = 0; ix < obj.raws; ix++)
        for (int jx = 0; jx < obj.columns; jx++)
            input >> obj.ArrayPtr[ix][jx]; // заполняем матрицу

    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

// перегруженный оператор взятия индекса
Array &Matrix::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= raws)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ArrayPtr[subscript]; // возврат ссылки на элемент массива
}

void Matrix::setMatrix() // заполнение массива
{
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            cin >> ArrayPtr[ix][jx]; // ввод элементов матрицы с клавиатуры
}

void Matrix::getMatrix() // вывод массива
{
    for (int ix = 0; ix < raws; ix++)
    {
        for (int jx = 0; jx < columns; jx++)
            cout << setw(5) << ArrayPtr[ix][jx]; // вывод элементов матрицы на экран
        cout << std::endl;
    }

    cout << std::endl; // новая строка
}

int *Matrix::search(const int key) const // поиск по ключу
{
    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            if ( key == ArrayPtr[ix][jx] ) // поиск по ключу
                return (&ArrayPtr[ix][jx]);             // позиция искомого элемента

    return NULL;
}

Matrix Matrix::operator+ (const Matrix &right)
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

Matrix Matrix::operator*(const Matrix &right)
{
    if(columns != right.raws){
        cout<<"Incompatable sizes of matrixes."<<std::endl;
        //cout<<size<<"x"<<ArrayPtr->getSize()<<";"<< right.size<<"x"<<right.getArrayPtr()->getSize()<<endl;
        exit(1);
    }
    Matrix result(raws,right.columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < right.columns; j++)
    {
        result[i][j] = 0;
        for(int k = 0; k < right.raws; k++)
            result.ArrayPtr[i][j] += ArrayPtr[i][k] * right.ArrayPtr[k][j];
    }
    return result;
}

Matrix Matrix::operator*( int right)
{
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < columns; j++)
    {
        result[i][j] = ArrayPtr[i][j]*right;

    }
    return result;
}

Matrix Matrix::operator+( int right)
{
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < this->columns; j++)
    {
        result[i][j] = ArrayPtr[i][j]+right;

    }
    return result;
}

Matrix Matrix::operator-( int right)
{
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < this->columns; j++)
    {
        result[i][j] = ArrayPtr[i][j]-right;

    }
    return result;
}

Matrix Matrix::operator/( int right)
{
    Matrix result(raws,this->columns);
    for(int i = 0; i < raws; i++)
    for(int j = 0; j < this->columns; j++)
    {
        result[i][j] = ArrayPtr[i][j]/right;

    }
    return result;
}

void Matrix::T()
{
    Matrix tmp = *this;
    int tmpraw = raws;
    int tmpcolumn = columns;
    delete  [] ArrayPtr;
    ArrayPtr = new Array [tmpcolumn];

    for (int ix = 0; ix < tmpcolumn; ix++){ // перераспределяем выделенную память
        ArrayPtr[ix].setSize(tmpraw); // количество столбцов
    }
    raws = tmpcolumn;
    for(int i = 0;i<tmpraw;i++){
        for(int j = 0; j<tmpcolumn;j++){
            ArrayPtr[j][i] = tmp[i][j];
        }
    }
}

Matrix Matrix::operator+= (const Matrix &right)
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

Matrix Matrix::operator- (const Matrix &right)
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

const Matrix &Matrix::operator= (const Matrix &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {

        if (raws != right.raws || columns != right.columns)
        {
            delete [] ArrayPtr; // освободить пространство
            raws = right.raws; // установить нужный размер матрицы
            columns = right.columns;
            ArrayPtr = new Array [right.columns]; // выделить память под копируемый массив

            for (int ix = 0; ix < raws; ix++) // перераспределяем выделенную память
                ArrayPtr[ix].setSize(right.columns); // количество столбцов
         }

        for (int ix = 0; ix < raws; ix++)
            for (int jx = 0; jx < columns; jx++)
                ArrayPtr[ix][jx] = right.ArrayPtr[ix][jx]; // скопировать массив
    }

    return *this; // разрешает множественное присваивание, например x = t = e
}

bool Matrix::operator== (const Matrix &right) const// оператор сравнения
{
    if (raws != right.raws || columns != right.columns)
        return false; // матрицы с разным количеством элементов

    for (int ix = 0; ix < raws; ix++)
        for (int jx = 0; jx < columns; jx++)
            if (ArrayPtr[ix][jx] != right.ArrayPtr[ix][jx])
                return false; // матрицы не равны

    return true; // матрицы равны
}
*/
