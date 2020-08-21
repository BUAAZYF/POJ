#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

const int MAX = 205;

int T, m, n;
string A, B, C;
bool dp[MAX][MAX];

int main() {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> A >> B >> C;
        if (A.size() + B.size() != C.size()) {
            cout << "Data set " << t << ": no\n";
            continue;
        }
        memset(dp, false, sizeof(dp));
        m = A.size();
        n = B.size();
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (i > 0 && A[i - 1] == C[i + j - 1]) dp[i][j] |= dp[i - 1][j];
                if (j > 0 && B[j - 1] == C[i + j - 1]) dp[i][j] |= dp[i][j - 1];
            }
        }
        cout << "Data set " << t << ": " << (dp[m][n] ? "yes" : "no") << "\n";
    }

    return 0;
}