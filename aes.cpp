#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// bool checkHex( vector<int> hex );
vector<int> decToHex( int decimal );
int hexToDec( vector<int> hex );
// void printHex( vector<int> hex );
string hexToString( vector< vector<int> > hex );
vector< vector<int> > stringToHex( string s );

const char hexadecimal[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

int main(){
    vector< vector<int> > h = stringToHex("Two One Nine Two");
    for( int i = 0; i < h.size(); i++ ){
        printHex(h[i]);
        cout<<" ";
    }

    cout<<endl<<hexToString(h)<<endl;
}

/*
bool checkHex( vector<int> hex ){
    bool ret = true;
    for( int i = 0; i < hex.size(); i++ ){
        if( (hex[i] >= 0 && hex[i] <= 15) ){
            ;
        } else{
            ret = false;
            break;
        }
    }
    return ret;
}
*/

vector<int> decToHex( int decimal ){
    vector<int> r;
    while( decimal != 0 ){
        int remainder = decimal%16;
        decimal = decimal/16;
        r.push_back(remainder);
    }
    
    vector<int> ret;
    for( int i = r.size()-1; i >= 0; i-- ){
        ret.push_back(r[i]);
    }

    return ret;
}

int hexToDec( vector<int> hex ){
    int ret = 0;
    for( int i = hex.size()-1; i >= 0; i-- ){
        ret += hex[i]*pow(16, (hex.size()-1-i));
        // cout<<endl<<hex[i]<<" * 16^"<<hex.size()-1-i<<endl;
        // cout<<"add "<<hex[i]*pow(16, (hex.size()-1-i))<<endl;
    }
    return ret;
}

void printHex( vector<int> hex ){
    for( int i = 0; i < hex.size(); i++ ){
        cout<<hexadecimal[hex[i]];
    }
}

string hexToString( vector< vector<int> > hex ){
    string ret;
    for( int i = 0; i < hex.size(); i++ ){
        int dec = hexToDec(hex[i]);
        ret += (char)dec;
    }
    return ret;
}

vector< vector<int> > stringToHex( string s ){
    vector< vector<int> > ret;
    for( int i = 0; i < s.length(); i++ ){
        vector<int> r = decToHex((int)(s[i]));
        ret.push_back(r);
    }
    return ret;
}
