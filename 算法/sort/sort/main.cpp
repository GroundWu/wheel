#include <iostream>
#include "inner_sort.h"
using namespace std;

int main()
{
    int A[] = {1,3,2,4,6,9,7,4,8,11,10};
    int n = sizeof(A)/sizeof(int);
    /*
    cout<<"origin"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;
    // insert sort
    insert_sort(A,n,true);

    cout<<"sorted(desc)"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;

    insert_sort(A,n,false);

    cout<<"sorted(asc)"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;
    */

    cout<<"origin"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;
    // bub sort
    //bub_sort(A,n,true);
    // select sort
    //select_sort(A,n,true);
    // shell sort
    //shell_sort(A,n,true);
    // merge sort
    //merge_sort(A,n,true);
    //quick sort
    quick_sort(A,n,true);

    cout<<"sorted(desc)"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;

    //bub_sort(A,n,false);
    //select_sort(A,n,false);
    //shell_sort(A,n,false);
    // merge_sort(A,n,false);
    quick_sort(A,n,false);

    cout<<"sorted(asc)"<<endl;
    for(int i=0;i<n;i++)
        cout<<A[i]<<" ";
    cout<<endl;
    return 0;
}
