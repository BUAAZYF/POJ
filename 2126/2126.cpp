#include <cstdio>

using namespace std;

int n, a, b, c;

int main() {
    scanf("%d", &n);
    if (n < 2) printf("YES\n");
    else if (n > 2) printf("NO\n");
    else {
        scanf("%d%d%d", &a, &b, &c);
        if (b * b - 4 * a * c < 0) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}