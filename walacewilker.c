#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MAX_TENTATIVAS_FORCA 6
#define TAMANHO_PALAVRA_FORCA 20

void imprimirForca(int tentativasRestantes);

int verificarLetra(char letra, char palavra[], char palavraEscondida[]);

void jogarForca();

void jogarAdivinhacao();

int obterEscolha();

void determinarVencedor(int escolhaUsuario, int escolhaComputador);

void jogarPedraPapelTesoura();

int main() {
    int escolha;

    do {
        printf("\nEscolha o jogo:\n1. Adivinhação\n2. Forca\n3. Pedra, Papel e Tesoura\n4. Dungeons And Dragons\n0. Sair\nDigite o número correspondente ao jogo desejado: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                jogarAdivinhacao();
                break;
            case 2:
                jogarForca();
                break;
            case 3:
                jogarPedraPapelTesoura();
                break;
            case 4:
                printf("Não implementado ainda, mas esse trabalho top vale 3 pontos em (｡◕‿‿◕｡)\n");
                break;
            case 0:
                printf("Saindo do programa. Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
void imprimirForca(int tentativasRestantes) {
    printf("\n  +---+\n  |   |\n");
    if (tentativasRestantes < MAX_TENTATIVAS_FORCA) {
        printf("  |   O\n");
        if (tentativasRestantes < MAX_TENTATIVAS_FORCA - 1) {
            printf("  |   |\n");
            if (tentativasRestantes < MAX_TENTATIVAS_FORCA - 2) {
                printf("  |   /|");
            } else if (tentativasRestantes < MAX_TENTATIVAS_FORCA - 3) {
                printf("  |   /|\\ ");
            } else {
                printf("  |  /|\\");
            }
        } else {
            printf("  |  / \\\n");
        }
    } else {
        printf("  \n");
    }
    printf("  |\n======\n\n");
}
int verificarLetra(char letra, char palavra[], char palavraEscondida[]) {
    int i, encontrou = 0;
    for (i = 0; i < strlen(palavra); i++) {
        if (tolower(letra) == tolower(palavra[i])) {
            palavraEscondida[i] = palavra[i];
            encontrou = 1;
        }
    }
    return encontrou;
}
void jogarForca() {
    char palavra[TAMANHO_PALAVRA_FORCA];
    char palavraEscondida[TAMANHO_PALAVRA_FORCA];
    char letra;
    int tentativasRestantes = MAX_TENTATIVAS_FORCA;
    int palavraRevelada = 0;
    printf("Digite a palavra para o jogo da forca (sem espaços, com no máximo %d caracteres): ", TAMANHO_PALAVRA_FORCA - 1);
    scanf("%s", palavra);
    while (getchar() != '\n');
    memset(palavraEscondida, '-', strlen(palavra));
    palavraEscondida[strlen(palavra)] = '\0';
    while (tentativasRestantes > 0 && !palavraRevelada) {
        printf("\nPalavra: %s\n", palavraEscondida);
        printf("Tentativas restantes: %d\n", tentativasRestantes);
        printf("Digite uma letra: ");
        scanf(" %c", &letra);
        while (getchar() != '\n');
        if (strchr(palavraEscondida, tolower(letra)) != NULL) {
            printf("Você já tentou esta letra. Tente outra.\n");
            continue;
        }

        if (verificarLetra(letra, palavra, palavraEscondida)) {
            printf("Letra correta!\n");

            if (strcmp(palavra, palavraEscondida) == 0) {
                palavraRevelada = 1;
            }
        } else {
            printf("Letra incorreta.\n");
            tentativasRestantes--;
        }

        imprimirForca(tentativasRestantes);
    }

    if (palavraRevelada) {
        printf("\nParabéns! Você adivinhou a palavra \"%s\"!\n", palavra);
    } else {
        printf("\nVocê perdeu! A palavra era \"%s\".\n", palavra);
    }
}

void jogarAdivinhacao() {
    int numeroAleatorio, tentativa, tentativasRestantes = 5;

    srand(time(NULL));

    numeroAleatorio = rand() % 100 + 1;

    printf("Bem-vindo ao jogo de adivinhação!\n");
    printf("Tente adivinhar o número secreto entre 1 e 100.\n");

    do {
        printf("Você tem %d tentativas restantes.\n", tentativasRestantes);
        printf("Digite seu palpite: ");
        scanf("%d", &tentativa);

        if (tentativa > numeroAleatorio) {
            printf("Tente um número menor.\n");
        } else if (tentativa < numeroAleatorio) {
            printf("Tente um número maior.\n");
        } else {
            printf("Parabéns! Você adivinhou o número secreto %d!\n", numeroAleatorio);
            break;
        }

        tentativasRestantes--;
    } while (tentativasRestantes > 0);

    if (tentativasRestantes == 0) {
        printf("Suas tentativas acabaram. O número secreto era %d.\n", numeroAleatorio);
    }
}

int obterEscolha() {
    int escolha;
    printf("\nEscolha:\n1. Pedra\n2. Papel\n3. Tesoura\nDigite o número correspondente a sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

void determinarVencedor(int escolhaUsuario, int escolhaComputador) {
    if (escolhaUsuario == escolhaComputador) {
        printf("Empate!\n");
    } else if ((escolhaUsuario == 1 && escolhaComputador == 3) ||
               (escolhaUsuario == 2 && escolhaComputador == 1) ||
               (escolhaUsuario == 3 && escolhaComputador == 2)) {
        printf("Você venceu!\n");
    } else {
        printf("Você perdeu!\n");
    }
}

void jogarPedraPapelTesoura() {
    int escolhaUsuario, escolhaComputador;
    printf("Bem-vindo ao jogo Pedra, Papel e Tesoura!\n");

    srand(time(NULL));

    do {
        escolhaUsuario = obterEscolha();
        escolhaComputador = rand() % 3 + 1;

        switch (escolhaComputador) {
            case 1:
                printf("O computador escolheu Pedra.\n");
                break;
            case 2:
                printf("O computador escolheu Papel.\n");
                break;
            case 3:
                printf("O computador escolheu Tesoura.\n");
                break;
        }

        determinarVencedor(escolhaUsuario, escolhaComputador);
        printf("\nDeseja jogar novamente? (1 = Sim, 0 = Não): ");
        scanf("%d", &escolhaUsuario);
    } while (escolhaUsuario == 1);

    printf("Obrigado por jogar!\n");
}

