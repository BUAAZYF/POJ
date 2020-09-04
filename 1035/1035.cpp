#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX = 10005;
const int MAXC = 16;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline abs(int a) {
    return a >= 0 ? a : -a;
}

int dlen, clen;
bool correct;
char cur[MAXC], dict[MAX][MAXC];
int dict_len[MAX];
vector<int> ans;

int trans(const char* src, const char* dst) {
    int diff = 0;
    if (strlen(src) == strlen(dst)) {
        while (*src != '\0') {
            if (*src != *dst) ++diff;
            ++src, ++dst;
        }
    }
    else {
        if (strlen(src) > strlen(dst)) swap(src, dst);
        while (*src != '\0' && *dst != '\0') {
            if (*src != *dst) {
                ++diff;
                ++dst;
            } else ++src, ++dst;
        }
        if (*dst != '\0') ++diff;
    }
    return diff;
}

int main() {
    dlen = 0;
    while(scanf("%s", &dict[dlen]) != EOF && strcmp(dict[dlen], "#")) {
        dict_len[dlen] = strlen(dict[dlen]);
        ++dlen;
    }
    while(scanf("%s", &cur) != EOF && strcmp(cur, "#")) {
        printf("%s", cur);
        clen = strlen(cur);
        correct = false;
        ans.clear();
        for (int i = 0; i < dlen; ++i) {
            if (abs(dict_len[i] - clen) <= 1) {
                int diff = trans(cur, dict[i]);
                if (diff == 0) {
                    correct = true;
                    break;
                } else if (diff == 1) ans.push_back(i);
            }
        }
        if (correct) printf(" is correct");
        else {
            printf(":");
            for (int i = 0;i < ans.size(); ++i) printf(" %s", dict[ans[i]]);
        }
        printf("\n");
    }

    return 0;
}