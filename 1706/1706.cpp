#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

char c;
string line, cur;
int num;
vector<string> paragraphs;
map<int, string> refs;
map<int, int> orders;
map<int, int> rev_orders;

bool isemptyline(string& line) {
    for (int i = 0; i < line.size(); ++i)
        if (line[i] != ' ') return false;
    return true;
}

void process(string& cur) {
    if (cur[0] == '[') {
        num = 0;
        for (int i = 1; i < cur.size(); ++i) {
            if (cur[i] == ']') break;
            num = num * 10 + cur[i] - '0';
        }
        refs[num] = cur;
    } else {
        paragraphs.push_back(cur);
        int i = 1;
        while (i < cur.size()) {
            if (cur[i] == '[') {
                ++i;
                num = 0;
                while (cur[i] != ']') {
                    num = num * 10 + cur[i] - '0';
                    ++i;
                }
                if (orders.find(num) == orders.end()) {
                    orders[num] = orders.size();
                    rev_orders[orders.size()] = num;
                }
            }
            ++i;
        }
    }
    cur = "";
}

int main() {
    orders.clear();
    rev_orders.clear();
    string line = cur = "";
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (isemptyline(line)) {
                if (cur != "") process(cur);
            } else cur += line + "\n";
            line = "";
        } else line += c;
    }
    if (line != "") cur += line + "\n";
    if (cur != "") process(cur);
    for (int i = 0; i < paragraphs.size(); ++i) {
        for (int j = 0; j < paragraphs[i].size(); ++j) {
            putchar(paragraphs[i][j]);
            if (paragraphs[i][j] == '[') {
                ++j;
                num = 0;
                while (paragraphs[i][j] != ']') {
                    num = num * 10 + paragraphs[i][j] - '0';
                    ++j;
                }
                printf("%d", orders[num]);
                putchar(']');
            }
        }
        putchar('\n');
    }
    for (int i = 1; i <= rev_orders.size(); ++i) {
        string ref = refs[rev_orders[i]];
        for (int j = 0; j < ref.size(); ++j) {
            putchar(ref[j]);
            if (ref[j] == '[') {
                ++j;
                num = 0;
                while (ref[j] != ']') {
                    num = num * 10 + ref[j] - '0';
                    ++j;
                }
                printf("%d", orders[num]);
                putchar(']');
            }
        }
        putchar('\n');
    }

    return 0;
}