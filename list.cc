#include "/public/read.h"
#include <list> // DLL -> Doubly Linked List
#include <forward_list> // SLL -> Singly Linked List
#include <deque>
#include <algorithm>
#include <stdexcept>
using namespace std;

// SLL Big-O:
// Insert: O(1) - ONLY at the end
// Search: O(N) 
// Delete: O(1) - ONLY at the end

// DLL Big-O:
// Insert: O(1) - Front/End
// Search: O(N) 
// Delete: O(1) - Front/end

// INVARIANTS: Things that must always be true!
// 	1. Must have a prev pointer which points to
// 		the previous node in the list or nullptr if no
// 		in front of us
//  2. Ditto for next pointer
//  3. Size always holds the number of nodes in the list
// 
class List {
	struct Node {
		int data{};
		Node* next = nullptr;
		Node* prev = nullptr;
	};
	int size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
	public: 
	List() {} //Super ultra advanced constructor
			  //Choose the form of the destructor
	~List() { //Destructor
		for (Node *ptr = head; ptr; ) {
			Node *next = ptr->next;
			delete ptr;
			ptr = next;
		}
		size -= size;
	}

	int get_size() const { return size; }

	// This is where the fun begins...
	// If you see the buddha...

	// O(1) Insert
	void push_back(int newVal) { // insert at end
								 // Case #1: Am I empty?
		if (!size or !head or !tail) {
			head = tail = new Node(newVal);
		}
		// Case #2: At least 1 item in here
		else {
			Node* newGuy = new Node(newVal);
			tail->next = newGuy;
			newGuy->prev = tail;
			tail = newGuy;
		}
		size++;
	}
	// O(1) Insert
	void push_front(int newVal) { // insert at end
								  // Case #1: Am I empty?
		if (!size or !head or !tail) {
			head = tail = new Node(newVal);
		}
		// Case #2: At least 1 item in here
		else {
			Node* newGuy = new Node(newVal);
			head->prev = newGuy;
			newGuy->next = head;
			head = newGuy;
		}
		size++;
	}
	//Insert value val before index index
	void insert_at(int index, int val) {
		if (index > size or index < 0) throw runtime_error("No you're out of bounds!");
		//Case #1 - list is empty
		//Case #2 - inserting at front
		if (!size or !index) push_front (val); 
		//Case #3 - inserting at end
		else if (index == size) push_back(val);
		//Case #4 - inserting in middle
		else {
			Node* newGuy = new Node(val);
			//Doublemint For loop
			Node *after = head;
			for (int i = 0; i < index; i++) {
				after = after->next;
			}
			Node *previous = after->prev;
			//Four pointers have to update
			//When you insert in the middle
			newGuy->next = after;
			newGuy->prev = previous;
			after->prev = newGuy;
			previous->next = newGuy;
			size++;
		}
	}

	// push_front(int newVal)
	// O(N) Search
	// contains(int key)
	// O(1) Delete
	// pop_back()
	// pop_front()
	// O(N) Print
	void print() {
		for (Node* curNode = head; curNode; curNode = curNode->next) {
			cout << curNode->data << endl;
		}
	}
	void R_print() {
		for (Node* curNode = tail; curNode; curNode = curNode->prev) {
			cout << curNode->data << endl;
		}
	}
};

int main() {
	List lit;
	lit.push_back(10);
	lit.push_back(20);
	lit.push_back(30);
	lit.push_front(42);
	lit.insert_at(3,26); //Put a 26 between 20 and 30
	lit.print();
}
