#include<bits/stdc++.h>

using namespace std;

string bits;
int base[20];
int p[20];
int cnt = 0;

void build(int n){
    int l = 0, i = 1;
    while(l < n){
        if(__builtin_popcount(i) != 1){
            base[i] = bits[l++] - '0';
        } else {
            base[i] = 0;
        }
        i++;
    }
    vector<int> p;
    p.push_back(0);
    int cnt = 1, ind = 1;
    cout << i <<  ' ' << n << endl;
    while(ind < i - n){
        string out1 = "", out2 = "";
        out1 += "p" + to_string(ind++) + ": ";
        int sum = 0;
        for(int j = 1; j < i; j++){
            if(j%(1<<cnt) >= (1<<(cnt-1))){
                sum ^= base[j];
                out1 += "b" + to_string(j);
                out2 += to_string(base[j]);
                if(j != i-1) out1 += "+", out2 += "+";
                else out1 += " = ", out2 += " = ";
            }
        }
        cout << out1 + out2 + to_string(sum) + ".\n";
        p.push_back(sum);
        cnt++;
    }
    p[0] = 0, l = 1;
    for(int j = 1; j < i; j++){
        if(__builtin_popcount(j) == 1) base[j] = p[l++];
        p[0] ^= base[j];
    }
    l = 0;
    for(int j = 0; j < i; j++){
        if(j == 0 || __builtin_popcount(j) == 1){
            cout << p[l++] << ' ';
        }
        else cout << base[j] << ' ';
    }
    cout << endl;
}

int main(){
    bits = "1011";
    int n = bits.size();
    build(n);
}