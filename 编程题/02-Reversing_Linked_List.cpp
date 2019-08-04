#include <cstdio>

struct Node{
    int data;
    int next;
}L[100001];

void Read(int N) {
    int cur;
    while(N--) {
        scanf("%d", &cur);
        scanf("%d %d", &(L[cur].data), &(L[cur].next));
    }
}

int DoReverse(int head, int K) {
    int pre, cur, next, newh;
    pre = L[head].next;
    newh = pre;
    cur = L[pre].next;
    while(--K) {
        next = L[cur].next;
        L[cur].next = pre;
        pre = cur;
        cur = next;
    }
    L[newh].next = cur;
    L[head].next = pre;
    return newh;
}

void Reverse(int K) {
    int head = 100000, tmp;
    while(1) {
        tmp = head;
        for(int i = 0; i < K; i++) {
            tmp = L[tmp].next;
            if(tmp == -1) break;
        }
        if(tmp == -1) break;
        head = DoReverse(head, K);
    }
}

void Output() {
    int head = L[100000].next;
    while(L[head].next != -1) {
        printf("%05d %d %05d\n", head, L[head].data, L[head].next);
        head = L[head].next;
    }
    printf("%05d %d -1", head, L[head].data);
}

int main() {
    int N, K;
    scanf("%d %d %d", &(L[100000].next), &N, &K);
    Read(N);
    Reverse(K);
    Output();
    return 0;
}

