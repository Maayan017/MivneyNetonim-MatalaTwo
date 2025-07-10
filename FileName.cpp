#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key;
    Node* next;
    Node* prev;
};


Node* BuildList()
{
    Node* head = nullptr;
    Node* tail = nullptr;

    while (true)
    {
        if (rand() % 100 + 1 == 1) 
            break;

        Node* node = new Node;
        node->key = (rand() % 100 <= 50) ? 1 : 0;
        node->next = node->prev = nullptr;

        if (!head) {
            head = tail = node;
            head->next = head;
            head->prev = head;
        }
        else {
            node->prev = tail;
            node->next = head;
            tail->next = node;
            head->prev = node;
            tail = node;
        }
        
    }

    
    return head;
}

// פונקציה איטית - זמן ריצה O(n^2)
int Circle_list_1(Node* p)
{
    p->key = 1;
    int k = 0;

    while (true) {
        k = k + 1;

        for (int i = 0; i < k; ++i) {
            p = p->next;
        }

        p->key = 0;

        for (int i = 0; i < k; ++i) {
            p = p->prev;
        }

        if (p->key == 0)
            break;
    }

    return k;
}



// פונקציה יעילה - זמן ריצה O(n log n) עקב מיון
int Circle_list_2(Node* p)
{
    p->key = 1;
    int k = 0;

    while (true) {
        k = k + 1;

        for (int i = 0; i < 2^k; ++i) {
            p = p->next;
        }

        p->key = 0;

        for (int i = 0; i < 2^k; ++i) {
            p = p->prev;
        }

        if (p->key == 0)
            break;
    }

    p->key = 1;
    p = p->next;
    int helper = 1;
    while (true)
    {
        if (p->key == 1)
            break;
        helper++;
        p = p->next;
    }

    return helper;
}


void freeList(Node* head) {
    if (!head) return;
    Node* curr = head->next;
    while (curr != head) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

int main() {
    srand(time(NULL));

    Node* list = BuildList();


    int len1 = Circle_list_1(list);
    cout << "Length using Circle_list_1 (O(n^2)): " << len1 << endl;

    int len2 = Circle_list_2(list);
    cout << "Length using Circle_list_2 (O(n log n)): " << len2 << endl;

    freeList(list);

    return 0;
}
