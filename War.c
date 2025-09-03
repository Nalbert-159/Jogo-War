#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar informações de um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para sortear uma missão aleatória e atribuir ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes; // Sorteio do índice da missão
    strcpy(destino, missoes[indice]);   // Copia a missão para o destino
}

// Função para verificar se a missão foi cumprida (lógica simples de exemplo)
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    // Exemplo de lógica: Se a missão contém a palavra "Conquistar"
    // e houver pelo menos um território com mais de 10 tropas, considera-se cumprida
    if (strstr(missao, "Conquistar") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10) {
                return 1; // Missão cumprida
            }
        }
    }

    // Exemplo: Se a missão contém "Eliminar todas as tropas da cor vermelha"
    // e não houver territórios vermelhos com tropas, missão cumprida
    if (strstr(missao, "vermelha") != NULL) {
        int tropasVermelhas = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                tropasVermelhas++;
            }
        }
        if (tropasVermelhas == 0) {
            return 1; // Missão cumprida
        }
    }

    return 0; // Missão não cumprida
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Vetor de descrições de missões
    char *missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Conquistar todos os territórios azuis",
        "Controlar 5 territórios ao mesmo tempo",
        "Reduzir as tropas inimigas a menos de 20"
    };
    int totalMissoes = 5;

    // Criação de um mapa simples com territórios
    Territorio mapa[3] = {
        {"Território Norte", "azul", 12},
        {"Território Sul", "vermelha", 5},
        {"Território Leste", "verde", 8}
    };

    // Atribuição dinâmica da missão ao jogador
    char *missaoJogador = (char *)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("Missão atribuída ao jogador: %s\n", missaoJogador);

    // Verificação ao final do turno
    if (verificarMissao(missaoJogador, mapa, 3)) {
        printf("Parabéns! Você cumpriu sua missão e venceu!\n");
    } else {
        printf("Missão ainda não cumprida. Continue jogando!\n");
    }

    free(missaoJogador); // Liberação da memória alocada
    return 0;
}
