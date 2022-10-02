#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define z 1.96

int _comparar_float(const void *a, const void *b)
{
    float *x = (float *)a;
    float *y = (float *)b;

    if (*x < *y)
    {
        return -1;
    }
    else if (*x == *y)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

float calcular_mediana(size_t qt_numeros, float numeros[])
{
    float numeros_copia[qt_numeros];

    for (size_t i = 0; i < qt_numeros; i++)
    {
        numeros_copia[i] = numeros[i];
    }

    qsort(numeros_copia, qt_numeros, sizeof(float), _comparar_float);

    if (qt_numeros % 2 == 1)
    {
        return numeros_copia[qt_numeros / 2];
    }
    else
    {
        return (numeros_copia[qt_numeros / 2 - 1] + numeros_copia[qt_numeros / 2]) / 2;
    }
}

int main()
{
    float *vet = NULL;
    float soma = 0, media, var = 0, var_amostra = 0, var_pop, dp, dp_amostra, dp_pop, e, LI, LS, t, ez, mediana, max, min;
    int N, i, j, gl;
    printf("Programa que calcula a media, variancia e desvio padrao\n\n");
    printf("Quantos valores? ");
    scanf("%i", &N);
    vet = (float *)malloc(N * sizeof(float));
    if (vet == NULL)
    {
        printf("\n!!!ERRO!!! Fracasso na alocacao do vetor.\n");
        system("Pause");
        exit(1);
    }
    for (i = 0; i < N; i++)
    {
        printf("valor[%i]: ", i);
        scanf("%f", &vet[i]);
        soma = (soma + vet[i]);
    }

    min = vet[0];
    for (i = 1; i < N; i++)
    {
        if (vet[i] < min)
        {
            min = vet[i];
        }
    }

    max = vet[0];
    for (i = 1; i < N; i++)
    {
        if (vet[i] > max)
        {
            max = vet[i];
        }
    }

    media = (soma) / N;
    for (i = 0; i < N; i++)
    {
        var = (var + (pow(vet[i] - media, 2)) / N);
        var_amostra = (var_amostra + (pow(vet[i] - media, 2)) / (N - 1));
        var_pop = (var_pop + (pow(vet[i] - media, 2)) / (N));
    }

    mediana = calcular_mediana(N, vet);

    dp = sqrt(var);
    dp_amostra = sqrt(var_amostra);
    dp_pop = sqrt(var_pop);
    if (N > 30)
    {
        // Distribuição Normal com nível de confiança de 95%, logo z = 1,96/
        e = ((z) * (dp_amostra)) / (sqrt(N));
        LI = media - e;
        LS = media + e;
    }
    else
    {
        //*Distribuição "t de Student" com nível de confiança de 95%  logo p = 5%/
        // analisando na tabela na coluna de 5% e verificando seu grau de liberdade*/
        gl = N-1;
        if(gl == 1) t = 12.706;
        else if(gl == 2) t = 4.0303;
        else if(gl == 3) t = 3.182;
        else if(gl == 4) t = 2.776;
        else if(gl == 5) t = 2.571;
        else if(gl == 6) t = 2.447;
        else if(gl == 7) t = 2.365;
        else if(gl == 8) t = 2.306;
        else if(gl == 9) t = 2.262;
        else if(gl == 10) t = 2.228;
        else if(gl == 11) t = 2.201;
        else if(gl == 12) t = 2.179;
        else if(gl == 13) t = 2.160;
        else if(gl == 14) t = 2.145;
        else if(gl == 15) t = 2.131;
        else if(gl == 16) t = 2.120;
        else if(gl == 17) t = 2.110;
        else if(gl == 18) t = 2.101;
        else if(gl == 19) t = 2.093;
        else if(gl == 20) t = 2.086;
        else if(gl == 21) t = 2.080;
        else if(gl == 22) t = 2.074;
        else if(gl == 23) t = 2.069;
        else if(gl == 24) t = 2.064;
        else if(gl == 25) t = 2.060;
        else if(gl == 26) t = 2.056;
        else if(gl == 27) t = 2.057;
        else if(gl == 28) t = 2.048;
        else if(gl == 29) t = 2.045;
        else if(gl == 30) t = 2.042;
        else if(gl == 35) t = 2.030;
        else if(gl == 40) t = 2.021;
        else if(gl == 50) t = 2.009;
        else if(gl == 60) t = 2.000;
        else if(gl == 120) t = 1.980;
        ez = ((t) * (dp_amostra)) / (sqrt(N));
        LI = media - ez;
        LS = media + ez;
    }
    printf("\n\nResultados obtidos\n");
    printf("Soma dos valores: %.2f\n", soma);
    printf("Valor Minimo: %.2f\n", min);
    printf("Valor Maximo: %.2f\n", max);
    printf("Valor da Mediana: %.2f\n", mediana);
    printf("Valor da Media: %.2f\n", media);
    printf("Valor da Variancia: %.2f\n", var);
    printf("Valor do Desvio Padrao: %.2f\n", dp);
    printf("Valor da Variancia da Amostral: %.2f\n", var_amostra);
    printf("Valor da Variancia da Populacional: %.4f\n", var_pop);
    printf("Valor do Desvio Padrao da Amostral: %.4f\n", dp_amostra);
    printf("Valor do Desvio Padrao da Populacional: %.4f\n", dp_pop);
    printf("\n\nIntervalo de Confianca -> 95%% => ]%.4f ; %.4f[\n\n", LI, LS);
    printf("\n******\n");
    free(vet); // Libera o vetor alocado anteriormente/
    vet = NULL;
}
