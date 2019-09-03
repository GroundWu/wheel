#include <iostream>
#include "insert_sort.h"
using namespace std;

int main()
{
    int A[] = {1,3,7,1,2,9,5,3,12,4,6};
    int n = sizeof(A)/sizeof(int);

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

    return 0;
}
