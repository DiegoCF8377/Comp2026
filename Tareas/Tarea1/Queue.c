#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct Queue
{
    int arr[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initialize(Queue *queue){
    queue->front = 0;
    queue->rear = -1;
}

bool isEmpty(Queue *queue){
    return queue->rear < queue->front;
}

bool isFull(Queue *queue){
    return queue->rear ==MAX_SIZE - 1;
}

void enqueue(Queue *queue, int value) { //insertion of an element
    if (isFull(queue)){
        printf("Queue Overflow\n");
        return;
    }
    queue->arr[++queue->rear] = value;
    printf("Queued %d onto the queue\n");
}

int dequeue(Queue *queue){
    if (isEmpty(queue)){
        printf("Queue empty\n");
        return;
    }
    int dequeued = queue->arr[queue->front];
    queue->front++;
    printf("Dequeued %d from the queue\n", dequeued);
    return dequeued;
}

int getFront(Queue *queue){
    if (isEmpty(queue)){
        printf("Queue empty\n");
        return;
    }
    return queue->arr[queue->front];
}
int getRear(Queue *queue){
    if (isEmpty(queue)){
        printf("Queue empty\n");
        return;
    }
    return queue->arr[queue->rear];
}

int main() {
    Queue queue;
    initialize(&queue);  

    enqueue(&queue, 1);
    printf("Last element: %d\n", getRear(&queue));

    enqueue(&queue, 2);
    printf("Last element: %d\n", getRear(&queue));

    enqueue(&queue, 3);
    printf("Last element: %d\n", getRear(&queue));

    enqueue(&queue, 4);
    printf("Last element: %d\n", getRear(&queue));

    while (!isEmpty(&queue)) {
        printf("Front element: %d\n", getFront(&queue));
        printf("Popped element: %d\n", dequeue(&queue));
    }
 
    return 0;
}