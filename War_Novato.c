#include <stdio.h>
#include <stdlib.h>

// Struct dos Territórios
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
};

// Funcao para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Definição do numero máximo de territórios
#define MAX_TERRITORIOS 5

// Funcao Principal
int main(){
    struct Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0; 
    int opcao;

    // Cadastrando os territórios
    printf("=============================================\n");
    printf("      CADASTRO DOS 5 TERRITORIOS INICIAIS    \n");
    printf("=============================================\n\n");
    for(int i = 0; i < MAX_TERRITORIOS; i++){
        printf("----- Cadastro do Território %d -----\n", i + 1);
        
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; // Remove o '\n' do final

        printf("Digite a cor do território: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0; // Remove o '\n' do final

        printf("Digite o número de tropas no território: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada(); // Limpa o buffer após scanf

        printf("\nTerritório %d cadastrado com sucesso!\n\n", i + 1);
    }

    // Mensagem de todos os territórios cadastrados
    printf("Cadastro dos territórios concluido com sucesso!\n\n");

    // Exibe os territórios cadastrados
    printf("===================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("===================================\n\n");
    
    for(int i = 0; i < MAX_TERRITORIOS; i++){
        printf("TERRITÓRIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exército %s\n", territorios[i].cor);
        printf("- Tropas: %d\n\n", territorios[i].tropas);
    }


    return 0;
}