/***

    Simple XOR Crypt Library
        --No Version Information--
        This is designed for showing the basics of encryption.

    NOTICE:
        This extremely basic encryption is not secure and should not be used for production use!


    This library is free to use and is free to distribute. This is completely open-source and may be modified on your behalf.
***/

#include "crypt.h"

using namespace std;

void sleep(long d) {
    clock_t start=clock();
    while(clock() - start < d);
}

bool Crypt::dispKey = false;
bool Crypt::silent = false;

Crypt::Crypt(string Path, string Key): badState(false) {
    if(!silent) cout << "Encryption started" << endl;
    file = new fstream(Path, ios_base::in | ios_base::out | ios_base::binary);
    { //SHA1 hash key
        SHA1 hash;
        hash.addBytes(Key.data(), Key.size());
        unsigned char* digest = hash.getDigest();
        key = string(digest, digest + 20);
        if(dispKey && !silent){
            cout << "Key: ";
            for(unsigned char x : key) cout << ("0123456789abcdef")[(int(x)/16)] << ("0123456789abcdef")[(int(x)%16)];
            cout << endl;
        }
    }
    for(int t=0;!file->is_open();t++){
        sleep(200);
        file->clear();
        file->open(Path, ios_base::in | ios_base::out | ios_base::binary);
        if(t > 3){
            if(!silent) cout << "Cannot access file path! \"" << Path << "\" is inaccessible at this time." << endl;
            badState = true;
            return;
        }
    }
}

Crypt::~Crypt(){
    if(!badState){
        file->flush();
    }
    file->close();
    delete file;
    if(!silent){
        if(badState) cout << "An Error Occurred!" << endl; else cout << "Encryption finished" << endl;
    }
}

bool Crypt::Encrypt(){
    if(badState) return 2;
    stringstream data;
    file->seekg(0, file->beg);
    data << file->rdbuf(); //file into memory
    file->seekg(0, file->end);
    unsigned int len = file->tellg();
    file->seekp(0, file->beg);
    const string& sdata = data.str();
    for(unsigned int pos=0; pos < len; ++pos) *file << char(sdata[pos] ^ key[pos % key.size()]); //This is the XOR encryption process
    return 0;
}
