#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/forro/ref/forro-debug.h"

int main(int argc, char *argv[])
{
    // criando contexto e saida
    stream_ctx input;
    uint64_t number_of_bytes = 64;
    uint8_t *output_forro = (uint8_t *)malloc(number_of_bytes);
    uint8_t *mensagem = (uint8_t *)malloc(number_of_bytes);
    uint8_t *cifrado = (uint8_t *)malloc(number_of_bytes);

    // capturando chave do primeiro argumento
    uint8_t key[32];
    strncpy(key, argv[1], 32);

    // capturando nonce do segundo argumento
    uint8_t nonce[8];
    strncpy(nonce, argv[2], 8);

    // capturando id_rodada no terceiro argumento
    uint8_t id_rodada[8];
    strncpy(id_rodada, argv[3], 8);

    // capturando id_dispositivo no quarto argumento
    uint8_t id_dispositivo[16];
    strncpy(id_dispositivo, argv[4], 16);

    // capturando configuracao a ser verificada
    uint8_t configuracao[32];
    strncpy(configuracao, argv[5], 32);

    // carregando chave, iv e rodando o algoritmo
    printf("rodando Key Setup\n");
    forro_keysetup(&input, key);
    // printf("rodando IV Setup\n");
    // forro_ivsetup(&input, iv);

    uint8_t configuracao_rodada[16] ;
    uint8_t configuracao_dispositivo[16];

    // id_rodada XOR C0 e C1 (0-3 e 4-7)
    for (int i=0; i < 8; i++) {
        configuracao_rodada[i] = id_rodada[i] ^ configuracao[i];
    }

    // id_dispositivo XOR C2 e C3 (8-11 e 12-15)
    for (int i=0; i < 8; i++) {
        configuracao_dispositivo[i] = id_dispositivo[i] ^ configuracao[i+8];
    }

    // nonce XOR C4 e C5 (16-19 e 20-23)
    for (int i=0; i < 8; i++) {
        configuracao_rodada[i+8] = nonce[i] ^ configuracao[i+16];
    }

    // id_dispositivo XOR C6 e C7 (24-27 e 28-31)
    for (int i=0; i < 8; i++) {
        configuracao_dispositivo[i+8] = id_dispositivo[i+8] ^ configuracao[i+24];
    }

    printf("rodando Verificador Setup\n");
    forro_versetup(&input, configuracao_rodada, configuracao_dispositivo);

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

    // imprimindo configuracao
    printf("Configuracao:\n");
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", configuracao[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    // imprimindo id_dispositivo
    printf("id_dispositivo:\n");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", id_dispositivo[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    // imprimindo id_rodada
    printf("id_rodada:\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%02x", id_rodada[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    // imprimindo configuracao_dispositivo e configuracao_rodada
    printf("\nconfiguracao_dispositivo:\n");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", configuracao_dispositivo[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("configuracao_rodada:\n");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", configuracao_rodada[i]);
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
        printf("%02x", nonce[i]);
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
