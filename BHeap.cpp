
#include<iostream>
using namespace std;
template <class keytype>
class BHeap
{
private:
    //Node
    struct Node 
    {
        keytype key;
        int degree;
        Node *child, *sibling, *parent;
    };

    Node *createNode(keytype key) // create node 
    {
        Node *n = new Node;
        n->key = key;
        return n;
    }
    Node* copyNode(Node *copyTo) // returns a copy of node copyTo
    {
        Node* n = new Node;
        n->key = copyTo->key;
        n->degree = copyTo->degree;
        n->child = copyTo->child;
        n->sibling = NULL;
        n->parent = NULL;
        return n;
    }
    Node *H; // head of binomial heap
    Node *Hr;
    
    // helper functions
    Node *InitializeHeap()
    {
        Node *np;
        np = NULL;
        return np;
    }
    void BinomialLink(Node *y, Node *z) // connect two tree(y and z) to create a new tree(Bx + 1)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    Node *mergeHelper(Node *H1, Node *H2) // merge two heap in order
    {
        Node* H = InitializeHeap();
        Node* y;
        Node* z;
        Node* a;
        Node* b;
        y = H1;
        z = H2;
        if (y != NULL)
        {
            if (z != NULL)
            {
                if (y->degree <= z->degree) 
                {
                    H = y;
                   
                }
                else if (y->degree > z->degree) 
                {
                    H = z;
                }    
            }
            else 
            {
               H = y;
            }   
        }
        else 
        {
            H = z;
        }
        while (y != NULL && z != NULL)
        {
            if (y->degree < z->degree)
            {
                y = y->sibling;
            }
            else if (y->degree == z->degree)
            {
                a = y->sibling;
                y->sibling = z;
                y = a;
            }
            else
            {
                b = z->sibling;
                z->sibling = y;
                z = b;
            }
        }
        return H;        
    }
    void printKeyHelper(Node* n) // help print the binomial heap in pre-order 
    {
        if (n == NULL)
        {
            return;
        }
        cout << n->key << " ";
        printKeyHelper(n->child);
        printKeyHelper(n->sibling);
    }
    void deleteHelper(Node *n) // help delete binomial heap (is like post-order)
    {
        if (n == NULL) 
        {
            return;
        }
        deleteHelper(n->child);
        deleteHelper(n->sibling);
        n = NULL;
    }
    Node *Union(Node *H1, Node *H2) // adds the the two binomial heap (like binary addition)
    {
        Node *Heap = InitializeHeap();   
        Heap = mergeHelper(H1, H2);
        if(Heap == NULL)
        {
            return Heap;
        }
        Node *prevX, *nextX, *x;
        prevX = NULL;
        x = Heap;
        nextX = x->sibling;
        while(nextX != NULL)
        {
            if((x->degree != nextX->degree) || ((nextX->sibling != NULL) && (nextX->sibling)->degree == x->degree))
            {
                prevX = x;
                x = nextX;
            }
            else
            {
                if(x->key <= nextX->key)
                {
                    x->sibling = nextX->sibling;
                    BinomialLink(nextX, x);
                }
                else
                {
                    if(prevX == NULL)
                    {
                        Heap = nextX;
                    }
                    else
                    {
                        prevX->sibling = nextX;
                    }
                    BinomialLink(x, nextX);
                    x = nextX;
                }
            }
            nextX = x->sibling;
        }
        return Heap;
    }

    Node *search(Node *h, int k) // looks for node with key k
    {
        Node *x = h;
        Node *p = NULL;
        if(x->n == k)
        {
            p = x;
            return p;
        }
        if(x->child != NULL && p == NULL)
        {
            p = search(x->child, k);
        }
        if(x->sibling != NULL && p == NULL)
        {
            p = search(x->sibling, k);
        }
        return p;
    }

    void decreaseKey(Node *h, int i, int k) // changes the node key with k and heapify the new key to correct position
    {
        int temp;
        Node *p, *y, *z;
        p = search(h , i);
        if(p == NULL)
        {

        }
        if(k > p->key)
        {

        }
        p->key = k;
        y = p;
        z = p->parent;
        while(z != NULL && y->key < z->key)
        {
            temp = y->key;
            y->key = z->key;
            z->key = temp;
            y = z;
            z = z->parent;
        }
    }

    void revertList(Node *y) 
    {
        if(y->sibling != NULL)
        {
            revertList(y->sibling);
            y->sibling->sibling = y;
        }
        else
        {
            Hr = y;
        }
    }

    Node *extractMinHelper(Node *H1) // return the node with minimum key 
    {
        Hr = NULL;
        Node *t = NULL;
        Node *x = H1;
        if(x == NULL)
        {
            cout<<"Nothing to Extract"<<endl;
            return x;
        }
        keytype min = x->key;
        Node *p = x;
        while(p->sibling != NULL)
        {
            if(p->sibling->key < min)
            {
                min = p->sibling->key;
                t = p;
                x = p->sibling;
            }
            p = p->sibling;
        }
        if(t == NULL && x->sibling == NULL)
        {
            H1 = NULL;
        }
        else if(t == NULL)
        {
            H1 = x->sibling;
        }
        else if(t->sibling == NULL)
        {
            t = NULL;
        }
        else
        {
            t->sibling = x->sibling;
        }
        if(x->child != NULL)
        {
            revertList(x->child);
            x->child->sibling = NULL;
        }
        H = Union(H1, Hr);
        return x;
    }
    
    

public:
    keytype peekKey() // return min key without deleting from heap
    {
        return H->key;
    }

    keytype extractMin() // return the minimum key
    {
        Node *np = extractMinHelper(H);
        keytype temp = np->key;
        free(np);
        return temp;
    }

    void insert(keytype key) // insert new key
    {
        Node *x = createNode(key);
        Node * H1 = InitializeHeap();
        x->parent = x->child = x->sibling = NULL;
        x->degree = 0;
        H1 = x;
        H = Union(H, H1);
    }

    void merge(BHeap<keytype> &H2) // merge heap H2 into current heap
    {
        Node* hold = InitializeHeap();
        hold = H2.H;
        Union(H, hold);
        H = hold;
    }

    void printKey() // prints keys in heap
    {
        Node* r = H;
        while (r != NULL) 
        {
            cout << "B" << r->degree << endl;
            cout << r->key << " ";
            printKeyHelper(r->child);
            cout << endl<<endl;
            r = r->sibling;
        }
        cout << endl;
    }

    //constructors, copy, destructors
    BHeap() // default constructor 
    {
        H = InitializeHeap();
        Hr = InitializeHeap();
    }
    BHeap(keytype k[], int s) // constructor that inserts array key type
    {
        for(int i = 0; i < s; i++)
        {
            insert(k[i]);
        }
    }
    BHeap<keytype>& operator=(const BHeap<keytype>& h) // constructor operator
    {
        if (this != &h)
        {
            this->H = h.H;
        }
        return *this;
    }
    BHeap(const BHeap<keytype>& h) // copy constructor 
    {
        this->H = h.H;
    }
    ~BHeap() // deconstructor
    {
        Node* r = H;
        while (r != NULL) 
        {
            deleteHelper(r->sibling);
            Node* hold = r;
            r = r->sibling;
            hold = NULL;
        }
    }

};

