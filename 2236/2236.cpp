#include <cstdio>

using namespace std;

const int MAXN = 1005;

struct {
    int x;
    int y;
    int par;
    bool repaired;
} computers[MAXN];

int n, p, q;
long long d;
char op;

int find(int x) {
    while (computers[x].par != x) {
        computers[x].par = find(computers[x].par);
        x = computers[x].par;
    }
    return x;
}

void merge_pair(int x, int y) {
    if (x == y) return;
    x = find(x);
    y = find(y);
    if (x > y)
        computers[x].par = y;
    else
        computers[y].par = x;
}

void merge(int x) {
    if (computers[x].repaired) return;
    computers[x].repaired = true;
    for (int i = 0; i < n; ++i) {
        if (computers[i].repaired && 
        (long long)(computers[x].x - computers[i].x) * (computers[x].x - computers[i].x) + 
        (long long)(computers[x].y - computers[i].y) * (computers[x].y - computers[i].y) <= d)
            merge_pair(x, i);
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%lld", &n, &d);
    d *= d;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &computers[i].x, &computers[i].y);
        computers[i].par = i;
        computers[i].repaired = false;
    }
    getchar();
    while ((op = getchar()) != EOF) {
        if (op == 'O') {
            scanf("%d", &p);
            --p;
            merge(p);
        } else {
            scanf("%d%d", &p, &q);
            --p, --q;
            if (same(p, q))
                printf("SUCCESS\n");
            else
                printf("FAIL\n");
        }
        getchar();
    }

    return 0;
}