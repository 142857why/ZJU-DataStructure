#include <cstdio>
#include <queue>

#define Null -1
using namespace std;

struct Node {
    int l;
    int r;
}T[10];


int BuildTree() {
    // 建树并返回树的根节点
    int s;
    char l, r;
    bool flag[10] = {0};
    scanf("%d", &s);
    getchar();
    for(int i = 0; i < s; i++) {
        scanf("%c %c", &l, &r);
        getchar();
        if(l != '-') {
            T[i].l = l - '0';
            flag[T[i].l] = true;
        } else
            T[i].l = Null;
        if(r != '-') {
            T[i].r = r - '0';
            flag[T[i].r] = true;
        } else
            T[i].r = Null;
    }
    for(int i = 0; i < s; i++)
        if(!flag[i]) return i;
}

void ListLeaves(int r) {
    queue<int> q;
    int t;
    bool flag = false;
    q.push(r);
    while(!q.empty()) {
        t = q.front();
        q.pop();
        if(T[t].l == Null && T[t].r == Null) {
            if(flag)
                printf(" ");
            printf("%d", t);
            flag = true;
            continue;
        }
        if(T[t].l != Null)
            q.push(T[t].l);
        if(T[t].r != Null)
            q.push(T[t].r);
    }
}

int main() {
    int r = BuildTree();
    ListLeaves(r);
    return 0;
}

