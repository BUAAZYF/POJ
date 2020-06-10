#include <cmath>
#include <cstdio>
#include <queue>

using namespace std;

int n, weight;
float cur;
priority_queue<float> pq;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &weight);
        pq.push(weight);
    }
    while (pq.size() > 1) {
        cur = pq.top();
        pq.pop();
        cur *= pq.top();
        pq.pop();
        cur = 2 * sqrt(cur);
        pq.push(cur);
    }

    printf("%.3f\n", pq.top());

    return 0;
}