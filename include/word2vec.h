/*
    This header file describe functions of word2vec model implementation by Google Research, Tomas Mikolov, 2013
    and functions that provide interface to combine code of model and matrix engine
    The license is located in cpp file.
    Some function was modified. See comment to understanding.
*/

#ifndef _WORD2VEC_H
#define _WORD2VEC_H

#define MAX_STRING 100
#define EXP_TABLE_SIZE 1000
#define MAX_EXP 6
#define MAX_SENTENCE_LENGTH 1000
#define MAX_CODE_LENGTH 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "word2vec.h"
#include "matrix.h"

typedef float real;

struct vocab_word {
  long long cn;
  int *point;
  char *word, *code, codelen;
};

//native functions
int AddWordToVocab(char *word);
int ArgPos(char* str,int argc, char** argv);
void CreateBinaryTree();
void InitNet();
void InitUnigramTable();
void LearnVocabFromTrainFile();
void ReadWord(char* word,FILE* fin);
int ReadWordIndex(FILE* fin);
void ReduceVocab();

int SearchVocab(char* word);
void SortVocab();
void *TrainModelThread(void* id);
int VocabCompare(const void*a, const void* b);

//modified function
void TrainModel(Matrix<real> &embed);
void SaveVocab(char * save_vocab_file);
void ReadVocab(char * read_vocab_file);

//interfaceses
void word2vecInit(long long size, int model_mode, real alp, int win,
                  real samp, int _hs, int neg, int num_thr, long long _iter,
                  int min_co, long long _classes);
void word2vecStandartInit(char* _train_file);
void clear_mem();


#endif
