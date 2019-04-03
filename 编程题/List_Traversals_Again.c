#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define Null 0
#define Tree int
#define MaxTree 31


// 这里是先构建树，再遍历，比较麻烦。
// 简单的方法是不构建树，直接根据前序遍历和中序遍历输出后续遍历
struct TreeNode {
    Tree left;
    Tree right;
}T[MaxTree];

int N;
static int count = 0;

Tree biuldTree(struct TreeNode T[]) {
    Tree root, cur, t, stack[MaxTree];
    int sh = 0, i = 1;
    scanf("%d", &N);
    if(N == 0) return Null;
    char str[5];
    scanf("%s %d", str, &root);
    cur = root;
    stack[sh++] = cur;
    scanf("%s", str);
    i++;
    while(i < 2 * N) {
        while(strlen(str) == 4 && i < 2 * N) {
            scanf("%d", &t);
            T[cur].left = t;
            stack[sh++] = t;
            cur = t;
            scanf("%s", str);
            i++;
        }
        cur = stack[--sh];
        scanf("%s", str);
        i++;
        if(strlen(str) == 4 && i < 2 * N) {
            scanf("%d", &t);
            T[cur].right = t;
            stack[sh++] = t;
            cur = t;
            scanf("%s", str);
            i++;
        }
    }
    return root;
}

void postTraversal(Tree R) {
    if(R == Null) return;
    postTraversal(T[R].left);
    postTraversal(T[R].right);
    printf("%d", R);
    count++;
    if(count != N) printf(" ");
    return;
}

int main()
{
    Tree R;
    R = biuldTree(T);
    postTraversal(R);
    return 0;
}

