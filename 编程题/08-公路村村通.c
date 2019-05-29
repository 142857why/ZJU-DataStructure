#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define INF 10000000

/* Prim 算法 */

int N, M, C[MAXN][MAXN];

int FindMinDist(int dist[MAXN]) {
    int MinV, MinDist = INF, V;
    for(V = 0; V < N; V++) {
        if(dist[V] && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if(MinDist < INF)
        return MinV;
    else
        return -1;
}

int Prim() {
    /* 这道题不需要返回最小生成树，只需要返回最小总权重就行了，所以不用储存树 */
    int V, W, TPrice, VCount, dist[MAXN];
    for(V = 0; V < N; V++)
        dist[V] = C[0][V];
    TPrice = 0;
    VCount = 0;
    dist[0] = 0;
    VCount++;
    while(1) {
        V = FindMinDist(dist);
        if(V == -1)
            break;
        VCount++;
        TPrice += dist[V];
        dist[V] = 0;
        for(W = 0; W < N; W++) {
            if(dist[W] && dist[W] > C[V][W])  // 若满足此条件，W 一定为 V 的邻接点，因为之前已经将没有边的权重初始化为 INF
                dist[W] = C[V][W];
        }
    }
    if(VCount == N)
        return TPrice;
    else
        return -1;
}

int main()
{
    int i, a, b, c;
    scanf("%d %d", &N, &M);
    for(a = 0; a < N; a++)
        for(b = 0; b < N; b++)
            C[a][b] = C[b][a] = INF;
    for(i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        a--;b--;
        C[a][b] = C[b][a] = c;
    }
    c = Prim();
    printf("%d\n", c);
    return 0;
}

