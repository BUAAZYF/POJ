#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 5005;

short inline max(short a, short b) {
    return a >= b ? a : b;
}

int n;
string s;
short dp[MAX][MAX];

int main() {
    memset(dp, 0, MAX * MAX * sizeof(short));
    cin >> n >> s;
    for (int i = 0; i < n; ++i) dp[i][i] = 1;
    for (int i = 0; i < n - 1; ++i) dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
    for (int step = 2; step < n; ++step) {
        for (int i = 0; i < n - step; ++i) {
            if (s[i] == s[i + step])
                dp[i][i + step] = dp[i + 1][i + step - 1] + 2;
            else
                dp[i][i + step] = max(dp[i + 1][i + step], dp[i][i + step - 1]);
        }
    }
    cout << n - dp[0][n - 1] << endl;

    return 0;
}