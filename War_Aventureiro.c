#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct dos Territórios:
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// Variaveis Globais e Ponteiros:
int MAX_TERRITORIOS;
int IDatacante, IDdefensor;
struct Territorio *lugar;
int *qtdTerritorios;

// Funcao para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para definir o número de territórios:
void Qtd(){

    printf("Digite com quantos territórios voce quer jogar: ");
    scanf("%d", &MAX_TERRITORIOS);
    limparBufferEntrada(); // Limpa o buffer após scanf
}

// Função para exibir o estado atual dos territórios
void estadoAtual(struct Territorio *lugar, int MAX_TERRITORIOS){
        // Exibe os territórios cadastrados
    printf("===================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("===================================\n\n");
    
    for(int i = 0; i < MAX_TERRITORIOS; i++){
        printf("TERRITÓRIO %d:\n", i + 1);
        printf("- Nome: %s\n", lugar[i].nome);
        printf("- Dominado por: Exército %s\n", lugar[i].cor);
        printf("- Tropas: %d\n\n", lugar[i].tropas);
    }
}

// Função de ATAQUE entre territórios:
void atacar(struct Territorio *lugar, int MAX_TERRITORIOS){

    printf("===================================\n");
    printf("         FASE DE ATAQUE            \n");
    printf("===================================\n\n");

    printf("Escolha o território atacante (1-%d): ", MAX_TERRITORIOS);
    scanf("%d", &IDatacante);;
    limparBufferEntrada();
    printf("Escolha o território defensor (1-%d): ", MAX_TERRITORIOS);
    scanf("%d", &IDdefensor);;
    limparBufferEntrada();


    // Validação das escolhas
    if (IDatacante < 1 || IDatacante > MAX_TERRITORIOS || IDdefensor < 1 || IDdefensor > MAX_TERRITORIOS) {
        printf("Escolhas inválidas. Tente novamente.\n");
    } else {
        printf("Território atacante: %s\n", lugar[IDatacante - 1].nome);
        printf("Território defensor: %s\n", lugar[IDdefensor - 1].nome);
    }
    // Rolagem dos dados:
    int dadosAtacante = (rand() % 6) + 1;
    int dadosDefensor = (rand() % 6) + 1;
    printf("Dado do atacante: %d\n", dadosAtacante);
    printf("Dado do defensor: %d\n", dadosDefensor);
    if (dadosAtacante > dadosDefensor) {
        printf("O atacante vence! O defensor recebe metade das tropas e a cor do atacante.\n");
        //Pega os índices reais
        int iA = IDatacante - 1;
        int iD = IDdefensor - 1;

        // Calcula quantas tropas serão movidas (metade do atacante)
        int tropasTransferidas = lugar[iA].tropas / 2;

        // Transfere a cor e as tropas
        strcpy(lugar[iD].cor, lugar[iA].cor);
        lugar[iD].tropas = tropasTransferidas;

        // Atualiza o atacante, que cede as tropas
        lugar[iA].tropas -= tropasTransferidas;

    } else {
        printf("O defensor vence! O atacante perde uma tropa.\n");
        lugar[IDatacante - 1].tropas--;
    }
    
}

// Função para cadastro de territórios:
void cadastrarTerrirorios(struct Territorio *lugar, int MAX_TERRITORIOS){

    printf("=============================================\n");
    printf("      CADASTRO DOS %d TERRITORIOS INICIAIS    \n", MAX_TERRITORIOS);
    printf("=============================================\n\n");
    for(int i = 0; i < MAX_TERRITORIOS; i++){
        printf("----- Cadastro do Território %d -----\n", i + 1);
        
        printf("Digite o nome do território: ");
        fgets(lugar[i].nome, 30, stdin);
        lugar[i].nome[strcspn(lugar[i].nome, "\n")] = 0; // Remove o '\n' do final

        printf("Digite a cor do território: ");
        fgets(lugar[i].cor, 10, stdin);
        lugar[i].cor[strcspn(lugar[i].cor, "\n")] = 0; // Remove o '\n' do final

        printf("Digite o número de tropas no território: ");
        scanf("%d", &lugar[i].tropas);
        limparBufferEntrada(); // Limpa o buffer após scanf

        printf("\nTerritório %d cadastrado com sucesso!\n\n", i + 1);
    }

    // Mensagem de todos os territórios cadastrados
    printf("Cadastro dos territórios concluido com sucesso!\n\n");
}

// Função de alocação de memória:
void alocar(){
    lugar = (struct Territorio *)calloc(MAX_TERRITORIOS,sizeof(struct Territorio));
    qtdTerritorios = (int *)calloc(1, sizeof(int));
}

// Função para verificar alocação da memória:
int verificarMemoria(){
    if(lugar == NULL || qtdTerritorios == NULL){
        printf("Erro na alocacao de memoria!\n");
        return 1; // Sai do programa e indica um erro
    } else {
        printf("\nMEMÓRIA ALOCADA CORRETAMENTE\n");
        return 0;
    }
}

// Função para liberar memória alocada:
void liberar(){
    free(lugar);
    free(qtdTerritorios);
}

int totalTerritorios = 0; 
int opcao;

// Funcao Principal
int main(){

    srand(time(NULL));

    // Definir a quantidade de territórios:
    Qtd();

    // Alocação de memória:
    alocar();

    // Verificação da memória alocada:
    verificarMemoria();

    // Cadastro de Territórios:
    cadastrarTerrirorios(lugar, MAX_TERRITORIOS);

    // Exibe os territórios cadastrados:
    estadoAtual(lugar, MAX_TERRITORIOS);

    // Rolagem dos dados para ataque:
    atacar(lugar, MAX_TERRITORIOS);

    // Exibe o estado final dos territórios:
    estadoAtual(lugar, MAX_TERRITORIOS);

    // Liberando memória alocada:
    liberar();

    return 0;
}