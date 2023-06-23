#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // Para uso da função rand()

using namespace std;

// Função para trocar dois elementos
void trocar(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Implementação do algoritmo Shellsort
void shellsort(vector<int> &arr, int &comparacoes, int &trocas)
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                comparacoes++;
                trocas++;
                arr[j] = arr[j - gap];
            }
            comparacoes++;
            arr[j] = temp;
        }
    }
}

// Função auxiliar para o mergesort
void merge(vector<int> &arr, int l, int m, int r, int &comparacoes, int &trocas)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        comparacoes++;
        if (L[i] <= R[j])
        {
            trocas++;
            arr[k] = L[i];
            i++;
        }
        else
        {
            trocas++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        trocas++;
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        trocas++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Implementação do algoritmo Mergesort
void mergesort(vector<int> &arr, int l, int r, int &comparacoes, int &trocas)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m, comparacoes, trocas);
        mergesort(arr, m + 1, r, comparacoes, trocas);

        merge(arr, l, m, r, comparacoes, trocas);
    }
}

// Função auxiliar para o quicksort
int particionar(vector<int> &arr, int low, int high, int &comparacoes, int &trocas)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        comparacoes++;
        if (arr[j] < pivot)
        {
            i++;
            trocas++;
            trocar(arr[i], arr[j]);
        }
    }
    trocas++;
    trocar(arr[i + 1], arr[high]);
    return (i + 1);
}

// Implementação do algoritmo Quicksort
void quicksort(vector<int> &arr, int low, int high, int &comparacoes, int &trocas)
{
    if (low < high)
    {
        int pi = particionar(arr, low, high, comparacoes, trocas);

        quicksort(arr, low, pi - 1, comparacoes, trocas);
        quicksort(arr, pi + 1, high, comparacoes, trocas);
    }
}

// Função auxiliar para o heapsort
void heapify(vector<int> &arr, int n, int i, int &comparacoes, int &trocas)
{
    int maior = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    comparacoes++;
    if (l < n && arr[l] > arr[maior])
        maior = l;

    comparacoes++;
    if (r < n && arr[r] > arr[maior])
        maior = r;

    if (maior != i)
    {
        trocas++;
        trocar(arr[i], arr[maior]);

        heapify(arr, n, maior, comparacoes, trocas);
    }
}

// Implementação do algoritmo Heapsort
void heapsort(vector<int> &arr, int &comparacoes, int &trocas)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparacoes, trocas);

    for (int i = n - 1; i > 0; i--)
    {
        trocas++;
        trocar(arr[0], arr[i]);

        heapify(arr, i, 0, comparacoes, trocas);
    }
}

// Função para ler os dados de um arquivo de texto
vector<int> lerDadosArquivo(const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo);
    vector<int> dados;
    int valor;

    if (arquivo.is_open())
    {
        while (arquivo >> valor)
        {
            dados.push_back(valor);
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo." << endl;
    }

    return dados;
}

// Função para gerar dados em ordem crescente
vector<int> gerarDadosCrescentes(int quantidade)
{
    vector<int> dados;
    for (int i = 1; i <= quantidade; i++)
    {
        dados.push_back(i);
    }
    return dados;
}

// Função para gerar dados em ordem decrescente
vector<int> gerarDadosDecrescentes(int quantidade)
{
    vector<int> dados;
    for (int i = quantidade; i >= 1; i--)
    {
        dados.push_back(i);
    }
    return dados;
}

// Função para gerar dados em ordem aleatória
vector<int> gerarDadosAleatorios(int quantidade)
{
    vector<int> dados;
    for (int i = 0; i < quantidade; i++)
    {
        dados.push_back(rand() % quantidade + 1);
    }
    return dados;
}

// Função para imprimir os resultados
void imprimirResultados(int quantidade, int comparacoesMax, int trocasMax, int comparacoes, int trocas)
{
    float valorRelativoComp = (static_cast<float>(comparacoes) / comparacoesMax) * 100;
    float valorRelativoTrocas = (static_cast<float>(trocas) / trocasMax) * 100;

    cout << quantidade << " " << valorRelativoComp << " " << valorRelativoTrocas << endl;
}

int main()
{
    srand(time(0)); // Para inicializar a semente do gerador de números aleatórios

    string nomeArquivo;
    cout << "Digite o nome do arquivo de dados: ";
    cin >> nomeArquivo;

    vector<int> dados = lerDadosArquivo(nomeArquivo);

    int quantidadeDados;
    cout << "Digite a quantidade de dados a serem ordenados (de 1 a 10.000): ";
    cin >> quantidadeDados;

    int tipoOrganizacao;
    cout << "Digite o tipo de organizacao inicial dos dados (1 - Crescente, 2 - Decrescente, 3 - Aleatorio): ";
    cin >> tipoOrganizacao;

    vector<int> dadosOrdenacao;
    if (tipoOrganizacao == 1)
    {
        dadosOrdenacao = gerarDadosCrescentes(quantidadeDados);
    }
    else if (tipoOrganizacao == 2)
    {
        dadosOrdenacao = gerarDadosDecrescentes(quantidadeDados);
    }
    else if (tipoOrganizacao == 3)
    {
        dadosOrdenacao = gerarDadosAleatorios(quantidadeDados);
    }
    else
    {
        cout << "Tipo de organizacao invalido." << endl;
        return 0;
    }

    int comparacoesMax = 0;
    int trocasMax = 0;

    // Execução do Shellsort
    vector<int> arrShellsort = dadosOrdenacao;
    int comparacoesShellsort = 0;
    int trocasShellsort = 0;
    shellsort(arrShellsort, comparacoesShellsort, trocasShellsort);
    comparacoesMax = max(comparacoesMax, comparacoesShellsort);
    trocasMax = max(trocasMax, trocasShellsort);

    // Execução do Mergesort
    vector<int> arrMergesort = dadosOrdenacao;
    int comparacoesMergesort = 0;
    int trocasMergesort = 0;
    mergesort(arrMergesort, 0, quantidadeDados - 1, comparacoesMergesort, trocasMergesort);
    comparacoesMax = max(comparacoesMax, comparacoesMergesort);
    trocasMax = max(trocasMax, trocasMergesort);

    // Execução do Quicksort
    vector<int> arrQuicksort = dadosOrdenacao;
    int comparacoesQuicksort = 0;
    int trocasQuicksort = 0;
    quicksort(arrQuicksort, 0, quantidadeDados - 1, comparacoesQuicksort, trocasQuicksort);
    comparacoesMax = max(comparacoesMax, comparacoesQuicksort);
    trocasMax = max(trocasMax, trocasQuicksort);

    // Execução do Heapsort
    vector<int> arrHeapsort = dadosOrdenacao;
    int comparacoesHeapsort = 0;
    int trocasHeapsort = 0;
    heapsort(arrHeapsort, comparacoesHeapsort, trocasHeapsort);
    comparacoesMax = max(comparacoesMax, comparacoesHeapsort);
    trocasMax = max(trocasMax, trocasHeapsort);

    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesShellsort, trocasShellsort);
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesMergesort, trocasMergesort);
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesQuicksort, trocasQuicksort);
    imprimirResultados(quantidadeDados, comparacoesMax, trocasMax, comparacoesHeapsort, trocasHeapsort);

    return 0;
}