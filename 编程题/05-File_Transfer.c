#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010

/* 注意集合的相关结构声名 */

typedef int ElementType;
typedef int SetName;  /* 根节点的下标作为集合名称 */
typedef int SetNode;  /* 集合的结点 */
typedef ElementType SetType[MAXN];


SetName Find(SetType S, ElementType X) {
    /* 所有的结点被初始化为-1 */
    if(S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);  /* 路径压缩 */
}

void Union(SetType S, SetNode Root1, SetNode Root2) {
    Root1 = Find(S, Root1);
    Root2 = Find(S, Root2);
    /* 这里要检查 Root1 和 Root2 是不是已经连好了 */
    if(Root1 == Root2)
        return;
    else if(S[Root1] < S[Root2]) {  /* 按秩归并 */
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    } else {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

void Check(SetType S, SetNode c1, SetNode c2) {
    c1 = Find(S, c1);
    c2 = Find(S, c2);
    if(c1 == c2)
        printf("yes\n");
    else
        printf("no\n");
}

int main()
{
    int N, c1, c2, k;
    char a;
    scanf("%d", &N);
    getchar();
    SetType S;
    for(int i = 1; i <= N; i++)
        S[i] = -1;
    scanf("%c", &a);
    while(a != 'S') {
        scanf("%d %d", &c1, &c2);
        getchar();  // 吸收换行符
        if(a == 'I')
            Union(S, c1, c2);
        else
            Check(S, c1, c2);
        scanf("%c", &a);
    }
    k = 0;
    for(int i = 1; i <= N; i++) {
        if(S[i] <= -1)
            k++;
    }
    if(k != 1)
        printf("There are %d components.", k);
    else
        printf("The network is connected.");
    return 0;
}

