#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int MAX = 1005;
const int MAXDIGIT = 62;

int t, src, dst, cur;
string num;
char digit[MAXDIGIT];
map<char, int> ch2digit;
int num_base[MAX], num_dst[MAX];

void init_digit() {
    for (int i = 0; i <= 9; ++i) {
        digit[i] = i + '0';
        ch2digit[i + '0'] = i;
    }
    for (int i = 0; i < 26; ++i) {
        digit[i + 10] = i + 'A';
        ch2digit[i + 'A'] = i + 10;
    }
    for (int i = 0; i < 26; ++i) {
        digit[i + 36] = i + 'a';
        ch2digit[i + 'a'] = i + 36;
    }
}

int main() {
    init_digit();
    cin >> t;
    int pos, cur, len, k;
    while (t--) {
        cin >> src >> dst >> num;
        pos = cur = 0;
        len = num.size();
        for (int i = len - 1; i >= 0; --i)
            num_base[len - 1 - i] = ch2digit[num[i]];
        k = 0;
        while (len) {
            for (int i = len - 1; i > 0; --i) {
                num_base[i - 1] += num_base[i] % dst * src;
                num_base[i] /= dst;
            }
            num_dst[k++] = num_base[0] % dst;
            num_base[0] /= dst;
            while (len && !num_base[len - 1]) --len;
        }
        printf("%d %s\n%d ", src, num.c_str(), dst);
        for (int i = k - 1; i >= 0; --i) putchar(digit[num_dst[i]]);
        putchar('\n');
        putchar('\n');
    }

    return 0;
}