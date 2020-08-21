#include <cctype>
#include <cstdio>
#include <set>

using namespace std;

const int MAX = 10000;
const int MAXALPHA = 26;

int t, n, cn, ans;
set<char> alphas;
int variables[MAXALPHA];
char expression[MAX];
char cmpress_expression[MAX];

int main() {
    scanf("%d\n", &t);
    while (t--) {
        n = cn = 0, ans = 0;
        for (int i = 0; i < MAXALPHA; ++i) variables[i] = i + 1;
        while ((expression[n] = getchar()) != EOF && expression[n] != '\n') {
            if (expression[n] != ' ') cmpress_expression[cn++] = expression[n];
            ++n;
        }
        expression[n] = '\0';
        alphas.clear();
        for (int i = 0; i < cn; ++i) {
            if (isalpha(cmpress_expression[i])) {
                alphas.insert(cmpress_expression[i]);
                if (i >= 2 && cmpress_expression[i - 1] == '+' && cmpress_expression[i - 2] == '+') {
                    ++variables[cmpress_expression[i] - 'a'];
                    if (i >= 3 && cmpress_expression[i - 3] == '-') ans -= variables[cmpress_expression[i] - 'a'];
                    else ans += variables[cmpress_expression[i] - 'a'];
                } else if (i >= 2 && cmpress_expression[i - 1] == '-' && cmpress_expression[i - 2] == '-') {
                    --variables[cmpress_expression[i] - 'a'];
                    if (i >= 3 && cmpress_expression[i - 3] == '-') ans -= variables[cmpress_expression[i] - 'a'];
                    else ans += variables[cmpress_expression[i] - 'a'];
                } else if (i + 2 < cn && cmpress_expression[i + 1] == '+' && cmpress_expression[i + 2] == '+') {
                    if (i > 0 && cmpress_expression[i - 1] == '-') ans -= variables[cmpress_expression[i] - 'a'];
                    else ans += variables[cmpress_expression[i] - 'a'];
                    ++variables[cmpress_expression[i] - 'a'];
                } else if (i + 2 < cn && cmpress_expression[i + 1] == '-' && cmpress_expression[i + 2] == '-') {
                    if (i > 0 && cmpress_expression[i - 1] == '-') ans -= variables[cmpress_expression[i] - 'a'];
                    else ans += variables[cmpress_expression[i] - 'a'];
                    --variables[cmpress_expression[i] - 'a'];
                } else {
                    if (i > 0 && cmpress_expression[i - 1] == '-') ans -= variables[cmpress_expression[i] - 'a'];
                    else ans += variables[cmpress_expression[i] - 'a'];
                }
            }
        }
        printf("Expression: %s\n", expression);
        printf("value = %d\n", ans);
        for (set<char>::iterator it = alphas.begin(); it != alphas.end(); ++it)
            printf("%c = %d\n", *it, variables[*it - 'a']);
    }

    return 0;
}