#include <stdio.h>
#include <stdlib.h>

#define MAX 20 // Define o tamanho máximo da fila

// Estrutura de dados da fila
typedef struct {
    int items[MAX]; // Matriz para armazenar os valores da fila
    int front; // Variável para armazenar o índice do início da fila
    int rear; // Variável para armazenar o índice do final da fila
} Queue;

// Função para verificar se a fila está vazia
int is_empty(Queue *q) {
    return q->rear == -1;
}

// Função para verificar se a fila está cheia
int is_full(Queue *q) {
    return q->rear == MAX - 1;
}

// Função para adicionar um valor à fila
void enqueue(Queue *q, int value) {
    if (is_full(q)) { // Verifica se a fila está cheia
        printf("Queue is full\n");
    } else {
        if (q->front == -1) { // Verifica se a fila está vazia
            q->front = 0;
        }
        q->rear++; // Move o índice do final da fila para a frente
        q->items[q->rear] = value; // Adiciona o valor à fila
    }
}

// Função para remover um valor da fila
int dequeue(Queue *q) {
    int item;
    if (is_empty(q)) { // Verifica se a fila está vazia
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front]; // Armazena o valor removido da fila
        q->front++; // Move o índice do início da fila para a frente
        if (q->front > q->rear) { // Verifica se a fila está vazia
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Função para exibir os valores na fila
void display(Queue *q) {
    if (is_empty(q)) { // Verifica se a fila está vazia
        printf("Queue is empty\n");
    } else {
        int i;
        printf("Values in queue: ");
        for (i = q->front; i <= q->rear; i++) { // Itera através dos valores na fila
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int main() {
    Queue q;
    q.front = -1; // Inicializa o índice do início da fila
    q.rear = -1; // Inicializa o índice do final da fila

    int i;
    int value;

    // Adiciona valores à fila
    for (i = 0; i < 20; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &value);
        enqueue(&q, value);
    }

    // Exibe os valores na fila
    display(&q);

    // Remove valores da fila
    for (i = 0; i < 20; i++) {
        printf("Removed value %d: %d\n", i + 1, dequeue(&q));
    }

    return 0;
}
