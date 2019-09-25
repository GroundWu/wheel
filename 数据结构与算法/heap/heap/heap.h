#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
class heap
{
private:
    int* Heap;  // heap array
    int maxsize;    //maximum size of the heap
    int n;  //Number of elements now in the heap

    // helper function to put element in its correct place
    void shiftdown(int pos)
    {
        int tmp = 0
        while(!isLeaf(pos))
        {
            int j = leftchild(pos); int rc = rightchild(pos);
            if(rc<n && Heap[rc]>Heap[j])
                j=rc;
            if(Heap[pos]>Heap[j]) return;
            // swap
            tmp = Heap[pos];
            Heap[pos] = Heap[j];
            Heap[j] = tmp;

            pos = j;
        }
    }

public:
    heap(int* h,int num,int max)
    {
        Heap = h;
        n = num;
        maxsize = max;
        buildHeap();
    }

    int size() const
    {
        return n;
    }

    bool isLeaf(int pos) const
    {
        return (pos >= n/2)&&(pos<n);
    }

    int leftchild(int pos) const
    {
        return 2*pos+1;
    }

    int rightchild(int pos) const
    {
        return 2*pos+2;
    }

    int parent(int pos) const
    {
        return (pos-1)/2;
    }

    void buildHeap()
    {
        for(int i=(n-1)/2;i>=0;i--)
        {
            shiftdown(i);
        }
    }

    //insert a new value
    void insert(const int& it)
    {
        int tmp = 0
        int cur = n++;
        Heap[cur] = it;
        while((curr!=0) && (Heap[parent(cur)]<Heap[cur]))
        {
            //swap
            tmp = Heap[cur];
            Heap[cur] = Heap[parent(cur)];
            Heap[parent(cur)] = tmp;
            //sift up
            cur = parent(cur);
        }
    }

    int removefirst()
    {
        //swap
        int tmp = Heap[0];
        Heap[0] = Heap[--n];
        Heap[n] = tmp;
        // sift down
        if(n!=0)
            shiftdown(0);
        return Heap[n];

    }

    int remove(int pos)
    {
        int tmp = 0;
        if(pos==(n-1)) n--;
        else
        {
            //swap
            tmp = Heap[pos];
            Heap[pos] = Heap[--n];
            Heap[n] = tmp;
            //sift up
            while((pos>=0)&&(Heap[pos]>Heap[parent(pos)]))
            {
                //swap
                tmp = Heap[pos];
                Heap[pos] = Heap[parent(pos)];
                Heap[parent(pos)] = tmp;

                pos = parent(pos);
            }
            if(n!=0) shiftdown(pos);
            return Heap[n];
        }
    }


#endif // HEAP_H_INCLUDED
