#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 28;

int sz;
string s, level[MAX];
struct node {
    char c;
    node *left, *right;
    node(char _c) : c(_c), left(NULL), right(NULL) {}
};

void insertnode(node* root, char c) {
    node *p = root, *cur = new node(c);
    while (p) {
        if (c > p->c) {
            if (!p->right) {
                p->right = cur;
                break;
            }
            p = p->right;
        } else {
            if (!p->left) {
                p->left = cur;
                break;
            }
            p = p->left;
        }
    }
}

void dfs(node* root) {
    putchar(root->c);
    if (root->left) dfs(root->left);
    if (root->right) dfs(root->right);
    delete root;
}

int main() {
    while (cin >> s && s != "$") {
        sz = 0;
        level[sz++] = s;
        while (cin >> level[sz++] && level[sz - 1] != "*" && level[sz - 1] != "$") ;
        --sz;
        node* root = new node(level[--sz][0]);
        for (int i = sz - 1; i >= 0; --i) {
            for (int j = 0; j < level[i].size(); ++j) insertnode(root, level[i][j]);
        }
        dfs(root);
        putchar('\n');
    }

    return 0;
}