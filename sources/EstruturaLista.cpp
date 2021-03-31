
#include "../headers/EstruturaLista.hpp"

//Contrutor
Grafo::Grafo(int Vertice){
    this->Vertice = Vertice; // Faz a atribuição ao numero de vertices, presentado pela variável n
    Arestas = new vector<int>[Vertice]; // Cria as listas de adjacencia
    Peso = new vector<float>[Vertice];  //Peso[Vertice][Vertice];//Criacao de uma matriz para representar os pesos
}

//Metodos

/*
*   para colocar valores dentro do vector você deve utilizar push_back(valor)
*   e para pegar um valor pode usar o operador [] ou a função at.
*   vector <int> c;
*   c.push_back(3);
*   c.push_back(4);
*   int a = c[0] // a recebe o valor 3
*   int b = c.at(1) // b recebe o valor 4
*/
void Grafo::setAresta(int v1, int v2 ,float peso) {
    Arestas[v1].push_back(v2); // Faz a inserção do vertice 2 no vertice 1
    Arestas[v2].push_back(v1); // e faz a inserção do vertice 1 no vertice 2
    Peso[v1].push_back(peso);
}

//A função get recebe como parametro um vertice e retorna o seu
// grau que é a quantidade de vertices adjacentes;
int Grafo::getGrau(int v) {
    return Arestas[v].size();
}

void Grafo::getVizinhos(int v, int *vizinhos){
    for (int i = 0; i < Arestas[v].size(); ++i){
        vizinhos[i] = this->Arestas[v].at(i) + 1;
    }
}

void Grafo::printGrafo(){
    cout<<endl;
    for (int i = 0; i < Vertice; ++i) {
        cout<< i + 1 <<": ";
        for (int j = 0; j < Arestas[i].size(); ++j) {
            cout << " " << this->Arestas[i].at(j) + 1;
        }
        cout << endl;
    }
}
int Grafo::CompsConexaGrafo(){
    int id = 0;
    int ordem[Vertice];

    for (int i = 0; i < Vertice; ++i) {
        ordem[i] = -1;
    }
    for (int i = 0; i < Vertice; ++i) {
        if (ordem[i] == -1){
            dfsRconComps(i,id++,ordem);
        }
    }
    return id;
}
void Grafo::dfsRconComps(int v, int id, int *ordem){
    ordem[v] = id;

    for (int i = 0; i < Arestas[v].size(); ++i){
        if (ordem[this->Arestas[v].at(i)] == -1){
            dfsRconComps(this->Arestas[v].at(i),id,ordem);
        }
    }
}

void Grafo::buscaProfundidade(int *ordem) {
    int cnt = 0;
    for (int i = 0; i < Vertice; ++i) {
        ordem[i] = -1;
    }
    for (int i = 0; i < Vertice; ++i) {
        if (ordem[i] == -1){
            explorar(i,&cnt,ordem);
        }
    }
}
void Grafo::explorar(int v, int *cnt, int *ordem) {
    int w;
    ordem[v] = (*cnt)++;
    for (int i = 0; i < Arestas[v].size(); ++i){
        if (ordem[this->Arestas[v].at(i)] == -1){
            w = this->Arestas[v].at(i);
            explorar(this->Arestas[v].at(i),cnt,ordem);
        }
    }
}
void Grafo::removeAresta(int v1, int v2) {
    for(unsigned int i=0;i<Arestas[v1].size();i++){
        if(Arestas[v1].at(i)==v2){
            Arestas[v1].erase(Arestas[v1].begin()+i);
            break;
        }
    }
    for(unsigned int j=0;j<Arestas[v2].size();j++){
        if(Arestas[v2].at(j)==v1){
            Arestas[v2].erase(Arestas[v2].begin()+j);
            break;
        }
    }
}
bool Grafo::verificaSeArestaPonto(int ncomponentes, int arestaR1, int arestaR2) {
    int ncomponetesRemocao;
    this->removeAresta(arestaR1,arestaR2);
    ncomponetesRemocao = this->CompsConexaGrafo();
    if (ncomponentes == ncomponetesRemocao){
        return false;
    }else{
        return true;
    }
}

void Grafo::removeVertice(int v) {
    for (int i = 0; i < Vertice; ++i) {
        for(int j=0;j<Arestas[i].size();j++){
            if(Arestas[i].at(j)==v){
                Arestas[i].erase(Arestas[i].begin()+j);
            }
            if(i == v){
                Arestas[i].erase(Arestas[i].begin(),Arestas[i].begin()+Arestas[i].size());
            }
        }
    }
}
bool Grafo::verificaSeVerticeArticulcao(int ncomponentes, int v) {
    int ncomponentesRemocao;
    this->removeVertice(v);
    ncomponentesRemocao = this->CompsConexaGrafo();
    if (ncomponentes == ncomponentesRemocao){
        return false;
    }else{
        return true;
    }
}