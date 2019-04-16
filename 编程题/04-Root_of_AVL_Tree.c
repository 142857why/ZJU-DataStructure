#include <stdio.h>
#include <stdlib.h>


/* 递归地讲新节点插入到树中，如果插入的子树高度不变，则插入完成，否则要进行对应的旋转，更新这些高度。*/

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode {
    ElementType Element;
    AVLTree Left, Right;
    int Height;
};

static int GetHeight(Position P) {
    if(P == NULL)
        return -1;
    else
        return P->Height;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

Position SingleRotateWithLeft(Position K2) {
    Position K1;
    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;
    /* Update heights */
    K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
    K1->Height = Max(GetHeight(K1->Left), GetHeight(K1->Right)) + 1;
    return K1;
}

Position SingleRotateWithRight(Position K2) {
    Position K1;
    K1 = K2->Right;
    K2->Right = K1->Left;
    K1->Left = K2;
    /* Update heights */
    K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
    K1->Height = Max(GetHeight(K1->Left), GetHeight(K1->Right)) + 1;
    return K1;
}

Position DoubleRotateWithLeft(Position K3) {
    K3->Left = SingleRotateWithRight(K3->Left);
    return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3) {
    K3->Right = SingleRotateWithLeft(K3->Right);
    return SingleRotateWithRight(K3);
}

AVLTree Insert(AVLTree T, ElementType X) {
    if(T == NULL) {
        /* Create and return a one-node tree */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    else if( X < T->Element) {
        T->Left = Insert(T->Left, X);
        if(GetHeight(T->Left) - GetHeight(T->Right) == 2) {
            if(X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else {
        T->Right = Insert(T->Right, X);
        if(GetHeight(T->Right) - GetHeight(T->Left) == 2) {
            if(X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T= DoubleRotateWithRight(T);
        }
    }
    /* 更新树高 */
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
    return T;
}

int main()
{
    int N, t;
    AVLTree T = NULL;
    scanf("%d", &N);
    while(N--) {
        scanf("%d", &t);
        T = Insert(T, t);
    }
    printf("%d\n", T->Element);
    return 0;
}

