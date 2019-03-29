#include <stdio.h>
#include <stdlib.h>

// 直接模拟出栈入栈就好，别想太多。
int main()
{
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int st[M], sc[1010], cur, n, i;
    while(K--) {
        i = 0;
        while(i < N)
            scanf("%d", &sc[i++]);
        i = 0;
        cur = 1;  // 当前入栈元素
        n = 0;  // 栈内元素个数
        int flag = 1;
        while(i < N) {
            while(n && sc[i] == st[n - 1]) {
                i++;
                n--;
            }
            if(n == M) {
                flag = 0;
                break;
            }
            st[n++] = cur++;
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

