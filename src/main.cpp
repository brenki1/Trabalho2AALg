#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int alg_troco_rec(const vector<int>& moedas, int n, int t) {
    if (t == 0) return 0;
    int min_moedas = t;

    for (int i = 0; i < n; i++) {
        if (moedas[i] <= t) {
            int num_moedas = 1 + alg_troco_rec(moedas, n, t - moedas[i]);
            if (num_moedas < min_moedas) {
                min_moedas = num_moedas;
            }
        }
    }

    return min_moedas;
}

int alg_troco_pd(const vector<int>& moedas, int n, int troco, vector<int>& min_moedas, vector<int>& moedas_usadas) {
    for (int centavos = 0; centavos <= troco; centavos++) {
        int cont_moeda = centavos;
        int nova_moeda = 1;

        for (int i = 0; i < n; i++) {
            if (moedas[i] <= centavos) {
                int temp = min_moedas[centavos - moedas[i]] + 1;
                if (temp < cont_moeda) {
                    cont_moeda = temp;
                    nova_moeda = moedas[i];
                }
            }
        }

        min_moedas[centavos] = cont_moeda;
        moedas_usadas[centavos] = nova_moeda;
    }

    return min_moedas[troco];
}

void print_moedas(const vector<int>& moedas_usadas, int troco) {
    int coin = troco;
    while (coin > 0) {
        int this_coin = moedas_usadas[coin];
        cout << this_coin << endl;
        coin -= this_coin;
    }
}

int main() {
    int t = 70;
    vector<int> moedas = {1, 5, 10, 25, 50, 100};
    int n = moedas.size();

    vector<int> moedas_usadas(t + 1, 0);
    vector<int> cont_moedas(t + 1, 0);

    cout << "Do algoritmo naive que utiliza recursão:\n";
    clock_t inicio1 = clock();
    int resultado = alg_troco_rec(moedas, n, t);
    clock_t fim1 = clock();
    double tempo1 = (double)(fim1 - inicio1) / CLOCKS_PER_SEC;
    cout << "O número de moedas para o troco de " << t << " foi: " << resultado << ", e o tempo de execução foi de " << tempo1 << " segundos\n\n";

    cout << "Do algoritmo que implementa Programação Dinâmica:\n";
    cout << "Para o troco de " << t << " foram necessárias ";
    clock_t inicio2 = clock();
    int resultado_pd = alg_troco_pd(moedas, n, t, cont_moedas, moedas_usadas);
    clock_t fim2 = clock();
    double tempo2 = (double)(fim2 - inicio2) / CLOCKS_PER_SEC;
    cout << resultado_pd << " moedas\n";

    cout << "São elas:\n";
    print_moedas(moedas_usadas, t);
    cout << "Lista de moedas mínimas:\n";
    for (int i = 0; i <= t; i++) {
        cout << moedas_usadas[i] << " ";
    }
    cout << "\nO algoritmo demorou " << tempo2 << " segundos para encontrar a solução ótima\n";

    return 0;
}
