#include "otimizacao.h"
#include "random.h"
#include <bits/stdc++.h>
#include <cmath>

int ta;
using namespace std;
int atu,n1, n2, n3;
vector<bool> vis;
vector<int> livres;
int pos = 1;
int guarda =0;
int ale;
int lim=0;


void concatenar(Data &data,sub &subs1, sub &subs2,sub &subresultado){
    
    sub subconcat;
    subconcat.C = subs1.C + (subs2.W * (subs1.T +data.getDistance(subs1.last, subs2.first))) + subs2.C;
    subconcat.T = subs1.T +subs2.T +  data.getDistance(subs1.last, subs2.first);
    subconcat.W = subs1.W + subs2.W;
    subconcat.first = subs1.first;
    subconcat.last = subs2.last;
    
    
    subresultado = subconcat;
 
    
}


void atualize(Data &data,vector<int> s, int n, vector<vector<sub>> &submatriz){
   
    submatriz.clear();
    submatriz.resize(n+1);

    for(int i = 0; i <= n; i++){
        submatriz[i].resize(n+1);
    }
   
    //no unico:
    for(int i = 0; i <= n; i++){
        sub atual;
        atual.C = 0;
        atual.T = 0;
        atual.first = s[i];
        atual.last = s[i];
        if(i == 0 ){
            atual.W = 0;
        }
        else{
            atual.W = 1;
        }
        
        
        submatriz[i][i] = atual;
    }
   
    //diretas
    for(int i = 0; i <= n; i++){
        
        for(int j = i+1; j <= n; j++){
            vector<int> atual;
            sub subatual;
            //vetores das posições
            concatenar(data,submatriz[i][j-1],submatriz[j][j], subatual);
            subatual.first = s[i];
            subatual.last = s[j];
            submatriz[i][j] = subatual;

        }}
        
    //inversas
    for(int i = 1; i <= n; i++){
        for(int j = i-1 ; j >= 0; j--){
            vector<int> atual;
            sub subatual;
           
            concatenar(data, submatriz[i][j+1], submatriz[j][j], subatual);
            
            submatriz[i][j] = subatual;
        }
        
    }

}

void atualizemov(Data &data,int alterado1, int alterado2,int n, vector<vector<sub>> &submatriz, vector<int> &s){
    
    //no unico:
    for(int i = alterado1; i <= alterado2; i++){
        if(i > s.size()-1){
            break;
        }

        sub atual;
        atual.C = 0;
        atual.T = 0;
        atual.first = s[i];
        atual.last = s[i];
        if(i == 0){
            atual.W = 0;
        }
        else{
            atual.W = 1;
        }
        
        
        submatriz[i][i] = atual;
    }
    //conversoes diretas:
    
    for(int i = 0; i <= alterado2; i++){
        if(i > s.size()-1){
            break;
        }
        else if(i < alterado1){
           for(int j = alterado1; j <= n; j++){
                if(j > s.size()-1){
                   break;
        }
                sub subatual;
                concatenar(data, submatriz[i][j-1], submatriz[j][j], subatual);     
                submatriz[i][j] = subatual;   
                
            }  
        }
           else{
            
                for(int j = i+1; j <= n; j++){
                if(j > s.size()-1){
                   break;
        }
                    sub subatual;
                    concatenar(data, submatriz[i][j-1], submatriz[j][j], subatual);
                    submatriz[i][j] = subatual;   
                }}}
                
    //inversas:
    for(int i = alterado1; i <= n; i++){
        if(i > s.size()-1){
                break;
        }
        else if( i <= alterado2){
        for(int j = i - 1; j >= 0; j--){
           if(j > s.size()-1){
                   break;
        } 
            sub subatual; 
            concatenar(data,submatriz[i][j+1], submatriz[j][j], subatual);  
            submatriz[i][j] = subatual; 
        }}
        else{
            for(int j = i - 1; j >= 0; j--){
                if(j > s.size()-1){
                   break;
        }
            
            sub subatual; 
            concatenar(data, submatriz[i][j+1], submatriz[j][j],  subatual);  
            submatriz[i][j] = subatual;
        
        }}}
    }

//pertubacao aleatoria da solucao s melhorada
void pertubacao(Data &data, vector<int> &s, double &total, vector<vector<sub>> &submatriz,int n, const vector<int> &mls , const double &mltotal,  vector<vector<sub>> &mlsubmatriz){
    
    int ale1, ale2, ale3, ale4;
    float meio = mls.size();
    meio = meio/2;
    int tamanho = mls.size();
   

    //escolha dos 4 nos aleatorios que delimitam os blocos a serem movimentados
    //obs: a separacao entre solucoes de tamanhos pares ou impares ocorre para definir o intervalo de escolha dos numeros

    if(mls.size()%2 ==0){
        ale2 = Random::getInt(2, (mls.size()/2)-1);

        ale3 = Random::getInt(mls.size()/2, mls.size()-3);

        ale1 = Random::getInt(1, ale2-1);

        ale4 = Random::getInt(ale3+1, tamanho-2);


    }
    else{

        ale2 = Random::getInt(2, floor(meio));

        ale3 = Random::getInt(ceil(meio), mls.size()-3);

        ale1 = Random::getInt(1, ale2-1);

        ale4 = Random::getInt(ale3+1, tamanho-2);


    }

    //separacao considerando que os blocos movimentados podem ser adjacentes
    if(ale2 != ale3-1){
            submatriz = mlsubmatriz;

            vector<int> antes(mls.begin(), mls.begin()+ale1);
            sub subantes = mlsubmatriz[0][ale1-1];
            
            vector<int> sub1(mls.begin()+ale1, mls.begin()+ale2+1);
            sub subsub1 = mlsubmatriz[ale1][ale2];

            vector<int> entre(mls.begin()+ale2+1, mls.begin() + ale3);
            sub subentre = mlsubmatriz[ale2+1][ale3-1];

            vector<int> sub2(mls.begin()+ale3, mls.begin()+ale4+1);
            sub subsub2 = mlsubmatriz[ale3][ale4];

            vector<int> depois(mls.begin()+ale4+1, mls.end());
            sub subdepois = mlsubmatriz[ale4+1][mls.size()-1];

            vector<int> cop;
            sub subcop;

            cop.insert(cop.end(), antes.begin(), antes.end());
            cop.insert(cop.end(), sub2.begin(), sub2.end());
            cop.insert(cop.end(), entre.begin(), entre.end());
            cop.insert(cop.end(), sub1.begin(), sub1.end());
            cop.insert(cop.end(), depois.begin(), depois.end());

            concatenar(data, subantes, subsub2, subcop);
            
            concatenar(data, subcop, subentre, subcop);

            concatenar(data, subcop, subsub1, subcop);

            concatenar(data, subcop, subdepois, subcop);
            
            atualizemov(data, ale1, ale4, n, submatriz, cop);

            s = cop;
            total = submatriz[0][mls.size()-1].C;
        }
    else{
        submatriz = mlsubmatriz;
        vector<int> antes(mls.begin(), mls.begin()+ale1);
        sub subantes = mlsubmatriz[0][ale1-1];

        vector<int> sub1(mls.begin()+ale1, mls.begin()+ale2+1);
        sub subsub1 = mlsubmatriz[ale1][ale2];

        vector<int> sub2(mls.begin()+ale3, mls.begin()+ale4+1);
        sub subsub2 = mlsubmatriz[ale3][ale4];

        vector<int> depois(mls.begin()+ale4+1, mls.end());
        sub subdepois = mlsubmatriz[ale4+1][s.size()-1];

        vector<int> cop;
        sub subcop;

        cop.insert(cop.end(), antes.begin(), antes.end());
        cop.insert(cop.end(), sub2.begin(), sub2.end());
        cop.insert(cop.end(), sub1.begin(), sub1.end());
        cop.insert(cop.end(), depois.begin(), depois.end());
        
        concatenar(data, subantes, subsub2, subcop);
            
        concatenar(data,subcop, subsub1, subcop);

        concatenar(data, subcop, subdepois, subcop);
            
        atualizemov(data, ale1, ale4, n, submatriz, cop);

        s = cop;
        total = subcop.C;
}}

//movimento swap
void impswap(Data &data, bool &melhora, vector<int> &s, double &total,int n,vector<vector<sub>> &submatriz){
    double mdif = 0;
    int meli, melj;
    vector<int> result;
    sub subresult, msub;

    //i e j = nos que serao invertidos
    for(int i = 1; i < (s.size() - 1); i++){
        double dif = 0;
            for(int j = 1 + i; j < s.size() - 1; j++){
                if(j == i+1){

                    concatenar(data, submatriz[0][i-1], submatriz[j][j], subresult);

                    concatenar(data, subresult, submatriz[i][i], subresult);

                    concatenar(data, subresult, submatriz[j+1][s.size()-1], subresult);

                    dif = subresult.C - total;
                }
                else{

                    concatenar(data, submatriz[0][i-1], submatriz[j][j], subresult);

                    concatenar(data, subresult, submatriz[i+1][j-1], subresult);

                    concatenar(data, subresult, submatriz[i][i], subresult);

                    concatenar(data, subresult, submatriz[j+1][s.size()-1], subresult);

                    dif = subresult.C - total;

                }
                if(dif < mdif){
                    mdif = dif;
                    meli = i;
                    melj = j;
                    msub = subresult;
                }}}


    if(mdif < 0){
            swap(s[meli], s[melj]);
            total = msub.C;
            melhora = true;
            atualizemov(data, meli, melj, n, submatriz, s);
    }}

//movimento 2-opt
void twopt(Data &data, bool &melhora, vector<int> &s, double &total,int n,vector<vector<sub>> &submatriz){
    double mdif = 0;
    int melj, meli;
    sub msub;
    double dif = 0;

    // i = define o primeiro no que sera invertido
    // j = define o ultimo no que sera invertido

    for(int i= 1; i < (s.size()-1); i++){

        for(int j = i + 2; j < (s.size()-1); j++){

                sub subresult;
                
                concatenar(data,  submatriz[0][i-1], submatriz[j][i], subresult);

                concatenar(data, subresult, submatriz[j+1][s.size()-1], subresult);

                dif = subresult.C - total;


            if(mdif > dif){
                mdif = dif;
                melj = j;
                meli = i;
                msub = subresult;
                
            }}}

            if(mdif < 0){
                
                reverse(s.begin() + meli, s.begin() + melj + 1);

                total = msub.C;

                melhora = true;

                atualizemov(data, meli, melj, n, submatriz, s);
            }}

//movimentos reinsertion, 2-or-opt, 3-or-opt. a escolha de qual movimento e guiada pela variavel "qual"
void outros(Data &data, int qual, bool &melhora, vector<int> &s, double &total,int n,vector<vector<sub>> &submatriz){

    //movimento reinsertion
    if(qual == 1){
        double mdif = 0;
        int melj, meli;
        double dif = 0;
        sub msub;
        int ins;
        vector<int> ms;

        // i = define o no movimentado
        // j = define a aresta onde o no sera inserido

        for(int i = 1; i < (s.size()-1); i++){

            for(int j = 1 ; j < s.size()-1; j++){

                sub subresultado;

                if(j == i || j == i+1){
                }
                else{
                    if(i < j){

                        concatenar(data, submatriz[0][i-1], submatriz[i+1][j-1],subresultado);

                        concatenar(data,subresultado, submatriz[i][i],  subresultado);

                        concatenar(data, subresultado, submatriz[j][s.size()-1],  subresultado);

                        dif = subresultado.C - total;
                    }
                    else{

                        concatenar(data, submatriz[0][j-1], submatriz[i][i],subresultado);

                        concatenar(data, subresultado, submatriz[j][i-1], subresultado);

                        concatenar(data, subresultado, submatriz[i+1][s.size()-1], subresultado);

                        dif = subresultado.C - total;
                    }}

                if(dif < mdif){
                    ins = s[i];
                    mdif = dif;
                    melj = j;
                    meli = i;
                    msub = subresultado;
    
                }}}


            if(mdif < 0){
                total = msub.C;

                melhora = true;

                if(meli < melj){
                    
                    s.erase(s.begin() + meli);
                    s.insert(s.begin()+melj-1, ins);
                    atualizemov(data, meli, melj, n, submatriz, s);

                }
                else{
                    
                    s.erase(s.begin() + meli);
                    s.insert(s.begin()+melj, ins);
                    atualizemov(data, melj, meli, n, submatriz, s);
        
                }
        

                
            }}


    //movimento 2-or-opt
    if(qual == 2){
        double mdif=0;
        int melj, meli;
        sub msub;
        vector<int> ms;

        // i = define o primeiro bloco a ser movimentado sendo ele i a i + 1
        // j = define a aresta onde o bloco sera inserido

        for(int i = 1; i < s.size() - 2; i++){

            for(int j = 1;  j < s.size(); j++){
                double dif = 0;
                sub subresultado;
                vector<int> resultado;

                if( j == i+2|| j == i+1|| j == i){
                }

                    else{
                        if(i < j){

                            concatenar(data, submatriz[0][i-1], submatriz[i+2][j-1], subresultado);

                            concatenar(data,subresultado, submatriz[i][i+1], subresultado);

                            concatenar(data, subresultado, submatriz[j][s.size()-1],  subresultado);

                            dif = subresultado.C - total;
                        }
                        else{

                            concatenar(data, submatriz[0][j-1], submatriz[i][i+1],subresultado);

                            concatenar(data, subresultado, submatriz[j][i-1],  subresultado);

                            concatenar(data, subresultado, submatriz[i+2][s.size()-1], subresultado);

                            dif = subresultado.C - total;
                        }}
                    if(mdif>dif){
                        mdif = dif;
                        melj = j;
                        meli = i;
                        msub = subresultado;
                  }}}

       if(mdif < 0){
                
                vector<int> cop(s.begin() + meli, s.begin()+meli + 2);
                s.erase(s.begin()+meli, s.begin()+meli+2);
                if(meli < melj){
                s.insert(s.begin()+melj-2, cop.begin(), cop.end());
                atualizemov(data, meli, melj+1, n, submatriz, s);
            }
                
                else{
                s.insert(s.begin()+melj, cop.begin(), cop.end());
                atualizemov(data,  melj,meli+1, n, submatriz, s);
            }

                total = msub.C;

                melhora = true;

                
       }}

    //movimento 3-or-opt
    if(qual == 3){
    double mdif=0;
    int melj, meli;
    sub msub;
    vector<int> ms;

    // i = define o primeiro bloco a ser movimentado sendo ele i a i + 2
    // j = define a aresta onde o bloco sera inserido

    for(int i = 1; i < s.size() - 3; i++){
        vector<int> resultado;
        sub subresultado;
        double dif = 0;

        for(int j = 1; j < s.size(); j++){
            if(j == i+3||j == i+2|| j == i+1|| j == i){
            }
            else{
                if(i < j){

                    concatenar(data, submatriz[0][i-1], submatriz[i+3][j-1],subresultado);

                    concatenar(data,subresultado, submatriz[i][i+2], subresultado);

                    concatenar(data, subresultado, submatriz[j][s.size()-1], subresultado);

                    dif = subresultado.C - total;
                }
                else{

                    concatenar(data, submatriz[0][j-1], submatriz[i][i+2] ,subresultado);

                    concatenar(data, subresultado, submatriz[j][i-1], subresultado);

                    concatenar(data, subresultado, submatriz[i+3][s.size()-1], subresultado);

                    dif = subresultado.C - total;
                }}
            if(dif < mdif){
                mdif = dif;
                melj = j;
                meli = i;
                msub = subresultado;
            }}}

      if(mdif < 0){
                vector<int> cop(s.begin() + meli, s.begin() + meli +3);

                s.erase(s.begin()+meli, s.begin()+meli+3);

                if(meli < melj){
                    s.insert(s.begin()+melj-3, cop.begin(), cop.end());
                    atualizemov(data, meli, melj+2, n, submatriz, s);
                }
                else{
                    s.insert(s.begin()+melj, cop.begin(), cop.end());
                    atualizemov(data, melj, meli+2, n, submatriz, s);
                }

                total = msub.C;

                melhora = true;
                
      }}}


//melhora da solucao s atraves de movimentos definidos de forma aleatoria (baseado em rvnd)
void buscalocal(Data &data, vector<int> &s, double &total,vector<vector<sub>> &submatriz, int n){
    bool melhora = true;
    vector<int> rvn = {1,2,3,4,5};
    while(!rvn.empty()){
        melhora = false;
        int r;
        r = Random::getInt(0, rvn.size()-1);

        switch(rvn[r]){
            case 1:

               impswap(data, melhora, s, total, n, submatriz);
    
                break;

            case 2:

               twopt(data, melhora, s, total, n, submatriz);

                break;

            case 3:

                outros(data, 1, melhora, s, total, n, submatriz);

                break;

            case 4:

                outros(data, 2, melhora, s, total, n, submatriz);
    
                break;

            case 5:

                outros(data, 3, melhora, s, total, n, submatriz);

                break;
        }
        if(melhora == true){

            rvn = {1,2,3,4,5};
        }
        else{
            rvn.erase(rvn.begin()+r);
    }}}


//calculo do custo de insercao de um valor em cada posicao da solucao s
void custos(Data &data, int x, vector<pair<double, int>> &inse, vector<int> &livres, vector<int> &s){
    for(int i = 0; i < livres.size(); i++){
            int custo;
            custo = 0;
            custo = data.getDistance(s[x], livres[i]);
            inse.push_back({custo, livres[i]});
        }}


// montagem aleatoria da solucao s inicial.

void construcao(Data &data, vector<int> &s, int n, double &total){

    // definicao do tamanho da lista de livres.
    livres.resize(n-1);

    //montagem da lista de livres,a funcao iota faz com que uma lista seja ocupada por um intervalo de x (ultimo valor fornecido a funcao) ate lista.tamanho
    iota(livres.begin(), livres.end(), 2);

    double r = Random::getInt(0,25);
    r = r/100;
    int cont = 0;


    int c = n*r;
    while(!livres.empty()){
            vector<pair<double, int>> inse = vector<pair<double, int>>();

            // escolha do y entre os r% de livres(candidatos);

            if(c >= livres.size()){
                c = c - 1;
            }

            int y = Random::getInt(0,c);
            //
            //chamada da funcao que calcula o custo da insercao do valor analisado em cada posicao da solucao
            custos(data, cont, inse, livres, s);



            std::sort(inse.begin(), inse.end());

            // como inse é o vetor com os valores a serem inseridos, é necessario escolher dentro dele

            s.insert(s.begin() + cont + 1, inse[y].second);


            livres.erase(remove(livres.begin(), livres.end(), inse[y].second), livres.end());


            cont++;
        }}

