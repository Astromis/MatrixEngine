#ifndef ARRAY_H
#define ARRAY_H


#include "array.h"
#include "math.h"
#include <iostream>
#include <iomanip> // для манипулятора setw
#include <cstdlib>
#include <istream>
#include <ostream>

using std::setw;   // пространство имен std для setw
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin
using std::istream;
using std::ostream;

template<class T>
class Array
{
    template<class F>
    friend istream &operator>> (istream &, Array<F> &); // перегруженный оператор ввода
    template<class F>
    friend ostream &operator<< (ostream &, const Array<F> &); // перегруженный оператор вывода
private:
    T *ptr; // указатель на массив
    int size; // размер массива
public:

    Array(); // конструктор по умолчанию
    Array(int ); // конструктор с параметрами
    Array( const Array & ); // конструктор копии
    virtual ~Array(); // десструктор

    T *getPtr();
    int getSize() const; // возвратить количество элементов массива
    void setArray(); // заполнение массива
    void getArray(); // вывод массива
    void setSize(int array_size);
    const Array &operator= (const Array &); // оператор присваивания
    bool operator== (const Array &) const; // оператор сравнения
    T &operator[] (int );
    Array operator+ (const Array &);
    Array &operator+= (const int &); // оператор добавления элемента в конец массива
    Array &operator- (const int &); // оператор удаления элемента по ключу
    T search(const T ) const;
    void choicesSort(); // сортировка выбором

    T sum() const;
    float mean() const;
    float std() const;
    void fill_rand(const T a,const T b);
    void fill_normal(float mean, float std);

    T max();
    T min();

};
template<class T>
T* Array<T>::getPtr()
{
    return ptr;
}

template<class T>
Array<T>::Array() // конструктор по умолчанию, без параметров
/**< Constructor */
{
    size = 5; // по умолчанию размер массива = 10 элементов
    ptr = new T [size]; // выделить место в памяти для массива

}

template<class T>
Array<T>::Array(int arraySize) // конструктор с параметрами
/**< Constructor with params */
{
    // если значение параметра больше 0, присвоить size значение arraySize, иначе - 10
    size = (arraySize > 0 ? arraySize : 5);
    //delete [] ptr;
    ptr = new T [size]; // выделить место в памяти для массива

}

template<class T>
Array<T>::Array( const Array &arrayToCopy ) // конструктор копии
    :size(arrayToCopy.size)              // инициализатор размера массива
/**< Constructor if copy */
{
    ptr = new T [size]; // выделить место в памяти для массива

    for (int ix = 0; ix < size; ix++)
        ptr[ix] = arrayToCopy.ptr[ix]; // заполняем массив значениями массива arrayToCopy
}

template<class T>
Array<T>::~Array() // десструктор класса Array
/**< Destructor */
{

    delete  [] ptr; // освободить память, удалив массив
}

template<class T>
int Array<T>::getSize() const // возвратить количество элементов массива
/**< Return size of array */
{
    return size;
}

// перегруженный оператор ввода, для ввода значений массива с клавиатуры
template<class F>
istream &operator>> (istream & input, Array<F> &obj)
/**< Overloaded operator for write in array from keyboard */
{
    for (int ix = 0; ix < obj.size; ix++)
        input >> obj.ptr[ix]; // заполняем массив объекта obj
    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
template<class F>
ostream &operator<< (ostream &output, const Array<F> &obj)
/**< Overloaded operator for read from array */
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        output << setw(10) // под каждое число выделяется 5 позиций
               << obj.ptr[ix];
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

template<class T>
void Array<T>::setArray() // заполнение массива
/**< Another function for set array from keyboard */
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
/**< Overloaded operator of assigment */
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
/**< Overloaded operator of equal compare */
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
/**< Overloaded operator of indexing */
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
/**< Overloaded operator of sum. Return sum of matrixes. */
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
 /**< Operator of inserting value in the end of vector */
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
 /**< Operator of deliting element by key */
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
 T Array<T>::search(const T key) const // поиск по ключу
 /**< Searching by key */
 {
     for (int ix = 0; ix < size; ix++)
         if ( key == ptr[ix] ) // поиск по ключу
             return (ix + 1);             // позиция искомого элемента

     return (T)-1;
 }

 template<class T>
 void Array<T>::choicesSort() // сортировка выбором
 /**< Sort by chose */
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
 /**< Resizing of vector */
 {
    delete [] ptr;
    size = array_size;
    ptr = new T [size];

 }

 template<class T>
 T Array<T>::sum() const
 /**< Sum all elements in vector */
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
 /**< Arithmetic mean  */
 {
     float res=0;
     res = this->sum()/(float)size;
     return res;
 }

 template<class T>
 float Array<T>::std() const
 /**< Standard deviation */
 {
     float res=0;
     float m = this->mean();
     for (int i=0;i<size;i++)
        res+=pow(ptr[i]-m,2);
     return sqrt(res/(size-1));

 }

 template<class T>
 void Array<T>::fill_rand(const T a,const T b)
 /** \brief Fill vector by random numbers in range from a to b
  *
  * \param [in] a Start range
  * \param [in] b End range
  * \return Nothing
  *
  */

 {
     T tmp = 0;
     for (int ix = 0; ix < size; ix++)
     {
         tmp = (T)(rand() % (int)b);
         if(tmp <= a)
         {
             ptr[ix] = a;
         }
         else
            ptr[ix] = tmp;
     }

 }

 template<class T>
void Array<T>::fill_normal(float mean, float std)
/** \brief Fill vector by normal distributed numbers with mean and std using Box–Muller transform
 *
 * \param [in] mean - first param of normal distribution
 * \param [in] std - second param of normal distribution
 * \return Nothing
 *
 */

{
    float u = 0;
    float v = 0;
    float s =0;
    for(int i=0; i< size; i++)
    {
        u = (float)rand() / RAND_MAX;
        //cout<< u<< " ";
        //cout<< u<<endl;
        if(u< 0.5)
            u = u * (-1) * 2;
        else
            u = u / 2;
        //cout<< u<<endl;
        v = (float)rand() / RAND_MAX;
        if(v< 0.5)
            v = v * (-1) * 2;
        else
            v = v / 2;

        s = u*u + v*v;

        if (s >= 1 || s == 0)
        {
            i--;
            continue;
        }

        ptr[i] = (u * sqrt((-2 * log(s)/s))) * std + mean - 0.171293;
    }


}

template<class T>
T Array<T>::max()
/** \brief Find max value in array
 *
 * \return Max value
 *
 */

{
    int max_val = ptr[0];
    for (int i = 1; i < size; i++) {
        if (ptr[i] > max_val) {
            max_val = ptr[i];
        }
    }
    return max_val;

}

template<class T>
T Array<T>::min()
/** \brief Find min value in array
 *
 * \return Min value
 *
 */
{
    int min_val = ptr[0];
    for (int i = 1; i < size; i++) {
        if (ptr[i] < min_val) {
            min_val = ptr[i];
        }
    }
    return min_val;
}

#endif // ARRAY_H
