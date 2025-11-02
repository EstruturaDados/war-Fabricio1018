#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definição do numero máximo de territórios
#define MAX_TERRITORIOS 5

// Struct dos Territórios
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// Variaveis Globais e Ponteiros:
int IDatacante, IDdefensor;
struct Territorio *lugar;
struct Territorio *exercito;
int *qtdTerritorios;
int totalTerritorios = MAX_TERRITORIOS; 
int opcao;
int missaoCumprida = 0;
int territoriosConquistados = 0;
int tropasPerdidas = 0;
int territoriosAtuais = 0;
int indiceMissao;

// Registro das missões:
char *missao[5] = {
    "Conquiste um Territorio",
    "Perca apenas 1 tropa",
    "Conquiste 3 territorios",
    "Não perca nenhuma tropa",
    "Conquiste 2 territórios"
};

// Protótipos das Funções:
    void limparBufferEntrada();
    void alocar();
    int verificarMemoria();
    void cadastrarTerrirorios(struct Territorio *lugar, int totalTerritorios);
    void estadoAtual(struct Territorio *lugar, int totalTerritorios);
    int sortearMissao();
    void atacar(struct Territorio *lugar, int totalTerritorios);
    void estadoAtual(struct Territorio *lugar, int totalTerritorios);
    int verificarMissao(int indiceMissao, struct Territorio *lugar, int totalTerritorios);
    void liberar();

//==========================================================================================================

// Funcao Principal:
int main(){

    srand(time(NULL));

    // Alocação de memória:
    alocar();

    // Verificação da memória alocada:
    verificarMemoria();

    // Cadastro de Territórios:
    cadastrarTerrirorios(lugar, MAX_TERRITORIOS);

    // Exibe os territórios cadastrados:
    estadoAtual(lugar, MAX_TERRITORIOS);

    // Sorteio e exibição da Missão:
    int total = sizeof(missao) / sizeof(missao[0]);
    sortearMissao(missao, total);

    // Rolagem dos dados para ataque:
    while (!missaoCumprida) {
        atacar(lugar, MAX_TERRITORIOS);
        estadoAtual(lugar, MAX_TERRITORIOS);

        atacar(lugar, MAX_TERRITORIOS);

        // Exibe o estado final dos territórios:
        estadoAtual(lugar, MAX_TERRITORIOS);

        // Verifica se a missão foi concluida:
        missaoCumprida = verificarMissao(indiceMissao, lugar, MAX_TERRITORIOS);

        // Verificando a missão "Não perca nenhuma Tropa":
        if (indiceMissao == 3 && tropasPerdidas > 0) {
            printf("\nVocê perdeu! Missão 'Não perca nenhuma tropa' falhou.\n");
            break;
        }

        if (missaoCumprida){
            printf("\nMissão concluída! Você venceu o jogo!\n");
        } else {
            printf("\nMissão ainda em andamento! Ataque novamente com o mesmo Território!...\n");
            printf("Pressione ENTER para atacar novamente...");
            limparBufferEntrada();
        }
    
   
    }

    // Liberando memória alocada:
    liberar();


    return 0;
}

//=========================================================================================================

// Declaração das Funções:

// Funcao para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Função para exibir o estado atual dos territórios
void estadoAtual(struct Territorio *lugar, int totalTerritorios){
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
void atacar(struct Territorio *lugar, int totalTerritorios){

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
        //lugar[IDdefensor - 1].tropas--;
        //Pega os índices reais
        int iA = IDatacante - 1;
        int iD = IDdefensor - 1;

        // Calcula quantas tropas serão movidas (metade do atacante)
        int tropasTransferidas = lugar[iA].tropas / 2;
        int tropasRecebidas = lugar[iD].tropas + tropasTransferidas;

        // Transfere a cor e as tropas
        strcpy(lugar[iD].cor, lugar[iA].cor);
        //lugar[iD].tropas = tropasTransferidas;
        lugar[iD].tropas = tropasRecebidas;

        // Atualiza o atacante, que cede as tropas
        lugar[iA].tropas -= tropasTransferidas;

        // Atualização para verificação de territórios onquistados
        territoriosConquistados ++;

    } else {
        printf("O defensor vence! O atacante perde uma tropa.\n");
        lugar[IDatacante - 1].tropas--;
        tropasPerdidas ++;
    }
    
}

// Função para cadastro de territórios:
void cadastrarTerrirorios(struct Territorio *lugar, int totalTerritorios){

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
    printf("\nMemória Liberada Corretamente!\n");
}

// Função para o sorteio das Missões:
int sortearMissao(char *missao[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    printf("\n Sua missão é: %s\n", missao[sorteio]);
    indiceMissao = sorteio;
    return sorteio;
}

// Função para verificar se a missão foi concluida
int verificarMissao(int indiceMissao, struct Territorio *lugar, int totalTerritorios){
    switch (indiceMissao){

        case 0: // "Conquiste um Território"
            return territoriosConquistados >= 1;

        case 1: // "Perca apenas 1 tropa"
            return tropasPerdidas == 1;

        case 2: // "Conquiste 3 territórios"
            return territoriosConquistados >= 3;

        case 3: // "Não perca nenhuma tropa"
            return tropasPerdidas == 0;

        case 4: // "Conquiste 2 territórios"
            return territoriosConquistados >= 2;

        default:
            return false;
    }
}
