#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500
#define INF 10000000

/* 就是个 Dijkstra，只是比较条件增加了一个 */

int FindMinDist(int G[MAXN][MAXN], int dist[MAXN], int pri[MAXN], bool collected[MAXN], int N) {
    int i, minl = INF, minp = INF, mini = -1;
    for(i = 0; i < N; i++) {
        if(!collected[i] && (minl > dist[i] || (minl == dist[i] && minp > pri[i]))) {
            minl = dist[i];
            minp = pri[i];
            mini = i;
        }
    }
    return mini;
}

void Dijkstra(int L[MAXN][MAXN], int dist[MAXN], int P[MAXN][MAXN], int pri[MAXN], int S, int N) {
    int i, j;
    bool collected[MAXN];
    for(i = 0; i < N; i++) {
        dist[i] = L[S][i];
        pri[i] = P[S][i];
        collected[i] = false;
    }

    dist[S] = 0;
    pri[S] = 0;
    collected[S] = true;

    while(1) {
        i = FindMinDist(L, dist, pri, collected, N);
        if(i == -1)
            break;
        collected[i] = true;
        for(j = 0; j < N; j++) {
            if(!collected[j] && L[i][j] < INF) {
                if(dist[i] + L[i][j] < dist[j] || (dist[i] + L[i][j] == dist[j] && pri[i] + P[i][j] < pri[j])) {
                    dist[j] = dist[i] + L[i][j];
                    pri[j] = pri[i] + P[i][j];
                }
            }
        }
    }
}

int main()
{
    int a, b, l, p, i, j, N, M, S, D, P[MAXN][MAXN], dist[MAXN], pri[MAXN], L[MAXN][MAXN];
    scanf("%d %d %d %d", &N, &M, &S, &D);
    for(i = 0; i < N; i++)
        for(j = i; j < N; j++) {
            L[i][j] = L[j][i] = INF;
            P[i][j] = P[j][i] = INF;
        }
    for(i = 0; i < M; i++) {
        scanf("%d %d %d %d", &a, &b, &l, &p);
        L[a][b] = L[b][a] = l;
        P[a][b] = P[b][a] = p;
    }
    Dijkstra(L, dist, P, pri, S, N);
    printf("%d %d\n", dist[D], pri[D]);
    return 0;
}

