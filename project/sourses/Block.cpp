
#include "Block.hpp"


Block::Block(int idx,  std::vector <transaction> &tr, const std::string &ph ,const hugeint &adr ,const hugeint &adr1, const hugeint &adr2,const hugeint &adr3) {
    this->index = idx;
    this->timeplace = boost::posix_time::second_clock::local_time();
    this->prev_hash = ph;
    this->trans = tr;
    this->curr_hash = calc_hash();
    this->address = adr;
    this->part_adr1 = adr1;
    this->part_adr2 = adr2;
    this->part_adr3 = adr3;
}

std::string Block::calc_hash() {
    std::stringstream stream;
    stream << timeplace;
    std::string str_hash = std::to_string(index) + stream.str();
    std::string new_hash = sha256(str_hash);
    std::string new_hash1 = sha256(new_hash + get_hash_of_trans(trans) + prev_hash);
    return new_hash1;
}

std::string Block::get_hash_of_trans(const std::vector < transaction > &tr) {
    std::vector <std::string> array_of_hash;
    std::string sum_of_hash;
    std::string result_hash_trans;
    for (auto it = tr.begin(); it != tr.end(); ++it) {
        std::string str_hash_trans = it->sender + it->recipient + std::to_string(it->amount);
        std::string hash_trans = sha256(str_hash_trans);
        array_of_hash.push_back(hash_trans);
    }
    for (auto it = array_of_hash.begin() ; it != array_of_hash.end() ; ++it){
        sum_of_hash += *it ;
    }
    result_hash_trans = sha256(sum_of_hash);
    return result_hash_trans;
}

std::string Block::get_hash_of_trans (){
    std::string hash_trans;
    std::string result_hash_trans;
    std::vector <std::string> array_of_hash2;
    for (auto it = trans.begin(); it != trans.end(); ++it) {
        std::string str_hash_trans = it->sender + it->recipient + std::to_string(it->amount);
        std::string hash_trans = sha256(str_hash_trans);
        array_of_hash2.push_back(hash_trans);
    }
    for (auto it = array_of_hash2.begin() ; it != array_of_hash2.end() ; ++it){
        hash_trans += *it ;
    }
    result_hash_trans = sha256(hash_trans);
    return result_hash_trans;
}

Block Block::create_gen_blok() {
    std::vector <transaction> gen_array;
    transaction tr = {0 , "genesis" , "genesis" };
    gen_array.push_back(tr);
    Block block2 (0 , gen_array , std::to_string(0),0,0,0,0);
    return block2;
}

int Block::get_index() {
    return this->index;
}

std::string Block::get_time() {
    std::stringstream stream;
    stream << this->timeplace;
    return stream.str();
}

std::string Block::get_hash() {
    return this->curr_hash;
}

hugeint Block::get_address() {
    return this -> address;
}

std::string Block::get_prev_hash() {
    return this->prev_hash;
}

hugeint Block::get_part_adr1() {
    return this->part_adr1;
}

hugeint Block::get_part_adr2() {
    return this->part_adr2;
}

hugeint Block::get_part_adr3() {
    return this->part_adr3;
}

std::vector <transaction> Block::get_trans(){
    return this->trans;
}

void Block::print_trans (){
    using std::cout;
    using std::endl;
    for ( auto it = trans.begin(); it != trans.end() ; ++it) {
        cout << " Amount : " <<  it->amount << endl;
        cout << " Sender : " << it->sender << endl;
        cout << " Recipient : " << it->recipient << endl << endl;
    }
}

void Block::print_trans( const char *filename , Block &block){
    std::ofstream out;
    out.open(filename);
    if ( out.is_open ()) {
        for (auto it = block.trans.begin(); it != block.trans.end(); ++it) {
            out << it->amount;//<< endl;
            out << it->sender;
            out << it->recipient;
        }
    }
}
