
#ifndef BLOCKCHAIN_KURS_BLOCK_H
#define BLOCKCHAIN_KURS_BLOCK_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "Sha256.hpp"
#include "hugeint.hpp"




struct transaction {
    double amount;
    std::string sender;
    std::string recipient ;

    transaction (double a = 0 , std::string b = "0" , std::string c = "0" ) { //,  time_t d = 0
        amount = a;
        sender = b;
        recipient = c;

    }
};

class Block {
    //std::string address;
    //std::multimap < std::string , transaction > tr5;
    //std::vector<std::string> merkle;
    //  std::string hash_of_trans;

    int index;
    boost::posix_time::ptime timeplace;
    std::vector <transaction> trans;
    std::string curr_hash;
    std::string prev_hash;
    hugeint address;
    hugeint part_adr1;
    hugeint part_adr2;
    hugeint part_adr3;
public:

    Block(int idx,  std::vector <transaction> &tr, const std::string &ph ,const hugeint &adr ,const hugeint &adr1, const hugeint &adr2,const hugeint &adr3);

    std::string calc_hash();
    static std::string get_hash_of_trans(const std::vector < transaction > &tr);
    std::string get_hash_of_trans ();
    static Block create_gen_blok();
    int get_index();
    std::string get_time();
    std::string get_hash();
    hugeint get_address();
    std::string get_prev_hash();
    hugeint get_part_adr1();
    hugeint get_part_adr2();
    hugeint get_part_adr3();
    std::vector <transaction> get_trans();
    void print_trans ();
    void print_trans( const char *filename , Block &block);
};
#endif //BLOCKCHAIN_KURS_BLOCKCKAIN_H
