#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* */
int x[101], y[101];  // 第 101 个点是 0, 0
bool escape[100], e[100][100], visited[100];

int Sqr(int x) {
    return x * x;
}

bool CanJump(int i, int j, int D) {
    return (Sqr(x[i] - x[j]) + Sqr(y[i] - y[j]) <= Sqr(D));
}

bool CanEscape(int i, double D) {
    return (x[i] + 50 <= D) || (50 - x[i] <= D) || ( y[i] + 50 <= D) || (50 - y[i] <= D);
}

bool DFS(int i, int N) {
    bool ans = escape[i]?true:false;
    visited[i] = true;
    for(int j = 0; !ans && j < N; j++) {
        if(e[i][j] && !visited[j])
            ans = DFS(j, N);
    }
    return ans;
}

bool Save007(int N, int D) {
    for(int i = 0; i < N; i++) {
        // 第一步单独处理
        if(CanJump(101, i, D + 15.0 / 2) && !visited[i] && DFS(i, N))
            return true;
    }
    return false;
}

int main()
{
    int N, D;
    scanf("%d %d", &N, &D);
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    // 遍历，建立鳄鱼之间和鳄鱼和岸的边
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            if(CanJump(i, j, D)) {
                e[i][j] = e[j][i] = true;
            }
        }
        if(CanEscape(i, D))
            escape[i] = true;
    }
    if(Save007(N, D))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

