    using namespace std;
    #include <string>
    #include <iostream> //cin, cout


    // Tree Data Structure & Traversal ----------------------------------------------------
    class Tree { 
        private: 
            char data; 
            Tree *leftptr, *rightptr; 
        public: 
            Tree(char newthing, Tree* L, Tree* R); // constructor with parameters 
            ~Tree() { } char RootData() { return data; } // inline functions 
            Tree* Left() { return leftptr; } 
            Tree* Right() { return rightptr; } 
        };

        Tree::Tree(char newthing, Tree* L, Tree* R) { 
            data = newthing; 
            leftptr = L; 
            rightptr = R; 
        }

        void InOrder(Tree * T){
            if (T == NULL) { return; }

            bool isOperator = (T->RootData() == '+' || T->RootData() == '-' || T->RootData() == '*' || T->RootData() == '/');
            if (isOperator) cout << "(";
            
            InOrder(T->Left());
            cout << T->RootData();
            
            InOrder(T->Right());
            if (isOperator) cout << ")";
        }

    // Unused traversal methods
        void PreOrder(Tree *T) { 
            if (T == NULL) { return; } 
            printf("%c \n", T->RootData()); 
            PreOrder(T->Left()); PreOrder(T->Right()); 
        }

        void PostOrder(Tree *T) { 
            if (T == NULL) { return; } 
            PostOrder(T->Left()); PostOrder(T->Right()); 
            printf("%c \n", T->RootData()); 
        }


    // Stack Data Structure and Methods ----------------------------------------------------

    struct Node {
        Tree* data;
        Node *next; 
    };

    class Stack {
        private:
            Node *listpointer;
            public:
            Stack();
            ~Stack();
            void Push(Tree* newthing);
            void Pop();
            Tree* Top();
            bool isEmpty();
    };

    Stack::Stack() {
        listpointer = NULL;
    }

    Stack::~Stack() {
        while (!isEmpty()) {
            Pop();
        }
    }

    void Stack::Push(Tree* newthing) { // new thing on top of the stack
        Node* newNode = new Node;
        newNode->data = newthing;
        newNode->next = listpointer;
        listpointer = newNode;
    }

    void Stack::Pop() { // remove the top item from the stack // takes care of underflow
        if (listpointer != NULL) {
            Node* temp = listpointer;
            listpointer = listpointer->next;
            delete temp;
        }
    }

    bool Stack::isEmpty() { // return true if the stack is empty
        return listpointer == NULL;
    }

    Tree* Stack::Top() { // return value of the top item in the stack // warning: what if stack is empty?
        if (listpointer == NULL) {
            return NULL;
        }
        return listpointer->data;
    }
    // Main ----------------------------------------------------

    int main() {
        string x;
        //cout << "Enter RPN expression: "; 
        cin >> x;

        Tree *T1, *T2, *T;
        Stack S;    // stack of tree pointers
        
        int n = 0; // indexing into string x
        
        while(n < static_cast<int>(x.length())) { //force casting length of x as int for comparator --- What is best practice here: siz_t, auto, or static casting ??
            
            if(x[n] >= '0' && x[n] <= '9') {
                S.Push(new Tree(x[n],NULL,NULL));
            }
            
            if(x[n] == '+' || x[n] == '-' || x[n] == '*' || x[n] == '/'){
                T1= S.Top();
                S.Pop();
                T2= S.Top();
                S.Pop();
                S.Push(new Tree(x[n],T2,T1)); // careful with order!
            }
            n++;
        }
        T = S.Top();
        InOrder(T);
    }



    /* Pseudo code from lecture
    1: declare Tree *T1, *T2, *T; 
    2: Stack S;//note: S is a stack of tree pointers 
    3: while (expression has data) do 
    4: x = read next item; 
    5: if(x is a number) 
    6: S.Push(new Tree(x,NULL,NULL)); 
    7: endif 
    8: if(x is an operator){ 
    9: T1=S.Top(); 
    10: S.Pop(); 
    11: T2=S.Top(); 
    12: S.Pop(); 
    13: S.Push(new Tree(x,T2,T1));//careful with order! 
    14: endif 
    15: end while 
    16: T = S.Top();*/

    /* 
    Write a C++ program that reads an arithmetic expression in reverse polish notation from
    standard input, and prints out the same expression using infix notation with brackets. You will
    want to construct a tree representing the expression for this. The only integers appearing in
    the expression will be single-digit ones (0. . . 9), so you can use char as data type for the value
    associated with tree nodes. Do not print any spaces (the input contains no spaces either) and
    include brackets for every operator, including the outer-most one. For example:

    Input Output
    10/3+ ((1/0)+3)
    123*4-+ (1+((2*3)-4))
    */