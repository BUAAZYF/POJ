#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int MAX = 505;

int n, cnt;
string pre, cur, s;
map<string, int> tops;
struct node {
    string name;
    map<string, node*> nxt;
    node(string _name) : name(_name) { nxt.clear(); }
} * trees[MAX], *root;

void dfs(node* root, int level) {
    for (int i = 0; i < level; ++i) putchar(' ');
    printf("%s\n", root->name.c_str());
    for (map<string, node*>::iterator it = root->nxt.begin(); it != root->nxt.end(); ++it)
        dfs(it->second, level + 1);
}

int main() {
    scanf("%d", &n);
    tops.clear();
    cnt = 0;
    while (n--) {
        cin >> s;
        root = NULL;
        cur = "";
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '\\') {
                if (root == NULL) {
                    if (tops.find(cur) == tops.end()) {
                        trees[cnt] = new node(cur);
                        tops[cur] = cnt;
                        ++cnt;
                    }
                    root = trees[tops[cur]];
                } else {
                    if (root->nxt.find(cur) == root->nxt.end())
                        root->nxt[cur] = new node(cur);
                    root = root->nxt[cur];
                }
                cur = "";
            } else
                cur += s[i];
        }
        if (cur != "") {
            if (root == NULL) {
                if (tops.find(cur) == tops.end()) {
                    trees[cnt] = new node(cur);
                    tops[cur] = cnt;
                    ++cnt;
                }
                root = trees[tops[cur]];
            } else {
                if (root->nxt.find(cur) == root->nxt.end())
                    root->nxt[cur] = new node(cur);
                root = root->nxt[cur];
                cur = "";
            }
        }
    }
    for (map<string, int>::iterator it = tops.begin(); it != tops.end(); ++it)
        dfs(trees[it->second], 0);

    return 0;
}