#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/forro/ref/forro-debug.h"

int main(int argc, char *argv[])
{
    // criando contexto e saida
    stream_ctx input;
    uint64_t number_of_bytes = 32;
    uint8_t *output_forro = (uint8_t *)malloc(number_of_bytes);
    uint8_t *mensagem = (uint8_t *)malloc(number_of_bytes);
    uint8_t *cifrado = (uint8_t *)malloc(number_of_bytes);

    // capturando chave do primeiro argumento
    uint8_t key[32];
    strncpy(key, argv[1], 32);

    // capturando nonce do segundo argumento
    uint8_t iv[8];
    strncpy(iv, argv[2], 8);

    // capturando mensagem a ser cifrada
    strncpy(mensagem, argv[3], number_of_bytes);

    // carregando chave, iv e rodando o algoritmo
    printf("rodando Key Setup\n");
    forro_keysetup(&input, key);
    printf("rodando IV Setup\n");
    forro_ivsetup(&input, iv);

    // Rodando a cifra da mensagem informada
    printf("Cifra da Mensagem\n");
    forro_encrypt_bytes(&input, mensagem, cifrado, number_of_bytes);

    // Cifra uma sequência de zeros como mensagem
    // printf("Rodando a cifra com zeros\n");
    // forro_keystream_bytes(&input, output_forro, number_of_bytes);

    // imprimindo mensagem
    printf("Mensagem:\n");
    for (int i = 0; i < number_of_bytes; i++)
    {
        printf("%02x", mensagem[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    // imprimindo detalhes da chave e do Nonce
    printf("KEY:\n");
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", key[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\nNONCE:\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%02x", iv[i]);
        if (i % 8 == 7)
            printf("\n");
    }

    // dividir o resultado sempre em 8 linhas de x/8 bytes
    int div_bloco = number_of_bytes/8;

    // imprimindo resultado em bloco e depois em texto corrido
    printf("\nResultado do estado:\n");
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < div_bloco; k++) {
            printf("%02x", output_forro[div_bloco * i + k]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < div_bloco; k++) {
            printf("%02x", output_forro[div_bloco * i + k]);
        }
    }
    printf("\n");

    printf("\nCifrado:\n");
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < div_bloco; k++) {
            printf("%02x", cifrado[div_bloco * i + k]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < div_bloco; k++) {
            printf("%02x", cifrado[div_bloco * i + k]);
        }
    }
    printf("\n");

    return 0;
}
