#include <iostream>

#include "matrix.h"
#include "array.h"
#include <cstdlib>

#include <fstream>
#include <stdio.h>
#include "word2vec.h"

//TODO:
//redaction methods for memory economy and speed increases
//problem with concat method: return truncated matrix - without raws or columns

//make clean with includes

void cp(char * s2)
{
    char s1[5];
    strcpy(s1,s2);
    printf("%s",s1);
}
int main()
{
    srand(time(NULL));
    Matrix<float> b(10,100);
    Matrix<float> c;
    //word2vecStandartInit("/home/igor/test.txt");
    //ReadVocab("./save.mod1");
    //TrainModel(b);
    //SaveVocab("./save.mod");
    b.fill_normal(0,1);
    b.save("./mat.bin");
    c.load("./mat.bin");
    //cout<<endl<<b;
    //cout<<c;
    if (c == b)
        cout<<"True"<<endl;
    //fclose(myfile);
    //myfile = fopen ("./hello.txt", "r");
    //fread(c, sizeof(int), 2, myfile);
   // std::cout<<c[0]<<c[1]<<std::endl;



    /*
    Matrix<float> input(4,2);
    Matrix<float> target(4,1);

    Matrix<float> h_inp(10,1);
    Matrix<float> h_out(10,1);

    Matrix<float> f_inp(2,1);
    Matrix<float> f_out(2,1);



    input[0][0] = 0;
    input[0][1] = 0;

    input[1][0] = 0;
    input[1][1] = 1;

    input[2][0] = 1;
    input[2][1] = 0;

    input[3][0] = 1;
    input[3][1] = 1;

    target[0][0] = 1;
    target[1][0] = 0;
    target[2][0] = 0;
    target[3][0] = 1;

    Array<Matrix<float> > weiths(2);

    weiths[0].resize_matrix(10,2);
    weiths[1].resize_matrix(1,10);
    weiths[0].fill_normal(0,pow(2,-0.5));
    weiths[1].fill_normal(0,pow(10,-0.5));
    for(int ep = 0; ep< 1000; ep++)
    for(int i=0;i<4;i++)
    {
        Matrix<float> tmp1(2,1);
        Matrix<float> error_h;
        Matrix<float> error;

        Matrix<float> now_input;
        Matrix<float> now_target;
        now_input = input.slice_raw(i,0);
        now_target = target.slice_raw(i,0);

        //forward prop
        h_inp= weiths[0].dot(now_input.transpose());
        h_out = h_inp.activation();
        f_inp = weiths[1].dot(h_out);
        f_out = f_inp.activation();

        //back prop
        error = now_target - f_out;
        error_h = weiths[1].transpose().dot(error);
        tmp1 = error * f_out*(f_out - 1);
        weiths[1] = weiths[1] + tmp1.dot(h_out.transpose());

        tmp1 = error_h * h_out * (1 - h_out);
        weiths[0] = weiths[0] + tmp1.dot(now_input);

    }
    for(int i=0;i<4;i++)
    {
        Matrix<float> tmp(2,1);
        Matrix<float> tmp1(2,1);
        Matrix<float> error_h(1,10);
        Matrix<float> error(1,1);

        tmp = input.slice_raw(i,0);
        tmp.T();
        //cout<<tmp;
        h_inp = weiths[0].dot(tmp);
        //cout<<h_inp;
        h_out = h_inp.activation();
        //cout<<h_out;
        f_inp = weiths[1].dot(h_out);
        f_out = f_inp.activation();
        cout<<"Input: "<<endl<<input.slice_raw(i,0);
        cout<<"Output: "<<f_out[0][0]<<endl;
    }
*/

    return 0;

}

