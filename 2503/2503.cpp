#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

char c;
string eng, fgn;
map<string, string> dict;

int main() {
    while ((c = getchar()) != EOF) {
        if (c == '\n') break;
        eng = c;
        fgn = "";
        while ((c = getchar()) != EOF && c != ' ') eng += c;
        while ((c = getchar()) != EOF && c != '\n') fgn += c;
        dict[fgn] = eng;
    }
    while ((c = getchar()) != EOF) {
        fgn = c;
        while ((c = getchar()) != EOF && c != '\n') fgn += c;
        if (dict.find(fgn) == dict.end()) printf("eh\n");
        else printf("%s\n", dict[fgn].c_str());
    }

    return 0;
}