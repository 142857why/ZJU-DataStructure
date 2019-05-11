#include <stdio.h>
#include <stdlib.h>

/* 采用邻接表储存图 */
#define MaxVertexNum 10010
typedef int Vertex;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;  // 邻接点下标
    PtrToAdjVNode Next; // 下一个邻接点
};

struct VNode {
    PtrToAdjVNode FirstEdge;  // 边表头指针
}AdjList[MaxVertexNum];  // 从 1 开始

void Initial(int N) {
    for(int i = 0; i <= N; i++) {
        AdjList[i].FirstEdge = NULL;
    }
}

void InsertEdge(int a, int b) {
    struct VNode *A = &(AdjList[a]), *B = &(AdjList[b]);
    PtrToAdjVNode adj1, adj2, t;
    adj1 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    adj1->AdjV = b;
    adj2 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    adj2->AdjV = a;
    adj1->Next = adj2->Next = NULL;
    if(t = A->FirstEdge) {
        while(t->Next)
            t = t->Next;
        t->Next = adj1;
    } else {
        A->FirstEdge = adj1;
    }
    if(t = B->FirstEdge) {
        while(t->Next)
            t = t->Next;
        t->Next = adj2;
    } else {
        B->FirstEdge = adj2;
    }
}

int visited[MaxVertexNum], QHead = 0, QTail = 0;

/* 队列相关 */
Vertex Q[MaxVertexNum];
void Enqueue(Vertex V) {
    Q[QTail++] = V;
}

Vertex Dequque() {
    return Q[QHead++];
}

int QEmpty() {
    return QTail == QHead;
}
/* 清除上一次遍历队列里剩余的结点 */
void Clear(int N) {
    for(int i = 1; i <= N; i++)
        visited[i] = 0;
    QHead = QTail = 0;
}

// 这里用 BFS，返回符合条件的结点个数
int SDS(Vertex V, int N) {
    int count = 1, level = 0, tail, last = V;
    Clear(N);
    Enqueue(V);
    visited[V] = 1;
    while(!QEmpty() && level < 6) {
        V = Dequque();
        PtrToAdjVNode edge = AdjList[V].FirstEdge;
        while(edge) {
            if(!visited[edge->AdjV]) {
                tail = edge->AdjV;
                Enqueue(tail);
                visited[tail] = 1;
                count++;
            }
            edge = edge->Next;
        }
        if(V == last) {
            level++;
            last = tail;
        }
    }
    return count;
}

int main()
{
    int N, M, a, b;
    scanf("%d %d", &N, &M);
    Initial(N);
    for(int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        InsertEdge(a, b);
    }
    for(int i = 1; i <= N; i++) {
        printf("%d: %4.2f%%\n", i, SDS(i, N) * 100.0 / N);
    }
    return 0;
}

