#include <stdio.h>
#include <stdbool.h>

// Tamanho do tabuleiro e navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Valores para representar o tabuleiro
#define AGUA 0
#define NAVIO 3

// Tipos de orientação para os navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,    // Diagonal principal (i == j)
    DIAGONAL_SECUNDARIA    // Diagonal secundária (i + j == TAMANHO_TABULEIRO - 1)
} Orientacao;

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se a posição do navio é válida
bool posicaoValida(int linha, int coluna, int tamanho, Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            return (linha >= 0) && (linha < TAMANHO_TABULEIRO) && 
                   (coluna >= 0) && (coluna + tamanho - 1 < TAMANHO_TABULEIRO);
        
        case VERTICAL:
            return (linha >= 0) && (linha + tamanho - 1 < TAMANHO_TABULEIRO) && 
                   (coluna >= 0) && (coluna < TAMANHO_TABULEIRO);
        
        case DIAGONAL_PRINCIPAL:
            return (linha >= 0) && (linha + tamanho - 1 < TAMANHO_TABULEIRO) && 
                   (coluna >= 0) && (coluna + tamanho - 1 < TAMANHO_TABULEIRO) &&
                   (linha == coluna); // Garante que está na diagonal principal
        
        case DIAGONAL_SECUNDARIA:
            return (linha >= 0) && (linha + tamanho - 1 < TAMANHO_TABULEIRO) && 
                   (coluna >= 0) && (coluna - tamanho + 1 >= 0) &&
                   (linha + coluna == TAMANHO_TABULEIRO - 1); // Garante que está na diagonal secundária
        
        default:
            return false;
    }
}

// Função para verificar se há sobreposição com navios existentes
bool semSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            for (int j = coluna; j < coluna + tamanho; j++) {
                if (tabuleiro[linha][j] == NAVIO) return false;
            }
            break;
        
        case VERTICAL:
            for (int i = linha; i < linha + tamanho; i++) {
                if (tabuleiro[i][coluna] == NAVIO) return false;
            }
            break;
        
        case DIAGONAL_PRINCIPAL:
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[linha + k][coluna + k] == NAVIO) return false;
            }
            break;
        
        case DIAGONAL_SECUNDARIA:
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[linha + k][coluna - k] == NAVIO) return false;
            }
            break;
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, Orientacao orientacao) {
    // Verifica se a posição é válida
    if (!posicaoValida(linha, coluna, tamanho, orientacao)) {
        printf("Posição inválida para o navio!\n");
        return false;
    }
    
    // Verifica se há sobreposição com outros navios
    if (!semSobreposicao(tabuleiro, linha, coluna, tamanho, orientacao)) {
        printf("Navio sobreposto a outro navio!\n");
        return false;
    }
    
    // Posiciona o navio de acordo com a orientação
    switch (orientacao) {
        case HORIZONTAL:
            for (int j = coluna; j < coluna + tamanho; j++) {
                tabuleiro[linha][j] = NAVIO;
            }
            break;
        
        case VERTICAL:
            for (int i = linha; i < linha + tamanho; i++) {
                tabuleiro[i][coluna] = NAVIO;
            }
            break;
        
        case DIAGONAL_PRINCIPAL:
            for (int k = 0; k < tamanho; k++) {
                tabuleiro[linha + k][coluna + k] = NAVIO;
            }
            break;
        
        case DIAGONAL_SECUNDARIA:
            for (int k = 0; k < tamanho; k++) {
                tabuleiro[linha + k][coluna - k] = NAVIO;
            }
            break;
    }
    
    return true;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    printf("Posicionando navios no tabuleiro...\n");
    
    // Navio horizontal (linha 2, coluna 3)
    printf("1. Navio horizontal na linha 2, coluna 3\n");
    if (!posicionarNavio(tabuleiro, 2, 3, TAMANHO_NAVIO, HORIZONTAL)) {
        printf("Falha ao posicionar navio horizontal.\n");
        return 1;
    }
    
    // Navio vertical (linha 5, coluna 7)
    printf("2. Navio vertical na linha 5, coluna 7\n");
    if (!posicionarNavio(tabuleiro, 5, 7, TAMANHO_NAVIO, VERTICAL)) {
        printf("Falha ao posicionar navio vertical.\n");
        return 1;
    }
    
    // Navio na diagonal principal (linha 0, coluna 0)
    printf("3. Navio na diagonal principal na linha 0, coluna 0\n");
    if (!posicionarNavio(tabuleiro, 0, 0, TAMANHO_NAVIO, DIAGONAL_PRINCIPAL)) {
        printf("Falha ao posicionar navio na diagonal principal.\n");
        return 1;
    }
    
    // Navio na diagonal secundária (linha 0, coluna 9)
    printf("4. Navio na diagonal secundária na linha 0, coluna 9\n");
    if (!posicionarNavio(tabuleiro, 0, 9, TAMANHO_NAVIO, DIAGONAL_SECUNDARIA)) {
        printf("Falha ao posicionar navio na diagonal secundária.\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}