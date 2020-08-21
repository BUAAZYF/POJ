#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int inline max(int a, int b) {
    return a >= b? a : b;
}

const int MAX = 14;
const int UNIT = 8;
const int SHIFT = 100000000;

string num;
int maxpos, pos, cur, ans[MAX];

int main() {
    for (int i = 0; i < MAX; ++i) ans[i] = 0;
    maxpos = 0;
    while(getline(cin, num) && num != "0") {
        pos = 0;
        for(int i = num.size() - 1; i >= 0; i -= UNIT) {
            cur = 0;
            for(int j = max(0, i - UNIT + 1); j <= i; ++j) cur = cur * 10 + num[j] - '0';
            ans[pos] += cur;
            ans[pos + 1] += ans[pos] / SHIFT;
            ans[pos] %= SHIFT;
            ++pos;
        }
        maxpos = max(maxpos, pos);
    }
    for (int i = 0; i < MAX - 1; ++i) {
        if (ans[i] >= SHIFT) {
            ++ans[i + 1];
            ans[i] %= SHIFT;
        }
    }
    while  (ans[maxpos] == 0) --maxpos;
    if (maxpos >= 0) printf("%d", ans[maxpos]);
    else printf("0");
    for (int i = maxpos - 1; i >= 0; --i) {
        for (int sep = SHIFT / 10; sep >= 10; sep /= 10) {
            if (ans[i] >= sep) break;
            putchar('0');
        }
        printf("%d", ans[i]);
    }
    putchar('\n');
    
    return 0;
}