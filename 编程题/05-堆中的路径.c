#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int
#define MinData -10001

/* 注意堆的相关结构声名 */

typedef struct HNode *Heap;
struct HNode {
    ElementType *Data;
    int Size;
    int Capacity;
};

typedef Heap MinHeap;

MinHeap CreateMinHeap(int MaxSize) {
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));  // 注意这里
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MinData;  // 哨兵
    return H;
}

bool IsFull(MinHeap H) {
    return (H->Size == H->Capacity);
}

bool Insert(MinHeap H, ElementType X) {
    if(IsFull(H)) return false;
    int i = ++(H->Size);
    while(X < H->Data[i / 2]) {
        H->Data[i] = H->Data[i / 2];
        i /= 2;
    }
    H->Data[i] = X;
    return true;
}

int main()
{
    int N, M, t;
    scanf("%d%d", &N, &M);
    MinHeap H = CreateMinHeap(N);
    while(N--) {
        scanf("%d", &t);
        Insert(H, t);
    }
    while(M--) {
        scanf("%d", &t);
        bool flag = false;
        for(; t > 0; t /= 2) {
            if(flag)
                printf(" ");
            else
                flag = true;
            printf("%d", H->Data[t]);
        }
        printf("\n");
    }
    return 0;
}

