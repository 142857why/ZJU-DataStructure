#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MINDATA -1

/* 利用最小堆构建赫夫曼树，求出最小字节数，再验证每种方案是否符合前缀码。 */

/* 最大N&M，code长度等于63 通不过，有点BUG */
/* 找不出来，要疯了 */


/* 结构声名开始 */

typedef struct HNode *Heap;
typedef struct TreeNode *HTree;
typedef Heap MinHeap;

struct HNode {
    HTree *Data;
    int Size;
    int Capacity;
};

struct TreeNode {
    int Weight;
    HTree Left, Right;
};

int Hash(char c);
void Exchange(HTree *a, HTree *b);
void Adjust(MinHeap H, int pos);
void Insert(MinHeap H, HTree T);
HTree NewNode(int weight);
HTree GetMin(MinHeap H);
MinHeap CreateMinHeap(int capacity, int data[]);
HTree CreateHTreeByHeap(MinHeap H);
int CountWPL(HTree H, int depth);
bool TestPrefixCode(HTree T, char code[], int count);  // 测试学生提供的方案是否符合前缀码
void FreeTree(HTree T);

/* 结构声名结束 */

int Hash(char c) {
    // 将字符映射成 0-62 的数字
    if('0' <= c && c <= '9')
        return c - '0';
    else if('a' <= c && c <= 'z')
        return c - 'a' + 10;
    else if('A' <= c && c <= 'Z')
        return c - 'A' + 36;
    else
        return 62;
}

void Exchange(HTree *a, HTree *b) {
    HTree t = *a;
    *a = *b;
    *b = t;
}

HTree NewNode(int weight) {
    HTree New = (HTree)malloc(sizeof(struct TreeNode));
    New->Left = New->Right = NULL;
    New->Weight = weight;
    return New;
}

void Adjust(MinHeap H, int pos) {
    if(pos * 2 > H->Size)
        return;
    else if(pos * 2 == H->Size) {
        // 此时 pos 只有一个左儿子
        if(H->Data[pos]->Weight > H->Data[H->Size]->Weight) {
            // 交换
            Exchange(&(H->Data[pos]), &(H->Data[H->Size]));
        }
    } else {
        // 有两个儿子

        // 递归版本
        int minp = (H->Data[pos * 2]->Weight <= H->Data[pos * 2 + 1]->Weight)?(pos * 2):(pos * 2 + 1);
        if(H->Data[pos]->Weight > H->Data[minp]->Weight) {
            // 这里一定要将整个节点一起交换，不能单纯交换 Weight
            Exchange(&(H->Data[pos]), &(H->Data[minp]));
            Adjust(H, minp);
        }

    }
}

void Insert(MinHeap H, HTree T) {
    int i = ++H->Size;
    while(T->Weight < H->Data[i / 2]->Weight) {
        H->Data[i] = H->Data[i / 2];
        i = i / 2;
    }
    H->Data[i] = T;
}

HTree GetMin(MinHeap H) {
    HTree min = H->Data[1];
    H->Data[1] = H->Data[H->Size--];
    Adjust(H, 1);
    return min;
}

MinHeap CreateMinHeap(int capacity, int f[]) {
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (HTree *)malloc((capacity + 1) * sizeof(struct TreeNode));
    for(int i = 1, j = 0; i <= capacity; j++) {
        if(f[j])
            H->Data[i++] = NewNode(f[j]);
    }
    H->Size = capacity;
    H->Capacity = capacity;
    H->Data[0] = NewNode(MINDATA);
    for(int i = capacity / 2; i > 0; i--)
        Adjust(H, i);
    return H;
}

HTree CreateHTreeByHeap(MinHeap H) {
    HTree T;

    for(int i = 0; H->Size > 1; i++) {
        T = (HTree)malloc(sizeof(struct TreeNode));
        T->Left = GetMin(H);
        T->Right = GetMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    T = GetMin(H);
    return T;
}

int CountWPL(HTree T, int depth) {
    if(T->Left == NULL && T->Right == NULL)
        return depth * T->Weight;
    else
        return CountWPL(T->Left, depth + 1) + CountWPL(T->Right, depth + 1);
}

bool TestPrefixCode(HTree T, char code[], int count) {
    HTree cur, pre;
    cur = T;
    for(int i = 0; i < count; i++) {
        pre = cur;
        if(code[i] == '0') {
            if(!pre->Left)
                pre->Left = NewNode(0);
            cur = pre->Left;
        } else {
            if(!pre->Right)
                pre->Right = NewNode(0);
            cur = pre->Right;
        }
    }
    if(cur->Left || cur->Right || cur->Weight)
        return false;
    cur->Weight = 1;  // 标记为已存在的叶子，防止两点重合。
    return true;
}

void FreeTree(HTree T) {
    if(T->Left)
        FreeTree(T->Left);
    if(T->Right)
        FreeTree(T->Right);
    free(T);
}

int main()
{
    int N, M, t, f[63] = {0}, WPL, count, TestWPL;
    char c, code[63];
    bool flag;
    scanf("%d", &N);
    getchar();
    for(int i = 0; i < N; i++) {
        scanf("%c", &c);
        t = Hash(c);
        scanf("%d", &f[t]);
        getchar();
    }
    MinHeap H = CreateMinHeap(N, f);
    HTree T = CreateHTreeByHeap(H);
    WPL = CountWPL(T, 0);
    // 释放空间
    free(H);
    FreeTree(T);
    scanf("%d", &M);
    getchar();  //吸收换行符
    while(M--) {
        T = NewNode(0);  // 测试前缀码时不考虑权重，仅用来标记已存在的叶子节点
        TestWPL = 0;
        flag = true;
        for(int i = 0; i < N; i++) {
            count = 0;
            scanf("%c", &c);
            t = Hash(c);
            getchar();  // 吸收空格
            /* 如果已经判断不是最优解，就不再进行判断，但是还要把剩余的数据读完 */
            while((c = getchar()) != '\n') {
                if(flag) {
                    if(count < N - 1)
                        // 正确的编码最大长度为 N-1
                        code[count++] = c;
                    else
                        flag = false;
                }
            }
            if(flag) {
                TestWPL += f[t] * count;
                flag = TestPrefixCode(T, code, count);  // 这一项要放在前面
                if(TestWPL > WPL)
                    flag = false;
            }
        }
        FreeTree(T);
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}

