#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 1005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int t;
char c, op;
string first, second, ans, partial[MAX];

string caladd(string num1, string num2, int shift = 0) {
    int n1 = num1.size(), n2 = num2.size();
    string res(max(n1, n2 + shift), '0');
    int i = 0, j = 0, carry = 0;
    while (i < n1 && i < shift) {
        res[i] = num1[i];
        ++i;
    }
    if (n1 < shift) i = shift;
    while (i < n1 || j < n2) {
        res[i] = carry;
        if (i < n1) res[i] += num1[i] - '0';
        if (j < n2) res[i] += num2[j] - '0';
        carry = res[i] >= 10 ? 1 : 0;
        res[i] = res[i] % 10 + '0';
        ++i;
        ++j;
    }
    if (carry == 1) res += '1';
    return res;
}

string calsub(string num1, string num2) {
    int n1 = num1.size(), n2 = num2.size();
    string res(n1, '0');
    int i = 0, j = 0, carry = 0;
    while (i < n1 || j < n2) {
        res[i] = carry;
        if (i < n1) res[i] += num1[i] - '0';
        if (j < n2) res[i] -= num2[j] - '0';
        carry = res[i] < 0 ? -1 : 0;
        if (res[i] < 0) res[i] += 10;
        res[i] += '0';
        ++i;
        ++j;
    }
    while (!res.empty() && res[res.size() - 1] == '0') res.erase(res.size() - 1);
    if (res.empty()) res = "0";
    return res;
}

string calmul(string num1, int num2) {
    if (num2 == 0) return "0";
    int n1 = num1.size();
    string res(n1, '0');
    int i = 0, carry = 0;
    while (i < n1) {
        res[i] = carry;
        res[i] += (num1[i] - '0') * num2;
        carry = res[i] / 10;
        res[i] = res[i] % 10 + '0';
        ++i;
    }
    if (carry != 0) res += (carry + '0');
    return res;
}

int main() {
    scanf("%d\n", &t);
    while (t--) {
        first = second = ans = "";
        while (isdigit(c = getchar())) first += c;
        op = c;
        while (isdigit(c = getchar())) second += c;
        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());
        if (op == '+') ans = caladd(first, second);
        else if (op == '-') ans = calsub(first, second);
        else {
            for (int i = 0; i < second.size(); ++i) {
                partial[i] = calmul(first, second[i] - '0');
                ans = caladd(ans, partial[i], i);
            }
        }
        int outputlen = max(ans.size(), max(first.size(), second.size() + 1));
        for (int i = 0; i < outputlen - first.size(); ++i) putchar(' ');
        for (int i = 0; i < first.size(); ++i) putchar(first[first.size() - 1 - i]);
        putchar('\n');
        for (int i = 0; i < outputlen - second.size() - 1; ++i) putchar(' ');
        putchar(op);
        for (int i = 0; i < second.size(); ++i) putchar(second[second.size() - 1 - i]);
        putchar('\n');
        int dash = second.size() + 1;
        if (op == '*' && second.size() > 1) {
            dash = max(dash, partial[0].size());
            for (int i = 0; i < outputlen - dash; ++i) putchar(' ');
            for (int i = 0; i < dash; ++i) putchar('-');
            putchar('\n');
            for (int i = 0; i < second.size(); ++i) {
                for (int j = 0; j < outputlen - partial[i].size() - i; ++j) putchar(' ');
                for (int j = 0; j < partial[i].size(); ++j) putchar(partial[i][partial[i].size() - 1 - j]);
                putchar('\n');
                dash = partial[second.size() - 1].size();
            }
        }
        dash = max(dash, ans.size());
        for (int i = 0; i < outputlen - dash; ++i) putchar(' ');
        for (int i = 0; i < dash; ++i) putchar('-');
        putchar('\n');
        for (int i = 0; i < outputlen - ans.size(); ++i) putchar(' ');
        for (int i = 0; i < ans.size(); ++i) putchar(ans[ans.size() - 1 - i]);
        putchar('\n');
        putchar('\n');
    }

    return 0;
}