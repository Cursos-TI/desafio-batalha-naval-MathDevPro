
#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro com letras nas colunas
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   ");
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c", letra); // Cabeçalho das colunas com letras
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]); // Mostra 0 (água) ou 3 (navio)
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) // Verifica se o navio cabe horizontalmente
        return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) // Verifica se há sobreposição
            return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO; // Posiciona o navio
    }
    return 1;
}

// Função para posicionar um navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) // Verifica se o navio cabe verticalmente
        return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) // Verifica se há sobreposição
            return 0;
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO; // Posiciona o navio
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Exibe o tabuleiro vazio antes de posicionar os navios
    printf("Visualização inicial do tabuleiro (0 = água):\n");
    exibirTabuleiro(tabuleiro);

    // Define as posições dos navios diretamente no código
    int linhaNavio1 = 2, colunaNavio1 = 4; // Navio 1: Horizontal, começa na linha 2, coluna 4
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio 2: Vertical, começa na linha 5, coluna 7

    // Posiciona o primeiro navio (horizontal)
    if (!posicionarNavioHorizontal(tabuleiro, linhaNavio1, colunaNavio1)) {
        printf("Erro ao posicionar o primeiro navio!\n");
    }

    // Posiciona o segundo navio (vertical)
    if (!posicionarNavioVertical(tabuleiro, linhaNavio2, colunaNavio2)) {
        printf("Erro ao posicionar o segundo navio!\n");
    }

    // Exibe o tabuleiro após posicionar os navios
    printf("\nTabuleiro com navios posicionados (3 = navio):\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
