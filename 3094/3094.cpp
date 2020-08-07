#include <cstdio>

using namespace std;

int main() {
    char c;
    int idx, ans;
    while((c = getchar()) != EOF && c != '#'){
        ans = c - 'A' + 1;
        idx = 2;
        while ((c = getchar()) != EOF && c != '\n'){
            if (c != ' ') ans += (c - 'A' + 1) * idx;
            ++idx;
        }
        printf("%d\n", ans);
    }

    return 0;
}