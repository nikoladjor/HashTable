#include <list>
#include "stdio.h"
#include <cstring>
#include "HashTable.h"

uint32_t hash_djb2(const char* key)
{

    std::string _key(key);
    uint32_t ll = _key.length();

    uint32_t hash = 5381;

    for (uint32_t i = 0; i < ll; i++)
    {
        auto c = _key[i];
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;

}

bool HashTable::isEmpty(uint32_t idx)
{
//    std::string ss = this->table[idx].key;
//    return ss.empty();
    return this->table[idx].key == nullptr;
}

bool HashTable::_find_key_idx(const char* key, uint32_t* id)
{
    uint32_t idx = hash_djb2(key); // First obtain the index where to put data in
    idx = idx & (MAX_TABLE_SIZE - 1);

    if(strcmp(this->table[idx].key, key) == 0) {
        *id = idx;
        return true;
    }

    // Key not found at requested idx. It is either removed or there was a confilct
    // BRUTE FORCE SOLUTION: We do not know history of insertions, so we do a search
    for (auto i = 0; i < idx; i++)
    {
        if(strcmp(this->table[i].key, key) == 0) {
            *id = i;
            return true;
        }
    }

    for (auto i = idx+1; i < MAX_TABLE_SIZE; i++)
    {
        if(strcmp(this->table[i].key, key) == 0) {
            *id = i;
            return true;
        }
    }

    // None of the return statements fired, we did not find key
    return false;


}

HashTable::HashTable()
{
    this->size = 0;
    last_mod_idx = 0;
}

HashTable::~HashTable()
{
}


void HashTable::insert(const char* key, int value)
{
    // TODO: Check if we should return a value from insert to know if we actually added data
    // Check if we can actually insert data

    if (this->size == MAX_TABLE_SIZE)
    {
        // We cannot add more data
        return;
    }

    uint32_t idx = hash_djb2(key); // First obtain the index where to put data in
    // Hash value is probably larger than the table size, use module to get the real index
    // Assumtion is that we limit the size of the hash-table to power of two --> this can be improved
//    idx = idx & (MAX_TABLE_SIZE-1);
    idx = idx % MAX_TABLE_SIZE;
    DataItem new_pair = {key, value};

    uint32_t current_search_idx;

    // Now, check if the element exists at the proposed index --> we label the element as 0 if it is emtpy
    if (this->isEmpty(idx))
    {
        // Emtpy slot, just add
        this->table[idx] = new_pair;
    }
    else
    {
        // Slot is occupied, use linear probing to find a new slot or edit existing

        if(strcmp(this->table[idx].key, key) == 0) {
            this->table[idx].value = value;
            this->last_mod_idx = idx;
            this->_last_pair = {key, value};
            return;
        }

        // Forward search
        current_search_idx = this->last_mod_idx + 1;
        // Debug
        for (auto i = current_search_idx; i < MAX_TABLE_SIZE; i++)
        {
            if (this->isEmpty(i))
            {
                this->table[i] = new_pair;
                this->last_mod_idx = i;
                this->size++;
                this->_last_pair = {key, value};
                return;
            } else {
                if(strcmp(this->table[i].key, key) == 0) {
                    this->table[i].value = value;
                    this->last_mod_idx = i;
                    this->_last_pair = {key, value};
                    return;
                }
            }

        }

        // Search from the beginning, rest is full
        for (auto i = 0; i < this->last_mod_idx; i++)
        {
            if (this->isEmpty(i))
            {
                this->table[i] = new_pair;
                this->last_mod_idx = i;
                this->size++;
                this->_last_pair = {key, value};
                return;
            } else {
                if(strcmp(this->table[i].key, key) == 0) {
                    this->table[i].value = value;
                    this->last_mod_idx = i;
                    this->_last_pair = {key, value};
                    return;
                }
            }

        }
        
    }

    // Update the last element and increment the size
    this->last_mod_idx = idx;
    this->size++;

    if(this->size == 1) {
        this->_first_pair = new_pair;
        this->_last_pair = new_pair;
    } else {
        this->_last_pair = new_pair;
    }
}

void HashTable::remove(const char* key)
{
    uint32_t idx;
    bool isFound;
    isFound = this->_find_key_idx(key, &idx);
    if(isFound)
    {
        // Key found
        this->table[idx] = DataItem(); // Make it empty
        this->size -= 1; // Reduce the size info
        // TODO: Should we update most recently deleted as well?
        this->last_mod_idx = idx;
    }
}

int HashTable::get(const char* key)
{
    uint32_t idx;
    bool isFound;
    isFound = this->_find_key_idx(key, &idx);

    if(!isFound) {
        return -1;
    } else {
        return this->table[idx].value;
    }


    // TODO: This is architecture problem: What do we do if there is no key?
    return -1;
}

DataItem HashTable::get_last()
{
    return this->_last_pair;
}

DataItem HashTable::get_first()
{
    return this->_first_pair;
}

int HashTable::get_last_mod_idx()
{
    return this->last_mod_idx;
}
