#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const int MAXC = 22;
const int MAX = 1002;
const string SEP = string(60, '-');

string name, op, second_name;
struct member {
    string name;
    member* leader;
    vector<member*> subs;
    member(string _name):name(_name), leader(NULL) {subs.clear();}
};
member *admin, *root, *cur;
map<string, member*> member_ptr;

void promote(string& name) {
    member* leader = member_ptr[name]->leader;
    int idx = 0;
    for (int i = 0; i < leader->subs.size(); ++i) {
        if (leader->subs[i] == member_ptr[name]) {
            idx = i;
            break;
        }
    }
    if (!leader->subs[idx]->subs.empty()) {
        leader->subs[idx]->name = leader->subs[idx]->subs[0]->name;
        promote(leader->subs[idx]->subs[0]->name);
        member_ptr[leader->subs[idx]->name] = leader->subs[idx];
    } else {
        leader->subs.erase(leader->subs.begin() + idx);
    }
}

void printorg(member* node, int level = 0) {
    for (int i = 0; i < level; ++i) putchar('+');
    printf("%s\n", node->name.c_str());
    for (int i = 0; i < node->subs.size(); ++i)
        printorg(node->subs[i], level + 1);
}

int main() {
    member_ptr.clear();
    admin = new member("admin");
    cin >> name;
    root = new member(name);
    admin->subs.push_back(root);
    root->leader = admin;
    member_ptr[name] = root;
    while (cin >> name) {
        if (name == "print") {
            printorg(root);
            printf("%s\n", SEP.c_str());
        }
        else if (name == "fire") {
            cin >> name;
            promote(name);
            member_ptr.erase(name);
        } else {
            cin >> op >> second_name;
            cur = new member(second_name);
            member_ptr[second_name] = cur;
            member_ptr[second_name]->leader = member_ptr[name];
            member_ptr[name]->subs.push_back(cur);
        }
    }
    return 0;
}