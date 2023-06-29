#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include "sorts.h"

using namespace std;


vector<int> lerDadosArquivo(const string& nomeArquivo, int qunt) {
    vector<int> dados;
    ifstream arquivo(nomeArquivo);
    int aux = 0;
    if (arquivo.is_open()) {
        int numero;
        while (arquivo >> numero and aux < qunt) {
            dados.push_back(numero);
            aux++;
        }
        arquivo.close();
    }
    else {
        cout << "Nao foi possivel abrir o arquivo." << endl;
    }

    return dados;
}

float relativo(int i, int max){

     return ((float) i/ (float) max)*100;

}

int maior(int a, int b, int c, int d){
    int maior = a;

    if (b > maior) {
        maior = b;
    }

    if (c > maior) {
        maior = c;
    }

    if (d > maior) {
        maior = d;
    }

    return maior;

}

void teste(vector<int> dados, int qtd){
    int teste = 1;
    bool ok = true;
    for(int i = 0; i < dados.size(); i++){
        if (dados[i] == teste)
            teste++;
        else
            ok = false;
    }
    if(!ok)
        cout << " NOK!"<<endl;
    else
        cout << " OK!"<<endl;
}

void criaArquivo(string nome){
    ofstream arquivo(nome);
    if(!arquivo.is_open()){
        cout << "erro ao criar os arquivos" <<endl;
        return;
    }
    cout << "arquivo " << nome << " criado com sucesso" << endl;
    arquivo.close();
}

bool existeArquivo(const string& nome){
    ifstream arquivo(nome);
    return arquivo.good();
}

void escreveLinhaArquivo(const string nomeArquivo, const string linha){
    ofstream arquivo(nomeArquivo, std::ios::app); // Abre o arquivo no modo de escrita (append)

    if (arquivo.is_open()) {
        arquivo << linha << endl; // Escreve a linha no arquivo
        cout << nomeArquivo << " recebe linha " << linha <<endl;
        arquivo.close(); // Fecha o arquivo
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

void saida(int tipo, int qtd, float shell_trocas, float merge_trocas, float quick_trocas, float heap_trocas,float shell_compare, float merge_compare, float quick_compare, float heap_compare){
    string arquivo="", linha = to_string(qtd) + "," + to_string(shell_trocas) + ","+ to_string(merge_trocas) + "," + to_string(quick_trocas) + "," + to_string(heap_trocas) + "," + to_string(shell_compare) + "," + to_string(merge_compare) + "," + to_string(quick_compare) + "," + to_string(heap_compare); 

    if (tipo == 1){
        arquivo="crescente.csv";
    }else if(tipo == 2){
        arquivo = "decrescente.csv";
    }else if(tipo == 3){
        arquivo = "aleatorio.csv";
    }

    if(!existeArquivo(arquivo)){
        criaArquivo(arquivo);
        escreveLinhaArquivo(arquivo, "qtdDados,shell_trocas,merge_trocas,quick_trocas,heap_trocas,shell_compare,merge_compare,quick_compare,heap_compare"); //cabecalho
    }

    escreveLinhaArquivo(arquivo,linha);

}

int main() {
    string nomeArquivo="";
    int quantidadeDados=0, tipoOrganizacao=0;
    do{
    cout << "Digite o nome do arquivo de dados: ";
    cin >> nomeArquivo;

    cout << "Digite a quantidade de dados a serem ordenados (1 a 10000): ";
    cin >> quantidadeDados;

    cout << "Selecione a organizacao" << endl;
    cout << "1 - Crescente" << endl;
    cout << "2 - Decrescente" << endl;
    cout << "3 - Aleatorio" << endl;
    cin >> tipoOrganizacao;

    if(nomeArquivo == "")
        cout << endl << "[ERRO] Nome do arquivo nao pode ser nulo" << endl;
    if(quantidadeDados < 1)
        cout << endl << "[ERRO] Quantidade de dados nao pode ser menor do que 1" << endl;
    else if (quantidadeDados > 10000)
        cout << endl << "[ERRO] Quantidade de dados nao pode ser maior que 10000" << endl;
    if(tipoOrganizacao<1 || tipoOrganizacao>3 )
        cout << endl << "[ERRO] Tipo de Organizacao de dados deve estar entre 1 e 3" << endl;

    }while (nomeArquivo == "" || quantidadeDados <1 || quantidadeDados > 10000 || tipoOrganizacao <1 || tipoOrganizacao > 3);

    cout<<endl;
    
    vector<int> dados = lerDadosArquivo(nomeArquivo,quantidadeDados);
    if(tipoOrganizacao==2){
        reverse(dados.begin(),dados.end());
    }
    if(tipoOrganizacao==3){
        random_shuffle(dados.begin(),dados.end());
    }
    vector<int> shell_dados = dados, quick_dados = dados, merge_dados = dados, heap_dados = dados;
    
    int quick_trocas=0,quick_comparacoes=0,merge_trocas=0,merge_comparacoes=0,shell_trocas=0,shell_comparacoes=0,heap_trocas=0,heap_comparacoes=0;
    cout << "QUICK SORT: ";
    quicksort(quick_dados,0,quantidadeDados,quick_trocas,quick_comparacoes);
    teste(quick_dados,quantidadeDados);
    
    cout << "MERGE SORT: ";
    mergesort(merge_dados,0,quantidadeDados-1,merge_trocas,merge_comparacoes);
    teste(merge_dados,quantidadeDados);

    cout << "SHELL SORT: ";
    shellsort(shell_dados,shell_trocas,shell_comparacoes);
    teste(shell_dados,quantidadeDados);

    cout << "HEAP SORT: ";
    heapsort(heap_dados,quantidadeDados, heap_trocas, heap_comparacoes);
    teste(heap_dados,quantidadeDados);

    cout << "------ RESULTADO BRUTO -------" << endl;
    cout<<"SHELL SORT:"<<endl<<"trocas: "<<shell_trocas<<endl<<"comparacoes: "<<shell_comparacoes<<endl;
    cout<<"MERGE SORT:"<<endl<<"trocas: "<<merge_trocas<<endl<<"comparacoes: "<<merge_comparacoes<<endl;
    cout<<"QUICK SORT:"<<endl<<"trocas: "<<quick_trocas<<endl<<"comparacoes: "<<quick_comparacoes<<endl;
    cout<<"HEAP SORT:"<<endl<<"trocas: "<<heap_trocas<<endl<<"comparacoes: "<<heap_comparacoes<<endl;

    cout<<endl<<"------ MAIOR RESULTADO -------"<<endl;
    int maiorComparacao = maior(shell_comparacoes,merge_comparacoes,quick_comparacoes,heap_comparacoes);
    int maiorTrocas = maior(shell_trocas,merge_trocas,quick_trocas,heap_trocas);

    if(maiorComparacao == shell_comparacoes)
        cout << "O metodo SHELL SORT ("<<maiorComparacao<<") teve a maior quantidade de comparacoes!"<<endl;
    else if (maiorComparacao == merge_comparacoes)
        cout << "O metodo MERGE SORT ("<<maiorComparacao<<") teve a maior quantidade de comparacoes!"<<endl;
    else if (maiorComparacao == quick_comparacoes)
        cout << "O metodo QUICK SORT ("<<maiorComparacao<<") teve a maior quantidade de comparacoes!"<<endl;
    else
        cout << "O metodo HEAP SORT ("<<maiorComparacao<<") teve a maior quantidade de comparacoes!"<<endl;

    if(maiorTrocas == shell_trocas)
        cout << "O metodo SHELL SORT ("<<maiorTrocas<<") teve a maior quantidade de trocas!"<<endl;
    else if (maiorTrocas == merge_trocas)
        cout << "O metodo MERGE SORT ("<<maiorTrocas<<") teve a maior quantidade de trocas!"<<endl;
    else if (maiorTrocas == quick_trocas)
        cout << "O metodo QUICK SORT ("<<maiorTrocas<<") teve a maior quantidade de trocas!"<<endl;
    else
        cout << "O metodo HEAP SORT ("<<maiorTrocas<<") teve a maior quantidade de trocas!"<<endl;

    cout<<endl<<"------ RESULTADO RELATIVO -------"<<endl;
    cout<<"SHELL SORT:"<<endl<<"trocas: "<<relativo(shell_trocas, maiorTrocas)<<endl<<"comparacoes: "<<relativo(shell_comparacoes, maiorComparacao)<<endl;
    cout<<"MERGE SORT:"<<endl<<"trocas: "<<relativo(merge_trocas,maiorTrocas)<<endl<<"comparacoes: "<<relativo(merge_comparacoes,maiorComparacao)<<endl;
    cout<<"QUICK SORT:"<<endl<<"trocas: "<<relativo(quick_trocas,maiorTrocas)<<endl<<"comparacoes: "<<relativo(quick_comparacoes,maiorComparacao)<<endl;
    cout<<"HEAP SORT:"<<endl<<"trocas: "<<relativo(heap_trocas,maiorTrocas)<<endl<<"comparacoes: "<<relativo(heap_comparacoes,maiorComparacao)<<endl;

    saida(tipoOrganizacao,quantidadeDados,relativo(shell_trocas, maiorTrocas),relativo(merge_trocas,maiorTrocas),relativo(quick_trocas,maiorTrocas),relativo(heap_trocas,maiorTrocas),relativo(shell_comparacoes, maiorComparacao),relativo(merge_comparacoes,maiorComparacao),relativo(quick_comparacoes,maiorComparacao),relativo(heap_comparacoes,maiorComparacao));

    return 0;
}
