#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 100005;
const int BUCKET_SIZE = 1000;

int N, Q, l, r, k, a[MAX], b[MAX];
vector<int> bucket[MAX / BUCKET_SIZE];

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        bucket[i / BUCKET_SIZE].push_back(a[i]);
    }
    sort(b, b + N);
    for (int i = 0; i < N / BUCKET_SIZE; ++i) sort(bucket[i].begin(), bucket[i].end());
    int low, high, mid, tl, tr, x, cnt;
    while (Q--) {
        scanf("%d%d%d", &l, &r, &k);
        --l;
        low = -1, high = N - 1;
        while (high - low > 1) {
            mid = (low + high) >> 1;
            x = b[mid];
            tl = l, tr = r, cnt = 0;
            while (tl < tr && tl % BUCKET_SIZE != 0)
                if (a[tl++] <= x) ++cnt;
            while (tl < tr && tr % BUCKET_SIZE != 0)
                if (a[--tr] <= x) ++cnt;
            while (tl < tr) {
                int b = tl / BUCKET_SIZE;
                cnt += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += BUCKET_SIZE;
            }
            if (cnt >= k) high = mid;
            else low = mid;
        }
        printf("%d\n", b[high]);
    }
    return 0;
}