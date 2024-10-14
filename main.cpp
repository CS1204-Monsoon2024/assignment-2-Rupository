#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(8);
    ht.printTable();
    ht.insert(15);
    ht.printTable();
    ht.insert(22);
    ht.printTable();
    ht.insert(29);
    ht.printTable();

    return 0;
}
