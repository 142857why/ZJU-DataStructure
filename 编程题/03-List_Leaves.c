#include <stdio.h>
#include <stdlib.h>


#define Null -1
#define Tree int
#define MaxTree 10

struct TreeNode {
    Tree left;
    Tree right;
}T[MaxTree];

Tree biuldTree(struct TreeNode T[]) {
    int N;
    scanf("%d", &N);
    getchar();  // 吸收换行符
    if(N == 0) return Null;
    Tree root;
    char cl, cr;
    int track[MaxTree] = {0};
    for(int i = 0; i < N; i++) {
        scanf("%c %c", &cl, &cr);
        getchar();
        if(cl == '-')
            T[i].left = Null;
        else {
            T[i].left = cl - '0';
            track[T[i].left] = 1;
        }
        if(cr == '-')
            T[i].right = Null;
        else {
            T[i].right = cr - '0';
            track[T[i].right] = 1;
        }
    }
    for(root = 0; root < N; root++)
        if(track[root] != 1) break;
    return root;
}


void listLeaves(Tree R) {
    int q[MaxTree];
    int head = 0, rear = 0, flag = 1;
    Tree t = R;
    while(t != Null && head <= rear) {
        if(T[t].left == Null && T[t].right == Null) {
            if(!flag)
                printf(" ");
            else
                flag = 0;
            printf("%d", t);
        } else {
            if(T[t].left != Null)
                q[rear++] = T[t].left;
            if(T[t].right != Null)
                q[rear++] = T[t].right;
        }
        t = q[head++];
    }
    printf("\n");
}


int main()
{
    Tree R;
    R = biuldTree(T);
    listLeaves(R);
    return 0;
}

