#include <cstdio>
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> numbers;

void init_numbers() {
    numbers["zero"] = 0;
    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;
    numbers["four"] = 4;
    numbers["five"] = 5;
    numbers["six"] = 6;
    numbers["seven"] = 7;
    numbers["eight"] = 8;
    numbers["nine"] = 9;
    numbers["ten"] = 10;
    numbers["eleven"] = 11;
    numbers["twelve"] = 12;
    numbers["thirteen"] = 13;
    numbers["fourteen"] = 14;
    numbers["fifteen"] = 15;
    numbers["sixteen"] = 16;
    numbers["seventeen"] = 17;
    numbers["eighteen"] = 18;
    numbers["nineteen"] = 19;
    numbers["twenty"] = 20;
    numbers["thirty"] = 30;
    numbers["forty"] = 40;
    numbers["fifty"] = 50;
    numbers["sixty"] = 60;
    numbers["seventy"] = 70;
    numbers["eighty"] = 80;
    numbers["ninety"] = 90;
}

int ans, cur_ans, sign;
char sep;
string cur;

int main() {
    init_numbers();
    while(cin >> cur) {
        cur_ans = ans = 0;
        sign = 1;
        if (cur == "negative") sign = -1;
        else cur_ans = numbers[cur];
        while ((sep = getchar()) != EOF && sep != '\n'){
            cin >> cur;
            if (numbers.find(cur) != numbers.end()) cur_ans += numbers[cur];
            else if (cur == "hundred") cur_ans *= 100;
            else if (cur == "thousand") {
                ans += cur_ans * 1000;
                cur_ans = 0;
            }
            else if (cur == "million"){
                ans += cur_ans * 1000000;
                cur_ans = 0;
            }
        }
        ans += cur_ans;
        cout << ans * sign << endl;
    }
    
    return 0;
}