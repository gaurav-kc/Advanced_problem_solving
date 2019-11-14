#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>
#include <limits.h>
#define RAMSIZE 4096
//  size    size in B       no. of elements
//  4gb     4294967296      1073741824
//  1gb     1073741824      268435456
//  512kb   524288          131072
//  32kb    32768           8192
//  4kb     4096            1024
using namespace std;

void createFile(long long int count)
{
    ofstream input("input.txt");
    srand(time(0));
    for(int i=count;i>0;i--)
    {
        input << rand();
        input << '\n';
    }
}

void swap(int* a,int *b)
{
    int temp=*a;
    *a = *b;
    *b = temp;
}


int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

string getInputFileName()
{
    static int i=0;
    string filename = "input_" + to_string(i);
    i++;
    return filename;
}

void swappairs(pair<int,long long int> *a, pair<int,long long int> *b)
{
    int t1 = a->first;
    long long int t2 = a->second;
    a->first = b->first;
    a->second = b->second;
    b->first = t1;
    b->second = t2;
}

void setNode(pair<int,long long int>  *arr,int i,long long int size)
{
    if(i>(size-1)/2)
        return;
    if(i==((size-1)/2))
    {
        if(size%2==0)
        {
            if(arr[2*i + 1].first <= arr[i].first)
            {
                swappairs(&arr[2*i + 1],&arr[i]);
            }
        }else{
            if(arr[2*i + 1].first <= arr[2*i + 2].first)
            {
                if(arr[2*i + 1].first <= arr[i].first)
                {
                    swappairs(&arr[2*i + 1],&arr[i]);
                }
            }else{
                if(arr[2*i + 2].first <= arr[i].first)
                {
                    swappairs(&arr[2*i + 2],&arr[i]);
                }
            }
        }
        return;
    }
    if(arr[2*i + 1].first <= arr[2*i + 2].first)
    {
        if(arr[2*i + 1].first <= arr[i].first)
        {
            swappairs(&arr[2*i + 1],&arr[i]);
            setNode(arr,2*i+1,size);
        }
    }else{
        if(arr[2*i + 2].first <= arr[i].first)
        {
            swappairs(&arr[2*i + 2],&arr[i]);
            setNode(arr,2*i+2,size);
        }
    }
}

void make_min_heap(pair<int,long long int> *arr,long long int size)
{
    long long int i=(size-1)/2;
    for(; i>=0 ;i--)
    {
        setNode(arr,i,size);
    }
}

void setNodeFromBottom(pair<int,long long int> *arr, int i,long long int size)
{
    if(i==0)
        return;
    if(i==(size-1))
    {
        if(size%2 == 0)
        {
            if(arr[i].first <= arr[(i-1)/2].first)
            {
                swappairs(&arr[i],&arr[(i-1)/2]);
            }
        }else{
            if(arr[i].first <= arr[i-1].first)
            {
                if(arr[i].first <= arr[(i-1)/2].first)
                {
                    swappairs(&arr[i],&arr[(i-1)/2]);
                }
            }
            /*else{
                if(arr[i-1] <= arr[(i-1)/2])
                {
                    swapints(&arr[i-1],&arr[(i-1)/2]);
                }
            }
            */
        }
        return;
    }
    if(arr[i].first <= arr[i-1].first)
    {
        if(arr[i].first <= arr[(i-1)/2].first)
        {
            swappairs(&arr[i],&arr[(i-1)/2]);
        }
    /*
    }else{
        if(arr[i-1] <= arr[(i-1)/2])
        {
            swapints(&arr[i-1],&arr[(i-1)/2]);
        }
    */
    }
    return;
}

void insert_in_heap(pair<int,long long int> *arr,pair<int,long long int> val, long long int size)
{
    arr[size-1].first=val.first;
    arr[size-1].second=val.second;
    for(long long int i=size-1; i > 0;i=(i-1)/2)
    {
        setNodeFromBottom(arr,i,size);
    }
}

pair<int,long long int> extractMin(pair<int,long long int> *arr,long long int size,bool flag)
{
    pair<int,long long int> result = arr[0];
    if(flag)
    {
        arr[0]=arr[size-1];
    }
    else
    {
        arr[0].first=INT_MAX;
        arr[0].second=-1;
    }
    setNode(arr,0,size);
    return result;
}

int main(int argc, const char* argv[])
{

    long long int element_count=0;
    //createFile(100000);
    ifstream myfile(argv[1],ios_base::in);
    int a;
    while(myfile >> a)
    {
        element_count++;
    }
    long long int ram_size = RAMSIZE;
    long long int possible_elements = RAMSIZE/(sizeof(int));
    long long int element_count_copy = element_count;
    int no_of_files = 0;
    no_of_files = ceil(element_count/(float)possible_elements);
    //now we have number of files.
    int buffer_for_file[possible_elements];
    element_count_copy = element_count;
    myfile.close();
    ifstream myfile1("input.txt",ios_base::in);
    ifstream myfile2("input.txt",ios_base::in);
    long long int i=0;
    bool flag=true;
    int count=0;
    //cout<<"ele count "<<element_count<<" possible ele "<<possible_elements<<" no of files "<<no_of_files<<endl;
    while(element_count_copy > 0)
    {
        i=0;
        while((i < possible_elements) && (myfile1 >> a ))
        {
            buffer_for_file[i] = a;
            i++;
        }
        //cout<<" and i is "<<i<<endl;
        quickSort(buffer_for_file,0,possible_elements-1);
        //put sorted elements in file
        ofstream temp(getInputFileName());
        for(long long int j=0;j < i;j++)
        {
            a = buffer_for_file[j];
            temp << a;
            temp << '\n';
        }
        element_count_copy = element_count_copy - i;
        temp.close();
    }
    pair<int,long long int> heap[no_of_files];
    long long int buffer_size_per_file = possible_elements/(no_of_files+1);
    ifstream file_array[no_of_files];
    int main_array[no_of_files][buffer_size_per_file];
    for(int i=0;i<no_of_files;i++)
    {
        string filename = "input_" + to_string(i);
        file_array[i].open(filename,ios_base::in);
        long long int j=0;
        while((j<buffer_size_per_file) && (file_array[i] >> main_array[i][j]))
        {
            j++;
        }
        //cout<<"elements copied "<<j<<endl;
        file_array[i].close();
    }
    //init done
    int file_index[no_of_files];
    for(int i=0;i<no_of_files;i++)
    {
        string filename = "input_" + to_string(i);
        file_array[i].open(filename);
        file_array[i] >> heap[i].first;
        heap[i].second = i;
    }
    ofstream result(argv[2]);
    make_min_heap(heap,no_of_files);
    int output_buffer[buffer_size_per_file];
    long long int indices_of_array[no_of_files];
    for(long long int i=0;i<no_of_files;i++)
        indices_of_array[i]=0;
    //while all files get exhausted
    long long int index_of_op_buffer=0;
    pair<int, long long int> minimum;
    pair<int, long long int> pair_to_be_inserted;
    long long int temp,temp1;
    long long int limits[no_of_files];
    for(int i=0;i<no_of_files;i++)
    {
        limits[i]=buffer_size_per_file;
    }
    long long int j=0;
//cout<<"buffer"<<buffer_size_per_file<<"buffer";

    while(heap[0].first!=INT_MAX)
    {
        minimum = extractMin(heap,no_of_files,true);
        temp1 = minimum.second;
        result << minimum.first;
        result << '\n';
        if(file_array[temp1] >> temp)
        {
            pair_to_be_inserted.first = temp;
            pair_to_be_inserted.second = temp1;
        }else{
            pair_to_be_inserted.first = INT_MAX;
            pair_to_be_inserted.second = temp1;
        }
        insert_in_heap(heap,pair_to_be_inserted,no_of_files);
    }

    for(int i=0;i<no_of_files;i++)
        file_array[i].close();
    result.close();
    return 0;
}
