#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Graph {
    int V;
    int E;
    int** Adj; //이차원 행렬을 위해
} Graph;

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link; // 다음 노드를 가리키는 포인터
} GraphNode;

typedef struct listGraph {
    int V;
    int E;
    struct GraphNode** Adj;
} listGraph;

Graph* AdjMatrix(int v, int e) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    if (!G) {
        printf("Memory Error");
        return;
    }
    G->V = v;
    G->E = e;
    G->Adj = (int**)malloc(sizeof(int*) * G->V);
    for (int i = 0; i < G->V; i++)
        G->Adj[i] = malloc(sizeof(int) * G->V);
    for (int i = 0; i < G->V; i++)
        for (int j = 0; j < G->V; j++)
            G->Adj[i][j] = 0;

    return G;
}

Graph* insert_direct(Graph* G, int array[], int size)
{
    int u, v;
    for (int i = 0; i < size; i += 2)
    {
        u = array[i];
        v = array[i + 1];

        if (u >= G->V || v >= G->V) 
        {
            printf(" No such vertex!!");
            exit(0);
        }
        G->Adj[u][v] = 1;
    }

    return G;
}

Graph* deleteMatrix(Graph* G) {
    for (int i = 0; i < G->V; i++)
        free(G->Adj[i]);
    free(G->Adj);
    free(G);
}

void print_adj_mat(Graph* G) {
    if (G
        ->Adj == NULL) {
        printf("No Matrix exist!\n");
        return;
    }
    printf("\n Adjacency Matrix of Direct Graph\n");
    for (int u = 0; u < G
        ->V; u++) {
        for (int v = 0; v < G
            ->V; v++) {
            printf("%2d ", G->Adj[u][v]);
        }
        printf("\n");
    }
}

listGraph* AdjList(int v, int e) {
    listGraph* G = (listGraph*)malloc(sizeof(listGraph));
    if (!G) {
        printf("Memory Error!!");
        exit(0);
    }
    G->V = v;
    G->E = e;
    G->Adj = (GraphNode**)malloc(G->V * sizeof(GraphNode*));
    for (int i = 0; i < G->V; i++) {
        G->Adj[i] = (GraphNode*)malloc(sizeof(GraphNode));
        G->Adj[i]->vertex = i;
        G->Adj[i]->link = NULL;
    }
    return G;
}

listGraph* insert_Node(listGraph* G, int array[], int size)
{
    GraphNode* temp;
    int u, v;

    for (int i = 0; i < size; i += 2)
    {
        int u = array[i];
        int v = array[i + 1];

        if (u >= G->V || v >= G->V) 
        {
            printf(" No such vertex!!\n");
            exit(0);
        }

        temp = (GraphNode*)malloc(sizeof(GraphNode));
        temp->vertex = v;
        temp->link = G->Adj[u]->link;
        G->Adj[u]->link = temp;
    }
    return G;
}


void deleteList(Graph* G) {
    GraphNode* auxiliaryNode, * iterator;
    for (int i = 0; i < G->V; i++) {
        iterator = G->Adj[i];
        while (iterator) {
            auxiliaryNode = iterator->link;
            free(iterator);
            iterator = auxiliaryNode;
        }
    }
    free(G->Adj);
    free(G);
}

void print_adj_list(Graph* G)
{
    printf("\n Adjacency List of Graph\n");
    for (int i = 0; i < G->V; i++) {
        GraphNode* head = G->Adj[i];

        for (GraphNode* p = head; p != NULL; p = p->link)
            printf(" %d ->", p->vertex);
        printf(" NULL \n");
    }
    printf("\n");
}

typedef struct stack
{
    GraphNode* data;
    struct stack* link;
}stack;

stack* push(stack* head, GraphNode* data)
{
    stack* new = malloc(sizeof(stack));
    new->data = data;
    new->link = head;
    head = new;
    return head;
}

GraphNode* pop(stack** head)
{
    stack* remove = *head;
    GraphNode* data = (*head)->data;
    *head = (*head)->link;

    free(remove);
    return data;
}

void draw_graph(Graph* g, int number)
{
    int visited[100] = { 0 };
    stack* stacknode = NULL;

    stacknode = push(stacknode, g->Adj[number]); // 시작 노드 push
    visited[number] = 1;
    printf("%d -> ", number);

    while (stacknode != NULL)
    {
        GraphNode* head = pop(&stacknode);

        for (GraphNode* p = head->link; p != NULL; p = p->link)
        {
            if (!visited[p->vertex])
            {
                printf("%d -> ", p->vertex);
                visited[p->vertex] = 1;
                stacknode = push(stacknode, g->Adj[p->vertex]);
            }
        }
    }
    printf("NULL\n");
}

int main() 
{
    FILE* fp;
    int v;
    int k;
    int count = 0;
    int array[100];

    fp = fopen("C:\\Users\\user\\Downloads\\10(b) 그래프 과제 입력.txt", "r");
    fscanf(fp, "%d", &v);
    fscanf(fp, "%d", &k);

    while (k != -1)
    {
        array[count] = k;
        count++;
        fscanf(fp, "%d", &k);
    }
    Graph* g = AdjList(v, count);
    Graph* f = AdjMatrix(v, count);
    f = insert_direct(f, array, count);
    g = insert_Node(g, array, count);
    print_adj_mat(f);
    print_adj_list(g);
    draw_graph(g, 0);

    return 0;
}