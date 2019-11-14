#include <iostream>
typedef long long int lli;
using namespace std;

struct node{
    bool val;
    struct node* arr[2];
};

struct treeptr{
    struct node* arr[2];
};

struct treeptr* createTree()
{
    struct treeptr* temp = new treeptr;
    temp->arr[0]=NULL;
    temp->arr[1]=NULL;
    return temp;
}

struct node* createNode(bool val)
{
    struct node* temp = new node;
    temp->val = val;
    temp->arr[0]=NULL;
    temp->arr[1]=NULL;
    return temp;
}


void insert(struct treeptr* root,lli val)
{
    struct node* temp;
    struct node* temp1;
    bool rep[64];
    for(int i=0,j=63;i<64;i++,j--)
    {
        rep[j]=val&1;
        val=val>>1;
    }
    /*          prints bool rep of number
    for(int i=0;i<64;i++)
        cout<<arr[i];*/
    if(!(root->arr[rep[0]]))
    {
        temp=createNode(rep[0]);
        root->arr[rep[0]]=temp;
    }
    temp=root->arr[rep[0]];
    for(int i=1;i<64;i++)
    {
       if(!(temp->arr[rep[i]]))
        {
            temp1=createNode(rep[i]);
            temp->arr[rep[i]]=temp1;
        }
        temp=temp->arr[rep[i]];
    }
}

lli printXor(struct treeptr* root,lli x)
{
    bool xval[64];
    for(int i=0,j=63;i<64;i++,j--)
    {
        xval[j]=x&1;
        x=x>>1;
    }
    /*
    for(int i=0;i<64;i++)
        cout<<xval[i];
    cout<<endl;*/
    struct node* temp;
    lli result=0;
    if(root->arr[!(xval[0])])
    {
        temp=root->arr[!(xval[0])];
    }else{
        temp=root->arr[(xval[0])];
    }
    result=result*2+temp->val;
    for(int i=1;i<64;i++)
    {
        if(temp->arr[!(xval[i])])
        {
            temp=temp->arr[!(xval[i])];
        }else{
            temp=temp->arr[(xval[i])];
        }
        result=result*2+temp->val;
    }
    return result;
}

int main()
{
    lli q,n,x,input;
    cin>>n;
    cin>>q;
    if(n<1)
        return 0;
    lli arr[n];
    struct treeptr* root = createTree();
    for(lli i=0;i<n;i++)
    {
        cin>>input;
        insert(root,input);
    }
    while(q--)
    {
        cin>>x;
        input=printXor(root,x);
        input = input^x;
        cout<<input<<endl;
    }
    return 0;
}
