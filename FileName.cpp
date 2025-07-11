#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
        node->key = (rand() % 2);
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

int Circle_list_1(Node* p) {
    if (!p) return 0;

    p->key = 1;
    int k = 0;

    while (true) {
        k++;

        // התקדם k צעדים קדימה
        for (int i = 0; i < k; ++i) {
            p = p->next;
        }

        // אפס את הצומת שהגעת אליו
        p->key = 0;

        // חזור k צעדים אחורה
        for (int i = 0; i < k; ++i) {
            p = p->prev;
        }

        // אם הצומת שסימנת קודם כבר אפס → סיימנו
        if (p->key == 0) {
            break;
        }
    }

    return k;
}

int Circle_list_2(Node* p) {

    if (!p) return 0;

    // סימון נקודת ההתחלה
    p->key = 1;
    int k = 0;

    // חיפוש מעריכי: 1, 2, 4, 8, ...
    while (true) {
        int steps = 1 << k;  // 2^k
        k++;

        for (int i = 0; i < steps; ++i) {
            p = p->next;
        }

        p->key = 0;

        for (int i = 0; i < steps; ++i) {
            p = p->prev;
        }

        if (p->key == 0)
            break;
    }

    // חישוב אורך מדויק (מעבר אחד)
    p->key = 1;
    p = p->next;
    int count = 1;

    while (p->key != 1) {
        count++;
        p = p->next;
    }

    return count;
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
    cout << "Length using Circle_list_1 (Theta(n^2)): " << len1 << endl;

    int len2 = Circle_list_2(list);
    cout << "Length using Circle_list_2 (O(n log n)): " << len2 << endl;

    freeList(list);

    return 0;
}
