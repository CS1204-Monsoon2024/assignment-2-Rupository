#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 
    ht.insert(71);
    ht.printTable();
    ht.insert(13);
    ht.printTable();
    ht.insert(4);
    ht.printTable();

    int find = ht.search(13);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
