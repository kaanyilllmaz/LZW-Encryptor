/** Ascii Randomizer by Kaan Yilmaz
 *  Takes strings or characters and places them in an HashTable according to their ascii values
 *  Creates an Array "Ascii Table" same sized as HashTable
 *  Shuffles numbers randomly
 *  To get so called ascii of a character, find it's index in HashTable
 *  then find it's value in AsciiTable[index]
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Used in second hash function.
#define PRIME 941

// Define HashTable size
#define TABLE_SIZE 4096

class AsciiRandomizer {

    string* hashTable;
    int* AsciiTable;
    int curr_size;

public:

    //constructor to initialize hashtable
    //to randomize Ascii Table
    AsciiRandomizer()
    {

        hashTable = new string[TABLE_SIZE];
        AsciiTable = new int[TABLE_SIZE];
        curr_size = 0;

        for (int i = 0; i < TABLE_SIZE; i++) {
            hashTable[i] = "-1"; // -1 means it is empty
            AsciiTable[i] = i;
        }

        random_shuffle(&AsciiTable[0], &AsciiTable[TABLE_SIZE-1]);

    }

    // function to check if hash table is full
    bool isFull(){
        return (curr_size == TABLE_SIZE);
    }

   //function to check if a key is present in HashTable
    bool ispresent(string key) {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == "-1") {
                return false;
            }
            i++;
        }
        return true;
    }

    // function to calculate first hash
    int hash1(string s) {
        int x = 0;
        for (int a = 0; a < s.size(); a++) {
            x = x + (int) (char) s[a];
        }
        if(x < 0) {
            x = -x;
        }
        return (x % TABLE_SIZE);
    }


    // function to calculate second hash
    int hash2(string s)
    {
        int x = 0;
        for (int a = 0; a < s.size(); a++) {
            x = x + (int) (char) s[a];
        }
        if(x < 0) {
            x = -x;
        }
        return (PRIME - (x % PRIME)); // never evaluates to 0
    }



    // function to insert key into hash table
    void insert(string key)
    {
        // check fullness
        if (isFull())
            return;
        // first hash
        int index = hash1(key);
        // if collision occurs
        if (hashTable[index] != "-1") {
            // second hash
            int index2 = hash2(key);
            int i = 1;
            while (1) {
                // get newIndex
                int newIndex = (index + i * index2) % TABLE_SIZE;

                // if no collision occurs, store
                if (hashTable[newIndex] == "-1") {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }
        // if no collision occurs
        else
            hashTable[index] = key;
        curr_size++;
    }

    //function to import AsciiTable
    void importKey(string filename){
        string key2 = filename.substr(0, filename.size()-4) + ".key";
        ifstream infile(key2);
        string str;
        for (int i = 0; i < TABLE_SIZE; i++){
            getline(infile, str);
            if (str == "")
                continue;

            AsciiTable[i] = atoi(str.c_str());
        }
    }

    //function to export AsciiTable
    void exportKey(string filename){
        string key2 = filename.substr(0, filename.size()-4) + ".key";
        ofstream out_file;
        out_file.open(key2,std::ios_base::app);

        for (int i = 0; i < TABLE_SIZE; i++) {
            out_file << AsciiTable[i] << endl;
        }
        out_file.close();
    }

    //function to import HashTable
    void importHash(string filename){
        string key3 = filename.substr(0, filename.size()-4) + ".key";
        ifstream infile(key3);
        string str;

        for (int i = 0; i < TABLE_SIZE; i++) {
            getline(infile, str);
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            getline(infile, str);
            if (str == "")
                continue;

            hashTable[i] = str;
        }
    }

     //function to export HashTable
    void exportHash(string filename){
        string key3 = filename.substr(0, filename.size()-4) + ".key";
        ofstream out_file;
        out_file.open(key3, std::ios_base::app);
         for (int i = 0; i < TABLE_SIZE; i++) {

            if (hashTable[i] != "-1")
                out_file << hashTable[i] << endl;
            else
                out_file << endl;
        }
        out_file.close();
    }


    //to get a value from an index present a HashTable
    string getValue (int key){
        string o = hashTable[key];
        return o;
    }

    // function to search key in hash table
    void search(string key)
    {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == "-1") {
                cout << key << "not found" << endl;
                return;
            }
            i++;
        }
        cout << key << "found" << endl;
    }

    //function to get index value of given item in HashTable
    int getindex(string key){
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (hashTable[(index1 + i * index2) % TABLE_SIZE] != key) {
            if (hashTable[(index1 + i * index2) % TABLE_SIZE] == "-1") {
                return -1;
            }
            i++;
        }
        return ((index1 + i * index2) % TABLE_SIZE);
    }

   //function to return assigned ascii values
   int Ascii(char key) {
       int x;
       string o = "";
       o = to_string(key);
       x = AsciiTable[getindex(o)];
       return x;
   }

    //function to wipe Hashtable
    void clearHash(){
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = "-1";
    }

    // function to display the hashtable
    void displayHash() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != "-1")
                cout << i << " -> "
                     << hashTable[i] << endl;
            else
                cout << i << endl;
        }
    }

    // function to display the Asciitable
    void displayKey() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " -> "
                     << AsciiTable[i] << endl;
        }
    }
};

