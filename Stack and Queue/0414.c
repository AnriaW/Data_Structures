#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->rear == -1);
}

int isFull(Queue *q) {
    return (q->rear == MAX_SIZE - 1);
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            initializeQueue(q);
        }
        return item;
    }
}

void printQueue(Queue *q) {
    int i;
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue elements: ");
        for (i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int count_cases(Queue *Pi, Queue *sorted_pi, int M) {
    int unchanged_count = 0;
    for (int i = 0; i < M; i++) {
        if (Pi->items[i] == sorted_pi->items[i]) {
            unchanged_count++;
        }
    }
    return unchanged_count;
}

void sortQueue(Queue *q, int M) {
    int temp;
    for (int i = 0; i < M - 1; i++) {
        for (int j = i + 1; j < M; j++) {
            if (q->items[i] < q->items[j]) {
                temp = q->items[i];
                q->items[i] = q->items[j];
                q->items[j] = temp;
            }
        }
    }
}

int main() {
    int N, M, value;
    Queue Pi, sorted_pi;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &M);

        if (M < 1 || M > MAX_SIZE) {
            printf("Invalid input for M.\n");
            return 1; // Sa�da com erro
        }

        initializeQueue(&Pi);
        initializeQueue(&sorted_pi);
        for (int j = 0; j < M; j++) {
            scanf("%d", &value);

            if (value < 1 || value > MAX_SIZE) {
                printf("Invalid input for Pi.\n");
                return 1; // Sa�da com erro
            }

            enqueue(&Pi, value);
            enqueue(&sorted_pi, value);
        }

        sortQueue(&sorted_pi, M);

        int unchanged_cases = count_cases(&Pi, &sorted_pi, M);
        printf("%d\n", unchanged_cases);

        initializeQueue(&Pi);
        initializeQueue(&sorted_pi);
    }

    return 0;
}
