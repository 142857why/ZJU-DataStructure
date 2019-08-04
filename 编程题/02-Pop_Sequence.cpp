#include <cstdio>


int s[1000], p;

int main() {
    int M, N, K, t, x;
    bool flag;
    scanf("%d %d %d", &M, &N, &K);
    while(K--) {
        flag = true;
        p = 0;
        x = 1;
        for(int i = 0; i < N; i++) {
            scanf("%d", &t);
            // 小于 t 的元素都要入栈
            if(flag) {
                while(x <= t)
                    s[p++] = x++;
                if(p > M) flag = false;
                if(p <= 0 || s[--p] != t) flag = false;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

