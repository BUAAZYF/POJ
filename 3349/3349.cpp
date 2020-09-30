#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;

const int MAX = 1000010;
const int MOD = 99991;
const int N = 6;

int n;
int tot, head[MAX], next[MAX];
struct snowflake {
    int a[N];
} table[MAX];

int hash(const snowflake &sf) {
    int sum = 0, mul = 1;
    for (int k = 0; k < N; ++k) {
        sum = (sum + sf.a[k]) % MOD;
        mul = ((ll)mul * sf.a[k]) % MOD;
    }
    return (sum + mul) % MOD;
}

bool issame(const snowflake &A, const snowflake &B) {
    bool same;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            same = true;
            for (int k = 0; k < N; ++k)
                if (A.a[(i + k) % N] != B.a[(j + k) % N]) same = false;
            if (same) return true;
            same = true;
            for (int k = 0; k < N; ++k)
                if (A.a[(i + k) % N] != B.a[(j - k + N) % N]) same = false;
            if (same) return true;
        }
    }
    return false;
}

bool insert(const snowflake &sf) {
    int has = hash(sf);
    for (int i = head[has]; i; i = next[i])
        if (issame(table[i], sf)) return true;

    table[++tot] = sf;
    next[tot] = head[has];
    head[has] = tot;
    return false;
}

int main() {
    tot = 0;
    memset(head, 0, sizeof(head));
    scanf("%d", &n);
    while (n--) {
        snowflake sf;
        for (int k = 0; k < N; k++) scanf("%d", &sf.a[k]);
        if (insert(sf)) {
            printf("Twin snowflakes found.\n");
            return 0;
        }
    }
    printf("No two snowflakes are alike.\n");
}