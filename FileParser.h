#ifndef __FILE_PARSER__
#define __FILE_PARSER__

#include "HashTable.h"
#include <vector>
#include <stdio.h>
#include <fstream>

class FileParser
{
private:
    /* data */
    std::ifstream file;
public:
    FileParser(std::string file_path);
    ~FileParser();
    HashTable createDataSet();
    std::vector<std::string> getExactNumberOfWords(int num_words);

};




#endif /* __FILE_PARSER__ */