#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100000

/* 各种排序算法 */
/* 1.简单选择排序 */
/* 2.堆排序 */
/* 3.简单插入排序 */
/* 4.希尔排序（用 Sedgwick 增量序列） */
/* 5.冒泡排序 */
/* 6.归并排序（递归版本） */
/* 7.归并排序（非递归版本） */

void Swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* 1.简单选择排序 */
void SimpleSelectionSort(int A[], int N) {
    int i, j, min;
    for(i = 0; i < N - 1; i++) {
        min = i;
        for(j = i + 1; j < N; j++)
            if(A[j] < A[min])
                min = j;
        Swap(&A[i], &A[min]);
    }
}

/* 2.堆排序 */
/* 不断生成最大堆，然后将堆顶元素与堆的最后一个元素交换，再将堆的大小减一，这样只用 O(1) 的额外空间。 */

void PercDown(int A[], int p, int N) {
    /* 将 N 个元素的数组以 A[p] 为根的子堆调整为最大堆 */
    int Parent, Child, X;
    X = A[p];  /* 存放根节点的值 */
    for(Parent = p; Parent * 2 + 1 < N; Parent = Child) {
        Child = 2 * Parent + 1;
        if(Child != N - 1 && A[Child] < A[Child + 1])
            Child++;
        if(X >= A[Child]) break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void HeapSort(int A[], int N) {
    int i;
    /* 建立堆，N/2 - 1 是最后一个有孩子的节点（从 0 开始编号） */
    for(i = N / 2 - 1; i >= 0; i--)
        PercDown(A, i, N);
    for(i = N - 1; i > 0; i--) {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}

/* 3.简单插入排序 */
void InsertionSort(int A[], int N) {
    int P, i, Tmp;
    for(P = 1; P < N; P++) {
        Tmp = A[P];
        for(i = P; i > 0 && A[i - 1] > Tmp; i--)
            A[i] = A[i - 1];
        A[i] = Tmp;
    }
}

/* 4.希尔排序（用 Sedgwick 增量序列） */
void ShellSort(int A[], int N) {
    int Si, D, P, i, Tmp;
    /* 这里只列出小一部分增量 */
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for(Si = 0; Sedgewick[Si] >= N; Si++)
        ;   /* 初始增量不能超过待排序列长度 */
    for(D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {
        for(P = D; P < N; P++) {
            Tmp = A[P];
            for(i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
            A[i] = Tmp;
        }
    }
}

/* 5.冒泡排序 */
void BubbleSort(int A[], int N) {
    int P, i;
    bool flag;
    for(P = N - 1; P >= 0; P--) {
        flag = false;
        for(i = 0; i < P; i++) {
            if(A[i] > A[i + 1]) {
                Swap(&A[i], &A[i + 1]);
                flag = true;
            }
        }
        if(flag == false) break;
    }
}

/* 6.归并排序（递归版本） */
/* L:左边起始位置，R:右边起始位置，RightEnd：右边终点位置 */
void Merge(int A[], int TmpA[], int L, int R, int RightEnd) {
    int LeftEnd, NumElements, Tmp;
    int i;
    LeftEnd = R - 1;
    Tmp = L;
    NumElements = RightEnd - L + 1;
    while(L <= LeftEnd && R <= RightEnd) {
        if(A[L] <= A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while(L <= LeftEnd)
        TmpA[Tmp++] = A[L++];
    while(R <= RightEnd)
        TmpA[Tmp++] = A[R++];
    for(i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd];  // (话说如果把 -- 写在这里会发生什么呀？)
}

void Msort(int A[], int TmpA[], int L, int RightEnd) {
    int Center;
    if(L < RightEnd) {
        Center = (L + RightEnd) / 2;
        Msort(A, TmpA, L, Center);
        Msort(A, TmpA, Center + 1, RightEnd);
        Merge(A, TmpA, L, Center + 1, RightEnd);
    }
}
 /* L:左边起始位置，R:右边起始位置，RightEnd：右边终点位置 */

void MergeSort_Recursive_Version(int A[], int N) {
    int *TmpA;
    TmpA = (int *)malloc(N * sizeof(int));
    if(TmpA != NULL) {
        Msort(A, TmpA, 0, N - 1);
        free(TmpA);
    }
    else printf("空间不足");
}

/* 7.归并排序（非递归版本） */
void Merge1(int A[], int TmpA[], int L, int R, int RightEnd) {
    /* 不再把 TmpA 放回 A */
    int LeftEnd, Tmp;
    LeftEnd = R - 1;
    Tmp = L;
    while(L <= LeftEnd && R <= RightEnd) {
        if(A[L] <= A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while(L <= LeftEnd)
        TmpA[Tmp++] = A[L++];
    while(R <= RightEnd)
        TmpA[Tmp++] = A[R++];
}


void MergePass(int A[], int TmpA[], int N, int length) {
    /* 两两归并相邻有序子列 */
    int i, j;
    for(i = 0; i < N - 2 * length; i += 2 * length)
        Merge1(A, TmpA, i, i + length, i + 2 * length - 1);
    if(i + length < N)  /* 归并最后两个子序列 */
        Merge1(A, TmpA, i, i + length, N - 1);
    else  /* 最后只剩一个子序列 */
        for(j = i; j < N; j++) TmpA[j] = A[j];
}

void MergeSort_Non_recursive_Version(int A[], int N) {
    int length, *TmpA;
    length = 1;
    TmpA = (int *)malloc(N * sizeof(int));
    if(TmpA != NULL) {
        while(length < N) {
            MergePass(A, TmpA, N, length);
            length *= 2;
            MergePass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else printf("空间不足");
}

int main()
{
    int i, N, A[MAXN];
    scanf("%d", &N);
    for(i = 0; i < N; i++)
        scanf("%d", &A[i]);
//    SimpleSelectionSort(A, N);
//    HeapSort(A, N);
//    InsertionSort(A, N);
//    ShellSort(A, N);
//    BubbleSort(A, N);
    MergeSort_Recursive_Version(A, N);
//    MergeSort_Non_recursive_Version(A, N);
    for(i = 0; i < N - 1; i++)
        printf("%d ", A[i]);
    printf("%d\n", A[i]);
    return 0;
}

