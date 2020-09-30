#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 19;

ll n;
int rank;
ll cnt[MAX], acc[MAX];

void printtree(ll n, ll rank) {
    int idx, left_rank = 0;
    for (int i = 0; i < rank; ++i) {
        if (n > cnt[i] * cnt[rank - 1 - i])
            n -= cnt[i] * cnt[rank - 1 - i];
        else {
            left_rank = i;
            break;
        }
    }
    if (left_rank) {
        printf("(");
        printtree(n / cnt[rank - 1 - left_rank] + (n % cnt[rank - 1 - left_rank] == 0 ? 0 : 1), left_rank);
        printf(")");
    }
    printf("X");
    if (rank - 1 - left_rank) {
        printf("(");
        printtree(n % cnt[rank - 1 - left_rank] == 0 ? cnt[rank - 1 - left_rank] : n % cnt[rank - 1 - left_rank], rank - 1 - left_rank);
        printf(")");
    }
}

int main() {
    cnt[0] = cnt[1] = acc[1] = 1;
    cnt[2] = 2;
    acc[2] = 3;
    for (int i = 3; i < MAX; ++i) {
        cnt[i] = 0;
        acc[i] = acc[i - 1];
        for (int j = 0; j < i; ++j) cnt[i] += cnt[j] * cnt[i - 1 - j];
        acc[i] += cnt[i];
    }
    while (scanf("%lld", &n) != EOF && n) {
        if (n == 1) {
            printf("X\n");
            continue;
        }
        rank = MAX - 1;
        for (int i = 0; i < MAX; ++i) {
            if (acc[i] >= n) {
                rank = i;
                break;
            }
        }
        n -= acc[rank - 1];
        printtree(n, rank);
        printf("\n");
    }

    return 0;
}