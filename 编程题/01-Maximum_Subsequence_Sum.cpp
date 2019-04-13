#include <cstdio>


using namespace std;


int main() {
    int K, sum = 0, max_sum = 0, f = 0, l, n[10000], c = 0;
    scanf("%d", &K);
    l = K - 1;
    for (int i = 0; i < K; i++)
    {
        scanf("%d", n + i);
        sum += n[i];
        c++;
        if(c == 1 && sum == 0) f = l = i;
        if(sum > max_sum) {
            max_sum = sum;
            l = i;
            f = i - c + 1;
        }
        if(sum < 0) {
            sum = 0;
            c = 0;
        }
    }
    printf("%d %d %d", max_sum, n[f], n[l]);
    return 0;
}

