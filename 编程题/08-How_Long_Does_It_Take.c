#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define INF 99999999

/* 拓扑排序变形 */


int main()
{
    int i, V, W, l, N, M, L[MAXN][MAXN], S[MAXN], Scnt, cnt, Indegree[MAXN], Earliest[MAXN], ETime;
    scanf("%d %d", &N, &M);
    for(V = 0; V < N; V++)
        for(W = 0; W < N; W++)
            L[V][W] = INF;
    for(i = 0; i < M; i++) {
//        如果这样写，V 和 W 是未读入之前的数
//        printf("%d %d\n", V, W);
//        scanf("%d %d %d", &V, &W, &L[V][W]);
        scanf("%d %d %d", &V, &W, &l);
        L[V][W] = l;
    }
    /* 先遍历图，得到每个顶点的入度，把入度为 0 的点放到栈（队列亦可）里 */
    for(V = 0; V < N; V++) {
        Indegree[V] = 0;
        Earliest[V] = 0;
    }
    for(V = 0; V < N; V++)
        for(W = 0; W < N; W++)
            if(V != W && L[V][W] < INF)
                Indegree[W]++;
    Scnt = 0;
    for(V = 0; V < N; V++)
        if(!Indegree[V])
            S[Scnt++] = V;
    cnt = 0;
    while(Scnt) {
        V = S[--Scnt];
        cnt++;
        for(W = 0; W < N; W++) {
            if(L[V][W] < INF) {
                if(0 == --Indegree[W])
                    S[Scnt++] = W;
                if(Earliest[W] < Earliest[V] + L[V][W])
                    Earliest[W] = Earliest[V] + L[V][W];
            }
        }
    }

    if(cnt == N) {
        ETime = 0;
        for(V = 0; V < N; V++)
            if(ETime < Earliest[V])
                ETime = Earliest[V];
        printf("%d\n", ETime);
    } else
        printf("Impossible\n");
    return 0;
}

