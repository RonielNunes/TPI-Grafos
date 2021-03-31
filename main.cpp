#include "headers/EstruturaLista.hpp"
#include <cstring>

int main() {
    //DECLARACAO VARIÁVEIS
    FILE *arquivo; //Ponteiro para o tipo arquivo
    int n, aresta1,aresta2,vertice,verticeLido;
    int ordem,tamanho, quantidadeArestas = 0, grau, ncomponentes,arestaR1,arestaR2,arestaR1Lido,arestaR2Lido;
    float peso;
    char nomeArquivoEntrada[20],nomeArquivoSaida[20],nomeArquivo[20] = " ";
    Grafo *grafo;


    //LEITURA DO NOME DO ARQUIVO DE ENTRADA
    cout << endl;
    cout << "**********************GRAFOS LISTA DE ADJACENCIA*******************************" << endl;
    cout << "* Digite o nome do arquivo sem sua extensao: ";
    cin >> nomeArquivoEntrada;
    cout << "* Nome do digitado: " << nomeArquivoEntrada << endl;
    cout << "********************************************************************************" << endl;
    strcpy(nomeArquivo,nomeArquivoEntrada);
    strcat(nomeArquivoEntrada,".txt");
    //ABERTURA DO ARQUIVO
    cout<<nomeArquivo;
    arquivo = fopen(nomeArquivoEntrada,"r");

    if (arquivo == nullptr){
        cout << "ERRO NA ABERTURA DO ARQUIVO!"<< endl; //CASO O ARQUIVP NAO ABRA
        fclose(arquivo);
        return 0;
    }else{
        cout << "ARQUIVO ABERTO COM SUCESSO!" << endl;

        fscanf(arquivo,"%d",&n); //LEITURA DA QUANTIDADE DE VERTICES
        grafo = new Grafo(n);

        cout << "Quantidade de vertices : " << n << endl;
        cout <<"Arestas: " <<endl;
        while(!feof(arquivo)){
            fscanf(arquivo,"%d %d %f",&aresta1,&aresta2,&peso);
            cout << "\t("<<aresta1<<")=="<<peso<<"==("<<aresta2<<")"<<endl;
            grafo->setAresta(aresta1-1,aresta2-1,peso); //A subtração por -1 é para a proveitar o primeiro indice da lista
            quantidadeArestas++;
        }
        fclose(arquivo);
    }
    cout<< "Digite o vertice a ser analisado: ";
    cin>>verticeLido;
    vertice = verticeLido - 1; //Coreção para encontrar os valores certos

    cout<< "Digite as arestas para analisar: " << endl;
    cout<<"Aresta 1: ";
    cin>>arestaR1Lido;
    cout<<"Aresta 2:";
    cin>>arestaR2Lido;
    arestaR1 = arestaR1Lido - 1;
    arestaR2 = arestaR2Lido - 1;

    //Variaveis usadas no prrenchimento do arquivo
    ordem = n; // a
    tamanho= quantidadeArestas; //b
    int vizinhosVertice[grafo->getGrau(vertice)];//c
    grafo->getVizinhos(vertice,vizinhosVertice);//c
    grau = grafo->getGrau(vertice);//d

    int ordemVisitas[n];//e
    grafo->buscaProfundidade(ordemVisitas);
    ncomponentes = grafo->CompsConexaGrafo();//f


    //Prenche novo arquivo;
    strcpy(nomeArquivoSaida,nomeArquivo);
    strcat(nomeArquivoSaida,"_Saida.txt");

    arquivo = fopen(nomeArquivoSaida,"w");

    fprintf(arquivo,"* Ordem do grafo V(G): %d\n",ordem);

    fprintf(arquivo,"* Tamanho do grafo E(G): %d\n",tamanho);

    fprintf(arquivo,"* Vizinhos do vertice V = %d : {",verticeLido);
    for (int i = 0; i < grafo->getGrau(vertice); ++i) {
        fprintf(arquivo," %d ",vizinhosVertice[i]);
    }
    fprintf(arquivo,"}\n");

    fprintf(arquivo,"* Grau do vertice d(x%d): %d\n",verticeLido,grau);

    fprintf(arquivo,"* Ordem de visitas em BP : \n");
    for (int i = 0; i < n; ++i) {
        fprintf(arquivo,"    Vertice %d  ordem de acesso: %d \n",i+1,ordemVisitas[i]+1);
    }
    fprintf(arquivo,"\n");

    fprintf(arquivo,"* Numero de componentes: %d\n",ncomponentes);

    //grafo->printGrafo();
    if(grafo->verificaSeArestaPonto(ncomponentes,arestaR1,arestaR2)){
        fprintf(arquivo,"* A aresta escolhida eh uma ponte\n");
    }else{
        fprintf(arquivo,"* A aresta escolhida nao eh uma ponte\n");
    }
    //grafo->printGrafo();

    if (grafo->verificaSeVerticeArticulcao(ncomponentes,vertice)){
        fprintf(arquivo,"* O vertice escolhido eh uma articulacao\n");
    }else{
        fprintf(arquivo,"* O vertice escolhido nao eh uma articulacao\n");
    }
    //grafo->printGrafo();

    fclose(arquivo);


    return 0;
}
