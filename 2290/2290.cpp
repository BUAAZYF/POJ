#include <cstdio>
#include <cstring>
#include <set>
#include <sstream>
#include <string>

using namespace std;

const int MAX = 55;

int t, m, n, a, b, c, ans_cnt, digit_cnt;
char street_name[MAX];
set<int> inc, exc;
char op;
stringstream ss;
string num;
int cnt[10];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d\n", &t);
    while (t-- > 0) {
        m = 0;
        while ((c = getchar()) != '\n') {
            street_name[m++] = c;
        }
        street_name[m] = '\0';
        scanf("%d\n", &n);
        inc.clear();
        exc.clear();
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            op = getchar();
            if (op == '+' || op == '-') {
                scanf("%d%d%d\n", &a, &b, &c);
                if (op == '+') {
                    while (a <= b) {
                        inc.insert(a);
                        a += c;
                    }
                } else {
                    while (a <= b) {
                        exc.insert(a);
                        a += c;
                    }
                }
            } else {
                ungetc(op, stdin);
                scanf("%d\n", &a);
                inc.insert(a);
            }
        }
        ans_cnt = digit_cnt = 0;
        for (set<int>::iterator it = inc.begin(); it != inc.end(); ++it) {
            if (exc.find(*it) != exc.end()) continue;
            ++ans_cnt;
            ss.clear();
            ss << (*it);
            ss >> num;
            for (int j = 0; j < num.size(); ++j) ++cnt[num[j] - '0'];
        }
        printf("%s\n", street_name);
        printf("%d %s\n", ans_cnt, ans_cnt == 1 ? "address" : "addresses");
        for (int j = 0; j < 10; ++j) {
            digit_cnt += cnt[j];
            printf("Make %d digit %d\n", cnt[j], j);
        }
        printf("In total %d %s\n", digit_cnt, digit_cnt == 1 ? "digit" : "digits");
    }

    return 0;
}