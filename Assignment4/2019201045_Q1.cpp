#include <iostream>

using namespace std;

void Swap(int *a, int *b){
    int k = *a;
    *a = *b;
    *b = k;
}

int Partition(int arr[], int low, int high){
    int t = low;
    Swap(&arr[low], &arr[high]);
    int index = low - 1;
    int key = arr[high];
    for(int i = low ; i < high; i++)
    {
        if(arr[i] <= key)
        {
            index++;
            Swap(&arr[index], &arr[i]);
        }
    }
    index++;
    Swap(&arr[index], &arr[high]);
    return index;
}

int findnth(int *a, int low,int high,int n)
{
    int part = Partition(a,low,high);
    if( part == (n-1))
    {
        return a[part];
    }
    if( part < (n-1))
    {
        return findnth(a,part+1,high,n);
    }
    if( part > (n-1))
    {
        return findnth(a,low,part-1,n);
    }
}

int main()
{
    int no_of_ele,n;
    cin>>no_of_ele;
    int arr[no_of_ele];
    for(int i=0;i<no_of_ele;i++)
    {
        cin>>arr[i];
    }
    //cin>>n  
    //cout<<findnth(arr,0,no_of_ele-1,n); 
    cout<<"\nOutput\n"; 
    for(int i=1;i<=no_of_ele;i++)
    {
        cout<<findnth(arr,0,no_of_ele-1,i)<<endl;
    }
}

