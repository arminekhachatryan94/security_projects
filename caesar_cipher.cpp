

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    // input encrypt or decrypt
    bool crypt;
    cout<<"Type 1 (encrypt) or 0 (decrypt): ";
    cin>>crypt;
    cin.ignore();

    if( crypt ){ // encryption
        // Input message string
        string message;
        cout<<"Enter a message (only lowercase letters): ";
        getline(cin, message);

        // clean up extra spaces
        string new_message;
        for( int i = 0; i < message.length(); i++ ){
            if( message[i] != ' '){
                new_message += message[i];
            }
            else{
                new_message += ' ';
                i++;
                while( message[i] == ' ' && i < message.length()){
                    i++;
                }
                i--;
            }
        }
        
        // encrypt string
        for( int i = 0; i < new_message.length(); i++ ){
            
            if( new_message[i] >= 'a' && new_message[i] <= 'z'){
                cout<< (char)((((new_message[i]-'a')+3)%26)+'A');
            }
            else if( new_message[i] == ' '){
                cout<<' ';
            }
            
        }
        cout<<endl;
    } else{ // decryption
        // Input message string
        string message;
        cout<<"Enter a message (only uppercase letters): ";
        getline(cin, message);

        // clean up extra spaces
        string new_message;
        for( int i = 0; i < message.length(); i++ ){
            if( message[i] != ' '){
                new_message += message[i];
            }
            else{
                new_message += ' ';
                i++;
                while( message[i] == ' ' && i < message.length()){
                    i++;
                }
                i--;
            }
        }
        
        // decrypt string
        for( int i = 0; i < new_message.length(); i++ ){
            if( new_message[i] >= 'A' && new_message[i] <= 'Z'){
                cout<<(char)((((new_message[i]-'A')+23)%26)+'a');
            }
            else if( new_message[i] == ' '){
                cout<<' ';
            }
            
        }
        cout<<endl;
    }
}