#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100005;

int n, m, arr[MAX], tmp[MAX], left, right, k;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    while (m--) {
        scanf("%d%d%d", &left, &right, &k);
        memcpy(tmp, arr + left, (right - left + 1) * sizeof(int));
        nth_element(tmp, tmp + k - 1, tmp + right - left + 1);
        printf("%d\n", tmp[k - 1]);
    }

    return 0;
}