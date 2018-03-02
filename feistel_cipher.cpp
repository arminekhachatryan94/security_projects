#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int XOR(int c1, int c2);
string toBinary(int deci);
int toDecimal(string bin);
string * feistel_cipher(string str);
string shiftRight(string str);
string shiftLeft(string str);

int str_len = 0;

int main(){
    string s1 = "1110";
    cout<<"Left Shift: "<<shiftLeft(s1)<<endl;
    cout<<"Right Shift: "<<shiftRight(s1)<<endl;

    char a = '1';
    cout<<"ASCII: "<<(int)a<<endl;
    cout<<"Binary: "<<toBinary((int)a)<<endl;
    cout<<"Decimal: "<<(char)(toDecimal(toBinary((int)a)))<<endl;

    string * str = feistel_cipher("abc");

    for( int i = 0; i < str_len; i++ ){
        cout<<str[i]<<endl;
    }
    for( int i = 0; i < str_len; i++ ){
        cout<<(char)toDecimal(str[i])<<endl;
    }
}


int XOR(int c1, int c2){
    if( c1 && c2 ){
        return 0;
    }
    else if( !c1 && !c2 ){
        return 0;
    }
    else{
        return 1;
    }
}

string toBinary(int deci){
    string bin;
    while(deci > 0 ){
        char temp = (deci % 2) + '0';
        bin = temp + bin;
        deci = deci/2;
    }

    return bin;
}

int toDecimal(string bin){
    int deci = 0;
    for( int i = 0; i < bin.length(); i++ ){
        int temp = bin.length() - i - 1;
        if( bin[temp] == '1' ){
            deci += pow(2, i);
        }
    }
    return deci;
}

string * feistel_cipher( string str ){

    str_len = str.length();

    string * bin;
    bin = new string[str_len];

    cout<<bin[0][0]<<endl;
    string L = str.substr(0, str_len/2);
    string R = str.substr(str_len/2);

    int i = 0;
    for( i = 0; i < L.length(); i++ ){
        bin[i] = toBinary((int)L[i]);
    }

    for( int j = 0; j < R.length(); j++ ){
        bin[i] = toBinary((int)R[j]);
        i++;
    }

    // cout<<"You entered: "<<L<<R<<endl;


    return bin;
}

string shiftRight(string str){
    string ret = str.substr(str.length() - 1, str.length()) + str.substr(0, str.length() - 1);
    return ret;
}

string shiftLeft(string str){
    string ret = str.substr(1, str.length()) + str[0];
    return ret;
}