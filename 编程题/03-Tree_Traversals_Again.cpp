#include <cstdio>
#include <stack>
#include <cstring>

#define Null -1
using namespace std;

// 这是笨办法，先建树再遍历。
// 更好的办法是根据前序和中序遍历输出后续遍历。

struct Node {
    int l;
    int r;
}T[31];


int BuildTree() {
    // 建树并返回树的根节点
    int N, X, root, t;
    stack<int> s;
    char act[5];
    // 初始化
    for(int i = 0; i < 31; i++) {
        T[i].l = Null;
        T[i].r = Null;
    }
    scanf("%d", &N);
    scanf("%s %d", act, &root);
    s.push(root);
    t = root;
    scanf("%s", act);
    for(int i = 2; i < 2 * N;) {
        while(strcmp(act, "Push") == 0) {
            scanf("%d", &X);
            s.push(X);
            T[t].l = X;
            t = X;
            if(i < 2 * N) {
                scanf("%s", act);
                i++;
            }
        }
        s.pop();  // 当前节点已经输出，接下来处理右子树或返回到栈顶节点
        if(i < 2 * N) {
            scanf("%s", act);
            i++;
            while(strcmp(act, "Pop") == 0 && i < 2 * N) {
                t = s.top();
                s.pop();
                scanf("%s", act);
                i++;
            }
            if(i == 2 * N) break;
            scanf("%d", &X);
            s.push(X);
            T[t].r = X;
            t = X;
            scanf("%s", act);
            i++;
        }
    }
    return root;
}

bool flag = false;
void PostorderTraversal(int root) {
    if(T[root].l != Null) PostorderTraversal(T[root].l);
    if(T[root].r != Null) PostorderTraversal(T[root].r);
    if(flag) printf(" ");
    printf("%d", root);
    flag = true;
}

int main() {
    int r = BuildTree();
    PostorderTraversal(r);
    return 0;
}

