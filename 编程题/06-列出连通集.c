#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 这里建立完整的图结构，作为基础练习 */

#define MaxVertexNum 10  /* 最大顶点数*/

typedef int Vertex;
typedef bool WeightType;

/* 边的定义 */
typedef struct ENode *PtrToENode;  // 用指针的好处是结果做参数时可以直接传入地址
struct ENode {
    Vertex V1, V2;
//    WeightType Weight;
};
typedef PtrToENode Edge;


/* 图的定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数 */
    WeightType M[MaxVertexNum][MaxVertexNum];
//    DataType Data[MaxVertexNum];  /* 结点的数据（如果有） */
};
typedef PtrToGNode MGraph;

MGraph CreateMGraph(int VertexNum) {
    /* 初始化一个有 VertexNum 结点但没有边的图 */
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < VertexNum; V++) {
        for(W = 0; W < VertexNum; W++)
            Graph->M[V][W] = false;
    }
    return Graph;
}

void InsertEdge(MGraph G, Edge E) {
    G->M[E->V1][E->V2] = true;
    G->M[E->V2][E->V1] = true;
}

MGraph BiuldMGraph() {
    int N, i;
    Edge E;
    MGraph G;

    scanf("%d", &N);
    G = CreateMGraph(N);
    scanf("%d", &G->Ne);
    if(G->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for(i = 0; i < G->Ne; i++) {
            scanf("%d %d", &E->V1, &E->V2);
            InsertEdge(G, E);
        }
    }

    return G;
}

bool visited[MaxVertexNum];

void init(MGraph G) {
    for(int i = 0; i < G->Nv; i++)
        visited[i] = false;
}

void DFS(MGraph G, Vertex V) {
    Vertex W;
    /* 从 V 开始 DFS */
    printf(" %d", V);
    visited[V] = true;
    for(W = 0; W < G->Nv; W++) {
        if(!visited[W] && G->M[V][W])
            DFS(G, W);
    }
}

void DoDFS(MGraph G) {
    Vertex V;
    init(G);
    for(V = 0; V < G->Nv; V++) {
        if(!visited[V]) {
            printf("{");
            DFS(G, V);
            printf(" }\n");
        }
    }
}

void BFS(MGraph G, Vertex V) {
    Vertex W;
    int Q[MaxVertexNum];
    int head, tail;
    head = tail = 0;
    Q[head++] = V;
    visited[V] = true;
    while(tail < head) {
        V = Q[tail++];
        printf(" %d", V);
        // 一定要从 0 开始，不能从 V + 1 开始
        for(W = 0; W < G->Nv; W++) {
            if(!visited[W] && G->M[V][W]) {
                Q[head++] = W;
                visited[W] = true;  // 一定要及时标记，不然会重复添加到队列里
            }
        }
    }
}

void DoBFS(MGraph G) {
    Vertex V;
    init(G);
    for(V = 0; V < G->Nv; V++) {
        if(!visited[V]) {
            printf("{");
            BFS(G, V);
            printf(" }\n");
        }
    }
}


int main()
{
    MGraph G;
    G = BiuldMGraph();
    DoDFS(G);
    DoBFS(G);
    return 0;
}

