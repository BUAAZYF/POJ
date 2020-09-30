#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 30005;

int M, N, len;
long arr[MAX];
vector<long> minheap, maxheap;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; ++i) scanf("%ld", &arr[i]);
    int idx = 0;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &len);
        while (idx < len) {
            maxheap.push_back(arr[idx]);
            ++idx;
            push_heap(maxheap.begin(), maxheap.end());
        }
        while (!minheap.empty() && (-minheap.front() < maxheap.front() || maxheap.size() < i)) {
            pop_heap(minheap.begin(), minheap.end());
            maxheap.push_back(-minheap[minheap.size() - 1]);
            minheap.pop_back();
            push_heap(maxheap.begin(), maxheap.end());
        }
        while (maxheap.size() > i) {
            pop_heap(maxheap.begin(), maxheap.end());
            minheap.push_back(-maxheap[maxheap.size() - 1]);
            maxheap.pop_back();
            push_heap(minheap.begin(), minheap.end());
        }
        printf("%ld\n", maxheap.front());
    }

    return 0;
}