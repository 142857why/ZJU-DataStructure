#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    int next;
};

struct Node list[100010];
const int HEAD = 100009; // 头结点
int len = 0;

int reverse(int pos, int k) {
    // 把 pos 之后的 n 个结点逆序, 返回逆序后的尾结点
    int pre, cur, next, rear;
    rear = list[pos].next;
    pre = rear;
    cur = list[pre].next;
    while(--k) {
        next = list[cur].next;
        list[cur].next = pre;
        pre = cur;
        cur = next;
    }
    list[pos].next = pre;
    list[rear].next = cur;
    return rear;
}

int main()
{
    int n, k, adr, i;
    scanf("%d %d %d", &(list[HEAD].next), &n, &k);
    for(i = 0; i < n; i++) {
        scanf("%d", &adr);
        scanf("%d %d", &(list[adr].data), &(list[adr].next));
    }
    adr = list[HEAD].next;
    while(adr != -1) {
        len++;
        adr = list[adr].next;
    }
    adr = HEAD;
    i = 0;
    while(len - i >= k) {
        adr = reverse(adr, k);
        i += k;
    }
    adr = list[HEAD].next;
    i = 0;
    while(++i < len) {
        printf("%05d %d %05d\n", adr, list[adr].data, list[adr].next);
        adr = list[adr].next;
    }
    printf("%05d %d -1\n", adr, list[adr].data);
    return 0;
}

