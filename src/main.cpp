// arrumar atualizmov + movimentos
#include <iomanip>
#include "Data.h"
#include "otimizacao.h"
#include "random.h"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;


vector<vector<sub>> submatriz;
vector<int> seque;
vector<vector<sub>> msubmatriz;
vector<int> mseque;
double total;
double mtotal = 10e18;
int iterILS;

int main(int argc, char** argv) {
    auto cronometroi = chrono::steady_clock::now();
    Random::randomize(time(NULL));
    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();
    
    int maxIter  = 10;
    int maxIterILS;
    if(n>100){
        maxIterILS = 100;
    }
    else{
        maxIterILS = n;
    }
    
for(int i = 0; i < maxIter; i++){
// solucao e valor inicial � iniciado
    seque = {1};

    vector<vector<sub>> mlsubmatriz;
    vector<int> mlseque;
    double mltotal = 10e18;

// construcao gera a primeira sequencia

    
    construcao(data, seque, n, total);
    
    seque.insert(seque.end(), 1);
    
    atualize(data,seque, n, submatriz);
    
    total = submatriz[0][n].C;

    

    if(total < mtotal){
        mseque = seque;
        msubmatriz = submatriz;
        mtotal = total;
    }

    iterILS = 0;

    while(iterILS <= maxIterILS){
//uso da busca local baseada em movimentos para aprimorar a solucao
    
    buscalocal(data, seque, total, submatriz,n);
    
//checa se busca local montou um novo melhor local
     if(total < mltotal){
        mlseque = seque;
        mlsubmatriz = submatriz;
        mltotal = total;
        iterILS = 0;
     }

    iterILS++;
    
     pertubacao(data, seque, total,submatriz, n, mlseque, mltotal, mlsubmatriz);
    
    }

    //comparacao melhor local x melhor
    if(mltotal < mtotal){
        msubmatriz = mlsubmatriz; 
        mseque = mlseque;
        mtotal = mltotal;

     }
    
    }


    for(int i =0; i < mseque.size(); i++){
     cout << mseque[i] << "->";
    }
    auto cronometrof = chrono::steady_clock::now();
    chrono::duration<double> cronometro = cronometrof - cronometroi;
     cout << "\nTempo de execucao: " << cronometro.count();
    cout << "\nCusto:" << fixed << setprecision(0) << mtotal;
    return 0;
}
