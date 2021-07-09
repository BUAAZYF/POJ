#include <cstdio>

using namespace std;

int N;

int main() {
    while (scanf("%d", &N) != EOF && N) {
        printf("%s\n", N <= 2 ? "Alice" : "Bob");
    }
    return 0;
}