#ifndef CRYPT_H
#define CRYPT_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include "sha1.h"

void sleep(long d);

class Crypt {
public:
    Crypt(std::string, std::string);
    virtual ~Crypt();

    bool Encrypt();
    static void showKey(bool v=true) { dispKey = v; }
    static void silentMode(bool v=true) { silent = v; }
private:
    std::string key;
    std::fstream* file;
    bool badState;
    static bool silent, dispKey;
};







#endif // CRYPT_H
