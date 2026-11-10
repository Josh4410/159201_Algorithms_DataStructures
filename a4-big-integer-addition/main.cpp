using namespace std;
#include <vector>
#include <cstdio> //printf()
#include <iostream> //cin, cout

vector<int> x;

//lecture 
template <class T>
class List {
    private:
        struct Node {
            T data;
            Node *next;
        };
        Node *front, *current;
    public:
        List();
        ~List();
        void AddtoFront(T newthing);
        bool FirstItem(T & item);
        bool NextItem(T & item);
        void AddtoBack(T newthing);
    };

template <class T> //construction
    List<T>::List() {
    front = NULL; current = NULL;
}

template <class T> // Destructor
List<T>::~List() {

}

// lecture data struct functions
template <class T>
void List<T>::AddtoFront(T newthing) {
    Node *temp;
    temp = new Node;
    temp->data = newthing;
    temp->next = front;
    front = temp;
}

template <class T>
bool List<T>::FirstItem(T & item) {
    if (front == NULL) { 
        return false; 
    }
    item = front->data;
    current = front;
    return true;
}

template <class T>
bool List<T>::NextItem(T & item) {
    current = current->next;
    if (current == NULL) { return false; }
    item = current->data;
    return true;
}





// added back elemnt
template <class T>
void List<T>::AddtoBack(T newthing) {
    Node *temp = new Node;
    temp->data = newthing;
    temp->next = NULL;
    if (!front) { 
        front = temp; return; 
    }
    Node *cur = front;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = temp;
}

//basically lecture func
void DisplayWholeNumber(List<int> &L){
    bool ok; int x;
    ok = L.FirstItem(x); //52 prints first
    while (ok) {
        printf("%i", x); //prints List as string 535428
        ok = L.NextItem(x);
    }
}




List<int> num1, num2, result;
// helper methods

void GetData() { //input
    string s1, s2; // could have used unsigned long, but hits digit limit
    //cout << "num1: ";
    cin >> s1;
    //cout << "num2: ";
    cin >> s2;
    for (char c : s1) {
        num1.AddtoBack(c - '0');
    }
    for (char c : s2) {
        num2.AddtoBack(c - '0');
    }
}

void addition(){
    vector<int> a, b;
    int x; bool ok;
    ok = num1.FirstItem(x); 
    while (ok) { //for every x in num1, add to vector a
        a.push_back(x); 
        ok = num1.NextItem(x);
    }
    
    ok = num2.FirstItem(x); //same num2, vector b
    while (ok) { 
        b.push_back(x); 
        ok = num2.NextItem(x); 
    }

    int carry = 0;
    int i = a.size() - 1; // need to work backwards / start at end
    int j = b.size() - 1; 

    while (i >= 0 || j >= 0 || carry) { // Until i've reached end of vectors a,b OR if I have a spare carry
        int sum = carry; //add carry at start
        if (i >= 0) { 
            sum = sum + a[i]; //add num in a
            i--; 
        }
        if (j >= 0) { 
            sum = sum + b[j]; // Add num in b
            j--; 
        }
        carry = sum / 10; // Convert 10s column for carry, want:1 have: 10, carry = 1, int division saves me from fractions
        result.AddtoFront(sum % 10); // add to front ones column digit
    }
}



List<int> L; //creates list of integers
int main() {
    GetData();
    //cout << "num1   = "; DisplayWholeNumber(num1);
    //cout << "num2   = "; DisplayWholeNumber(num2);
    addition();
    DisplayWholeNumber(result);
    return 0;
}
