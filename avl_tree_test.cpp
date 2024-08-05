

#include <iostream>
#include <string.h>
#include <chrono>
#include <map>
#include <fstream>
#include "avl_tree.h"
#include "avl_tree_test.h"
using namespace std;

int main()
{
    AvlTree<int,std::string> mytree;
    mytree.Graph();

    cout << "\n\n";

    mytree.Insert(2,"B");
    mytree.Graph();

    cout << "\n\n";


    mytree.Insert(3,"C");
    mytree.Insert(4,"D");
    mytree.Graph();

    cout << "\n\n";


    mytree.Insert(5,"E");
    mytree.Insert(6,"F");
    mytree.Insert(7,"G");
    mytree.Insert(8,"H");
    mytree.Graph();

    cout << "\n\n";


    mytree.Insert(9,"I");
    mytree.Insert(10,"J");
    mytree.Graph();

    cout << "\n\n";


    mytree.Remove(2);
    mytree.Graph();

    cout << "\n\n";


    mytree.Remove(4);
    mytree.Graph();


    cout << "\n\n";

    AvlTree<int,std::string> mytree2;
    mytree2 = mytree;
    mytree.Graph();


    for (int rep = 0; rep < 5; ++rep)
     {
         ifstream is("beagle_voyage.txt");
         if (!is){
             cout << "Error opening input file.\n";
             return 1;
         }
         auto start_time = std::chrono::high_resolution_clock::now();
         AvlTree<string,int> wcnt = count_words(is);
         auto end_time = std::chrono::high_resolution_clock::now();
         auto time = end_time - start_time;
         std::cout << "Ellapsed time: " << time/std::chrono::milliseconds(1) << " ms.\n";
         is.close();
     }






    return 0;
}
