
#include "Blockchain.hpp"

Blockchain::Blockchain(int gen) {
    if (gen == 0) {
        blockchain.push_back(Block::create_gen_blok());
    }
}


void Blockchain::adding_new_block ( std::vector <transaction> &tr){
    hugeint hi1(85);
    hugeint hi2(85);
    hugeint hi3(85);

    std::string ph = get_latest_block().get_hash();
    int idx = get_latest_block().get_index() + 1 ;

    boost::posix_time::ptime time;
    std::stringstream stream;
    stream << time;

    std::string hash = Block::get_hash_of_trans(tr);
    trust.write_to_file("transaction_hash.txt" , hash);

    cryptkey publicKey1 = trust.get_publkey();
    rsa::encryptTxtFile("transaction_hash.txt" ,  "electronic_signature.txt" , publicKey1);

    std::ifstream input("electronic_signature.txt");
    for (size_t i = 0 ; i < 3 ; ++i)
    {
        if ( i == 0 ){
            input >> hi1;
        }
        if ( i == 1){
            input >> hi2;
        }
        if ( i == 2){
            input >> hi3;
        }
        if (input.eof())
            break;
    }
    input.close();

    hugeint signature = trust.from_file("electronic_signature.txt" );

    Block block (idx , tr , ph , signature , hi1 , hi2 , hi3 );
    blockchain.push_back(block);
}

bool Blockchain::checking_signature () {
    for ( auto it = (blockchain.begin()+1) ; it != blockchain.end() ; ++it){
        hugeint a = (*it).get_part_adr1();
        hugeint b = (*it).get_part_adr2();
        hugeint c = (*it).get_part_adr3();
        cryptkey privateKey1 = trust.get_privkey();

        //write_to_file_address("blok_signature.txt", a);
        //rsa::decryptTxtFile("blok_signature.txt", "decrypted_signature.txt", privateKey1);
        //std::string test_hash = from_file_hash("decrypted_signature.txt");

        std::string str1 = rsa::decrypt(a,privateKey1);
        std::string str2 = rsa::decrypt(b,privateKey1);
        std::string str3 = rsa::decrypt(c,privateKey1);
        std::string test_hash = (str1 + str2) + str3;
        if (test_hash == (*it).get_hash_of_trans()) {
            return 1;
        }
    }
    return 0;
}

bool Blockchain::valid_chain(){
    for ( auto it = (blockchain.begin()+1) ; it != blockchain.end() ; ++it){
        if ( (*it).get_hash() != (*it).calc_hash()){
            return false ;
        }

        if ( (*it).get_prev_hash() != ((it-1)->get_hash())){
            return false ;
        }
    }
    return true;
}

std::string Blockchain::from_file_hash (const char *out) {
    std::string str_hash;
    std::ifstream in(out);
    if (in.is_open()) {
        getline(std::cin , str_hash);
    }
    in.close();
    return str_hash;
}

void Blockchain::write_to_file_address(const char *in1 , hugeint a){
    std::ofstream out;
    out.open(in1);
    if (out.is_open()) {
        out << a << std::endl;
    }
}

Block Blockchain::get_latest_block() {
    return blockchain.back();
}

const char * Blockchain::chain_to_file (){
    const char * filename = "result blockchain.txt";
    std::ofstream out;
    out.open(filename);
    if (out.is_open()){
        for ( auto it = blockchain.begin() ; it != blockchain.end() ; ++it){
            //cout << endl;
            Block currentBlock = *it;
            out << "Block == " << "Index " << currentBlock.get_index()  << "\n";
            out << "Time :"   <<  currentBlock.get_time() << "\n"    ;
            //out << "trans " << currentBlock.print_trans();
            currentBlock.print_trans(filename , *it);
            // for (auto it1 = it-> ; )
            out << "address " << currentBlock.get_address()  << "\n"  ;
            out << "hash "    << currentBlock.get_hash()   << "\n"    ;
            out << "prevHash "<< currentBlock.get_prev_hash() << "\n" ;
        }
    }
    return filename;
}

void Blockchain::print_chain () {
    using std::cout;
    using std::endl;
    for (auto it = blockchain.begin(); it != blockchain.end(); ++it)
    {
        cout << endl;
        Block currentBlock = *it;
        cout << "Block == " << "Index : " << currentBlock.get_index() << endl;
        cout << "Time : "   <<  currentBlock.get_time()     << endl;
        cout << "Trans " << endl << endl ; currentBlock.print_trans();
        cout << "Address : " << currentBlock.get_address()   << endl;
        cout << "Hash : "    << currentBlock.get_hash()      << endl;
        cout << "PrevHash : "<< currentBlock.get_prev_hash() << endl;
        cout << endl;
    }
}
