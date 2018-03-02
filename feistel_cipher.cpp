#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int const ROUNDS = 16;
int const BIN_LEN = 6;

/*
char const characters[] = {
    ' ', '!', '\"', '#', '$', '%', '&', '\'', '(',
    ')', '*', '+', ',', '-', '.', '/', ':', ';', '<',
    '=', '>', '?', '@', '[' '\\', ']', '^', '_', ';'
};
*/

bool checkChars( string str );
char XOR(char c1, char c2);
string toBinary(char deci); // converts char to int then corresponding binary string
char toDecimal(string bin); // converts binary string to decimal then corresponding char
string shiftRight(string str);
string shiftLeft(string str);

string encrypt(string str);
string decrypt(string str);

int str_len = 0;

int main(){
    string enc_dec;
    cout<<"Type 'encrypt' or 'decrypt': ";
    cin>>enc_dec;

    string s;

    if( enc_dec == "encrypt" ){
        cout<<"Enter a message to encrypt (A-Z, 0-9, space, ! \" # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \\ ] ^ _ ):"<<endl;
        cin.ignore();
        getline(cin, s);

        if( checkChars(s) ){
            string e = encrypt(s);
            cout<<"Encryption: "<<e<<endl;
        } else{
            cout<<"String contains at least one invalid character."<<endl;
        }
    } else if( enc_dec == "decrypt" ){
        cout<<"Enter a message to decrypt:"<<endl;
        cin.ignore();
        getline(cin, s);

        if( checkChars(s) ){
            string d = decrypt(s);
            cout<<"Decryption: "<<d<<endl;
        } else {
            cout<<"String contains at least one invalid character."<<endl;
        }
    } else{
        cout<<"Invalid entry."<<endl;
    }

}

bool checkChars( string str ){
    str_len = str.length();
    
    bool ret = true;

    for( int i = 0; i < str_len; i++ ){
        if( str[i] >= ' ' && str[i] <= '_'){
            ;
        } else{
            ret = false;
            break;
        }
    }
    
    return ret;
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
    int dec = (int)deci - 32;

    string bin;
    while(dec > 0 ){
        char temp = (dec % 2) + '0';
        bin = temp + bin;
        dec = dec/2;
    }

    while( bin.length() < BIN_LEN ){
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
    deci+=32;
    return (char)deci;
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
    string bin;
    for( int i = 0; i < str_len; i++ ){
        bin += toBinary(str[i]);
    }

    string L = bin.substr(0, bin.length()/2);
    string R = bin.substr(bin.length()/2);

    for( int i = 0; i < ROUNDS; i++ ){
        string newL = R;
        string shiftR = shiftRight(R);
        string newR;
        for( int j = 0; j < L.length(); j++ ){
            newR += XOR(shiftR[j], L[j]);
        }

        L = newL;
        R = newR;
    }

    bin = R + L;

    string ret;

    for( int i = 0; i < bin.length(); i+=BIN_LEN ){
        string sub = bin.substr(i, BIN_LEN);
        ret += toDecimal(sub);
    }

    return ret;
}

string decrypt( string str ){
    string bin;
    for( int i = 0; i < str_len; i++ ){
        bin += toBinary(str[i]);
    }

    string L = bin.substr(0, bin.length()/2);
    string R = bin.substr(bin.length()/2);

    for( int i = ROUNDS; i > 0; i-- ){
        string newL = R;
        string shiftR = shiftRight(R);
        string newR;
        for( int j = 0; j < L.length(); j++ ){
            newR += XOR(shiftR[j], L[j]);
        }

        L = newL;
        R = newR;
    }

    bin = R + L;

    string ret;

    for( int i = 0; i < bin.length(); i+=BIN_LEN ){
        string sub = bin.substr(i, BIN_LEN);
        ret += toDecimal(sub);
    }

    return ret;
}