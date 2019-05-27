#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 102
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;

/* 还有两个测试点未通过，改天再看看 */

/* 图节点定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;
    WeightType G[MaxVertexNum][MaxVertexNum];  // 此题只有 INFINITY 和 1 ，表示是否可以一次跳到
};
typedef PtrToGNode MGraph;

int X[MaxVertexNum], Y[MaxVertexNum];
bool escape[MaxVertexNum] = {false};

MGraph CreateGraph(int VertexNum) {
    /* 初始化一个有 VertexNum 个顶点但没有边的图 */
    Vertex V, W;
    MGraph G;

    G = (MGraph)malloc(sizeof(struct GNode));
    G->Nv = VertexNum + 1;
    /* 初始化邻接矩阵 */
    for(V = 0; V < G->Nv; V++)
        for(W = 0; W < G->Nv; W++)
            G->G[V][W] = INFINITY;
    return G;
}

void InsertEdge(MGraph G, Vertex V1, Vertex V2) {
    G->G[V1][V2] = G->G[V2][V1]  = 1;
}

bool NotInIsleAndBank(Vertex V) {
    /* 不在岸上或者岛上 */
    return X[V] > -50 && X[V] < 50 && Y[V] > -50 && Y[V] < 50 && ((X[V] * X[V] + Y[V] * Y[V]) > (7.5 * 7.5));
}

bool CanJump(Vertex V1, Vertex V2, double D) {
    double d1 = (X[V1] - X[V2]), d2 = (Y[V1] - Y[V2]);
    return ( d1 * d1 + d2 * d2 ) <= (D * D);  // 这里emmmm，取等号和不去等号总有一个点(还不同)过不了（不知道为啥）...
}

bool CanEscape(Vertex V, double D) {
    return (X[V] - D <= -50) || (X[V] + D >= 50) || (Y[V] - D <= -50) || (Y[V] + D >= 50);
}

MGraph BuildGraph() {
    MGraph G;
    int Nv, D;
    Vertex i, j, start;

    scanf("%d %d", &Nv, &D);
    G = CreateGraph(Nv);
    for(i = 0; i < G->Nv - 1; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    start = i;
    X[start] = 0;
    Y[start] = 0;
    /* 建立边 */
    for(i = 0; i < G->Nv - 1; i++) {
        if(!NotInIsleAndBank(i))
            continue;
        G->G[i][i] = INFINITY;
        for(j = i + 1; j < G->Nv - 1; j++) {
            if(CanJump(i, j, D))
                InsertEdge(G, i, j);
        }
        // 起始点和终点要特殊处理，终点单独判断，不放图里。
        if(CanJump(start, i, D + 7.5))  // 注意 15 是直径
            InsertEdge(G, start, i);
        if(CanEscape(i, D))
            escape[i] = true;
    }
    if(CanEscape(start, D + 7.5))
        escape[start] = true;
    return G;
}

Vertex FindMinDist(MGraph G, bool collected[], int dist[]) {
    Vertex i, Min = -1;
    int MinDist = INFINITY;
    for(i = 0; i < G->Nv; i++)
        if(!collected[i] && MinDist > dist[i]) {
            MinDist = dist[i];
            Min = i;
        }
    return Min;
}

void Dijkstra(MGraph G, int dist[], int path[], Vertex S) {
    Vertex V, W;
    bool collected[MaxVertexNum] = {false};
    for(V = 0; V < G->Nv; V++) {
        dist[V] = G->G[S][V];
        if(dist[V] == 1)
            path[V] = S;
        else
            path[V] = -1;
    }
    collected[S] = true;
    dist[S] = 0;
    while(1) {
        V = FindMinDist(G, collected, dist);
        if(V == -1)
            break;
        collected[V] = true;
        /* 对图中的每个节点更新距离 */
        for(W = 0; W < G->Nv; W++) {
            /* 若 W 是 V 的邻接点且未收录，是否存在到 W 的更短的距离 */
            if(!collected[W] && G->G[V][W] == 1 && dist[V] + 1 < dist[W]) {
                dist[W] = dist[V] + 1;
                path[W] = V;
            }
        }
    }
}

void Escape(MGraph G) {
    int dist[MaxVertexNum], count, MinDist;
    Vertex path[MaxVertexNum], i, Min, start, PathStack[MaxVertexNum];
    start = G->Nv - 1;
    Dijkstra(G, dist, path, start);
    /* 在可以到岸的节点中找路径最短的节点 */
    Min = -1;
    MinDist = INFINITY;
    for(i = 0; i < G->Nv; i++) {
        if(escape[i] && dist[i] < MinDist) {
            Min = i;
            MinDist = dist[i];
        }
    }
    if(Min == -1)
        /* 到不了岸 */
        printf("0\n");
    else {
        count = 0;
        i = Min;
        // 这个路径可以之间递归输出
        while(path[i] != -1) {
            PathStack[count++] = i;
            i = path[i];
        }
        printf("%d\n", count + 1);
        /* 跳过起点 */
        for(count -= 1; count >= 0; count--)
            printf("%d %d\n", X[PathStack[count]], Y[PathStack[count]]);
    }
}

int main()
{
    MGraph G = BuildGraph();
    Escape(G);
    return 0;
}
