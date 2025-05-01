#include "/public/read.h"
using namespace std;

template <class T>
class Tree {
	class Node {
		T data;
		Node* left;
		Node* right;
		public:
		Node() {
			left = right = nullptr;
		}
		Node(T newData, Node* newLeft = nullptr, Node* newRight = nullptr) {
			data = newData;
			left = newLeft;
			right = newRight;
		}
		~Node() {
			delete left;
			delete right;
		}
		[[nodiscard]]
		T get_data() const { return data; }
		[[nodiscard]]
		Node* get_left() const { return left; }
		[[nodiscard]]
		Node* get_right() const { return right; }

		void set_data(T newData) { data = newData; }
		void set_left(Node* newLeft) { left = newLeft; }
		void set_right(Node* newRight) { right = newRight; }

	};
	Node* root;
	int size;
	[[nodiscard]] //This will send a warning if you ignore the return value
	int recursive_sum(Node* temp) {
		int sum = 0;
		if (!temp) return 0; // If temp is nullptr, return 0
		sum += recursive_print(temp->get_left()); // We're going all the way down the left side of tree until we hit null
		sum += temp->get_data(); // Once we hit null, we print that value
		sum += recursive_print(temp->get_right()); // Once that root is printed, go down the right side of the subtree
		return sum;
	}
	void recursive_print(Node* temp) {
		if (!temp) return; // If temp is nullptr, return from the function
		recursive_print(temp->get_left()); // We're going all the way down the left side of tree until we hit null
		cout << temp->get_data() << endl; // Once we hit null, we print that value
		recursive_print(temp->get_right()); // Once that root is printed, go down the right side of the subtree
	}
	public:
	Tree() {
		root = nullptr;
		size = 0;
	}
	~Tree() {
		delete root;
	}
	[[nodiscard]]
	int get_size() const { return size; }

	void insert(const T& newData) {
		if (!size) {
			root = new Node{newData, nullptr, nullptr};	
			size++;
			return;
		}
		Node* current = root;
		while (current) {
			if (current->get_data() == newData) return;
			if (newData < current->get_data()) {
				if (current->get_left() == nullptr) {
					current->set_left(new Node{newData});
					size++;
					return;
				}
				current = current->get_left();
			}
			else {
				if (current->get_right() == nullptr) {
					current->set_right(new Node{newData});
					size++;
					return;
				}
				current = current->get_right();
			}
		}
	}

	bool contains(const T& key) {
		if (!root) return false;
		Node* current = root;	
		while (current) {
			if (current->get_data() == key) {
				cout << "Found: " << key << " in the tree!" << endl;
				return true;
			}
			if (key < current->get_data()) {
				current = current->get_left();
			}
			else {
				current = current->get_right();
			}
		}
		return false;
	}
	void print() { recursive_print(root); }
};

int main() {
	Tree<string> wedding_list;
	string name;
	while (true) {
		cout << "Please enter a name to join the wedding (Enter QUIT to quit): " << endl;
		cin >> name;
		if (name == "QUIT") break;
		else {
			wedding_list.insert(name);
		}
	}

	wedding_list.print();
	string toSearch;
	while (true) {
		cout << "Please enter a name to see if they are on the wedding list (Enter QUIT to quit):" << endl;
		cin >> toSearch;
		if (toSearch == "QUIT") break;
		else {
			cout << boolalpha << wedding_list.contains(toSearch) << endl;
		}
	}
}
