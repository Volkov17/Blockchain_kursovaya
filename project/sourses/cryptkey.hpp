
#ifndef BLOCKCHAIN_KURS_CRYPTKEY_H
#define BLOCKCHAIN_KURS_CRYPTKEY_H



#include <fstream>
#include "hugeint.h"



struct cryptkey
{
  hugeint a;
  hugeint b;


  bool loadFromFile(const char *filename)
  {
    hugeint temp(800);
    
    std::ifstream in (filename);
    if (in.good())
    {  
      in >> temp;
      a = temp;
      in >> temp;
      b = temp;
      in.close();
      return true;
    }
    return false;
  }


  bool saveToFile(const char *filename)
  {
    std::ofstream out (filename);
    if (out.good()) 
    {
      out << a << endl;
      out << b << endl;
      out.close();
      return true;
    }
    return false;
  }
};

#endif
