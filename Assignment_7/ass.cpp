#include<bits/stdc++.h>

using namespace std;

string blocks[10000];
int sz = 0;
string joined;

void div_eight(string s){
    int l = 0, r = 0;
    while(r < s.size()){
        for(int i = 0; i < 8; i++){
            if(r+i >= s.size()) break;
            blocks[l] += s[r+i];
        }
        l++;
        r += 8;
        sz++;
    }
}

void div_16(string s){
    int l = 0, r = 0;
    while(r < s.size()){
        for(int i = 0; i < 16; i++){
            if(r+i >= s.size()) break;
            blocks[l] += s[r+i];
        }
        l++;
        r += 16;
        sz++;
    }
}

void ErrorGen(){
    set<int> st;
    while(st.size() < 0.4*sz){
        int x = rand()%sz;
        st.insert(x);
    }
    cout << "Blocks with errors: ";
    for(auto i : st){
        set<int> sp;
        while(sp.size() < /*0.3*blocks[i].size()*/ 1){
            int x = rand()%blocks[i].size();
            sp.insert(x);
        }
        for(auto j : sp){
            if(blocks[i][j] == '0') blocks[i][j] = '1';
            else blocks[i][j] = '0';
        }
        cout << "b" << i+1 << ": " << blocks[i] << ", ";
    }
    cout << endl << endl;
}

void HammingDecode(string t){
    int n = t.size();
    bool ok = true;
    string decoded = "";
    for(int i = 0; i < n; i++){
        if(i && __builtin_popcount(i) != 1) decoded += t[i];
        cout << t[i] << ' ';
    }
    cout << ":" << endl << "Checking parity bits:\n";
    vector<int> errpar;
    map<int, int> mp;
    for(int i = 1; i < 5; i++){
        string out1 = "", out2 = "";
        out1 += "p" + to_string(i) + ": ";
        int res = 0;
        vector<int> pos;
        for(int j = 1; j < n; j++){
            if(__builtin_popcount(j) == 1) continue;
            if(j%(1<<i) >= (1<<(i-1))){
                out1 += "b" + to_string(j);
                out2 += t[j];
                res ^= (t[j]-'0');
                pos.push_back(j);
                if(j != n-1) out1 += "+", out2 += "+";
                else out1 += " = ", out2 += " = ";
            }
        }
        if((1<<(i-1)) >= n) break;
        cout << out1 + out2 + to_string(res) << ' ';
        if(res != t[(1<<(i-1))] -'0'){
            cout << "incorrect.\n";
            ok = false;
            errpar.push_back(i);
            for(int j = 0; j < pos.size(); j++){
                if(mp[pos[j]] != -1) mp[pos[j]]++;
            }
            mp[(1<<(i-1))]++;
        } else {
            cout << "correct.\n";
            for(int j = 0; j < pos.size(); j++){
                mp[pos[j]] = -1;
            }
            mp[(1<<(i-1))] = -1;
        }
    }
    pair<int, int> ans = {-1, -1};
    for(auto i : mp){
        if(i.second > ans.second) ans = i;
    }
    if(ok){
        cout << "No error.\n";
    } else {
        cout << "Error in position: " << ans.first << endl;
        int l = 0;
        for(int i = 1; i < n; i++){
            if(__builtin_popcount(ans.first) == 1) break;
            if(i == ans.first) {
                decoded[l] = (1 - (decoded[l] - '0')) + '0';
                break;
            }
            if(__builtin_popcount(i) != 1) l++;
        }
    }
    cout << "Decoded bitstring: " << decoded << "\n\n";
    joined += decoded;
}

int main(){
    string s = "";
    string textchar;

    ifstream infile;
    infile.open("txt/hamming-encoded.txt");

    while(getline(infile, textchar)){
        s += textchar;
    }
    infile.close();

    cout << "Original file: " << s << "\n";
    div_eight(s);
    cout << "Initial blocks: ";
    for(int i = 0; i < sz; i++){
        cout << "b" <<i+1 << ": " << blocks[i];
        if(i != sz-1) cout << ", ";
    }
    cout << "\n\n";
    ErrorGen();
    for(int i = 0; i < sz; i++){
        HammingDecode(blocks[i]);
    }
    cout << joined << endl;

    ofstream MyFile("txt/encoded.txt");
    MyFile << joined;
    MyFile.close();
}