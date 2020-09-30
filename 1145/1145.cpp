#include <cctype>
#include <cstdio>

using namespace std;

int pathsum;
bool ans;

bool dfs(int len) {
    char c;
    while ((c = getchar()) == ' ' || c == '\n') ;
    if (c == ')') return false;
    int val = 0, sign = 1;
    if (c == '-') sign = -1;
    else val = c - '0';
    while ((c = getchar()) && isdigit(c)) val = val * 10 + c - '0';
    val *= sign;
    if (c != '(') while (getchar() != '(') ;
    bool has_child = false;
    has_child |= dfs(len + val);
    while (getchar() != '(') ;
    has_child |= dfs(len + val);
    while (getchar() != ')') ;
    if (!has_child) ans |= (pathsum == len + val);
    return true;
}

int main() {
    while (scanf("%d", &pathsum) != EOF) {
        ans = false;
        while (getchar() != '(') ;
        dfs(0);
        printf("%s\n", ans ? "yes" : "no");
    }

    return 0;
}