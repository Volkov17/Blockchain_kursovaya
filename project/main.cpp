#include <iostream>
#include <ctime>
#include <vector>

#include "trusted_comp.h"
#include "Block.h"
#include "Blockchain.h"
#include "client.h


int main() {

      Blockchain volkovCoin(0); //создаем монету и генерим гениз блок

    //  volkovCoin.get_latest_block().print_trans();
      std::cout << std::endl;
      volkovCoin.print_chain();

      transaction tr1 = {1 , "olya" , "masha"};
      std::vector < transaction > arr;
      arr.push_back(tr1);

      std::cout << std::endl;

      volkovCoin.adding_new_block(arr);

      volkovCoin.get_latest_block().print_trans();
      std::cout << std::endl;
      volkovCoin.print_chain();


      const char * filename1 = volkovCoin.chain_to_file();

     


      transaction tr3 = {4 , "pasha" , "dima"};
      transaction tr2 = {2 , "olya" , "nikita"};
      std::vector < transaction > arr1;
      arr1.push_back(tr2);
      arr1.push_back(tr3);

      volkovCoin.adding_new_block(arr1);

      transaction tr4 = {3 , "gena" , "kate"};
      transaction tr5 = {6 , "alina" , "sonya"};
      transaction tr6 = {10 , "gudgf" , "regeg"};
      std::vector < transaction > arr2;
      arr2.push_back(tr4);
      arr2.push_back(tr5);
      arr2.push_back (tr6);

      volkovCoin.adding_new_block(arr2);

      std::cout << std::endl;
      volkovCoin.print_chain();

      if (volkovCoin.valid_chain()){
             std::cout << " valid" << std::endl ;
      }
      else {
            std::cout << " unvalid" << std::endl;
      }

      volkovCoin.checking_signature();
      
      connect_with_server(filename1);

//      if (volkovCoin.checking_signature()){
//          std::cout << " valid" << std::endl ;
//      }
//      else {
//          std::cout << " unvalid" << std::endl;
//      }


      Block hackBlock = volkovCoin.get_latest_block();

      std::vector <transaction> hackArr;
      transaction hacktr = {10 , "grfv" , "drg"};
      hackArr.push_back(hacktr);
    return 0;
}
