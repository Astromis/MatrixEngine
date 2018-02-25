/*
#include "array.h"
#include "math.h"
#include <iostream>
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin

#include <iomanip> // для манипулятора setw
using std::setw;   // пространство имен std для setw

#include <cstdlib>
template<class T>
Array<T>::Array() // конструктор по умолчанию, без параметров
{
    size = 1000; // по умолчанию размер массива = 10 элементов
    ptr = new T [size]; // выделить место в памяти для массива
    for (int ix = 0; ix < size; ix++) // обнуляем массив
        ptr[ix] = 0;
}

template<class T>
Array<T>::Array(int arraySize) // конструктор с параметрами
{
    // если значение параметра больше 0, присвоить size значение arraySize, иначе - 10
    size = (arraySize > 0 ? arraySize : 10);
    //delete [] ptr;
    ptr = new T [size]; // выделить место в памяти для массива

    for (int ix = 0; ix < size; ix++) // обнуляем массив
        ptr[ix] = 0;
}

template<class T>
Array<T>::Array( const Array &arrayToCopy ) // конструктор копии
    :size(arrayToCopy.size)              // инициализатор размера массива
{
    ptr = new T [size]; // выделить место в памяти для массива

    for (int ix = 0; ix < size; ix++)
        ptr[ix] = arrayToCopy.ptr[ix]; // заполняем массив значениями массива arrayToCopy
}

template<class T>
Array<T>::~Array() // десструктор класса Array
{
    delete  [] ptr; // освободить память, удалив массив
}

template<class T>
int Array<T>::getSize() const // возвратить количество элементов массива
{
    return size;
}

// перегруженный оператор ввода, для ввода значений массива с клавиатуры
template<class T>
istream &operator>> (istream & input, Array<T> &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
        input >> obj.ptr[ix]; // заполняем массив объекта obj
    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
template<class T>
ostream &operator<< (ostream &output, const Array<T> &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        output << setw(5) // под каждое число выделяется 5 позиций
               << obj.ptr[ix];
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

template<class T>
void Array<T>::setArray() // заполнение массива
{
    for (int ix = 0; ix < size; ix++)
        cin >> ptr[ix]; // ввод элемента массива с клавиатуры
}

template<class T>
void Array<T>::getArray() // вывод массива
{
    for (int ix = 0; ix < size; ix++)
        cout << setw(5) << ptr[ix]; // вывод элементов массива на экран

    cout << std::endl; // новая строка
}

template<class T>
const Array<T> &Array<T>::operator= (const Array &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {
        if (size != right.size)
        {
            delete [] ptr; // освободить пространство
            size = right.size; // установить нужный размер массива
            ptr = new T [size]; // выделить память под копируемый массив
        }

        for (int ix = 0; ix < size; ix++)
            ptr[ix] = right.ptr[ix]; // скопировать массив
    }

    return *this; // разрешает множественное присваивание, например x = t = e
}

template<class T>
bool Array<T>::operator== (const Array &right) const// оператор сравнения
{
    if (size != right.size)
        return false; // массивы с разным количеством элементов
    for (int ix = 0; ix < size; ix++)
        if (ptr[ix] != right.ptr[ix])
            return false; // массивы не равны

    return true; // массивы равны
}

template<class T>
T &Array<T>::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= size)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ptr[subscript]; // возврат ссылки на элемент массива
}

template<class T>
Array<T> Array<T>::operator+ (const Array &right)
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

template<class T>
 Array<T> &Array<T>::operator+= (const int &number) // оператор добавления элемента в конец массива
{
    Array result(size);
    result = *this; // временно сохраним текущий массив

    delete [] ptr; // освобождаем память

    size = size + 1; // увеличиваем размер массива на 1
    ptr = new T [size]; // выделяем память

    for (int ix = 0; ix < (size - 1); ix++)
        ptr[ix] = result.ptr[ix]; // скопировать массив

    ptr[size - 1] = number; // добавляем число в конец массива

    return *this; // каскадный вызов перегруженного оператора
}

template<class T>
 Array<T> &Array<T>::operator- (const int & key) // оператор удаления элемента по ключу
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

     ptr = new T [size];
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

template<class T>
 int Array<T>::search(const T key) const // поиск по ключу
 {
     for (int ix = 0; ix < size; ix++)
         if ( key == ptr[ix] ) // поиск по ключу
             return (ix + 1);             // позиция искомого элемента

     return -1;
 }

 template<class T>
 void Array<T>::choicesSort() // сортировка выбором
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

 template<class T>
 void Array<T>::setSize(int array_size)
 {
    size = array_size;
 }

 template<class T>
 T Array<T>::sum() const
 {
     T res = 0;
     for(int i=0;i<size;i++)
     {
         res += ptr[i];
     }
     return res;
 }

 template<class T>
 float Array<T>::mean() const
 {
     float res=0;
     res = this->sum()/(float)size;
     return res;
 }

 template<class T>
 float Array<T>::std() const
 {
     float res=0;
     float m = this->mean();
     for (int i=0;i<size;i++)
        res+=pow(ptr[i]-m,2);
     return sqrt(res/(size-1));

 }

 template<class T>
 void Array<T>::fill_(const T a,const T b)
 {
     T tmp = 0;
     for (int ix = 0; ix < size; ix++)
     {
         tmp = 1;//rand() % b;
         if(tmp <= a)
         {
             ptr[ix] = a;
         }
         else
            ptr[ix] = tmp;
     }

 }

*/
//void
