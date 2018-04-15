
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/*
const int p = 3;
const int q = 17;
*/

const int p = 2;
const int q = 13;

int const N = p * q;
int const phi = (p-1)*(q-1);

int e; // encryption key
int d; // decryption key

vector<int> generateFactorsPhi();

void generateCoPrimes( vector<int> & c );
void eliminateFactorsPQ( vector<int> & c );
void eliminateFactorsPhi( vector<int> & c );

void encryptionKey( vector<int> c );
void decryptionKey();

void printVector( vector<int> c );

bool checkChars( string str );

string encryptMessage( string s );
string decryptMessage( string s );

int charToInt( char c );
char intToChar( int n );

int main() {
    vector<int> c;

    // generate coprime
    generateCoPrimes(c);

    // generate encryption key
    encryptionKey(c);
    //generate decryption key
    decryptionKey();

    char op;
    string msg;
    
    cout<<"Enter e to encrypt a message or d to decrypt a message: ";
    cin>>op;
    if( op == 'e' ){
        cout<<"Enter a message to encrypt (A-Z):"<<endl;
        cin.ignore();
        getline(cin, msg);
        if( checkChars(msg) ){
            string encrypted = encryptMessage(msg);
            cout<<"Encryption: "<<encrypted<<endl;
        } else{
            cout<<"String contains at least one invalid character."<<endl;
        }
    } else if( op == 'd' ){
        // generate decryption key
        cout<<"Enter a message to decrypt:"<<endl;
        cin.ignore();
        getline(cin, msg);
        string decrypted = decryptMessage(msg);
        cout<<"Decryption: "<<decrypted<<endl;
    }
}


vector<int> generateFactorsPhi(){
    vector<int> factorsPhi;
    int temp = 1;

    while (temp <= phi){
        if (not(phi % temp))
            factorsPhi.push_back(temp);
        temp++;
    }
    return factorsPhi;
}

void generateCoPrimes( vector<int> & c ){
    for( int i = 1; i <= N; i++ ){
        c.push_back(i);
    }

    eliminateFactorsPQ(c);
    eliminateFactorsPhi(c);

}

void eliminateFactorsPQ( vector<int> & c ){
    for( int i = 0; i < c.size(); i++ ){
        if( c[i]%p == 0 || c[i]%q == 0 ){
            c.erase(c.begin()+i);
            i--;
        }
    }
}

void eliminateFactorsPhi( vector<int> & c ){
    vector<int> phi = generateFactorsPhi();

    for( int i = 0; i < c.size(); i++ ){
        for( int j = 0; j < phi.size(); j++ ){ // loop through phi factors
            if( c[i] % phi[j] == 0 ){
                c.erase(c.begin()+i);
                i--;
            }
        }
    }
}

void encryptionKey( vector<int> c ){
    for( int i = 0; i < c.size(); i++ ){
        if( c[i] > 1 && c[i] < phi ){
            e = c[i];
            break;
        }
    }
}

void decryptionKey(){
    for( int i = 1; i <= phi; i++ ){
        if( (e * i) % phi == 1 ){
            d = i;
            break;
        }
    }
}

void printVector( vector<int> c ){
    for( int i = 0; i < c.size(); i++ ){
        cout<<c[i]<<" ";
    }
    cout<<endl;
}

bool checkChars( string str ){

    bool ret = true;

    for( int i = 0; i < str.length(); i++ ){
        if( (str[i] >= 'A' && str[i] <= 'Z') ){
            ;
        } else{
            ret = false;
            break;
        }
    }
    return ret;
}

string encryptMessage( string s ){
    
    string ret = "";

    for( int i = 0; i < s.length(); i++ ){
        int num = charToInt(s[i]);
        if( num != -1 ){
            unsigned long long temp = pow(num, e);
            temp = temp % N;
            ret += intToChar(temp);
        }
    }
    return ret;

}

string decryptMessage( string s ){

    string ret = "";

    for( int i = 0; i < s.length(); i++ ){
        int num = charToInt(s[i]);
        if( num != -1 ){
            unsigned long long temp = pow(num, d);
            temp = temp % N;
            ret += intToChar(temp);
        }
    }
    return ret;
}

int charToInt( char c ){
    /*
    A - Z => 0 - 25
    */

    int num = -1;
    
    if( c >= 'A' && c <= 'Z' ){
        num = c - 'A';
    }

    return num;
}


char intToChar( int n ){
    char c = '\0';

    if( n >= 0 && n <= 25 ){
        c = n + 'A';
    }

    return c;
}
