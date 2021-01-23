/** Simple Encryptor
 *  This program encrypts and decrypts your text documents
 *  both works both with drag & drop and executable
 *  in 01 2020 from Kaan Yilmaz
 *
 * */

#include <iostream>
#include <string>
#include <stdio.h>
#include "LZWComp.h"
#include <unistd.h>


using namespace std;

bool fileexists(string filename){ //file existence checker
    FILE *file;
    if (file = fopen(filename.c_str(), "r")){
        fclose(file);
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    system("Color 80");
    LZWComp *LZW;
    string filename;
    string command;

    if (argc < 2) {    //if opened without file arguments
        cout << "Simple Encryptor" << endl;
        cout << "!help to get help" << endl;
        cout << endl;
        Jump:
        cout << R"("!en" to encrypt, "!de" to decrypt)" << endl;
        cin >> command;

        if (command == "!help") { //help document
            system("color 84");
            system("cls");
            cout << "This program encrypts and decrypts your text documents" << endl;
            cout << "place your text file in the directory of program" << endl;
            cout << "When you process a file you will have a key and a lzw file" << endl;
            cout << "key unlocks the lzw file" << endl;
            cout << "delete your text and keep lzw and key" << endl;
            cout << "to decrypt your file, place both in directory" << endl;
            cout << "use program to process .lzw file" << endl;
            cout << "tip: drag & drop also works" << endl;
            cout << "**Simple Encryptor by Kaan Y�lmaz**" << endl;
            system("pause");
            goto Jump;

        } else if (command == "!en"){   //encryption mode
            jump0:
            system("cls");
            cout << "Enter name of file" << endl;
            cin >> filename;
            if(filename.size() < 5) {  //if user enter filename without type
                cout << "unsupported file" << endl;
                system("pause");
                system("cls");
                goto jump0;
            } else if (filename.substr(filename.size()-4, filename.size()) == ".txt") { //if user entered txt file
                if ((fileexists(filename.substr(0, filename.size()-4) + ".LZW" ))) { //check for pre existing files
                    cout << "encrypted file already exists!" << endl;
                    system("pause");
                    system("cls");
                    goto jump0;
                } else if ((fileexists(filename.substr(0, filename.size()-4) + ".key" ))) { //check for pre existing files
                    cout << "key file already exists!" << endl;
                    system("pause");
                    system("cls");
                    goto jump0;
                } else if (!(fileexists(filename) )) { //check if the file to be processed exists
                    cout << "file to be encrypted doesn't exist!" << endl;
                    system("pause");
                    system("cls");
                    goto jump0;
                } else {
                    LZW = new LZWComp(filename);
                    LZW->compress();
                }
            } else {
                cout << "please enter correct file name" << endl; //if user enter wrong file type
                system("pause");
                system("cls");
                goto jump0;
            }
        } else if (command == "!de"){ //decryption mode
            jump1:
            system("cls");
            cout << "Enter File Name" << endl;
            cin >> filename;
            if (filename.size() < 5) { //if user enter filename without type
                cout << "unsupported file" << endl;
                system("pause");
                system("cls");
                goto jump1;
            } else if(((filename.substr(filename.size()-4, filename.size()) == ".LZW") ) || (filename.substr(filename.size()-4, filename.size()) == ".lzw")){ //correct type
                if (!(fileexists(filename))) { //check if the file to be processed exists
                    cout << "file does not exist!" << endl;
                    system("pause");
                    system("cls");
                    goto jump1;
                } else if (!(fileexists(filename.substr(0, filename.size()-4) + ".key" ))) { //check if the key to be processed exists
                    cout << "key does not exist!" << endl;
                    system("pause");
                    system("cls");
                    goto jump1;
                } else if ((fileexists(filename.substr(0, filename.size()-4) + ".txt" ))) { //check if file already exists
                    cout << "text file already exists!" << endl;
                    system("pause");
                    system("cls");
                    goto jump1;
                } else {
                    LZW = new LZWComp(filename);
                    LZW->decompress();
                }
            } else {
                cout << "please enter correct file name" << endl; //if user enter wrong type
                system("pause");
                system("cls");
                goto jump1;
            }
        } else {
            cout << "unknown command" << endl; //if user enter wrong command
            system("pause");
            system("cls");
            goto Jump;
        }

    }
    else {  //opened from drag & drop or command prompt with arguments
        filename = argv[1];
        LZW = new LZWComp(filename);
        if (filename.size() < 5) { //file without type
            cout << "please open a valid file" << endl;
            cout << "exiting in 5 seconds" << endl;
            sleep(5);
            return -1;
        } else if(filename.substr(filename.size()-4, filename.size()) == ".txt") { //encryption mode
            if ((fileexists(filename.substr(0, filename.size()-4) + ".LZW" ))) { //if file already exists
                cout << "encrypted file already exists!" << endl;
                system("pause");
            } else if ((fileexists(filename.substr(0, filename.size()-4) + ".key" ))) { //if key already exists
                cout << "key file already exists!" << endl;
                system("pause");
            } else {
                LZW->compress();
            }
        } else if(filename.substr(filename.size()-4, filename.size()) == ".LZW") { //decryption mode
            if (!(fileexists(filename.substr(0, filename.size()-4) + ".key" ))) { //if key doesnt exists
                cout << "key does not exist!" << endl;
                system("pause");
            }  else if ((fileexists(filename.substr(0, filename.size()-4) + ".txt" ))) { //text already exists
                cout << "text file already exists!" << endl;
                system("pause");
            } else {
                    LZW->decompress();
                }
        } else{ //wrong file type
            cout << "File you opened is not valid." " it is of type " << filename.substr(filename.size()-3, filename.size()) << endl;
            cout << "you need to open either .txt or .LZW" << endl;
            cout << "exiting in 5 seconds" << endl;
            sleep(5);
            return -1;
        }
    }
return 0;
}

