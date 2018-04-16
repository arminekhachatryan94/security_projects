#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// bool checkHex( vector<int> hex );
vector<int> decToHex( int decimal );
int hexToDec( vector<int> hex );
void printHex( vector<int> hex );
string hexToString( vector< vector<int> > hex );
vector< vector<int> > stringToHex( string s );
void shiftLeft( vector< vector<int> > & v );
void byteSub( vector< vector<int> > & v );


const char hexadecimal[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
const int sbox[16][16][2] = {
    /*          0           1          2         3           4           5          6          7          8         9          A          B           C           D          E          F    */
    /* 0 */ { {6, 3},    {7, 12},   {7, 7},    {7, 11},   {15, 2},    {6, 11},   {6, 15},   {12, 5},   {3, 0},    {0, 1},    {6, 7},    {2, 11},    {15, 13},  {13, 7},   {10, 11},   {7, 6} },
    /* 1 */ { {12, 10},  {8, 2},    {12, 9},   {7, 13},   {15, 10},   {5, 9},    {4, 7},    {15, 0},   {10, 13},  {13, 4},   {10, 2},   {10, 15},   {9, 12},   {10, 4},   {7, 2},     {12, 0} },
    /* 2 */ { {11, 7},   {15, 13},  {9, 3},    {2, 6},    {3, 6},     {3, 15},   {15, 7},   {12, 12},  {3, 4},    {10, 5},   {14, 1},   {15, 1},    {7, 1},    {13, 8},   {3, 1},     {1, 5} },
    /* 3 */ { {0, 4},    {12, 7},   {2, 3},    {12, 3},   {1, 8},     {9, 6},    {0, 5},    {9, 10},   {0, 7},    {1, 2},    {8, 0},    {14, 2},    {14, 11},  {2, 7},    {11, 2},    {7, 5} },
    /* 4 */ { {0, 9},    {8, 3},    {2, 12},   {1, 10},   {1, 11},    {6, 14},   {5, 10},   {10, 0},   {5, 1},    {3, 11},   {13, 6},   {11, 3},    {2, 9},    {14, 3},   {2, 15},    {8, 4} },
    /* 5 */ { {5, 3},    {13, 1},   {0, 0},    {14, 13},  {2, 0},     {15, 12},  {11, 1},   {5, 11},   {5, 2},    {12, 11},  {11, 15},  {3, 9},     {4, 10},   {4, 12},   {5, 8},     {12, 15} },
    /* 6 */ { {13, 0},   {14, 15},  {10, 10},  {15, 11},  {4, 3},     {4, 13},   {3, 3},    {8, 5},    {4, 5},    {15, 9},   {0, 2},    {7, 15},    {5, 0},    {3, 12},   {9, 15},    {10, 8} },
    /* 7 */ { {5, 1},    {10, 3},   {4, 0},    {8, 15},   {9, 2},     {9, 13},   {3, 8},    {15, 5},   {11, 12},  {11, 6},   {13, 10},  {2, 1},     {1, 0},    {15, 15},  {15, 3},    {13, 2} },
    /* 8 */ { {12, 13},  {0, 12},   {1, 3},    {15, 12},  {5, 15},    {9, 7},    {4, 4},    {1, 7},    {12, 4},   {10, 7},   {7, 14},   {3, 13},    {6, 4},    {5, 13},   {1, 9},     {7, 3} },
    /* 9 */ { {6, 0},    {8, 1},    {4, 15},   {13, 12},  {2, 2},     {2, 10},   {9, 0},    {8, 8},    {4, 6},    {14, 14},  {11, 8},   {1, 4},     {13, 14},  {5, 14},   {0, 11},    {13, 11} },
    /* A */ { {14, 0},   {3, 2},    {3, 10},   {0, 10},   {4, 9},     {0, 6},    {2, 4},    {5, 12},   {12, 2},   {13, 3},   {10, 12},  {6, 2},     {9, 1},    {9, 5},    {14, 4},    {7, 9} },
    /* B */ { {14, 7},   {12, 8},   {3, 7},    {6, 13},   {8, 13},    {13, 5},   {4, 14},   {10, 9},   {6, 12},   {5, 6},    {15, 4},   {14, 10},   {6, 5},    {7, 10},   {10, 14},   {0, 8} },
    /* C */ { {11, 10},  {7, 8},    {2, 5},    {2, 14},   {1, 12},    {10, 6},   {11, 4},   {12, 6},   {14, 8},   {13, 13},  {7, 4},    {1, 15},    {4, 11},   {11, 13},  {8, 11},    {8, 10} },
    /* D */ { {7, 0},    {3, 14},   {11, 5},   {6, 6},    {4, 8},     {0, 3},    {15, 6},   {0, 14},   {6, 1},    {3, 5},    {5, 7},    {11, 9},    {8, 6},    {12, 1},   {1, 13},    {9, 14} },
    /* E */ { {14, 1},   {15, 8},   {9, 8},    {1, 1},    {6, 9},     {13, 9},   {8, 14},   {9, 4},    {9, 11},   {1, 14},   {8, 7},    {14, 9},    {12, 14},  {5, 5},    {2, 8},     {13, 15} },
    /* F */ { {8, 10},   {10, 1},   {8, 9},    {0, 13},   {11, 15},   {14, 6},   {4, 2},    {6, 8},    {4, 1},    {9, 9},    {2, 13},   {0, 15},    {11, 0},   {5, 4},    {11, 11},   {1, 6} }
};

int main(){
    vector< vector<int> > h = stringToHex("Thats my Kung Fu");
    // shiftLeft(h);
    for( int i = 0; i < h.size(); i++ ){
        printHex(h[i]);
        cout<<" ";
    }
    cout<<endl;

    byteSub(h);
    for( int i = 0; i < h.size(); i++ ){
        printHex(h[i]);
        cout<<" ";
    }
    
    /*
    // for( int i = 0; i <= 10; i++ ){
        vector< vector<int> > w0;
        w0.push_back(h[0]);
        w0.push_back(h[1]);
        w0.push_back(h[2]);
        w0.push_back(h[3]);

        vector< vector<int> > w1;
        w1.push_back(h[4]);
        w1.push_back(h[5]);
        w1.push_back(h[6]);
        w1.push_back(h[7]);

        vector< vector<int> > w2;
        w2.push_back(h[8]);
        w2.push_back(h[9]);
        w2.push_back(h[10]);
        w2.push_back(h[11]);

        vector< vector<int> > w3;
        w3.push_back(h[12]);
        w3.push_back(h[13]);
        w3.push_back(h[14]);
        w3.push_back(h[15]);

    // }
    */
    // cout<<endl<<hexToString(h)<<endl;
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

void shiftLeft( vector< vector<int> > & v ){
    vector< vector<int> > ret;
    for( int i = 1; i < v.size(); i++ ){
        ret.push_back(v[i]);
    }
    ret.push_back(v[0]);
    v = ret;
}

void byteSub( vector< vector<int> > & v ){
    vector< vector<int> > r;
    for( int i = 0; i < v.size(); i++ ){
        vector<int> temp;
        int x = sbox[v[i][0]][v[i][1]][0];
        int y = sbox[v[i][0]][v[i][1]][1];
        // cout<<v[i][0]<<" "<<v[i][1]<<": "<<x<<" "<<y<<endl;
        temp.push_back(x);
        temp.push_back(y);
        r.push_back(temp);
    }
    v = r;
}
