#include <iostream>
using namespace std;

#include "matrix.h"

#include <cstdlib>

int main()
{
    srand(time(NULL));/*
    Matrix myMatrix1(2,2); // конструктор с параметрами

    // заполнение матрицы
    for (int ix = 0; ix < myMatrix1.getSize(); ix++)
        for (int jx = 0; jx < myMatrix1.getArrayPtr()->getSize(); jx++)
            myMatrix1[ix][jx] = rand() % 100;

    cout << myMatrix1;  // перегруженный оператор вывода

    Matrix myMatrix2(myMatrix1); // конструктор копии

    myMatrix2.getMatrix(); // вывод матрицы с помощью метода класса Matrix

    //myMatrix2.setMatrix(); // заполнение матрицы с помощью метода класса Matrix

    int * adr = myMatrix2.search(99);

    if (adr == NULL)
        cout << "Значения " << 99 << " в матрице нет!\n";
    else
        cout << "Значение " << 99 << " находится в памяти по адресу: " << adr << endl;

    cout << (myMatrix1 + myMatrix2); // перегруженная операция сложения

    cout << "Как видите, myMatrix1 осталась без изменения!\n";
    cout << myMatrix1;

    myMatrix1 += myMatrix2; // перегруженная операция сложения-присвоения

    cout << "myMatrix1 содержит значения ,полученные при: myMatrix1 += myMatrix2; !\n";
    cout << myMatrix1;

    cout << (myMatrix1 - myMatrix1); // перегруженная операция вычитания

    Matrix myMatrix3 = myMatrix2; // перегруженная операция присваивания

    cout << myMatrix3;

    if (myMatrix3 == myMatrix2)
        cout << "Матрицы myMatrix3 и myMatrix2 равны!\n";
*/
    cout<< "Matrix multiplying\n\n";

    Matrix myMatrix1(2,2); // конструктор с параметрами
    // заполнение матрицы
    myMatrix1.getSize();
    myMatrix1.getArrayPtr()->getSize();
    //cout<<"Donesssssssssssssssssss!"<<endl;
    //myMatrix1[0][49];
    //return 0;

    for (int ix = 0; ix < myMatrix1.getSize()[0]; ix++)
        for (int jx = 0; jx < myMatrix1.getArrayPtr()->getSize(); jx++){
               // cout<<"ix: "<<ix<<"jx: "<<jx<<endl;
            myMatrix1[ix][jx] = rand() % 3;

        }
    Array vec(10);
    for (int ix = 0; ix < vec.getSize(); ix++)
            vec[ix] = rand() % 3;
    cout<<vec;
    cout<<vec.sum()<<endl;
    cout<<vec.std()<<endl;
    cout<<"Array init is complite"<<endl;
    cout<<"Filling done"<<endl;

    //cout << myMatrix1;  // перегруженный оператор вывода
    //cout<<"Donesssssssssssssssssss!";
    Matrix myMatrix2(myMatrix1);
    cout<<myMatrix1;
    myMatrix1.T();
    //cout<<myMatrix1;
    cout<<"Transposing done"<<endl;
    cout<< myMatrix1;
    Matrix res;
    res =  myMatrix1*2 + 2;
    cout<<"Multiplication done"<<endl;
    cout<<res;
    char c;
    cin>>c;
    return 0;
}
