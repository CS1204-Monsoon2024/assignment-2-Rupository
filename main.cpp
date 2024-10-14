#include "HashTable.cpp"

int main() {
    int initialSize = 5; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(3);
    ht.printTable();
    ht.insert(12);
    ht.printTable();
    ht.insert(9);
    ht.printTable(); 
    ht.insert(1);
    ht.printTable();
    ht.remove(1);
    ht.printTable();
    ht.insert(6); 
    ht.printTable();
    ht.insert(5);
    ht.printTable();
    ht.insert(7);
    ht.printTable();
    ht.insert(1);
    ht.printTable();
    ht.insert(4);
    ht.printTable();
    ht.insert(10);
    ht.printTable();
    ht.remove(7);
    ht.printTable();
    ht.insert(23);
    ht.printTable();
    
    return 0;
}
