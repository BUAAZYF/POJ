#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 10005;

long dp[MAX];

long numDecodings(string s) {
    int n = s.size();
    if (n == 0) return 1;
    if (s.size() == 1 && s[0] == '0') return 0;
    dp[0] = 1;
    if (s[1] == '0') dp[1] = 1;
    else {
        if (s[0] == '1' || s[0] == '2' && s[1] <= '6') dp[1] = 2;
        else dp[1] = 1;
    }
    for (int i = 2; i < n; ++i) {
        if (s[i] == '0') dp[i] = dp[i - 2];
        else {
            dp[i] = dp[i - 1];
            if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') dp[i] += dp[i - 2];
        }
    }
    return dp[n - 1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    string s;
    while (cin >> s) {
        if (s == "0") break;
        printf("%ld\n", numDecodings(s));
    }
    return 0;
}