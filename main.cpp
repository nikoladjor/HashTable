#include <stdio.h>
#include "HashTable.h"
#include <array>
#include <vector>
#include "string.h"
#include "FileParser.h"

int main(int, char**){

    DataItem collection[MAX_TABLE_SIZE];

    HashTable myTable;

    std::string fpath = "/home/nikola/source/hash_table_words/words_source.txt";
    FileParser parser(fpath);

    myTable.insert("A",1);
    myTable.insert("A",10);

//    int val = myTable.get("B");


    std::vector<std::string> vv = parser.getExactNumberOfWords(MAX_TABLE_SIZE);
    DataItem di = {vv[1543].c_str(), 2};

    myTable.insert(di.key, di.value);

    for (int i = 0; i < vv.size(); i++)
    {
        try {
            myTable.insert(vv[i].c_str(), i);
            std::cout << i << "inserted OK" << std::endl;
        }
        catch (...) {
            printf("Problem here!\n");
        }
    }



    printf("Hello, from hash_table_words!\n");
}
