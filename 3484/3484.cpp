#include <cstdio>
#include <iostream>

using namespace std;

const int MAX = 20005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, X[MAX], Y[MAX], Z[MAX], low, high, mid, cnt;
string buffer;

int main() {
    while (true) {
        cnt = N = 0;
        low = high = 1;
        buffer = "";
        while (getline(cin, buffer) && buffer == "")
            ;
        do {
            if (sscanf(buffer.c_str(), "%d%d%d", &X[N], &Y[N], &Z[N]) == EOF) break;
            cnt += (Y[N] - X[N]) / Z[N] + 1;
            high = max(high, Y[N]);
            ++N;
        } while (getline(cin, buffer) && buffer != "");
        if (N == 0) break;
        if (cnt % 2 == 0) {
            printf("no corruption\n");
            continue;
        }
        while (low < high) {
            mid = (high - low) / 2 + low;
            cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (mid < X[i]) continue;
                cnt += (min(mid, Y[i]) - X[i]) / Z[i] + 1;
            }
            if (cnt & 1) high = mid;
            else low = mid + 1;
        }
        cnt = 0;
        for (int i = 0; i < N; ++i) {
            if (low < X[i] || low > Y[i]) continue;
            if ((low - X[i]) % Z[i] == 0) ++cnt;
        }
        printf("%d %d\n", low, cnt);
    }

    return 0;
}