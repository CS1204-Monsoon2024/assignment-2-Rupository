#include <iostream>

using namespace std;

bool is_prime(int n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

class HashNode
{
public:
    int key;
    int val;

    HashNode(int k, int v)
    {
        this->key = k;
        this->val = v;
    }
};

class HashTable
{
    int m;            // size of the table
    int n;            // number of keys
    float alpha;      // load factor
    HashNode **table; // array of pointers to HashNode

public:
    HashTable(int size = 5)
    {
        m = size;
        n = 0;
        alpha = 0;
        table = new HashNode *[m]();

        for (int i = 0; i < m; i++)
        {
            table[i] = nullptr;
        }
    }

    void insert(int k)
    {
        if (alpha > 0.8)
        {
            resize();
        }

        int index = h(k);
        int i = 0;

        int probeCount = 0;
        while (table[index] != nullptr)
        {
            if (table[index]->key == k)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return; // Key already exists
            }

            i++;
            
            index = (h(k) + i * i) % m; // quadratic probing
            if (probeCount == (m + 1) / 2)
            {
                cout << "Max probing limit reached!" << endl;
                resize(); // resize and rehash, preventing an infinite loop
                index = h(k); // reset index to new hash function 
            }
            probeCount++;
            
        }

        table[index] = new HashNode(k, k); // insert a new node. the key of the value is the value itself.
        n++;
        alpha = float(n) / float(m); // recalculate alpha
    }

    void remove(int k)
    {
        int index = h(k);
        int i = 0;

        while (table[index] != nullptr)
        {
            if (table[index]->key == k)
            {
                table[index] = nullptr; // deleted
                n--;
                alpha = float(n) / float(m); // recalculate alpha
                return;
            }
            i++;
            index = (h(k) + i * i) % m; // quadratic probing
            // does not need max probe limit condition, as the
            // every position due to insert is correctly mapped
            // to the quadratic probing positions.

        }

        cout << "Element not found" << endl;
    }

    int search(int k)
    {
        int index = h(k);
        int i = 0;

        while (table[index] != nullptr)
        {
            if (table[index]->key == k)
            {
                return index; // return index at which it is found
            }
            i++;
            index = (h(k) + i * i) % m; // quadratic probing
            // does not need max probe limit condition, as the
            // every position due to insert is correctly mapped
            // to the quadratic probing positions.
        }

        return -1; // not found
    }

    void printTable()
    {
        for (int i = 0; i < m; i++)
        {
            if (table[i] == nullptr)
            {
                cout << "- ";
            }
            else
            {
                cout << table[i]->val << " ";
            }
        }
        cout << endl;
    }

private:
    int h(int k)
    {
        return k % m;
    }

    void resize()
    {
        int oldSize = m;
        m = 2 * oldSize + 1;
        while (!is_prime(m))
        {
            m += 2; // ensures m is prime
        }

        HashNode **oldTable = table;
        table = new HashNode *[m]();

        // set resized table to null
        for (int i = 0; i < m; i++)
        {
            table[i] = nullptr;
        }

        // rehash and copy to new table
        for (int i = 0; i < oldSize; i++)
        {
            if (oldTable[i] != nullptr)
            {
                int k = oldTable[i]->key;
                int index = h(k);

                while (table[index] != nullptr)
                {
                    index = (index + 1) % m; // just a linear probe for the rehash
                }

                table[index] = oldTable[i]; // Move the node to the new table
            }

        }

        delete[] oldTable; // free the old table
    }
};
