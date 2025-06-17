#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó e da fila
typedef struct Node {
    char nome[100];
    int registro;
    struct Node *next;
} Node;

typedef struct {
    Node *head, *tail;
} Queue;

// Inicializa fila vazia
void initQueue(Queue *q) {
    q->head = q->tail = NULL;
}

// Enfileira paciente no fim
void enqueue(Queue *q, const char *nome, int registro) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    strncpy(n->nome, nome, sizeof(n->nome)-1);
    n->nome[sizeof(n->nome)-1] = '\0';
    n->registro = registro;
    n->next = NULL;
    if (q->tail) q->tail->next = n;
    else q->head = n;
    q->tail = n;
}

// Desenfileira paciente do início; retorna 1 se retirou, 0 se fila vazia
int dequeue(Queue *q, char *nomeOut, int *regOut) {
    if (!q->head) return 0;
    Node *n = q->head;
    strcpy(nomeOut, n->nome);
    *regOut = n->registro;
    q->head = n->next;
    if (!q->head) q->tail = NULL;
    free(n);
    return 1;
}

// Lista todos os pacientes na fila
void listar(Queue *q) {
    if (!q->head) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Pacientes na fila:\n");
    for (Node *p = q->head; p; p = p->next)
        printf(" - %s (registro %d)\n", p->nome, p->registro);
}

// Libera toda a fila
void freeQueue(Queue *q) {
    Node *p = q->head;
    while (p) {
        Node *t = p;
        p = p->next;
        free(t);
    }
    q->head = q->tail = NULL;
}

int main() {
    Queue q;
    initQueue(&q);
    int opc, reg;
    char nome[100];

    do {
        printf("\n=== Fila da Clinica ===\n");
        printf("1 - Registrar paciente\n");
        printf("2 - Chamar próximo\n");
        printf("3 - Listar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc)!=1) break;
        getchar(); // consome '\n'
        switch (opc) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Registro: ");
                scanf("%d", &reg);
                getchar();
                enqueue(&q, nome, reg);
                printf("Paciente \"%s\" registrado.\n", nome);
                break;
            case 2:
                if (dequeue(&q, nome, &reg))
                    printf("Chamando: %s (registro %d)\n", nome, reg);
                else
                    printf("Fila vazia.\n");
                break;
            case 3:
                listar(&q);
                break;
            case 0:
                freeQueue(&q);
                printf("Encerrando.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opc != 0);

    return 0;
}
