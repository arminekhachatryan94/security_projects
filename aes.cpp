#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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

unsigned char rcon[256] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

/* helper functions */
int XOR( int x, int y );
vector<int> XOR_VECTORS( vector<int> v1, vector<int> v2 );

vector<int> decToHex( int decimal );
int hexToDecimal( vector<int> hex );

vector<int> hexToBinary( int hex );
int binaryToHex( vector<int> bin );

void shiftLeft( vector<int> & v );
void shiftLeft( vector< vector<int> > & v );
void shiftRight( vector< vector<int> > & v );
void byteSub( vector< vector<int> > & v );
void inverseByteSub( vector< vector<int> > & v );
void addRoundConst( vector< vector<int> > & v, int round );
void shiftRows( vector< vector<int> > & v );
void mixColumn( vector< vector<int> > & v );
vector<int> multiplyBinaries( vector<int> c, vector<int> m );
// input: two hex arrays, output: hex element
vector<int> matrixMultiEl( vector< vector<int> > row, vector< vector<int> > col );

// generate key
void generateKey( vector< vector<int> > & keyHex, int round );

// encrypt message
string encryptMessage( string msg, string key );
string decryptMessage( string msg, string key );

/* TESTING */
void printHex( vector<int> hex );
void printHexArray( vector< vector<int> > hex );

int main() {
    string key = "Thats my Kung Fu";
    string msg = "Two One Nine Two";
    string enc = encryptMessage(msg, key);
    cout<<"encrypted message: "<<enc<<endl;
    string dec = decryptMessage(enc, key);
    cout<<"decrypted message: "<<dec<<endl;
}

/* helper functions */

int XOR( int x, int y ){
    if( x && y ){
        return 0;
    } else if( !x && !y ){
        return 0;
    } else {
        return 1;
    }
}

vector<int> XOR_VECTORS( vector<int> v1, vector<int> v2 ){
    vector<int> ret;
    for( int i = 0; i < v1.size(); i++ ){
        ret.push_back( XOR(v1[i], v2[i]) );
    }
    return ret;
}

vector<int> decToHex( int decimal ){
    vector<int> r;
    while( decimal != 0 ){
        int remainder = decimal%16;
        decimal = decimal/16;
        r.push_back(remainder);
    }
    for( int i = r.size(); i < 2; i++ ){
        r.push_back(0);
    }
    
    vector<int> ret;
    for( int i = r.size()-1; i >= 0; i-- ){
        ret.push_back(r[i]);
    }

    return ret;
}

int hexToDecimal( vector<int> hex ){
    int dec = 0;
    for( int i = hex.size()-1; i >= 0; i-- ){
        dec += hex[i]*pow(16, (hex.size()-1-i));
    }
    return dec;
}


vector<int> hexToBinary( int hex ){
    vector<int> bin;

    while( hex > 0 ){
        bin.push_back(hex%2);
        hex /= 2;
    }

    for( int i = bin.size(); i < 4; i++ ){
        bin.push_back(0);
    }
    vector<int> ret;
    for( int i = bin.size()-1; i >= 0; i-- ){
        ret.push_back(bin[i]);
        // cout<<bin[i];
    }

    return ret;
}

int binaryToHex( vector<int> bin ){
    int hex = 0;
    for( int i = bin.size()-1; i >= 0; i-- ){
        hex += bin[i]*pow(2, (bin.size()-1-i));
    }
    return hex;
}







void shiftLeft( vector<int> & v ){
    vector<int> ret;
    for( int i = 1; i < v.size(); i++ ){
        ret.push_back(v[i]);
    }
    ret.push_back(v[0]);
    v = ret;
}

void shiftLeft( vector< vector<int> > & v ){
    vector< vector<int> > ret;
    for( int i = 1; i < v.size(); i++ ){
        ret.push_back(v[i]);
    }
    ret.push_back(v[0]);
    v = ret;
}

void shiftRight( vector< vector<int> > & v ){
    vector< vector<int> > ret;
    ret.push_back(v[v.size()-1]);
    for( int i = 0; i < v.size()-1; i++ ){
        ret.push_back(v[i]);
    }
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

void inverseByteSub( vector< vector<int> > & v ){
    vector< vector<int> > r;
    for( int i = 0; i < v.size(); i++ ){
        vector<int> temp;
        int x = sbox[v[i][0]][v[i][1]][0];
        int y = sbox[v[i][0]][v[i][1]][1];
        int rev_x = sbox[x][y][0];
        int rev_y = sbox[x][y][1];
        // cout<<v[i][0]<<" "<<v[i][1]<<": "<<x<<" "<<y<<endl;
        temp.push_back(rev_x);
        temp.push_back(rev_y);
        r.push_back(temp);
    }
    v = r;
}

void addRoundConst( vector< vector<int> > & v, int round ){
    vector< vector<int> > ret;
    
    vector<int> r = decToHex((int)rcon[round]);
    vector<int> z; z.push_back(0); z.push_back(0);

    vector< vector<int> > rconst;
    rconst.push_back(r);
    rconst.push_back(z); rconst.push_back(z); rconst.push_back(z);
    for( int i = 0; i < rconst.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < rconst[i].size(); j++ ){
            vector<int> rcon_bin = hexToBinary(rconst[i][j]);
            vector<int> v_bin = hexToBinary(v[i][j]);
            vector<int> x = XOR_VECTORS(rcon_bin, v_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        ret.push_back(temp);
    }

    v = ret;
}

void shiftRows( vector< vector<int> > & v ){
    /*
    row 1 --> 0 left shifts
    row 2 --> 1 shift
    row 3 --> 2 shifts
    row 4 --> 3 shifts
    */

    vector< vector<int> > v2;
    vector< vector<int> > v3;
    vector< vector<int> > v4;
    for( int i = 0; i < v.size(); i++ ){
        if( (i-1)%4 == 0 ){
            v2.push_back(v[i]);
        } else if( (i-2)%4 == 0 ){
            v3.push_back(v[i]);
        } else if( (i-3)%4 == 0 ){
            v4.push_back(v[i]);
        }
    }

    shiftLeft(v2);
    shiftLeft(v3); shiftLeft(v3);
    shiftLeft(v4); shiftLeft(v4); shiftLeft(v4);

    for( int i = 0; i < v.size(); i++ ){
        if( (i-1)%4 == 0 ){
            v[i] = v2[(i-1)/4];
        } else if( (i-2)%4 == 0 ){
            v[i] = v3[(i-2)/4];
        } else if( (i-3)%4 == 0 ){
            v[i] = v4[(i-3)/4];
        }
    }

}

void mixColumn( vector< vector<int> > & v ){
    vector<int> a;
    a.push_back(0);
    vector<int> b = a;
    vector<int> c = a;
    a.push_back(1);
    b.push_back(2);
    c.push_back(3);

    vector< vector<int> > col;
    col.push_back(b);
    col.push_back(c);
    col.push_back(a);
    col.push_back(a);

    // multiply matrices
    vector< vector<int> > r;
    for( int j = 0; j < 4; j++ ){
        for( int i = 0; i < 4; i++ ){
            vector< vector<int> > temp;
            temp.push_back(v[(4*j)]);
            temp.push_back(v[(4*j)+1]);
            temp.push_back(v[(4*j)+2]);
            temp.push_back(v[(4*j)+3]);
            
            // multiply temp and col
            r.push_back(matrixMultiEl(col, temp));

            shiftRight(col);
        }
    }
    v = r;
}

vector<int> multiplyBinaries( vector<int> c, vector<int> m ){
    /*
    vector<int> r;
    if( c[c.size()-1] == 0 ){
        for( int i = 0; i < 8; i++ ){
            r.push_back(0);
        }
    } else{
        r = m;
    }
    if( c[c.size()-2] == 1 ){
        vector<int> m1;
        for( int i = 1; i < m.size(); i++ ){
            m1.push_back(m[i]);
        }
        m1.push_back(0);

        for( int i = 0; i < r.size(); i++ ){
            r[i] = XOR(r[i], m1[i]);
        }
    }
    // cout<<endl;
    // printHex(r);
    return r;
    */

    vector<int> a1;
    if( c[c.size()-2] == 0 && c[c.size()-1] == 1 ){ // c is 1
        a1 = m;
    } else if( c[c.size()-2] == 1 && c[c.size()-1] == 0 ){ // c is 2
        if( m[0] == 1 ){ // carry 1
            vector<int> temp;
            temp.push_back(0); temp.push_back(0); temp.push_back(0); temp.push_back(1);
            temp.push_back(m[0]); temp.push_back(m[1]); temp.push_back(m[2]); temp.push_back(m[3]);
            a1 = m;
            shiftLeft(a1);
            a1 = XOR_VECTORS(a1, temp);
        } else{
            a1 = m;
            shiftLeft(a1);
        }
    } else if( c[c.size()-2] == 1 && c[c.size()-1] == 1 ){ // c is 3
        if( m[0] == 1 ){ // carry 1
            vector<int> temp;
            temp.push_back(0); temp.push_back(0); temp.push_back(0); temp.push_back(1);
            temp.push_back(m[0]); temp.push_back(m[1]); temp.push_back(m[2]); temp.push_back(m[3]);
            a1 = m;
            shiftLeft(a1);
            a1 = XOR_VECTORS(a1, temp);
        } else{
            a1 = m;
            shiftLeft(a1);
        }

        a1 = XOR_VECTORS(a1, m);
    }
    return a1;
}


vector<int> matrixMultiEl( vector< vector<int> > row, vector< vector<int> > col ){
    vector<int> binary;
    for( int i = 0; i < row.size(); i++ ){
        vector<int> r_bin = hexToBinary(row[i][0]);
        vector<int> r_bin2 = hexToBinary(row[i][1]);
        r_bin.push_back(r_bin2[0]); r_bin.push_back(r_bin2[1]); r_bin.push_back(r_bin2[2]); r_bin.push_back(r_bin2[3]);

        vector<int> col_bin = hexToBinary(col[i][0]);
        vector<int> col_bin2 = hexToBinary(col[i][1]);
        col_bin.push_back(col_bin2[0]); col_bin.push_back(col_bin2[1]); col_bin.push_back(col_bin2[2]); col_bin.push_back(col_bin2[3]);

        vector<int> b = multiplyBinaries(r_bin, col_bin);
        if( binary.size() == 0 ){
            binary = b;
        } else{
            binary = XOR_VECTORS(binary, b);
        }
    }

    
    vector<int> b1;
    vector<int> b2;
    
    for( int i = 0; i < binary.size(); i++ ){
        if( i >= 0 && i < 4 ){
            b1.push_back(binary[i]);
        } else{
            b2.push_back(binary[i]);
        }
    }
    /*
    printHex(b1);
    cout<<" ";
    printHex(b2);
    cout<<endl;
    */
    vector<int> ret; // 2 hex values
    ret.push_back(binaryToHex(b1));
    ret.push_back(binaryToHex(b2));

    return ret;
}



// generate key
void generateKey( vector< vector<int> > & keyHex, int round ){

    vector< vector<int> > w0;
    w0.push_back(keyHex[0]); w0.push_back(keyHex[1]);
    w0.push_back(keyHex[2]); w0.push_back(keyHex[3]);

    vector< vector<int> > w1;
    w1.push_back(keyHex[4]); w1.push_back(keyHex[5]);
    w1.push_back(keyHex[6]); w1.push_back(keyHex[7]);

    vector< vector<int> > w2;
    w2.push_back(keyHex[8]); w2.push_back(keyHex[9]);
    w2.push_back(keyHex[10]); w2.push_back(keyHex[11]);

    vector< vector<int> > w3;
    w3.push_back(keyHex[12]); w3.push_back(keyHex[13]);
    w3.push_back(keyHex[14]); w3.push_back(keyHex[15]);

    vector< vector<int> > g3 = w3;

    /* CALCULATE g(w3) */
    // circular shift w3
    shiftLeft(g3);
    // byte substitution
    byteSub(g3);
    // add round constant
    addRoundConst(g3, round);
    cout<<endl;

    /* CALCULATE w4 */
    vector< vector<int> > w4;
    for( int i = 0; i < w0.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < w0[i].size(); j++ ){
            vector<int> w0_bin = hexToBinary(w0[i][j]);
            vector<int> g3_bin = hexToBinary(g3[i][j]);
            vector<int> x = XOR_VECTORS(w0_bin, g3_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        w4.push_back(temp);
    }
    // printHex(w4[0]); cout<<" "; printHex(w4[1]); cout<<" "; printHex(w4[2]); cout<<" "; printHex(w4[3]); cout<<endl;

    /* CALCULATE w5 */
    vector< vector<int> > w5;
    for( int i = 0; i < w4.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < w1[i].size(); j++ ){
            vector<int> w1_bin = hexToBinary(w1[i][j]);
            vector<int> w4_bin = hexToBinary(w4[i][j]);
            vector<int> x = XOR_VECTORS(w1_bin, w4_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        w5.push_back(temp);
    }
    // printHex(w5[0]); cout<<" "; printHex(w5[1]); cout<<" "; printHex(w5[2]); cout<<" "; printHex(w5[3]); cout<<endl;

    /* CALCULATE w6 */
    vector< vector<int> > w6;
    for( int i = 0; i < w5.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < w2[i].size(); j++ ){
            vector<int> w2_bin = hexToBinary(w2[i][j]);
            vector<int> w5_bin = hexToBinary(w5[i][j]);
            vector<int> x = XOR_VECTORS(w2_bin, w5_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        w6.push_back(temp);
    }
    // printHex(w6[0]); cout<<" "; printHex(w6[1]); cout<<" "; printHex(w6[2]); cout<<" "; printHex(w6[3]); cout<<endl;
    
    /* CALCULATE w7 */
    vector< vector<int> > w7;
    for( int i = 0; i < w6.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < w3[i].size(); j++ ){
            vector<int> w3_bin = hexToBinary(w3[i][j]);
            vector<int> w6_bin = hexToBinary(w6[i][j]);
            vector<int> x = XOR_VECTORS(w3_bin, w6_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        w7.push_back(temp);
    }
    // printHex(w7[0]); cout<<" "; printHex(w7[1]); cout<<" "; printHex(w7[2]); cout<<" "; printHex(w7[3]); cout<<endl;

    vector< vector<int> > abc;

    abc.push_back(w4[0]);
    abc.push_back(w4[1]);
    abc.push_back(w4[2]);
    abc.push_back(w4[3]);

    abc.push_back(w5[0]);
    abc.push_back(w5[1]);
    abc.push_back(w5[2]);
    abc.push_back(w5[3]);

    abc.push_back(w6[0]);
    abc.push_back(w6[1]);
    abc.push_back(w6[2]);
    abc.push_back(w6[3]);

    abc.push_back(w7[0]);
    abc.push_back(w7[1]);
    abc.push_back(w7[2]);
    abc.push_back(w7[3]);

    keyHex = abc;
}

// encrypt message
string encryptMessage( string message, string key ){
    // convert key to hex
    vector< vector<int> > k;
    for( int i = 0; i < key.length(); i++ ){
        k.push_back(decToHex((int)(key[i])));
    }

    // convert message to hex
    vector< vector<int> > m;
    for( int i = 0; i < message.length(); i++ ){
        m.push_back(decToHex((int)(message[i])));
    }

    printHexArray(m);
    cout<<endl;
    printHexArray(k);
    cout<<endl;

    // xor vectors for round 0
    for( int i = 0; i < k.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < k[i].size(); j++ ){
            vector<int> k_bin = hexToBinary(k[i][j]);
            vector<int> m_bin = hexToBinary(m[i][j]);
            vector<int> x = XOR_VECTORS(k_bin, m_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        m[i] = temp;
    }

    // rounds 1 - 10
    for( int i = 1; i <= 10; i++ ){
        // byte substitution
        byteSub(m);
        // shift rows
        shiftRows(m);
        // mix column
        mixColumn(m);

        // generate key for round i
        generateKey(k, i);

        // xor vectors for round i
        for( int l = 0; l < k.size(); l++ ){
            vector<int> temp;
            for( int j = 0; j < k[l].size(); j++ ){
                vector<int> k_bin = hexToBinary(k[l][j]);
                vector<int> m_bin = hexToBinary(m[l][j]);
                vector<int> x = XOR_VECTORS(k_bin, m_bin);
                int h = binaryToHex(x);
                temp.push_back(h);
            }
            m[l] = temp;
        }

        printHexArray(m);
        cout<<endl;
        printHexArray(k);
        cout<<endl;
    }

    string new_msg;
    for( int i = 0; i < m.size(); i++ ){
        new_msg += (char)hexToDecimal(m[i]);
    }

    return new_msg;
}

string decryptMessage( string message, string key ){
    // convert key to hex
    vector< vector<int> > k;
    for( int i = 0; i < key.length(); i++ ){
        k.push_back(decToHex((int)(key[i])));
    }

    // convert message to hex
    vector< vector<int> > m;
    for( int i = 0; i < message.length(); i++ ){
        m.push_back(decToHex((int)(message[i])));
    }

    printHexArray(m);
    cout<<endl;
    printHexArray(k);
    cout<<endl;

    // xor vectors for round 0
    for( int i = 0; i < k.size(); i++ ){
        vector<int> temp;
        for( int j = 0; j < k[i].size(); j++ ){
            vector<int> k_bin = hexToBinary(k[i][j]);
            vector<int> m_bin = hexToBinary(m[i][j]);
            vector<int> x = XOR_VECTORS(k_bin, m_bin);
            int h = binaryToHex(x);
            temp.push_back(h);
        }
        m[i] = temp;
    }

    // rounds 1 - 10
    for( int i = 1; i <= 10; i++ ){
        // byte substitution
        byteSub(m);
        // shift rows
        shiftRows(m);
        // mix column
        mixColumn(m);

        // generate key for round i
        generateKey(k, i);

        // xor vectors for round i
        for( int l = 0; l < k.size(); l++ ){
            vector<int> temp;
            for( int j = 0; j < k[l].size(); j++ ){
                vector<int> k_bin = hexToBinary(k[l][j]);
                vector<int> m_bin = hexToBinary(m[l][j]);
                vector<int> x = XOR_VECTORS(k_bin, m_bin);
                int h = binaryToHex(x);
                temp.push_back(h);
            }
            m[l] = temp;
        }
        
        printHexArray(m);
        cout<<endl;
        printHexArray(k);
        cout<<endl;
    }
    
    string new_msg;
    for( int i = 0; i < m.size(); i++ ){
        new_msg += (char)hexToDecimal(m[i]);
    }

    return new_msg;
}




/* TESTING */
void printHex( vector<int> hex ){
    for( int i = 0; i < hex.size(); i++ ){
        cout<<hexadecimal[hex[i]];
    }
}

void printHexArray( vector< vector<int> > hex ){
    for( int i = 0; i < hex.size(); i++ ){
        printHex(hex[i]);
        cout<<" ";
    }
}