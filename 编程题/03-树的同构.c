#include <stdio.h>
#include <stdlib.h>


#define Null -1
#define Tree int
#define ElementType char
#define MaxTree 10

struct TreeNode {
    ElementType element;
    Tree left;
    Tree right;
}T1[MaxTree], T2[MaxTree];

Tree biuldTree(struct TreeNode T[]) {
    int N;
    scanf("%d", &N);
    getchar();  // 吸收换行符
    if(N == 0) return Null;
    Tree root;
    char cl, cr;
    int track[MaxTree] = {0};
    for(int i = 0; i < N; i++) {
        scanf("%c %c %c", &(T[i].element), &cl, &cr);
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

int isomorphic(Tree R1, Tree R2) {
    if(R1 == Null && R2 == Null) return 1;
    if((R1 != Null && R2 == Null) || (R1 == Null && R2 != Null)) return 0;
    if(T1[R1].element != T2[R2].element) return 0;
    if(T1[R1].left == Null && T2[R2].left == Null)
        return isomorphic(T1[R1].right, T2[R2].right);
    if(T1[R1].left != Null && T2[R2].left != Null && T1[T1[R1].left].element == T2[T2[R2].left].element)
        return isomorphic(T1[R1].left, T2[R2].left) && isomorphic(T1[R1].right, T2[R2].right);
    else
        return isomorphic(T1[R1].left, T2[R2].right) && isomorphic(T1[R1].right, T2[R2].left);
}

int main()
{
    Tree R1, R2;
    R1 = biuldTree(T1);
    R2 = biuldTree(T2);
    printf("%s\n", isomorphic(R1, R2)?"Yes":"No");
    return 0;
}

