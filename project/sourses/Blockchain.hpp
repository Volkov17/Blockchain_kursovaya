
#ifndef BLOCKCHAIN_KURS_BLOCKCKAIN_H
#define BLOCKCHAIN_KURS_BLOCKCKAIN_H

#include <iostream>
#include <vector>
#include "Block.hpp"
#include "trusted_comp.hpp"
#include "rsa.hpp"



class Blockchain {

      std::vector <Block> blockchain;
      trusted_node trust;

public:

    Blockchain(int gen) ;

    void adding_new_block ( std::vector <transaction> &tr);
    bool checking_signature ();
    bool valid_chain();
    std::string from_file_hash (const char *out);
    void write_to_file_address(const char *in1 , hugeint a);
    Block get_latest_block() ;
    const char * chain_to_file ();
    void print_chain ();
};

#endif //BLOCKCHAIN_KURS_BLOCKCKAIN_H
