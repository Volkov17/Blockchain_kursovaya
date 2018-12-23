
#ifndef BLOCKCHAIN_KURS_RSA_H
#define BLOCKCHAIN_KURS_RSA_H



#include <fstream>
#include "cryptkey.h"

using namespace std;


class rsa
{
  //encrypt a string
  hugeint static encrypt(string &data, const vector<char>  &a, const hugeint &b);
  //decrypt a string
  string static decrypt(hugeint &data, const vector<char>  &a, const hugeint &b);
  //extended Euclidean algorithm
  void static extEuclid (hugeint  a, hugeint  b, hugeint &y);
public:
  //get public and private keys
  void static genKeys(cryptkey &pbkey, cryptkey &prkey);
  //encrypt a text file
  void static encryptTxtFile(const char *in, const char *out, cryptkey &key);
  //decrypt a text file
  void static decryptTxtFile(const char *in, const char*out, cryptkey &key);

  string static decrypt (hugeint &data, cryptkey &key);

};


#endif 
