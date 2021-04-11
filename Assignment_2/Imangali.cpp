#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {
    // system("cls");

    string s;
    string str = "";

    ifstream infile;
    infile.open("Text.txt");

    while(getline(infile, s)){
        // cout << s << '\n';
        str += s;
    }

    
    float total = 0;

    for(int i = 0 ; i < str.length(); i++){
        
        int pos = 0 , counter = 0;

        if(str.find(str[i]) >= i){
            while(true){
                if(str.find(str[i], pos) < str.length()){
                    pos = str.find(str[i], pos) + 1;
                    counter++;
                }else{
                    cout << str[i] << " - " <<  (float)counter/(float)str.length() << '\n';
                    total += (float)counter/(float)str.length();
                    break;
                }
            }
        }
    }
    
    cout << "total = " << total;

    return 1;
}