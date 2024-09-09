#ifndef __HASH_TABLE__
#define __HASH_TABLE__



#include <list>
#include "stdio.h"
#include <array>
#include <cstdint>
#include <string>
#include <iostream>
#include <utility>

constexpr uint32_t MAX_TABLE_SIZE = 1 << 18;

/**
 * 
 * @brief Struct to represent (key, value) pair stored in HashTable
 * 
 */
typedef struct DataItem
{
    const char* key;
    int value;
} DataItem;


// typedef std::pair<int, std::string> DataItem;

/// @brief Hash function for mapping string key to the int, index of the internal table
/// @param key 
/// @return Bucket index where to store the data.
/// @note This hashing function is chosen since it is minimizing collisions
uint32_t hash_djb2(const char* key);

class HashTable
{
private:
    /* data */
    // Using more efficient data structure here might be beneficial
    DataItem table[MAX_TABLE_SIZE] = {{nullptr, 0}};
    uint32_t last_mod_idx;
    bool isEmpty(uint32_t idx);

    bool _find_key_idx(const char* key, uint32_t* id);

    DataItem _first_pair;
    DataItem _last_pair;

public:
    HashTable();
    ~HashTable();

    void insert(const char* key, int value);
    void remove(const char* key);

    int get(const char* key);
    DataItem get_last();
    DataItem get_first();

    int get_last_mod_idx();
    uint32_t size;
};

#endif /* __HASH_TABLE__ */