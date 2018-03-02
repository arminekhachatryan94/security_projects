#include <iostream>
#include <string>
#include <cmath>

using namespace std;

char XOR(char c1, char c2);
string toBinary(char deci);
char toDecimal(string bin);
string shiftRight(string str);
string shiftLeft(string str);

string encrypt(string str);
string decrypt(string str);

int str_len = 0;

int main(){
    string s1 = "abcd";
    encrypt(s1);
}

char XOR(char c1, char c2){
    if( c1 == '1' && c2 == '1' ){
        return '0';
    }
    else if( c1 == '0' && c2 == '0' ){
        return '0';
    }
    else{
        return '1';
    }
}

string toBinary(char deci){
    // deci -= 33;
    string bin;
    while(deci > 0 ){
        char temp = (deci % 2) + '0';
        bin = temp + bin;
        deci = deci/2;
    }

    while( bin.length() < 8 ){
        bin = '0' + bin;
    }

    return bin;
}

char toDecimal(string bin){
    int deci = 0;
    for( int i = 0; i < bin.length(); i++ ){
        int temp = bin.length() - i - 1;
        if( bin[temp] == '1' ){
            deci += pow(2, i);
        }
    }
    return deci;
}

string shiftRight(string str){
    string ret = str.substr(str.length() - 1, str.length()) + str.substr(0, str.length() - 1);
    return ret;
}

string shiftLeft(string str){
    string ret = str.substr(1, str.length()) + str[0];
    return ret;
}

string encrypt( string str ){

    str_len = str.length();

    string bin;
    for( int i = 0; i < str_len; i++ ){
        bin += toBinary(str[i]);
    }

    string L = bin.substr(0, bin.length()/2);
    string R = bin.substr(bin.length()/2);

    cout<<"Before:"<<endl<<L<<endl<<R<<endl;

    for( int i = 0; i < 16; i++ ){
        string newL = R;
        string shiftR = shiftRight(R);
        string newR;
        for( int j = 0; j < L.length(); j++ ){
            newR += XOR(shiftR[j], L[j]);
        }

        L = newL;
        R = newR;
    }

    bin = L + R;

    string ret;

    cout<<"length: "<<bin.length()<<endl;
    cout<<"After: "<<bin<<endl;
    for( int i = 0; i < bin.length(); i+=8 ){
        string sub = bin.substr(i, 8);
        cout<<i<<", "<<i+8;
        cout<<": "<<sub<<endl;
        ret += toDecimal(sub);
        cout<<toDecimal(sub)<<endl;
    }
    cout<<endl<<"ret: "<<ret<<endl;
    return ret;
}

string decrypt( string str ){
    string s;
    return s;
}