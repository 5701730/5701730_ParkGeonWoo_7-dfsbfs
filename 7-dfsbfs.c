#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct Graph {
    Node* adjLists[MAX_VERTICES];
    bool visited[MAX_VERTICES];
} Graph;


typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;


Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 그래프 생성 함수
Graph* createGraph() {
    Graph* graph = malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}


void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// (DFS)깊이 우선 탐색 함수
int DFS(Graph* graph, int vertex, int searchValue, int* nodeCount) {
    graph->visited[vertex] = true;
    (*nodeCount)++;
    printf("%d ", vertex);

    if (vertex == searchValue) {
        return 1;
    }

    Node* temp = graph->adjLists[vertex];

    while (temp) {
        int connectedVertex = temp->vertex;

        if (!graph->visited[connectedVertex]) {
            if (DFS(graph, connectedVertex, searchValue, nodeCount)) {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

// (BFS)너비 우선 탐색 관련한 큐 함수
Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        return;
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// (BFS) 너비 우선 탐색 
int BFS(Graph* graph, int startVertex, int searchValue, int* nodeCount) {
    Queue* q = createQueue();

    graph->visited[startVertex] = true;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        (*nodeCount)++;
        printf("%d ", currentVertex);

        if (currentVertex == searchValue) {
            return 1;
        }

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    return 0;
}

// 초기화함수 
void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = false;
    }
}

int main() {
    Graph* graph = createGraph();

    
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 9);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 7);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 6);
    addEdge(graph, 4, 7);
    addEdge(graph, 6, 8);
    addEdge(graph, 7, 10);
    addEdge(graph, 8, 9);
    addEdge(graph, 8, 10);

    int choice, startVertex, searchValue;
    while (1) {
        printf("\n메뉴:\n");
        printf("1. 깊이 우선 탐색 (DFS)\n");
        printf("2. 너비 우선 탐색 (BFS)\n");
        printf("3. 프로그램 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
        case 2:
            printf("시작 번호와 탐색할 값을 입력: ");
            scanf_s("%d %d", &startVertex, &searchValue);
            if (startVertex < 0 || startVertex >= MAX_VERTICES || searchValue < 0 || searchValue >= MAX_VERTICES) {
                printf("잘못된 정점 번호입니다.\n");
                break;
            }
            resetVisited(graph);
            int nodeCount = 0;
            if (choice == 1) {
                printf("DFS 탐색 결과: ");
                if (DFS(graph, startVertex, searchValue, &nodeCount)) {
                    printf("\n탐색 성공: %d, 방문한 노드 수: %d\n", searchValue, nodeCount);
                }
                else {
                    printf("\n탐색 실패, 방문한 노드 수: %d\n", nodeCount);
                }
            }
            else {
                printf("BFS 탐색 결과: ");
                if (BFS(graph, startVertex, searchValue, &nodeCount)) {
                    printf("\n탐색 성공: %d, 방문한 노드 수: %d\n", searchValue, nodeCount);
                }
                else {
                    printf("\n탐색 실패, 방문한 노드 수: %d\n", nodeCount);
                }
            }
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}






