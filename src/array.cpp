#include "array.h"
#include "math.h"
#include <iostream>
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin

#include <iomanip> // для манипулятора setw
using std::setw;   // пространство имен std для setw

#include <cstdlib>

Array::Array() // конструктор по умолчанию, без параметров
{
    size = 1000; // по умолчанию размер массива = 10 элементов
    ptr = new int [size]; // выделить место в памяти для массива
    for (int ix = 0; ix < size; ix++) // обнуляем массив
        ptr[ix] = 0;
}

Array::Array(int arraySize) // конструктор с параметрами
{
    // если значение параметра больше 0, присвоить size значение arraySize, иначе - 10
    size = (arraySize > 0 ? arraySize : 10);
    //delete [] ptr;
    ptr = new int [size]; // выделить место в памяти для массива

    for (int ix = 0; ix < size; ix++) // обнуляем массив
        ptr[ix] = 0;
}

Array::Array( const Array &arrayToCopy ) // конструктор копии
    :size(arrayToCopy.size)              // инициализатор размера массива
{
    ptr = new int [size]; // выделить место в памяти для массива

    for (int ix = 0; ix < size; ix++)
        ptr[ix] = arrayToCopy.ptr[ix]; // заполняем массив значениями массива arrayToCopy
}

Array::~Array() // десструктор класса Array
{
    delete  [] ptr; // освободить память, удалив массив
}

int Array::getSize() const // возвратить количество элементов массива
{
    return size;
}

// перегруженный оператор ввода, для ввода значений массива с клавиатуры
istream &operator>> (istream & input, Array &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
        input >> obj.ptr[ix]; // заполняем массив объекта obj
    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Array &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        output << setw(5) // под каждое число выделяется 5 позиций
               << obj.ptr[ix];
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

void Array::setArray() // заполнение массива
{
    for (int ix = 0; ix < size; ix++)
        cin >> ptr[ix]; // ввод элемента массива с клавиатуры
}

void Array::getArray() // вывод массива
{
    for (int ix = 0; ix < size; ix++)
        cout << setw(5) << ptr[ix]; // вывод элементов массива на экран

    cout << std::endl; // новая строка
}

const Array &Array::operator= (const Array &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {
        if (size != right.size)
        {
            delete [] ptr; // освободить пространство
            size = right.size; // установить нужный размер массива
            ptr = new int [size]; // выделить память под копируемый массив
        }

        for (int ix = 0; ix < size; ix++)
            ptr[ix] = right.ptr[ix]; // скопировать массив
    }

    return *this; // разрешает множественное присваивание, например x = t = e
}

bool Array::operator== (const Array &right) const// оператор сравнения
{
    if (size != right.size)
        return false; // массивы с разным количеством элементов
    for (int ix = 0; ix < size; ix++)
        if (ptr[ix] != right.ptr[ix])
            return false; // массивы не равны

    return true; // массивы равны
}

int &Array::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= size)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ptr[subscript]; // возврат ссылки на элемент массива
}

Array Array::operator+ (const Array &right)
{
    if (size != right.size)
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

    Array result(size);
    for (int ix = 0; ix < size; ix++)
        result.ptr[ix] = ptr[ix] + right.ptr[ix];

    return result; // вернуть сумму
}

 Array &Array::operator+= (const int &number) // оператор добавления элемента в конец массива
{
    Array result(size);
    result = *this; // временно сохраним текущий массив

    delete [] ptr; // освобождаем память

    size = size + 1; // увеличиваем размер массива на 1
    ptr = new int [size]; // выделяем память

    for (int ix = 0; ix < (size - 1); ix++)
        ptr[ix] = result.ptr[ix]; // скопировать массив

    ptr[size - 1] = number; // добавляем число в конец массива

    return *this; // каскадный вызов перегруженного оператора
}

 Array &Array::operator- (const int & key) // оператор удаления элемента по ключу
 {
     int counterKey = 0; // счетчик найденных ключевых элементов
     // определяем количество элементов, которые необходимо удалить
     for (int ix = 0; ix < size; ix++)
     {
         if (ptr[ix] == key)
             counterKey++;
     }

     Array temp(size);
     temp = *this; // сохраняем текущий массив во временный объект

     delete [] ptr; // jосвобождае память
     size = size - counterKey; // переопределяем размер

     ptr = new int [size];
     int counter = 0, ix = 0;
     while (counter < size)
     {
         if (temp[counter] != key)
         {
             ptr[ix] = temp.ptr[counter]; // скопировать массив
             ix++;
         }
         counter++;
     }

     return *this;
 }

 int Array::search(const int key) const // поиск по ключу
 {
     for (int ix = 0; ix < size; ix++)
         if ( key == ptr[ix] ) // поиск по ключу
             return (ix + 1);             // позиция искомого элемента

     return -1;
 }

 void Array::choicesSort() // сортировка выбором
 {
     for (int repeat_counter = 0; repeat_counter < size; repeat_counter++)
     {
         int temp = ptr[0]; // временная переменная для хранения значения перестановки
         for (int element_counter = repeat_counter + 1; element_counter < size; element_counter++)
         {
             if (ptr[repeat_counter] > ptr[element_counter])
             {
                 temp = ptr[repeat_counter];
                 ptr[repeat_counter] = ptr[element_counter];
                 ptr[element_counter] = temp;
             }
         }
     }
 }

 void Array::setSize(int array_size)
 {
    size = array_size;
 }

 int Array::sum() const
 {
     int res = 0;
     for(int i=0;i<size;i++)
     {
         res += ptr[i];
     }
     return res;
 }

 float Array::mean() const
 {
     float res=0;
     res = this->sum()/(float)size;
     return res;
 }

 float Array::std() const
 {
     float res=0;
     float m = this->mean();
     for (int i=0;i<size;i++)
        res+=pow(ptr[i]-m,2);
     return sqrt(res/(size-1));

 }
