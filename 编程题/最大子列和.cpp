#include <cstdio>


using namespace std;


int main() {
    int K, sum = 0, t, max_sum = 0;
    scanf("%d", &K);
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &t);
        sum += t;
        if(sum > max_sum) max_sum = sum;
        if(sum < 0) sum = 0;
    }
    printf("%d", max_sum);
    return 0;
}

