#include<bits/stdc++.h>

using namespace std;
int used[260];

int main(){

    for(int i = 0; i < 260; i++){
        used[i] = 0;
    }
    string s = "", str;
    ifstream infile;
    infile.open("Text.txt");
    while(getline(infile, str)){
        s += str;
    }
    int n = s.size();
    for(int i = 0; i < n; i++){
        int x = s[i];
        used[x]++;
    }
    for(int i = 0; i < 260; i++){
        if(used[i]){
            cout << char(i) << " = " << fixed << setprecision(4) << (1.0*used[i])/n << endl;
        }
    }
    
    return 0;
}