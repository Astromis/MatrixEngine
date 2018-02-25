#include <iostream>
using namespace std;

#include "matrix.h"
#include "array.h"
#include <cstdlib>

int main()
{
    srand(time(NULL));
    //Array<int> b(50);
    Matrix<float> a(4,5);
    Matrix<float> b;
    a.fill_normal(0,1);
    b = a;
    b.T();
    cout<< b;
    return 0;
}
