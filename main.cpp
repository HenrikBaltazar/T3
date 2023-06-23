#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// Função auxiliar para trocar dois elementos de um vetor
void trocar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Implementação do algoritmo Shellsort
void shellsort(vector<int>& arr, int& comparacoes, int& trocas) {
    int n = arr.size();
    int intervalo = 1;

    while (intervalo < n / 3) {
        intervalo = 3 * intervalo + 1;
    }

    while (intervalo >= 1) {
        for (int i = intervalo; i < n; i++) {
            for (int j = i; j >= intervalo && arr[j] < arr[j - intervalo]; j -= intervalo) {
                comparacoes++;
                trocas++;
                trocar(arr[j], arr[j - intervalo]);
            }
        }
        intervalo /= 3;
    }
}

// Implementação do algoritmo Mergesort
void merge(vector<int>& arr, int left, int mid, int right, int& comparacoes, int& trocas) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            trocas++;
            arr[k] = L[i];
            i++;
        }
        else {
            trocas++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        trocas++;
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        trocas++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(vector<int>& arr, int left, int right, int& comparacoes, int& trocas) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid, comparacoes, trocas);
        mergesort(arr, mid + 1, right, comparacoes, trocas);
        merge(arr, left, mid, right, comparacoes, trocas);
    }
}

// Implementação do algoritmo Quicksort
int particionar(vector<int>& arr, int low, int high, int& comparacoes, int& trocas) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparacoes++;
        if (arr[j] <= pivot) {
            i++;
            trocas++;
            trocar(arr[i], arr[j]);
        }
    }

    trocas++;
    trocar(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(vector<int>& arr, int low, int high, int& comparacoes, int& trocas) {
    if (low < high) {
        int pi = particionar(arr, low, high, comparacoes, trocas);
        quicksort(arr, low, pi - 1, comparacoes, trocas);
        quicksort(arr, pi + 1, high, comparacoes, trocas);
    }
}

// Implementação do algoritmo Heapsort
void heapify(vector<int>& arr, int n, int i, int& comparacoes, int& trocas) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    comparacoes++;
    if (esquerda < n && arr[esquerda] > arr[maior]) {
        maior = esquerda;
    }

    comparacoes++;
    if (direita < n && arr[direita] > arr[maior]) {
        maior = direita;
    }

    if (maior != i) {
        trocas++;
        trocar(arr[i], arr[maior]);
        heapify(arr, n, maior, comparacoes, trocas);
    }
}

void heapsort(vector<int>& arr, int& comparacoes, int& trocas) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparacoes, trocas);
    }

    for (int i = n - 1; i >= 0; i--) {
        trocas++;
        trocar(arr[0], arr[i]);
        heapify(arr, i, 0, comparacoes, trocas);
    }
}

// Função para ler os dados de um arquivo
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

// Função para gerar dados em ordem crescente
vector<int> gerarDadosCrescentes(int quantidade) {
    vector<int> dados(quantidade);
    for (int i = 0; i < quantidade; i++) {
        dados[i] = i + 1;
    }
    return dados;
}

// Função para gerar dados em ordem decrescente
vector<int> gerarDadosDecrescentes(int quantidade) {
    vector<int> dados(quantidade);
    for (int i = quantidade - 1; i >= 0; i--) {
        dados[i] = quantidade - i;
    }
    return dados;
}

// Função para gerar dados aleatórios
vector<int> gerarDadosAleatorios(int quantidade) {
    vector<int> dados(quantidade);
    for (int i = 0; i < quantidade; i++) {
        dados[i] = rand() % quantidade + 1;
    }
    return dados;
}

// Função para imprimir os resultados
void imprimirResultados(int quantidade, int comparacoesMax, int trocasMax, int comparacoes, int trocas) {
    cout << "Quantidade de dados: " << quantidade << endl;
    cout << "Comparacoes (valor absoluto): " << comparacoes << endl;
    cout << "Comparacoes (valor relativo): " << (static_cast<double>(comparacoes) / comparacoesMax) * 100 << "%" << endl;
    cout << "Trocas (valor absoluto): " << trocas << endl;
    cout << "Trocas (valor relativo): " << (static_cast<double>(trocas) / trocasMax) * 100 << "%" << endl;
    cout << endl;
}

int main() {
    srand(time(0));

    // Leitura do nome do arquivo
    string nomeArquivo;
    cout << "Digite o nome do arquivo de dados: ";
    cin >> nomeArquivo;

    // Leitura da quantidade de dados a serem ordenados
    int quantidadeDados;
    cout << "Digite a quantidade de dados a serem ordenados (1 a 10000): ";
    cin >> quantidadeDados;

    // Leitura do tipo de organização inicial dos dados
    int tipoOrganizacao;
    cout << "Digite o tipo de organizacao inicial dos dados:" << endl;
    cout << "1 - Ordem crescente" << endl;
    cout << "2 - Ordem decrescente" << endl;
    cout << "3 - Ordem aleatoria" << endl;
    cout << "Escolha uma opcao: ";
    cin >> tipoOrganizacao;

    // Leitura dos dados do arquivo
    vector<int> dados;
    if (tipoOrganizacao == 1) {
        dados = gerarDadosCrescentes(quantidadeDados);
    }
    else if (tipoOrganizacao == 2) {
        dados = gerarDadosDecrescentes(quantidadeDados);
    }
    else if (tipoOrganizacao == 3) {
        dados = gerarDadosAleatorios(quantidadeDados);
    }
    else {
        cout << "Opcao invalida." << endl;
        return 0;
    }

    // Vetores auxiliares para manter os dados iniciais
    vector<int> dadosShellsort = dados;
    vector<int> dadosMergesort = dados;
    vector<int> dadosQuicksort = dados;
    vector<int> dadosHeapsort = dados;

    // Variáveis para armazenar as estatísticas
    int comparacoesMax = 0;
    int trocasMax = 0;
    int comparacoesShellsort = 0;
    int trocasShellsort = 0;
    int comparacoesMergesort = 0;
    int trocasMergesort = 0;
    int comparacoesQuicksort = 0;
    int trocasQuicksort = 0;
    int comparacoesHeapsort = 0;
    int trocasHeapsort = 0;

    // Execução dos algoritmos de ordenação
    shellsort(dadosShellsort, comparacoesShellsort, trocasShellsort);
    mergesort(dadosMergesort, 0, quantidadeDados - 1, comparacoesMergesort, trocasMergesort);
    quicksort(dadosQuicksort, 0, quantidadeDados - 1, comparacoesQuicksort, trocasQuicksort);
    heapsort(dadosHeapsort, comparacoesHeapsort, trocasHeapsort);

    // Cálculo das estatísticas máximas
    comparacoesMax = max(comparacoesShellsort, max(comparacoesMergesort, max(comparacoesQuicksort, comparacoesHeapsort)));
    trocasMax = max(trocasShellsort, max(trocasMergesort, max(trocasQuicksort, trocasHeapsort)));

    // Impressão dos resultados
    cout << endl << "----------SHELL SORT-----------"<<endl;
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesShellsort, trocasShellsort);
    cout << endl << "----------MERGE SORT-----------"<<endl;
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesMergesort, trocasMergesort);
    cout << endl << "----------QUICK SORT-----------"<<endl;
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesQuicksort, trocasQuicksort);
    cout << endl << "----------HEAP SORT-----------"<<endl;
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesHeapsort, trocasHeapsort);

    return 0;
}
