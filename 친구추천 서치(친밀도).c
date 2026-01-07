#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* link;
} GraphNode;

typedef struct listGraph {
    int V;
    int E;
    GraphNode** Adj;
} listGraph;

// 그래프 초기화
listGraph* AdjList(int v) {
    listGraph* G = (listGraph*)malloc(sizeof(listGraph));
    G->V = v;
    G->E = 0;
    G->Adj = (GraphNode**)malloc(v * sizeof(GraphNode*));
    for (int i = 0; i < v; i++) {
        G->Adj[i] = NULL;
    }
    return G;
}

// 간선 삽입 (무방향, 친밀도 포함)
void insertEdge(listGraph* G, int u, int v, int w) {
    GraphNode* temp = (GraphNode*)malloc(sizeof(GraphNode));
    temp->vertex = v;
    temp->weight = w;
    temp->link = G->Adj[u];
    G->Adj[u] = temp;

    temp = (GraphNode*)malloc(sizeof(GraphNode));
    temp->vertex = u;
    temp->weight = w;
    temp->link = G->Adj[v];
    G->Adj[v] = temp;

    G->E++;
}

// 2단계 친구 추천
void recommendFriends(listGraph* G, int node) {
    bool* visited = (bool*)calloc(G->V, sizeof(bool));
    int* scores = (int*)calloc(G->V, sizeof(int)); // 2촌 최대 친밀도 저장

    visited[node] = true;

    // 1촌 친구 표시
    GraphNode* p = G->Adj[node];
    while (p) {
        visited[p->vertex] = true;
        p = p->link;
    }

    // 1촌 친구들의 친구 탐색
    p = G->Adj[node];
    while (p) {
        GraphNode* q = G->Adj[p->vertex];
        while (q) {
            if (!visited[q->vertex]) {
                int score = p->weight + q->weight; // 1촌->2촌 점수 합
                if (score > scores[q->vertex]) {
                    scores[q->vertex] = score; // 최대값만 저장
                }
            }
            q = q->link;
        }
        p = p->link;
    }

    // 추천 출력 (친밀도 높은 순)
    printf("추천 친구 (2단계, 친밀도 합산 기준 최대값):\n");
    for (int count = 0; count < G->V; count++) {
        int maxScore = 0;
        int maxIdx = -1;
        for (int i = 0; i < G->V; i++) {
            if (scores[i] > maxScore) {
                maxScore = scores[i];
                maxIdx = i;
            }
        }
        if (maxIdx == -1) break;
        printf("정점 %d (친밀도 %d)\n", maxIdx + 1, maxScore);
        scores[maxIdx] = 0; // 출력 후 제거
    }

    free(visited);
    free(scores);
}

// 그래프 출력
void printGraph(listGraph* G) {
    printf("전체 그래프:\n");
    for (int i = 0; i < G->V; i++) {
        printf("%d:", i + 1);
        GraphNode* p = G->Adj[i];
        while (p) {
            printf(" -> %d(%d)", p->vertex + 1, p->weight);
            p = p->link;
        }
        printf("\n");
    }
}

// 메모리 해제
void deleteGraph(listGraph* G) {
    for (int i = 0; i < G->V; i++) {
        GraphNode* p = G->Adj[i];
        while (p) {
            GraphNode* temp = p->link;
            free(p);
            p = temp;
        }
    }
    free(G->Adj);
    free(G);
}

int main() {
    FILE* fp = fopen("C:\\Users\\user\\Downloads\\sns_weighted_friends.txt", "r");
    if (!fp) {
        printf("파일 열기 실패\n");
        return 0;
    }

    int V = 20;
    listGraph* G = AdjList(V);

    int u, v, w;
    int edgeCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d %d %d", &u, &v, &w) == 3) {
            insertEdge(G, u - 1, v - 1, w); // 0-indexed
            edgeCount++;
        }
    }
    fclose(fp);

    printf("총 %d개의 간선 삽입됨\n", edgeCount);
    if (edgeCount == 0) {
        printf("파일 데이터 확인 필요\n");
        deleteGraph(G);
        return 0;
    }

    printGraph(G);

    int target;
    printf("추천을 받을 특정 인물 번호: ");
    scanf("%d", &target);
    recommendFriends(G, target - 1);

    deleteGraph(G);
    return 0;
}