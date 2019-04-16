#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 先排序，然后按照中序遍历的特点与二叉树的特性递归找出根节点, 将节点存入 nodes 中
int nums[1000], nodes[11][500], nodes_c[11] = {0};

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}


void CBT(int l, int r, int level) {
    int N, h, left, last, half_last, root;  // h 为满层树高, l 为 h + 1节点数, last 为 h + 1全满时应有的节点数
    if(l > r)
        return;
    N = r - l + 1;
    h = (int)(log(N + 1)/log(2)); // 始终大于等于1
    last = (int)pow(2, h);
    half_last = last / 2;
    left = N - last + 1;
    root = l + ((left > half_last)?half_last:left) + last / 2 - 1;
    nodes[level][nodes_c[level]++] = nums[root];
    CBT(l, root - 1, level + 1);
    CBT(root + 1, r, level + 1);
}

int main()
{
    int N, flag = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", &nums[i]);
    // 排序
    qsort(nums, N, sizeof(int), cmp);
    CBT(0, N - 1, 0);
    for(int i = 0; nodes_c[i] != 0; i++) {
        for(int j = 0; j < nodes_c[i]; j++) {
            if(flag)
                printf(" ");
            else
                flag = 1;
            printf("%d", nodes[i][j]);
        }
    }
    printf("\n");
    return 0;
}

