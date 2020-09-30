#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 20;

int K;
char op[MAX];
struct query {
    int id, period, cnt;
} cur;

struct cmp {
    bool operator()(const query& a, const query& b) {
    return a.period * a.cnt > b.period * b.cnt || 
        a.period * a.cnt == b.period * b.cnt && a.id > b.id;
    }
};

priority_queue<query, vector<query>, cmp> pq;

int main() {
    while (scanf("%s", op) && strcmp(op, "#")) {
        scanf("%d%d", &cur.id, &cur.period);
        cur.cnt = 1;
        pq.push(cur);
    }
    scanf("%d", &K);
    while (K--) {
        cur = pq.top();
        printf("%d\n", cur.id);
        pq.pop();
        ++cur.cnt;
        pq.push(cur);
    }

    return 0;
}