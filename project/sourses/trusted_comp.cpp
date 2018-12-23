
#include "trusted_comp.h"


trusted_node::trusted_node(){
    cryptkey publicKey1, privateKey1;
    rsa::genKeys(publicKey1 , privateKey1);
    this -> privateKey = privateKey1;
    this -> publicKey = publicKey1;
    publicKey.saveToFile("public_key_for_coin.txt");
    privateKey.saveToFile("private_key_for_trustedNode.txt");
};

void trusted_node::write_to_file (const char *in1 , const std::string &str_h){
    std::ofstream out;
    out.open(in1);
    if (out.is_open()) {
        out << str_h << std::endl;
    }
}

cryptkey trusted_node::get_privkey() {
    return this -> privateKey;
}

cryptkey trusted_node::get_publkey (){
    return this -> publicKey;
}

hugeint trusted_node::from_file(const char *out1){
    hugeint signature = 0;
    char ch;
    std::ifstream in(out1);
    if (in.is_open()) {
        while ( in >> ch ){
            signature = signature*10 +ch-'0';
        }
    }
    in.close();
    return signature;
}
