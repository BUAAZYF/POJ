#include<iostream>
#include<string>

using namespace std;

int main(){
    int n;
    cin >> n;
    string a, b, sum;
    while(n-- > 0){
        cin >> a >> b;
        sum = "";
        size_t m = min(a.size(), b.size());
        int carry = 0, cur;
        for(size_t i = 0; i < m; ++i){
            cur = a[i] - '0' + b[i] - '0' + carry;
            carry = cur >= 10 ? 1 : 0;
            sum += char(cur % 10 + '0');
        }
        if(a.size() > b.size()) b = a;
        for(size_t i = m; i < b.size(); ++i){
            cur = b[i] - '0' + carry;
            carry = cur >= 10 ? 1 : 0;
            sum += char(cur % 10 + '0');
        }
        if(carry == 1) sum += '1';
        size_t prezero = 0;
        while(prezero < sum.size() and sum[prezero] == '0') ++prezero;
        cout << sum.substr(prezero) << endl;
    }

    return 0;
}