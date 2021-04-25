#include<bits/stdc++.h>

using namespace std;

string compressed;
string probs[10000];
string answer;
int step = 1;

void printChar(char c){
    if(c == ' ') cout << "Space";
    else if(c == '\n') cout << "Endline";
    else cout << c;
}

void decompress(int v, string cur, int pos){
    if(probs[v].size() == 1){
        answer += probs[v][0];
        cout << "Symbol: " << cur << ' ' << probs[v][0] << "\n\n";
        decompress(1, "", pos);
        return;
    }
    
    if(pos == compressed.size()) return;
    
    if(v == 1){
        cout << "Step " << step++ << ":\n";
    }else if(v != 1){
        cout << cur << ": Node " << v << ": (" << cur << ") ";
        for(int i = 0; i < probs[v].size(); i++){
            printChar(probs[v][i]);
            if(i != probs[v].size()-1) cout << ", ";
        }
        cout << "\n";
    }

    if(compressed[pos] == '0'){
        decompress(v*2, cur + "0", pos+1);
    } else {
        decompress(v*2+1, cur + "1", pos+1);
    }
}

int main(){

    compressed = "";
    string textchar;

    ifstream infile;
    infile.open("txt/encoded.txt");

    while(getline(infile, textchar)){
        compressed += textchar;
    }
    infile.close();


    //reading from decompres.txt file
    string textline, textsymbol;

    infile.open("txt/algorithm.txt");

    while(getline(infile, textline)){
        string prob = "";
        int id;
        for(char i : textline){
            if(i == ','){
                id = stoi(textsymbol);
                textsymbol = "";
            }else if(i == ' '){
                prob += textsymbol;
                textsymbol = "";
            }else{
                textsymbol += i;
            }
        }
        probs[id] = prob;
    }

    decompress(1, "", 0);
    cout << "Decompressed : " << answer << endl;
}