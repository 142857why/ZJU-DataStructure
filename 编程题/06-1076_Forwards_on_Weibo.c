#include <stdio.h>
#include <stdlib.h>

/* 采用邻接表储存图（有向），按上一题代码改一改就行了 */
#define MaxVertexNum 1010
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

void InsertEdge(int V, int E) {
    // V 被 E 关注了
    PtrToAdjVNode t, edge;
    edge = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    edge->AdjV = E;
    edge->Next = NULL;
    if(t = AdjList[V].FirstEdge) {
        while(t->Next)
            t = t->Next;
        t->Next = edge;
    } else {
        AdjList[V].FirstEdge = edge;
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
int BFS(Vertex V, int N, int L) {
    int count = 0, level = 0, tail, last = V;
    Clear(N);
    Enqueue(V);
    visited[V] = 1;
    while(!QEmpty() && level < L) {
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
    int N, L, K, n, t;
    scanf("%d %d", &N, &L);
    Initial(N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &n);
        while(n--) {
            scanf("%d", &t);
            InsertEdge(t, i);
        }
    }
    scanf("%d", &K);
    while(K--) {
        scanf("%d", &t);
        printf("%d\n", BFS(t, N, L));
    }
    return 0;
}

