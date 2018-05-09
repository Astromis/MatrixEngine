#include <iostream>

#include "matrix.h"
#include "array.h"
#include <cstdlib>

#include <fstream>
#include <stdio.h>
#include "word2vec.h"
#include "stdio.h"
//TODO:
//redaction methods for memory economy and speed increases
//problem with concat method: return truncated matrix - without raws or columns
//Make method "drop" void type too.
//Crunch for type conversion. Make type conversion with overloading conversion operators.
//Trouble with friend operators. If expression given implicitly than compiler return an error of mismatch.
//In note to this error told that compiler could not find conversion from Matrix<> to Matrix<>& WTF??

void cp(char * s2)
{
    char s1[5];
    strcpy(s1,s2);
    printf("%s",s1);
}

int main()
{

    srand(time(NULL));

    Matrix<float> x_i, x_sum, weiths, loss, delta_w, x_train, y_train, z, p, u;
    Matrix<int> x1_train;
    float learning_rate = 0.001;
    x1_train.load("./train_matrix_int.bin");

    y_train = x1_train.slice_col(0,0).to_float();
    x_train = x1_train.drop_column(0).to_float();

    x_train = x_train + (float)0.1;
    y_train = y_train + (float)0.1;
    float y_train_mean = 0;
    for(int i =0; i < y_train.raws; i++)
    {
        y_train_mean += y_train[i][0];
    }
    y_train_mean /= y_train.raws;
    weiths.resize_matrix(1, x_train.columns);
    weiths[0][0] = y_train_mean;
    //weiths = weiths *weiths;
    int num_raws = x_train.raws;
    cout<<weiths;

    for(int i=0; i< 10; i++)
    {
        z = x_train.dot(weiths.transpose());
    }
    p.resize_matrix(x_train.raws, 1);
    for(int i =0 ;i  < p.raws; i++)
    {
        p[i][0] = 1/(1 + exp(- z[i][0]));
    }
    u = z + (y_train - p) / (p*((float)1-p));

    /*this cycle realise gradient descent algorithm.
    for(int i=0;i < num_raws; i++)
    {
       x_i = x_train.slice_raw(i, 0);
       x_i.T();
       x_sum = weiths.dot(x_i);

       x_sum = x_sum.activation();
        if(i % 1000 == 0) cout<<"x_i: "<<x_sum<<endl;
       loss = (y_train.slice_raw(i,0) - x_sum) * (y_train.slice_raw(i,0) - x_sum);
        //if(i % 1000 == 0) cout<<"x_i: "<<loss<<endl;
       //if(loss[0][0] < 0.0001 ) break;
       delta_w = (y_train.slice_raw(i, 0) - x_sum)*(x_sum*((float)1.0 - x_sum));
       //cout<<(y_train.slice_raw(i, 0) - x_sum);
       //(y_train.slice_raw(i, 0) - x_sum[0][0]);
       //if(i % 1 == 0 && i < 10) cout<<delta_w;
       delta_w = delta_w[0][0] * x_i;
       delta_w = delta_w*learning_rate;

       weiths = weiths - delta_w.transpose();
    }*/
    cout<<"Last loss: "<<loss<<endl;
    cout<< weiths;

    //word2vecStandartInit("/home/igor/test.txt");
    //ReadVocab("./save.mod1");
    //TrainModel(b);
    //SaveVocab("./save.mod");


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

