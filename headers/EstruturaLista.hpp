#ifndef ESTRUTURALISTA_HPP
#define ESTRUTURALISTA_HPP

#include <iostream>
#include <vector>

using namespace std;
class Grafo{
private:
    int Vertice; //A variável v contém o numero de vértices
    vector<int> *Arestas; //Contém um ponteiro para um array que possue a lista de vértices adjacêntes
    vector<float> *Peso;
public:
    Grafo(int v);    //CONTRUTOR EM C++
    void setAresta(int v1, int v2 , float peso); //ADIOCNAR ARESTA
    int getGrau(int v); // PEGAR O GRAU
    void getVizinhos(int v, int *vizinhos);
    void printGrafo();
    void dfsRconComps(int v, int id, int *ordem);
    int CompsConexaGrafo();
    void buscaProfundidade(int *ordem);
    void explorar(int v,int *cnt,int *ordem);
    void removeAresta(int v1,int v2);
    bool verificaSeArestaPonto(int ncomponentes,int arestaR1,int arestaR2);
    void removeVertice(int v);
    bool verificaSeVerticeArticulcao(int ncomponentes,int v);
};
#endif

