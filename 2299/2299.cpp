#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 500005;

ll n, arr[MAX], ans, tmp[MAX];

void merge_sort(ll low, ll high) {
    if (low == high) return;
    ll mid = (low + high) / 2;
    merge_sort(low, mid);
    merge_sort(mid + 1, high);
    ll i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (arr[i] > arr[j]) {
            ans += mid + 1 - i;
            tmp[k++] = arr[j++];
        } else tmp[k++] = arr[i++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= high) tmp[k++] = arr[j++];
    for (k = 0; low <= high; ++k, ++low) arr[low] = tmp[k];
}

int main() {
    while(scanf("%lld", &n) != EOF && n) {
        for (ll i = 0; i < n; ++i) scanf("%lld", &arr[i]);
        ans = 0;
        merge_sort(0, n - 1);
        printf("%lld\n", ans);
    }

    return 0;
}