/** Standard Double Hash which takes the ascii values of strings and places them accordingly
 *  Only difference is ascii values are predefined by another class "AsciiRandomizer"
 *  Supports importing/exporting the table
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "AsciiRandomizer.cpp"


using namespace std;

// Used in second hash function.
#define PRIME 941

// Hash table size
#define TABLE_SIZE 4096

class DoubleHash {
    // Pointer to an array containing buckets
    string* hashTable;
    int curr_size;
    AsciiRandomizer AR;

public:
    DoubleHash()
    {
        hashTable = new string[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = "-1"; // -1 means it is empty
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
            x = x + AR.Ascii(s[a]);
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
            x = x + AR.Ascii(s[a]);
        }
        if(x < 0) {
            x = -x;
        }
        return (PRIME - (x % PRIME)); // never evaluates to 0
    }

    //function to wipe Hashtable
    void clearHash(){
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = "-1";
    }

    // function to insert key into hash table
    void insert(string key)
    {
        AR.insert(key); //insert to AR first

        if (isFull()) //check if full
            return;

        int index = hash1(key); //first index

        // if collision occurs
        if (hashTable[index] != "-1") {
            int index2 = hash2(key); //second hash
            int i = 1;
            while (1) {
                // get newIndex
                int newIndex = (index + i * index2) % TABLE_SIZE;

                // if no collision occurs, store
                // the key
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

    //function to import HashTable
    void importHash(string filename){
        AR.importKey(filename); //import key
        AR.importHash(filename); //import hash of AR
        string key1 = filename.substr(0, filename.size()-4) + ".key";
        ifstream infile(key1);
        string str;

        for (int i = 0; i < TABLE_SIZE; i++) { //skipping lines in key file
            getline(infile, str);
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            getline(infile, str);
        }
        for (int i = 0; i < TABLE_SIZE; i++){
            getline(infile, str);
            if (str == "")
                continue;

            hashTable[i] = str;
        }
    }

    //function to export HashTable
    void exportHash(string filename) {
        AR.exportKey(filename);
        AR.exportHash(filename);
        string key1 = filename.substr(0, filename.size()-4) + ".key";
        ofstream out_file;
        out_file.open(key1,std::ios_base::app);

        for (int i = 0; i < TABLE_SIZE; i++) {

            if (hashTable[i] != "-1")
                out_file << hashTable[i] << endl;
            else
                out_file << endl;
        }
      out_file.close();
    }

     //function to get the value in given index
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
                cout << key << " does not exist" << endl;
                return;
            }
            i++;
        }
        cout << key << " found" << endl;
    }

    // function to get index of a given key
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

    // function to display the hash table
    void displayHash() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != "-1")
                cout << i << " --> "
                     << hashTable[i] << endl;
            else
                cout << i << endl;
        }
    }
};

