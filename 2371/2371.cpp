#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 100005;

int N, K, q;
int arr[MAX];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &arr[i]);
    sort(arr + 1, arr + N + 1);
    getchar();
    while (getchar() != '\n') ;
    scanf("%d", &K);
    for (int i = 1; i <= K; ++i) {
        scanf("%d", &q);
        printf("%d\n", arr[q]);
    }
    return 0;
}