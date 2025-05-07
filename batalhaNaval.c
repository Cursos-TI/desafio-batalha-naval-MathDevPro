#include <stdio.h>
#include <stdlib.h> // Para a função abs()

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA_HABILIDADE 5 // Novo valor para áreas de efeito

#define TAMANHO_HABILIDADE 5 // Tamanho das matrizes de habilidade (ex: 5x5)
#define ALTURA_CONE 3      // Altura específica para a forma do cone dentro da matriz de habilidade

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro com letras nas colunas e os diferentes elementos
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n    "); // Espaçamento para alinhar com os índices das linhas
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf(" %c", letra); // Cabeçalho das colunas com letras
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // O printf existente já lida com os diferentes valores (0, 3, 5)
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Fora dos limites
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) { // Verifica se há sobreposição
            return 0;
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO; // Posiciona o navio
    }
    return 1;
}

// Função para posicionar um navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna < 0 || coluna >= TAMANHO_TABULEIRO || linha < 0 || linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Fora dos limites
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) { // Verifica se há sobreposição
            return 0;
        }
    }
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO; // Posiciona o navio
    }
    return 1;
}

// --- Funções de Habilidade ---


void inicializarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int alturaCone) {
    int centroColuna = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0; // Inicializa com 0 (não afetado)
            // Verifica se está dentro da altura do cone
            if (i < alturaCone) {
                // Calcula a largura do cone para a linha atual 'i'
                // O cone se expande por 'i' unidades para cada lado do centroColuna
                if (j >= centroColuna - i && j <= centroColuna + i) {
                    habilidade[i][j] = 1; // Marca como afetado
                }
            }
        }
    }
}


void inicializarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0; // Inicializa com 0
        }
    }

    if (TAMANHO_HABILIDADE >= 3) {
        int centro = TAMANHO_HABILIDADE / 2;
        // Haste vertical superior (acima do centro)
        habilidade[centro - 1][centro] = 1;
        // Linha horizontal central
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[centro][j] = 1;
        }
        // Haste vertical inferior (abaixo do centro)
        habilidade[centro + 1][centro] = 1;
    } else if (TAMANHO_HABILIDADE > 0) { // Caso menor, faz uma cruz simples
        int centro = TAMANHO_HABILIDADE / 2;
         for (int i = 0; i < TAMANHO_HABILIDADE; i++) habilidade[i][centro] = 1;
         for (int j = 0; j < TAMANHO_HABILIDADE; j++) habilidade[centro][j] = 1;
    }
}


void inicializarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    int raio = 1; // Raio para o formato de losango do exemplo (menor)
                // Para um losango que preenche a matriz 5x5, o raio seria TAMANHO_HABILIDADE / 2

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar um losango (distância de Manhattan)
            if (abs(i - centro) + abs(j - centro) <= raio) {
                habilidade[i][j] = 1; // Marca como afetado
            } else {
                habilidade[i][j] = 0; // Não afetado
            }
        }
    }
}


void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                 int habilidadeMatriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                                 int linhaOrigemNoTabuleiro, int colunaOrigemNoTabuleiro) {
    int centroHabilidade = TAMANHO_HABILIDADE / 2; // Ponto central da matriz de habilidade (ex: 2 para tamanho 5)

    // Itera sobre cada célula da matriz de habilidade
    for (int i_h = 0; i_h < TAMANHO_HABILIDADE; i_h++) {
        for (int j_h = 0; j_h < TAMANHO_HABILIDADE; j_h++) {
            // Verifica se esta parte da habilidade afeta uma área
            if (habilidadeMatriz[i_h][j_h] == 1) {
                // Calcula a posição correspondente no tabuleiro principal.
                // A posição é relativa ao centro da habilidade e ao ponto de origem no tabuleiro.
                int targetLinha = linhaOrigemNoTabuleiro + (i_h - centroHabilidade);
                int targetColuna = colunaOrigemNoTabuleiro + (j_h - centroHabilidade);

                // Verifica se a posição calculada está dentro dos limites do tabuleiro
                if (targetLinha >= 0 && targetLinha < TAMANHO_TABULEIRO &&
                    targetColuna >= 0 && targetColuna < TAMANHO_TABULEIRO) {
                    // Marca a posição no tabuleiro como afetada pela habilidade
                    tabuleiro[targetLinha][targetColuna] = AREA_AFETADA_HABILIDADE;
                }
            }
        }
    }
}


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int linha, coluna, orientacao;

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Exibe o tabuleiro vazio antes de posicionar os navios
    printf("Visualização inicial do tabuleiro (0 = água):\n");
    exibirTabuleiro(tabuleiro);

    // --- Posicionamento de Navios (simplificado para demonstração) ---
    printf("\nPosicionando navios automaticamente para demonstração...\n");
    posicionarNavioHorizontal(tabuleiro, 1, 3); // Navio 1
    posicionarNavioVertical(tabuleiro, 5, 7);   // Navio 2

    // Exibe o tabuleiro após posicionar os navios
    printf("\nTabuleiro com navios posicionados (3 = navio):\n");
    exibirTabuleiro(tabuleiro);

    // --- HABILIDADES ESPECIAIS ---
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // 1. Criar Matrizes de Habilidade
    printf("\nInicializando matrizes de habilidade...\n");
    inicializarHabilidadeCone(habilidadeCone, ALTURA_CONE);
    inicializarHabilidadeCruz(habilidadeCruz);
    inicializarHabilidadeOctaedro(habilidadeOctaedro);

    

    // 2. Integrar Habilidades ao Tabuleiro
    // Definir pontos de origem para cada habilidade no tabuleiro 
    // Estas coordenadas (linha, coluna) são onde o *centro* da matriz de habilidade será posicionado.
    int origemConeLinha = 3, origemConeColuna = 3;
    int origemCruzLinha = 7, origemCruzColuna = 2;
    int origemOctaedroLinha = 5, origemOctaedroColuna = 6;

    printf("\nAplicando habilidades ao tabuleiro...\n");

    // Aplicar Habilidade Cone
    printf("Aplicando Cone em (%d, %c)...\n", origemConeLinha, 'A' + origemConeColuna);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCone, origemConeLinha, origemConeColuna);

    // Aplicar Habilidade Cruz
    printf("Aplicando Cruz em (%d, %c)...\n", origemCruzLinha, 'A' + origemCruzColuna);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCruz, origemCruzLinha, origemCruzColuna);
    
    // Aplicar Habilidade Octaedro
    printf("Aplicando Octaedro em (%d, %c)...\n", origemOctaedroLinha, 'A' + origemOctaedroColuna);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeOctaedro, origemOctaedroLinha, origemOctaedroColuna);

    // 3. Exibir o Tabuleiro com Habilidades
    printf("\nTabuleiro final com navios e áreas de efeito das habilidades (5 = area afetada):\n");
    exibirTabuleiro(tabuleiro);

    // --- Fim do Jogo (simulação) ---

    return 0;
}
