#include <iostream>
#include <cmath>
using namespace std;

const int p = 101; 
// a prime chosen according to sample space size for rolling hash
// assume our linked lists accepts around 100 unique possible
// integers as values in this case.
// adjust for sample space as needed.

const int m = 6562307; 
// a large prime modulus for hashing. Larger the m, lower the chance
// for the hashes of two nonequal linked lists to be equivalent.
// adjust as needed, convert to long long int if needed.

class Node
{
public:
    int key;
    Node *next;

    Node(int k, int h = 0)
    {
        key = k;
        next = NULL;
    }
};

class LinkedList
{
    Node *head;
    int size;
    

public:
    int hash;

    LinkedList()
    {
        head = NULL;
        size = 0;
        hash = 0;
    }

    void insert(int k) // inserts at head: default O(1) insert as
    // directed in the lecture "LL insert and delete"
    {
        Node *dataNode = new Node(k);

        if (head == NULL)
        {
            head = dataNode;
            cout << "Inserted" << endl;
            size ++;
            
            long long int currentHash = k*pow(p, size-1);
            // long as this value may get quite large
            hash = (hash + currentHash) % m; // a rolling hash is computed on each insert

            return;
        }

        dataNode->next = this->head;
        this->head = dataNode;
        cout << "Inserted" << endl;
        size ++;
        
        long long int currentHash = k*pow(p, size-1);
        hash = (hash + currentHash) % m;

        return;
    }

    Node *search(int k) // O(n) worst case, same as done in class
    {
        Node *x = head;
        while (x != NULL)
        {
            if (x->key == k)
            {
                cout << "Found" << endl;
                return x;
            }
            x = x->next;
        }
        cout << "Not Found" << endl;
        return x;
    }

    void del(int k) // O(n) in all cases, as complete traversal after deletion is necessarry for rehashing
    {
        Node *removeNode = search(k);
        if (removeNode == NULL)
        {
            cout << "Empty" << endl;
            return;
        } 
        else if (removeNode == head)
        {
            head = removeNode->next;
            free(removeNode);
            size --;
            cout << "Deleted" << endl;
            
            hash = 0;
            return;
        }

        Node *prev = head;
        while (prev->next != removeNode)
        {
            prev = prev->next;
        }

        prev->next = removeNode->next;
        free(removeNode);
        size --;
        cout << "Deleted" << endl;
        
        hash = 0; // recompute hash with new list, 
        //now that deleted element is not present
        Node* current = head;
        int raisedTo = size - 1;
        while (current != NULL)
        {
            long long int currentHash = (current->key)*pow(p, raisedTo);
            hash = (hash + currentHash) % m;
            current = current->next;
            raisedTo --;
        }
        
        return;
    }
    
    /*void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* x = head;
        while (x) {
            cout << x->key << " -> "; 
            x = x->next;
        }
        cout << "NULL" << endl; 
    }*/

    bool fastEQcheck(const LinkedList other) // O(1): Only constant (one) comparison needed!
    {
        if (hash == other.hash)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};

int main()
{
    LinkedList test;
    test.insert(5);
    test.insert(4);
    test.insert(7);
    test.insert(13);
    //test.display();

    LinkedList test2;
    test2.insert(12);
    test2.insert(5);
    test2.insert(4);
    test2.insert(7);
    test2.insert(13);
    test2.del(12);
    //test2.display();


    LinkedList test3;
    test3.insert(5);
    test3.insert(4);
    test3.insert(7);
    test3.insert(5);
    test3.insert(4);
    test3.insert(7);
    //test3.display();

    LinkedList test4;
    test4.insert(5);
    test4.insert(4);
    test4.insert(7);
    test4.insert(1);
    //test4.display();

    cout << test.fastEQcheck(test2) << endl; // should print 1 (True)
    cout << test2.fastEQcheck(test) << endl; // (test both sides)

    cout << test.fastEQcheck(test3) << endl; // should print 0 (False, different size and thus different hashing)
    cout << test3.fastEQcheck(test) << endl;

    cout << test.fastEQcheck(test4) << endl; // should print 0 (False, same size but different hashing)
    cout << test4.fastEQcheck(test) << endl;
    
    return 0;
}