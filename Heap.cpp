#include<iostream>
#include "CDA.cpp"
using namespace std;
template <class keytype>
class Heap
{
    private:
    void swap(keytype *x, keytype *y) // swap the key value of x and y
    {
        keytype temp = *x;
        *x = *y;
        *y = temp;
    }
    int parent(int i) // return the index of parent at index i
    {
        return i / 2;
    }
    int left(int i) // return the index of left child at index i
    {
        return 2 * i;
    }
    int right(int i) // return the index of right child at index i
    {
        return (2 * i) + 1;
    }

    void MinHeapify(int i) 
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap.Length() && heap[l] < heap[i])
        {
            smallest = l;
        }
        if (r < heap.Length() && heap[r] < heap[smallest])
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(&heap[i], &heap[smallest]);
            heapifyUpHelper(smallest);
        }
    }

    void heapifyUpHelper(int i) // down up heapify for set array
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;
        if(l < heap.Length() && heap[l] < heap[smallest])
        {
            smallest = l;
        }
        if(r < heap.Length() && heap[r] < heap[smallest])
        {
            smallest = r;
        }
        if(smallest != i)
        {
            swap(&heap[i], &heap[smallest]);
            heapifyUpHelper(smallest);
        }
    }


    void heapifyUp(int n) // down up heapify 
    {
        for (int i = n; i >= 0; i--) 
        {
            heapifyUpHelper(i);
        }
    }
    // variables
    CDA<keytype> heap;
    keytype hold;
    public:
        keytype peekKey() // returns the value of root/min_value
        {
            return heap[0];
        }
        keytype extractMin()
        {
            if(heap.Length() <= 0)
            {
                return hold;
            }
            if(heap.Length() == 1)
            {
                keytype temp = heap[0];
                heap.DelFront();
                return temp;;
            }

        keytype root = heap[0];
        heap[0] = heap[heap.Length() - 1];
        heap.DelEnd();
        MinHeapify(0);

        return root;
        }
        void insert(keytype element) // insert one element to the binary heap
        {
            heap.AddEnd(element);
            int i = heap.Length() - 1;
            heapifyUp(i);
        }
            
        void printKey() // print the keys in heap from index 0 - (size - 1)
        {
            for(int i = 0; i < heap.Length(); i++)
            {
                cout<<heap[i]<<" ";
            }
            cout<<endl;
        }
        Heap()
        {
            
        }

        Heap(keytype k[], int s) // fill array with values and down up heapify
        {
            for(int i = 0; i < s; i++)
            {
                heap.AddEnd(k[i]);
            }
            heapifyUp(heap.Length() - 1);
        }
        ~Heap() // deconstructor 
        {
        }
        
        Heap<keytype>& operator=(const Heap<keytype> &h) // copy operator 
        {
            if(this != &h)
            {
              this->heap = h.heap;
            }
            return *this;
        }
        Heap(const Heap<keytype> &h) // copy constructor 
        {
           this->heap = h.heap;
        }

};



