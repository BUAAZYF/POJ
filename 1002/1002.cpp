#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int MAXC = 50;

int n, num;
char cur[MAXC];
map<int, int> cnt;
map<char, int> digit;

void init() {
    digit.clear();
    digit['A'] = 2;
    digit['B'] = 2;
    digit['C'] = 2;
    digit['D'] = 3;
    digit['E'] = 3;
    digit['F'] = 3;
    digit['G'] = 4;
    digit['H'] = 4;
    digit['I'] = 4;
    digit['J'] = 5;
    digit['K'] = 5;
    digit['L'] = 5;
    digit['M'] = 6;
    digit['N'] = 6;
    digit['O'] = 6;
    digit['P'] = 7;
    digit['R'] = 7;
    digit['S'] = 7;
    digit['T'] = 8;
    digit['U'] = 8;
    digit['V'] = 8;
    digit['W'] = 9;
    digit['X'] = 9;
    digit['Y'] = 9;
}

int main() {
    init();
    cnt.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", cur);
        num = 0;
        for (int k = 0; k < strlen(cur); ++k) {
            if (isdigit(cur[k])) num = num * 10 + (cur[k] - '0');
            else if (isupper(cur[k])) num = num * 10 + digit[cur[k]];
        }
        if (cnt.find(num) == cnt.end()) cnt[num] = 0;
        ++cnt[num];
    }
    int ans = 0;
    for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second <= 1) continue;
        ++ans;
        num = it->first;
        for (int i = 0, mul = 1000000; i < 7; ++i, mul /= 10) {
            printf("%d", num / mul);
            num %= mul;
            if (i == 2) putchar('-');
        }
        printf(" %d\n", it->second);
    }
    if (ans == 0) printf("No duplicates.\n");

    return 0;
}