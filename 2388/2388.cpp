#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 10005;

int N, milk[MAX];

int main() {
    scanf("%d", &N);
    for (int i = 0;i < N; ++i) scanf("%d", &milk[i]);
    nth_element(milk, milk + N / 2, milk + N);
    printf("%d\n", milk[N / 2]);

    return 0;
}