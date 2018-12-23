
#ifndef BLOCKCHAIN_KURS_TRUSTED_COMP_H
#define BLOCKCHAIN_KURS_TRUSTED_COMP_H


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "Block.hpp"
//#include "Blockchain.h"

#include "cryptkey.hpp"
#include "rsa.hpp"
#include "hugeint.hpp"


class trusted_node {

    cryptkey privateKey;
    cryptkey publicKey;

public:

    trusted_node();

    void write_to_file (const char *in1 , const std::string &str_h);
    cryptkey get_privkey();
    cryptkey get_publkey ();
    hugeint from_file(const char *out1);
};


#endif //BLOCKCHAIN_KURS_TRUSTED_COMP_H
