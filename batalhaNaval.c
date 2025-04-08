#include <stdio.h>
#include <stdbool.h>

// Tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Valores para representar o tabuleiro
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se a posição do navio é válida
bool posicaoValida(int linha, int coluna, int tamanho, bool vertical) {
    if (vertical) {
        return (linha >= 0) && (linha + tamanho - 1 < TAMANHO_TABULEIRO) && 
               (coluna >= 0) && (coluna < TAMANHO_TABULEIRO);
    } else {
        return (linha >= 0) && (linha < TAMANHO_TABULEIRO) && 
               (coluna >= 0) && (coluna + tamanho - 1 < TAMANHO_TABULEIRO);
    }
}

// Função para verificar se há sobreposição com navios existentes
bool semSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical) {
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] == NAVIO) {
                return false;
            }
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] == NAVIO) {
                return false;
            }
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical) {
    // Verifica se a posição é válida
    if (!posicaoValida(linha, coluna, tamanho, vertical)) {
        printf("Posição inválida para o navio!\n");
        return false;
    }
    
    // Verifica se há sobreposição com outros navios
    if (!semSobreposicao(tabuleiro, linha, coluna, tamanho, vertical)) {
        printf("Navio sobreposto a outro navio!\n");
        return false;
    }
    
    // Posiciona o navio
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    }
    
    return true;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro de Batalha Naval:\n");
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
    
    // Posiciona o navio horizontal (linha 2, coluna 3)
    printf("Posicionando navio horizontal na linha 2, coluna 3...\n");
    if (!posicionarNavio(tabuleiro, 2, 3, TAMANHO_NAVIO, false)) {
        printf("Falha ao posicionar navio horizontal.\n");
        return 1;
    }
    
    // Posiciona o navio vertical (linha 5, coluna 7)
    printf("Posicionando navio vertical na linha 5, coluna 7...\n");
    if (!posicionarNavio(tabuleiro, 5, 7, TAMANHO_NAVIO, true)) {
        printf("Falha ao posicionar navio vertical.\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}