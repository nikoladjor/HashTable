#include "FileParser.h"


FileParser::FileParser(std::string file_path)
{
    this->file.open(file_path.c_str());
}

FileParser::~FileParser()
{
    this->file.close();
}

std::vector<std::string> FileParser::getExactNumberOfWords(int num_words)
{
    std::vector<std::string> vv;
    std::string word;
    int count = 0;

    if (!this->file.is_open())
    {
        return vv;
    }
    
    while (file >> word)
    {
        vv.push_back(word);
        count++;
        if(count > (num_words-1)) break;
    }

    // Go back to start
    this->file.clear();
    this->file.seekg(0);

    return vv;
    
}
