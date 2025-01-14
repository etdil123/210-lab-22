#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void pop_front(){
        // if the head null - list is empty nothing to pop
        if (!head) return;
    

        Node * temp = head;

        // if there's only one element - the head equals the tail
        if (head == tail){
            // delete temp and set head/tail to null
            delete temp;
            head = nullptr;
            tail = nullptr;
            return;
        }
        else{
            // make head next point to head prev
            head = temp->next;
            head->prev = nullptr;
            delete temp;
        }
    }

    void pop_back(){
        // If head is null return from function - no items to pop
        if (!head) return;

        Node * temp = tail;

        // if there's only one element - the head equals the tail
        if (head == tail){
            // delete temp and set head/tail to null
            delete temp;
            head = nullptr;
            tail = nullptr;
            return;
        }

        // make the tail equal to prev of tail
        tail = temp->prev;
        // set tail next to null
        tail->next = nullptr;
        // delete temp to pop the element
        delete temp;

    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
            // setting the head prev to nullptr to avoid malloc error
            if (head) head->prev = nullptr;
            else tail = nullptr;
        }   

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
            // setting tail next to nullptr to avoid any memory issues
            if (tail) tail->next = nullptr;
            else head = nullptr;
        }

        delete temp;
        
    }


    void delete_pos(int position){
        // if empty list just return
        if (!head) return;

        if (position < 0) {
            cout << "Position must be greater than 0" << endl;
            return;
        }

        Node * temp = head;

        // going through each element in linked list
        for (int i = 0; i < position; i++){
            // if temp is null - the loop has gone too far 
            if (!temp) {
                cout << "Position too far - no element has been deleted" << endl;
                return;
            }
            temp = temp->next;
        
        }

        if (temp->prev) {
            // get temp prev to point to temp next
            temp->prev->next = temp->next;
        } else {
            // delete head
            head = temp->next; 
        }

        if (temp->next) {
            // get temp next prev point to temp prev
            temp->next->prev = temp->prev;
        } else {
            // delete tail
            tail = temp->prev; 
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;

    srand(time(0));
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    int tempVal, tempPos;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Popped Element from Front:" << endl;
    list.pop_front();
    list.print();

    cout << "Popped Element from Back:" << endl;
    list.pop_back();
    list.print();

    cout << "Please select value to delete: " << endl;
    cin >> tempVal;
    list.delete_val(tempVal);
    list.print();

    cout << "Please select position to delete: " << endl;
    cin >> tempPos;
    list.delete_pos(tempPos);
    
    cout << "\nFinal Doubly Linked List" << endl;
    list.print();


    return 0;
}
