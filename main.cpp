#include <iostream>
#include <fstream>
#include <vector>
#include "sorts.h"

using namespace std;


vector<int> lerDadosArquivo(const string& nomeArquivo) {
    vector<int> dados;
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        int numero;
        while (arquivo >> numero) {
            dados.push_back(numero);
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

int main() {
    string nomeArquivo="";
    int quantidadeDados=0;
    do{
    cout << "Digite o nome do arquivo de dados: ";
    cin >> nomeArquivo;

    cout << "Digite a quantidade de dados a serem ordenados (1 a 10000): ";
    cin >> quantidadeDados;


    if(nomeArquivo == "")
        cout << endl << "[ERRO] Nome do arquivo nao pode ser nulo" << endl;
    if(quantidadeDados < 1)
        cout << endl << "[ERRO] Quantidade de dados nao pode ser menor do que 1" << endl;
    else if (quantidadeDados > 10000)
        cout << endl << "[ERRO] Quantidade de dados nao pode ser maior que 10000" << endl;

    }while (nomeArquivo == "" || quantidadeDados == 0);

    cout<<endl;
    
    vector<int> dados = lerDadosArquivo(nomeArquivo);
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

    return 0;
}
