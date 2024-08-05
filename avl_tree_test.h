
#ifndef TREE_TEST

#define TREE_TEST

#include <string>
#include <chrono>

    AvlTree<std::string, int> count_words(std::istream& is){
        AvlTree<std::string,int> ToBeReturned;
        std::string word;
        while(is >> word) ToBeReturned[word]++;
        return ToBeReturned;
    }


#endif // TREE_TEST
