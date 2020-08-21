#include <cstdio>
#include <cctype>

using namespace std;

const int ALPHASET = 26;

char c, decryption[ALPHASET];

int main() {
    for(int i = 0;i < ALPHASET; ++i) decryption[i] = getchar();
    getchar();
    while((c = getchar()) != EOF){
        if (isalpha(c))
            putchar(decryption[tolower(c) - 'a'] + (isupper(c) ? 'A' - 'a' : 0));
        else putchar(c);
    }

    return 0;
}