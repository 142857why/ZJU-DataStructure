#include <stdio.h>
#include <stdlib.h>


/* 用邻接矩阵建立有权图，然后用 floyd 算法求出两个动物之间最短咒语长度。*/
/* 对每一种动物遍历，找出每一种动物变到其他动物所许的最长咒语长度，选择其中最长咒语长度最短的那种动物。 */
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;

/* 图节点定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

/* 边界点定义 */
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

MGraph CreateGraph(int VertexNum) {
    /* 初始化一个有 VertexNum 个顶点但没有边的图 */
    Vertex V, W;
    MGraph G;

    G = (MGraph)malloc(sizeof(struct GNode));
    G->Nv = VertexNum;
    G->Ne = 0;
    /* 初始化临界矩阵 */
    for(V = 0; V < G->Nv; V++)
        for(W = 0; W < G->Nv; W++)
            G->G[V][W] = INFINITY;
    return G;
}

void InsertEdge(MGraph G, Edge E) {
    G->G[E->V1][E->V2] = E->Weight;
    G->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph() {
    MGraph G;
    Edge E;
    int Nv, i;

    scanf("%d", &Nv);
    G = CreateGraph(Nv);
    scanf("%d", &G->Ne);
    E = (Edge)malloc(sizeof(struct ENode));
    for(i = 0; i < G->Ne; i++) {
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        E->V1--;
        E->V2--;
        InsertEdge(G, E);
    }
    return G;
}

void Floyd(MGraph G, WeightType D[][MaxVertexNum]) {
    Vertex i, j ,k;

    for(i = 0; i < G->Nv; i++)
        for(j = 0; j < G->Nv; j++)
            D[i][j] = G->G[i][j];
    for(k = 0; k < G->Nv; k++)
        for(i = 0; i < G->Nv; i++)
            for(j = 0; j < G->Nv; j++)
                if(D[i][j] > D[i][k] + D[k][j])
                    D[i][j] = D[i][k] + D[k][j];
//            if( i ==j && D[i][j] < 0) // 发现负值圈，本题不会出现
//                return false;
}

int FindMax(int *x, int n, Vertex V) {
    /* 返回最大值 */
    int i, max;

    max = 0;
    for(i = 0; i < n; i++)
        /* 排除对角元 */
        if(V != i && max < x[i]) {
            max = x[i];
        }
    return max;
}

void FindAnimal(MGraph G) {
    Vertex V, MinV;
    int Min, t;
    WeightType D[MaxVertexNum][MaxVertexNum];  // 记录两点之间最短距离

    Floyd(G, D);
    Min = INFINITY;
    for(V = 0; V < G->Nv; V++) {
        t = FindMax(D[V], G->Nv, V);
        if(t == INFINITY) {
            /* 只带一直动物无法全部变出来 */
            printf("0\n");
            return;
        }
        if(t < Min) {
            Min = t;
            MinV = V;
        }
    }
    printf("%d %d\n", MinV + 1, Min);
}

int main()
{
    MGraph G = BuildGraph();
    FindAnimal(G);
    return 0;
}

