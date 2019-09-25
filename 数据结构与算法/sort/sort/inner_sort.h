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

void bub_sort(int* A,int n,bool order=true)
{
    for(int i=0;i<n-1;i++)
        for(int j=n-1;j>i;j--)
            if(prior(A[j],A[j-1],order))
                swap(A[j],A[j-1]);
    return;
}

void select_sort(int* A,int n ,bool order=true)
{
    for(int i=0;i<n;i++)
    {
        int idx = i;
        for(int j = i+1;j<n;j++)
        {
            if(prior(A[j],A[idx],order))
                idx = j;
        }
        swap(A[i],A[idx]);
    }
    return;
}

// special type of insert sort
void shell_helper(int* A, int n, bool order, int incr)
{
    for(int i=incr;i<n;i+=incr)
    {
        for(int j = i;(j>=incr)&&(prior(A[j],A[j-incr],order));j-=incr)
            swap(A[j],A[j-incr]);
    }
    return;
}

void shell_sort(int* A,int n,bool order=true)
{
    for(int i=n/2;i>=1;i/= 2)
        for(int j=0;j<i;j++)
            shell_helper(&A[j],n-j,order,i);

}

void __merge_sort(int A[],int tmp[],int left,int right,bool order)
{
    if(left==right) return;
    int mid = (left+right)/2;
    __merge_sort(A,tmp,left,mid,order);
    __merge_sort(A,tmp,mid+1,right,order);
    // copy
    for(int i=left;i<=right;i++)
        tmp[i] = A[i];

    int i1=left,i2=mid+1;
    for(int cur=left;cur<=right;cur++)
    {
        if(i1==mid+1)
            A[cur]=tmp[i2++];
        else if(i2>right)
            A[cur]=tmp[i1++];
        else if(prior(tmp[i1],tmp[i2],order))
            A[cur]=tmp[i1++];
        else
            A[cur]=tmp[i2++];
    }
    return;
}

void __merge_sort_opt(int A[],int tmp[],int left,int right,bool order)
{
    if(left==right) return;
    int mid = (left+right)/2;
    __merge_sort_opt(A,tmp,left,mid,order);
    __merge_sort_opt(A,tmp,mid+1,right,order);
    // fill the temp array
    for(int i=left;i<=mid;i++) tmp[i] = A[i];
    for(int i=right;i>=mid+1;i--) tmp[i] = A[mid+1+right-i];
    //merge
    for(int i=left,j=right,k=left;k<=right;k++)
        if(prior(tmp[i],tmp[j],order))
            A[k] = tmp[i++];
        else A[k] = tmp[j--];
        return;
}

void merge_sort(int *A,int n,bool order)
{
    // new a template array
    int * tmp = new int[n];
    __merge_sort_opt(A,tmp,0,n-1,order);
    delete [] tmp;
    return;
}

int __find_privot(int i,int j)
{
    return (i+j)/2;
}

int __partition(int A[],int l,int r,int& privot,bool order)
{
    while(l<r)
    {
        while((l<r)&&prior(A[++l],privot,order));
        while((l<r)&&prior(privot,A[--r],order));
        swap(A[l],A[r]);
    }

    return l;
}

void __quick_sort(int* A, int i,int j,bool order)
{
    if(j<=i) return;
    int privot_idx = __find_privot(i,j);
    swap(A[privot_idx],A[j]);
    int k = __partition(A,i-1,j,A[j],order);
    swap(A[j],A[k]);
    __quick_sort(A,i,k-1,order);
    __quick_sort(A,k+1,j,order);
}


void quick_sort(int *A,int n,bool order)
{
    __quick_sort(A,0,n-1,order);
    return;
}
#endif // INSERT_SORT_H_INCLUDED
