#ifndef OTIMIZACAO_H
#define OTIMIZACAO_H
#include "Data.h"
#include <iostream>
#include <vector>

using namespace std;

struct sub {
    double T, C;
    int W, first, last;
};

void atualize(Data &data,vector<int> s, int n, vector<vector<sub>> &submatriz);
void construcao(Data &data, vector<int> &s, int n, double &total);
void  buscalocal(Data &data, vector<int> &s, double &total,vector<vector<sub>> &submatriz, int n);
void pertubacao(Data &data, vector<int> &s, double &total, vector<vector<sub>> &submatriz,int n, const vector<int> &mls , const double &mltotal,  vector<vector<sub>> &mlsubmatriz);

#endif
