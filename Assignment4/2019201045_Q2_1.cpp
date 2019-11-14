#include <iostream>

using namespace std;

template <class Y>
struct node{
    int key;
    Y value;
    node<Y>* next;
};


template <class Y>
class umap{
public:
    Y result;
    int error;
    int size=50;
    node<Y> *linklist[50];
    umap()
    {
        for(int i=0;i<size;i++)
        {
            linklist[i]=NULL;
        }
    }
    void insert(int key,Y value)
    {
        int location = key%size;
        if(!linklist[location])
        {
            struct node<Y> *temp = new node<Y>;
            temp->key = key;
            temp->value = value;
            temp->next = NULL;
            linklist[location] = temp;
            return;
        }
        struct node<Y> *temp1 = linklist[location]->next;
        struct node<Y> *prev = linklist[location];
        while(temp1)
        {
            if(temp1->key == key)
            {
                temp1->value = value;
                return;
            }
            prev=temp1;
            temp1 = temp1->next;
        }
        struct node<Y> *temp = new node<Y>;
        temp->key = key;
        temp->value = value;
        temp->next = NULL;
        prev->next = temp;
    }
    void print()
    {
        for(int i=0;i<size;i++)
        {
            if(linklist[i])
            {
                struct node<Y> *temp = linklist[i];
                while(temp)
                {
                    cout<<"("<<temp->key<<","<<temp->value<<")  ";
                    temp=temp->next;
                }
            }
        }
        cout<<endl;
    }
    void find(int key)
    {
        int location = key%size;
        struct node<Y> *temp = linklist[location];
        while(temp)
        {
            if(temp->key == key)
            {
                 result = temp->value;
                 error = 0;
                 return;
            }
            temp=temp->next;
        }
         error = -1;
    }

    void remove(int key)
    {
        int location = key%size;
        if(linklist[location]->key == key)
        {
            struct node<Y> *t = linklist[location]->next;
            free(linklist[location]);
            linklist[location] = t;
            return;
        }
        struct node<Y> *temp = linklist[location]->next;
        struct node<Y> *prev;
        prev = linklist[location];
        while(temp)
        {
            if(temp->key == key)
            {
                prev->next = temp->next;
                free(temp);
                return;
            }
            prev=temp;
            temp=temp->next;
        }
    }
};

int main()
{
    umap<string> um;
    int key;
    string input;
    int choice;
    while(choice!=5)
    {
        cout<<"1. Insert\n";
        cout<<"2. Find\n";
        cout<<"3. Remove\n";
        cout<<"4. Print"
        cout<<"5. Quit\n";
        cin>>choice;
        switch(choice)
        {
            case 1 :
            {
                cin>>key;
                cin>>input;
                um.insert(key,input);
                break;
            }
            case 2 :
            {
                cin>>key;
                um.find(key);
                if(!um.error)
                    cout<<um.result<<endl;
                else
                    cout<<"Not found"<<endl;
                break;
            }
            case 3 :
            {
                cin>>key;
                um.remove(key);
                break;
            }
            case 4 :
            {
                um.print();
                break;
            }
            case 5 :
            {
                return 1;
                break;
            }
        }
    }
}
