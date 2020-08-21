#include <cstdio>

using namespace std;

const int MAX = 10000;

char c, lastc;
int cnt, norepeatcnt;
char norepeat[MAX];

int main() {
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            continue;
        }
        cnt = 1;
        lastc = c;
        norepeatcnt = 0;
        while ((c = getchar()) != EOF && c != '\n') {
            if (c == lastc) {
                ++cnt;
                if (cnt >= 2 && norepeatcnt > 0) {
                    putchar('1');
                    for (int i = 0; i < norepeatcnt; ++i) {
                        if (norepeat[i] == '1') printf("11");
                        else printf("%c", norepeat[i]);
                    }
                    putchar('1');
                    norepeatcnt = 0;
                }
                if (cnt == 9) {
                    printf("9%c", c);
                    cnt = 0;
                }
            } else {
                if (cnt == 1) norepeat[norepeatcnt++] = lastc;
                else printf("%d%c", cnt, lastc);
                lastc = c;
                cnt = 1;
            }
        }
        if (cnt == 1) norepeat[norepeatcnt++] = lastc;
        if (norepeatcnt > 0) {
            putchar('1');
            for (int i = 0; i < norepeatcnt; ++i) {
                if (norepeat[i] == '1') printf("11");
                else printf("%c", norepeat[i]);
            }
            putchar('1');
        }
        if (cnt > 1) printf("%d%c", cnt, lastc);
        putchar('\n');
    }

    return 0;
}