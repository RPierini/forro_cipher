#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/forro/ref/forro-debug.h"

int main(int argc, char *argv[])
{
    // criando contexto e saida
    stream_ctx input;
    uint64_t number_of_bytes = 128;
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
    strncpy(mensagem, argv[3], 128);

    // carregando chave, iv e rodando o algoritmo
    forro_keysetup(&input, key);
    forro_ivsetup(&input, iv);

    printf("Cifra da Mensagem\n");
    // Rodando a cifra da mensagem informada
    forro_encrypt_bytes(&input, mensagem, cifrado, number_of_bytes);

    printf("Rodando a cifra com zeros\n");
    // Cifra uma sequência de zeros como mensagem
    forro_keystream_bytes(&input, output_forro, number_of_bytes);

    // imprimindo mensagem
    printf("Mensagem:\n");
    for (int i = 0; i < 128; i++)
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

    // imprimindo resultado em bloco e depois em texto corrido
    printf("\nResultado:\n");
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 16; k++) {
            printf("%02x", output_forro[16 * i + k]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 16; k++) {
            printf("%02x", output_forro[16 * i + k]);
        }
    }
    printf("\n");

    printf("\nCifrado:\n");
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 16; k++) {
            printf("%02x", cifrado[16 * i + k]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 16; k++) {
            printf("%02x", cifrado[16 * i + k]);
        }
    }
    printf("\n");

    return 0;
}
