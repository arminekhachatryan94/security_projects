
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const int p = 2;
const int q = 7;

int const N = p * q;
int const phi = (p-1)*(q-1);

int e; // encryption key
int d; // decryption key

vector<int> generateFactorsPhi();

void generateCoPrimes( vector<int> & c );
void eliminateFactorsPQ( vector<int> & c );
void eliminateFactorsPhi( vector<int> & c );

void encryptionKey( vector<int> c );
void decryptionKey( vector<int> c );

void printVector( vector<int> c );

int main() {

    // encrypt

    // generate coprime
    vector<int> c;

    generateCoPrimes(c);

    // generate encryption key
    encryptionKey(c);

    // geneate decryption key
    decryptionKey(c);

    /*
    cout<<"e: "<<e<<endl;
    cout<<"d: "<<d<<endl;
    */
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
    // c.erase(c.begin()+5);

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

    for( int i = 0; i < c.size(); i++ ){ // loop through phi factors
        for( int j = 0; j < phi.size(); j++ ){
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
            c.erase(c.begin() + i);
            break;
        }
    }
}

void decryptionKey( vector<int> c ){
    int chosen = 0;
    for( int i = 1; i <= phi*2; i++ ){
        if( (e * i) % phi == 1 ){
            if( chosen == 1 ){
                d = i;
                break;
            }
            else {
                chosen++;
            }
        }
    }
}

void printVector( vector<int> c ){
    for( int i = 0; i < c.size(); i++ ){
        cout<<c[i]<<" ";
    }
    cout<<endl;
}