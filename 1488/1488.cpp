#include <cstdio>

using namespace std;

const int MAX = 26;

char c;
int quote_cnt;

int main() {
    freopen("in.txt", "r", stdin);
    quote_cnt = 0;
    while((c = getchar()) != EOF){
        if (c == '\"') {
            ++quote_cnt;
            if (quote_cnt % 2 == 1) printf("``");
            else printf("''");
        } else putchar(c);
    }
    return 0;
}