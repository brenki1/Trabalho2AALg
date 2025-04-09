#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int alg_troco_rec(int moedas[], int n, int t) {
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

int alg_troco_pd(int moedas[], int n, int troco, int* min_moedas, int* moedas_usadas) {
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

void print_moedas(int* moedas_usadas, int troco) {
    int coin = troco;
    while (coin > 0) {
        int this_coin = moedas_usadas[coin];
        printf("%d\n", this_coin);
        coin -= this_coin;
    }
}

int main() {
    int t = 70;
    int moedas[] = {1, 5, 10, 25, 50, 100};
    int n = sizeof(moedas) / sizeof(moedas[0]);

    int* moedas_usadas = (int*)calloc(t + 1, sizeof(int));
    int* cont_moedas = (int*)calloc(t + 1, sizeof(int));

    printf("Do algoritmo naive que utiliza recursão:\n");
    clock_t inicio1 = clock();
    int resultado = alg_troco_rec(moedas, n, t);
    clock_t fim1 = clock();
    double tempo1 = (double)(fim1 - inicio1) / CLOCKS_PER_SEC;
    printf("O número de moedas para o troco de %d foi: %d, e o tempo de execução foi de %f segundos\n\n", t, resultado, tempo1);

    printf("Do algoritmo que implementa Programação Dinâmica:\n");
    printf("Para o troco de %d foram necessárias", t);
    clock_t inicio2 = clock();
    int resultado_pd = alg_troco_pd(moedas, n, t, cont_moedas, moedas_usadas);
    clock_t fim2 = clock();
    double tempo2 = (double)(fim2 - inicio2) / CLOCKS_PER_SEC;
    printf(" %d moedas\n", resultado_pd);

    printf("São elas:\n");
    print_moedas(moedas_usadas, t);
    printf("Lista de moedas mínimas:\n");
    for (int i = 0; i <= t; i++) {
        printf("%d ", moedas_usadas[i]);
    }
    printf("\nO algoritmo demorou %f segundos para encontrar a solução ótima\n", tempo2);

    free(moedas_usadas);
    free(cont_moedas);

    return 0;
}
