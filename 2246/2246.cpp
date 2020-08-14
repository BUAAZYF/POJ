#include <cstdio>
#include <stack>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 26;

int n, row, col, ans;
char ch;
bool isconfict;
int matrow[MAX], matcol[MAX];
Pr top, cur;
stack<Pr> stk;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%c %d %d\n", &ch, &row, &col);
        matrow[ch - 'A'] = row;
        matcol[ch - 'A'] = col;
    }
    while ((ch = getchar()) != EOF) {
        while (!stk.empty()) stk.pop();
        ans = 0;
        isconfict = false;
        do {
            if (ch == '(') {
                stk.push(Pr(-1, -1));
            } else if (ch == ')') {
                cur = stk.top();
                stk.pop();
                while (stk.top().first != -1) {
                    if (stk.top().second != cur.first) {
                        isconfict = true;
                        break;
                    }
                    ans += stk.top().first * stk.top().second * cur.second;
                    cur.first = stk.top().first;
                    stk.pop();
                }
                stk.pop();
                stk.push(cur);
            } else {
                if (matrow[ch - 'A'] == 0) isconfict = true;
                stk.push(Pr(matrow[ch - 'A'], matcol[ch - 'A']));
            }
        }while((ch = getchar()) != EOF && ch != '\n');
        if (isconfict) printf("error\n");
        else printf("%d\n", ans);
    }

    return 0;
}