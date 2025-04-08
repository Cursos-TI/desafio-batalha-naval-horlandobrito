#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

// Valores para representar o tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Tipos de habilidades
typedef enum {
    CONE,
    CRUZ,
    OCTAEDRO,
    NUM_HABILIDADES
} TipoHabilidade;

// Estrutura para representar uma habilidade
typedef struct {
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int centroX;
    int centroY;
} Habilidade;

// Protótipos de funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criarHabilidade(Habilidade *hab, TipoHabilidade tipo);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      Habilidade *hab, int linha, int coluna);

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Habilidade habilidades[NUM_HABILIDADES];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios
    posicionarNavio(tabuleiro, 2, 3, TAMANHO_NAVIO, false); // Horizontal
    posicionarNavio(tabuleiro, 5, 7, TAMANHO_NAVIO, true);  // Vertical
    
    // Cria as habilidades
    criarHabilidade(&habilidades[CONE], CONE);
    criarHabilidade(&habilidades[CRUZ], CRUZ);
    criarHabilidade(&habilidades[OCTAEDRO], OCTAEDRO);
    
    // Define os centros das habilidades (coordenadas do tabuleiro)
    habilidades[CONE].centroX = 2;
    habilidades[CONE].centroY = 2;
    
    habilidades[CRUZ].centroX = 2;
    habilidades[CRUZ].centroY = 2;
    
    habilidades[OCTAEDRO].centroX = 2;
    habilidades[OCTAEDRO].centroY = 2;
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, &habilidades[CONE], 4, 4);
    aplicarHabilidade(tabuleiro, &habilidades[CRUZ], 7, 2);
    aplicarHabilidade(tabuleiro, &habilidades[OCTAEDRO], 3, 6);
    
    // Exibe o tabuleiro com os navios e áreas de habilidade
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona um navio no tabuleiro (versão simplificada do nível anterior)
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, bool vertical) {
    if (vertical) {
        for (int i = linha; i < linha + tamanho; i++) {
            if (i >= TAMANHO_TABULEIRO) return false;
            tabuleiro[i][coluna] = NAVIO;
        }
    } else {
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (j >= TAMANHO_TABULEIRO) return false;
            tabuleiro[linha][j] = NAVIO;
        }
    }
    return true;
}

// Cria uma matriz de habilidade com base no tipo
void criarHabilidade(Habilidade *hab, TipoHabilidade tipo) {
    int meio = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            switch (tipo) {
                case CONE:
                    // Forma de cone apontando para baixo
                    if (i >= j && i + j >= TAMANHO_HABILIDADE - 1) {
                        hab->matriz[i][j] = 1;
                    } else {
                        hab->matriz[i][j] = 0;
                    }
                    break;
                    
                case CRUZ:
                    // Forma de cruz
                    if (i == meio || j == meio) {
                        hab->matriz[i][j] = 1;
                    } else {
                        hab->matriz[i][j] = 0;
                    }
                    break;
                    
                case OCTAEDRO:
                    // Forma de losango (octaedro visto de frente)
                    if (abs(i - meio) + abs(j - meio) <= meio) {
                        hab->matriz[i][j] = 1;
                    } else {
                        hab->matriz[i][j] = 0;
                    }
                    break;
                    
                default:
                    hab->matriz[i][j] = 0;
            }
        }
    }
    
    // Define o centro da matriz de habilidade
    hab->centroX = meio;
    hab->centroY = meio;
}

// Aplica uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      Habilidade *hab, int linha, int coluna) {
    int offsetX = linha - hab->centroX;
    int offsetY = coluna - hab->centroY;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tabX = offsetX + i;
            int tabY = offsetY + j;
            
            // Verifica se está dentro do tabuleiro
            if (tabX >= 0 && tabX < TAMANHO_TABULEIRO && 
                tabY >= 0 && tabY < TAMANHO_TABULEIRO) {
                
                // Se a posição da habilidade está ativa, marca no tabuleiro
                if (hab->matriz[i][j] == 1) {
                    // Só marca se não for um navio (para preservar os navios)
                    if (tabuleiro[tabX][tabY] != NAVIO) {
                        tabuleiro[tabX][tabY] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro com cores diferentes para cada elemento
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval com Habilidades:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf(" . "); // Água
                    break;
                case NAVIO:
                    printf("\033[1;34m N \033[0m"); // Navio (azul)
                    break;
                case HABILIDADE:
                    printf("\033[1;31m H \033[0m"); // Habilidade (vermelho)
                    break;
                default:
                    printf(" ? "); // Desconhecido
            }
        }
        printf("\n");
    }
    
    printf("\nLegenda:\n");
    printf(" .  - Água\n");
    printf("\033[1;34m N \033[0m - Navio\n");
    printf("\033[1;31m H \033[0m - Área de Habilidade\n\n");
}