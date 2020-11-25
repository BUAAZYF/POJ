#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 5005;

int N, K, M, cur, cnt, decrease[MAX];
char direction;
bool forward[MAX];

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%c", &direction);
        getchar();
        forward[i] = direction == 'B' ? false : true;
    }
    K = M = N;
    for (int k = 1; k <= N; ++k) {
        memset(decrease, 0, sizeof(decrease));
        cur = cnt = 0;
        for (int i = 0; i <= N - k; ++i) {
            cur -= decrease[i];
            if (!forward[i] && cur % 2 == 0 || forward[i] && cur % 2 == 1) {
                ++cnt;
                ++cur;
                ++decrease[i + k];
            }
        }
        bool vaild = true;
        for (int i = N - k + 1; i < N; ++i) {
            cur -= decrease[i];
            if (!forward[i] && cur % 2 == 0 || forward[i] && cur % 2 == 1) {
                vaild = false;
                break;
            }
        }
        if (vaild && cnt < M) {
            M = cnt;
            K = k;
        }
    }
    printf("%d %d\n", K, M);

    return 0;
}