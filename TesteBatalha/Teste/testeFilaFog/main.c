#include <stdio.h>
#include <stdlib.h>

#define MAX 20 // Define o tamanho m�ximo da fila

// Estrutura de dados da fila
typedef struct {
    int items[MAX]; // Matriz para armazenar os valores da fila
    int front; // Vari�vel para armazenar o �ndice do in�cio da fila
    int rear; // Vari�vel para armazenar o �ndice do final da fila
} Queue;

// Fun��o para verificar se a fila est� vazia
int is_empty(Queue *q) {
    return q->rear == -1;
}

// Fun��o para verificar se a fila est� cheia
int is_full(Queue *q) {
    return q->rear == MAX - 1;
}

// Fun��o para adicionar um valor � fila
void enqueue(Queue *q, int value) {
    if (is_full(q)) { // Verifica se a fila est� cheia
        printf("Queue is full\n");
    } else {
        if (q->front == -1) { // Verifica se a fila est� vazia
            q->front = 0;
        }
        q->rear++; // Move o �ndice do final da fila para a frente
        q->items[q->rear] = value; // Adiciona o valor � fila
    }
}

// Fun��o para remover um valor da fila
int dequeue(Queue *q) {
    int item;
    if (is_empty(q)) { // Verifica se a fila est� vazia
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front]; // Armazena o valor removido da fila
        q->front++; // Move o �ndice do in�cio da fila para a frente
        if (q->front > q->rear) { // Verifica se a fila est� vazia
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Fun��o para exibir os valores na fila
void display(Queue *q) {
    if (is_empty(q)) { // Verifica se a fila est� vazia
        printf("Queue is empty\n");
    } else {
        int i;
        printf("Values in queue: ");
        for (i = q->front; i <= q->rear; i++) { // Itera atrav�s dos valores na fila
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int main() {
    Queue q;
    q.front = -1; // Inicializa o �ndice do in�cio da fila
    q.rear = -1; // Inicializa o �ndice do final da fila

    int i;
    int value;

    // Adiciona valores � fila
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
