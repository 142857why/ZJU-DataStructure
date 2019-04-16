#include <stdio.h>
#include <stdlib.h>

// 这里可以不建树直接比较输入序列，判断是否是同一棵二叉树。
// 本着练习树的相关操作的目的，这里按第一个输入序列建立一棵二叉树，与后面的序列比较。

typedef struct TreeNode *Tree;
struct TreeNode {
    int v;
    Tree left, right;
    int flag;
};

Tree NewNode(int V) {
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}


// 这里有点妙
Tree Insert(Tree T, int V) {
    if(!T) T = NewNode(V);
    else {
        if(V > T->v)
            T->right = Insert(T->right, V);
        else
            T->left = Insert(T->left, V);
    }
    return T;
}

Tree MakeTree(int N) {
    int V;
    Tree T = NULL;
    for(int i = 0; i < N; i++) {
        scanf("%d", &V);
        T = Insert(T, V);
    }
    return T;
}

int check(Tree T, int V) {
    if(T->flag) {
        if(V < T->v)
            return check(T->left, V);
        else if(V > T->v)
            return check(T->right, V);
        else
            return 0;
    } else {
        if(V == T->v) {
            T->flag = 1;
            return 1;
        } else
            return 0;
    }
}

int Judge(Tree T, int N) {
    int V, flag = 0;
    scanf("%d", &V);
    if(V != T->v) flag = 1;
    else T->flag = 1;
    while(--N) {
        // 即使判断不符合后依然要读完后面的数
        scanf("%d", &V);
        if ((!flag) && (!check(T, V))) flag = 1;
    }
    if(flag)
        return 0;
    else
        return 1;
}

void ResetT(Tree T) {
    // （看反了！！！，应该写 T 而不是 !T，后面的话忽略）这里如果写 !T 会导致第一个测试点（最大N，多组合）通不过
    if(T != NULL) {
        T->flag = 0;
        ResetT(T->left);
        ResetT(T->right);
    }
}

void FreeTree(Tree T) {
    if(T) {
        FreeTree(T->left);
        FreeTree(T->right);
        free(T);
    }
}

int main()
{
    int N, L, i;
    Tree T;
    scanf("%d", &N);
    while(N) {
        scanf("%d", &L);
        T = MakeTree(N);
        for(i = 0; i < L; i++) {
            if(Judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            ResetT(T);  // 清除 flag
        }
        FreeTree(T);
        scanf("%d", &N);
    }
    return 0;
}

