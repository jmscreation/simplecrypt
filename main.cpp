/***

    Simple Encryption Example
        --No Version Information--
        This is designed for showing the basics of encryption.

    NOTICE:
        This extremely basic encryption is not secure and should not be used for production use!

    Use at own risk! This encrypts the file it is given based on the command line. Follow help documentation.
    You may distribute the content within this project according to the applicable licenses for any library used.

    To decrypt the test.txt file that is within the binary, use encryption key: PaSSwOrD0911

***/


#include <iostream>
#include <string>
#include "crypt.h"

using namespace std;

string PROG_NAME;

string myName(string path){
    size_t pos = path.rfind("\\");
    if(pos == string::npos){
        pos = path.rfind("/");
        if(pos == string::npos) return path;
    }
    return string(path, pos+1, path.size()-pos-1);
}

void displayHelp(){
    cout << "How to use:" << endl
        << PROG_NAME << " (options) <cipher-key> <file-path>" << endl
        << "-showkey    Displays the hashed key result" << endl
        << "-silent     Does not display anything" << endl
        << "-help       Display this help menu" << endl;
}

int main(int argc, const char** argv){
    bool showKey = false, silentMode = false;
    PROG_NAME = myName(argv[0]);
    int ending = 0;
    for(int cmd=1; cmd < argc; cmd++){
        string c = argv[cmd];
        do{
            if(c == "-showkey") {showKey = true; break;}
            if(c == "-silent") {silentMode = true; break;}
            if(c == "-help") {displayHelp(); return 0;}
            if(++ending>2) {
                cout << "Unknown option: " << argv[cmd] << endl << "Please check the help. "<< PROG_NAME <<" -help" << endl;
                return 1;
            }
        } while(0);
    }

    if(ending != 2){
        cout << "Invalid command. Please check the help. "<< PROG_NAME <<" -help" << endl;
        return 1;
    }
    string path(argv[argc-1]);
    string key(argv[argc-2]);

    if(silentMode) Crypt::silentMode();
    if(showKey) Crypt::showKey();
    Crypt enc(path, key);
    return enc.Encrypt();
}
