#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da pilha
struct No {
    char valor;
    struct No *prox;
};

// Função para empilhar (push)
void push(struct No **topo, char c) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    if(novo == NULL) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    novo->valor = c;
    novo->prox = *topo;
    *topo = novo;
}

// Função para desempilhar (pop)
char pop(struct No **topo) {
    if(*topo == NULL) return '\0';

    struct No *temp = *topo;
    char valor = temp->valor;
    *topo = temp->prox;
    free(temp);

    return valor;
}

// Verifica se a pilha está vazia
int isEmpty(struct No *topo) {
    return topo == NULL;
}

// Função para verificar correspondência
int combina(char abertura, char fechamento) {
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '{' && fechamento == '}') ||
           (abertura == '[' && fechamento == ']');
}

int main() {
    char expressao[100];
    struct No *pilha = NULL;

    printf("Digite a expressao: ");
    scanf("%s", expressao);

    for(int i = 0; i < strlen(expressao); i++) {
        char c = expressao[i];

        // Se for abertura, empilha
        if(c == '(' || c == '{' || c == '[') {
            push(&pilha, c);
        }
        // Se for fechamento
        else if(c == ')' || c == '}' || c == ']') {
            if(isEmpty(pilha)) {
                printf("Expressao invalida!\n");
                return 0;
            }

            char topo = pop(&pilha);

            if(!combina(topo, c)) {
                printf("Expressao invalida!\n");
                return 0;
            }
        }
    }

    // Verifica se sobrou algo na pilha
    if(isEmpty(pilha)) {
        printf("Expressao valida!\n");
    } else {
        printf("Expressao invalida!\n");
    }

    return 0;
}