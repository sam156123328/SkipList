//Cheng Sam Cheang start at 10/10/2023
#include "skiplist.h"
#include <iostream>

int main(){
    SkipList<int,std::string> skiplist1(10, "s");

    skiplist1.InsertElement(60);
    skiplist1.InsertElement(15);
    skiplist1.InsertElement(4);

    skiplist1.DisplaySkipList();

    std::cout << std::endl << std::endl;
    skiplist1.DeleteElement(15);
    skiplist1.DeleteElement(16);

    skiplist1.DisplaySkipList();
}