#include <cstdio>
#include <stdlib.h>

// 写得太繁琐了，没有之前那个简洁

struct Node {
    char c;
    int l;
    int r;
};

typedef struct Node * Tree;

Tree BuildTree(int s) {
    char c, l, r;
    scanf("%d", &s);
    Tree T = (Tree)malloc(sizeof(Node) * 10);
    for(int i = 0; i < s; i++) {
        scanf("%c %c %c", &c, &l, &r);
        T[i].c = c;
        T[i].l = (l != '-')?(l - '0'):(-1);  // -1 表示 NULL
        T[i].r = (r != '-')?(r - '0'):(-1);
        // printf("%c%c%c\n", c, l, r);
        //printf("%c%d%d\n", T[i].c, T[i].l, T[i].r);
        getchar();  // 吸收换行符
    }
    return T;
}

int FindHead(Tree T, int s) {
    if(s <= 0)
        return -1;
    bool flag[10] = {0};
    for(int i = 0; i < s; i++) {
        if(T[i].l != -1) flag[T[i].l] = true;
        if(T[i].r != -1) flag[T[i].r] = true;
    }
    for(int i = 0; i < s; i++)
        if(flag[i] == false) return i;
}

bool isCST(Tree A, Tree B, int h1, int h2) {
    // 递归判断
    if(h1 == -1 || h2 == -1) {
        if(h1 == h2)
            return true;
        return false;
    }
    if(A[h1].c == B[h2].c) {
        int al = A[h1].l, ar = A[h1].r, bl = B[h2].l, br = B[h2].r;
        if(al == -1 && bl == -1 && ar == -1 && br == -1)
            return true;
        else if((al == -1 && bl == -1 && ar != -1 && br != -1 && A[ar].c == B[br].c) || (al != -1 && bl != -1 && ar == -1 && br == -1 && A[al].c == B[bl].c)
                 || (al != -1 && bl != -1 && ar != -1 && br != -1 && A[al].c == B[bl].c && A[ar].c == B[br].c))
            return isCST(A, B, al, bl) && isCST(A, B, ar, br);
        else if((al == -1 && br == -1 && ar != -1 && bl != -1 && A[ar].c == B[bl].c) || (al != -1 && br != -1 && ar == -1 && bl == -1 && A[al].c == B[br].c)
                 || (al != -1 && bl != -1 && ar != -1 && br != -1 && A[al].c == B[br].c && A[ar].c == B[bl].c))
            return isCST(A, B, al, br) && isCST(A, B, ar, bl);
        else
            return false;
    } else
        return false;
}

int main() {
    Tree A, B;
    int s1, s2, h1, h2;
    scanf("%d", &s1);
    A = BuildTree(s1);
    scanf("%d", &s2);
    B = BuildTree(s2);
    if(s1 != s2) {
        printf("No\n");
        return 0;
    }
    // 还要找树头
    h1 = FindHead(A, s1);
    h2 = FindHead(B, s2);
    if(isCST(A, B, h1, h2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

