#ifndef INSERT_SORT_H_INCLUDED
#define INSERT_SORT_H_INCLUDED
void swap(int &a,int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

bool prior(int a,int b,bool order)
{
    if((a>=b))
        return order==true?true:false;
    else
        return order==true?false:true;

}

void insert_sort(int* A,int n,bool order=true)
{
    for(int i=1;i<n;i++)
        for(int j=i;j>0&&prior(A[j],A[j-1],order);j--)
            swap(A[j],A[j-1]);
    return;
}


#endif // INSERT_SORT_H_INCLUDED
