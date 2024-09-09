#include "gtest/gtest.h"
#include "HashTable.h"


TEST(TestHashTable, testInit){
    HashTable myTable;
    ASSERT_EQ(myTable.size, 0);
}


TEST(TestHashTable, testInsertSimple){
    HashTable myTable;
    myTable.insert("A",1);
    myTable.insert("B",2);
    myTable.insert("C",3);

    ASSERT_EQ(myTable.size, 3);
}


TEST(TestHashTable, testInsertMultiple){
    HashTable myTable;
    const char* key_A = "A";
    myTable.insert(key_A,1);
    myTable.insert("B",2);
    myTable.insert(key_A,3);

    ASSERT_EQ(myTable.size, 2);
}


TEST(TestHashTable, testGetExisting){
    HashTable myTable;
    myTable.insert("A",1);
    myTable.insert("B",2);
    myTable.insert("C",3);

    ASSERT_EQ(myTable.get("A"), 1);
    ASSERT_EQ(myTable.get("B"), 2);
    ASSERT_EQ(myTable.get("C"), 3);
    

}

TEST(TestHashTable, FirstItemTest){
    HashTable myTable;
    DataItem first = {"Z", 0};
    myTable.insert(first.key, first.value);
    myTable.insert("A",1);
    myTable.insert("B",2);
    myTable.insert("C",3);

    DataItem gotFirst = myTable.get_first();

    ASSERT_TRUE(
        (first.key == gotFirst.key) && (first.value == gotFirst.value)
    );
}

TEST(TestHashTable, LastItemTest){
    HashTable myTable;
    DataItem first = {"Z", 0};
    DataItem lst_item = {"Y", 3};
    myTable.insert(first.key, first.value);
    myTable.insert("A",1);
    myTable.insert("B",2);
    myTable.insert("C",3);
    myTable.insert(lst_item.key, lst_item.value);


    DataItem gotLast = myTable.get_last();

    ASSERT_EQ(lst_item.key, gotLast.key);

    ASSERT_TRUE(
        (lst_item.key == gotLast.key) && (lst_item.value == gotLast.value)
    );
}


TEST(TestHashTable, TestRemoveItem){
    HashTable myTable;
    DataItem first = {"Z", 0};
    DataItem lst_item = {"Y", 3};
    myTable.insert(first.key, first.value);
    myTable.insert("A",1);
    myTable.insert("B",2);
    myTable.insert("C",3);
    myTable.insert(lst_item.key, lst_item.value);

    myTable.remove("A");

    ASSERT_EQ(myTable.size, 4);
//    ASSERT_EQ(myTable.get("A"), -1);

}