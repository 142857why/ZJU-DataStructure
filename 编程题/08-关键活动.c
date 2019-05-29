#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
#define INF 99999999

/* 关键路径问题，上一题的代码改一改（emmm改很多）就行了 */
/* 第一次拓扑排序计算最早时间，第二次计算最晚时间，机动时间为 0 则为关键路径，注意机动时间的计算方法。 */


void PrintPath(int V, int CPath[MAXN]) {
    /* 递归输出关键路径 */
    if(CPath[V] == -1)
        return;
    PrintPath(CPath[V], CPath);
    printf("%d->%d\n", CPath[V] + 1, V + 1);
}

bool TopSort_Earliest(int N, int L[MAXN][MAXN], int Indegree[MAXN], int Earliest[MAXN]) {
    int S[MAXN], Scnt, cnt, V, W;
    /* 把入度为 0 的点放到栈（队列亦可）里 */
    Scnt = 0;
    for(V = 0; V < N; V++)
        if(!Indegree[V])
            S[Scnt++] = V;
    cnt = 0;
    /* 第一次拓扑排序计算最早时间 */
    while(Scnt) {
        V = S[--Scnt];
        cnt++;
        for(W = 0; W < N; W++) {
            if(L[V][W] < INF) {
                if(0 == --Indegree[W])
                    S[Scnt++] = W;
                if(Earliest[W] < Earliest[V] + L[V][W]) {
                    Earliest[W] = Earliest[V] + L[V][W];
                }
            }
        }
    }
    if(cnt == N) {
        return true;
    } else
        return false;
}

void TopSort_Latest(int N, int L[MAXN][MAXN], int Outdegree[MAXN], int Latest[MAXN], int Earlist[MAXN], int D[MAXN][MAXN], int ETime) {
    int S[MAXN], Scnt, V, W;
    Scnt = 0;
    for(V = 0; V < N; V++) {
        /* 初始化最晚时间 */
        Latest[V] = ETime;
        if(!Outdegree[V])
            S[Scnt++] = V;
    }
    while(Scnt) {
        V = S[--Scnt];
        for(W = 0; W < N; W++) {
            if(L[W][V] < INF) {
                if(0 == --Outdegree[W])
                    S[Scnt++] = W;
                if(Latest[W] > Latest[V] - L[W][V]) {
                    Latest[W] = Latest[V] - L[W][V];
                }
                /* 同时把每条路径的机动时间算出来 */
                D[W][V] = Latest[V] - Earlist[W] - L[W][V];
            }
        }
    }
}

int main()
{
    int i, V, W, N, M, L[MAXN][MAXN], Indegree[MAXN], Outdegree[MAXN], Earliest[MAXN], ETime, Latest[MAXN], D[MAXN][MAXN];
    scanf("%d %d", &N, &M);
    for(V = 0; V < N; V++)
        for(W = 0; W < N; W++) {
            L[V][W] = INF;
            D[V][W] = INF;
        }
    for(i = 0; i < M; i++) {
        scanf("%d %d", &V, &W);
        scanf("%d", &L[--V][--W]);
    }
    /* 先遍历图，得到每个顶点的入度和出度, 初始化最晚时间和最早时间 */
    for(V = 0; V < N; V++) {
        Indegree[V] = 0;
        Outdegree[V] = 0;
        Earliest[V] = 0;
    }
    for(V = 0; V < N; V++)
        for(W = 0; W < N; W++)
            if(V != W && L[V][W] < INF) {
                Indegree[W]++;
                Outdegree[V]++;
            }
    if(TopSort_Earliest(N, L, Indegree, Earliest)) {
        ETime = 0;
        for(V = 0; V < N; V++) {
            if(Earliest[V] > ETime)
                ETime = Earliest[V];
        }
        TopSort_Latest(N, L, Outdegree, Latest, Earliest, D, ETime);
        printf("%d\n", ETime);
        for(V = 0; V < N; V++)
            for(W = N - 1; W >= 0; W--)
                if(D[V][W] == 0)
                    printf("%d->%d\n", V + 1, W + 1);

    } else {
        printf("0\n");
    }
    return 0;
}

