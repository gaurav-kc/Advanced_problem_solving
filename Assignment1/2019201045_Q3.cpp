#include<iostream>
#include "mydeque.h"
#include<string>
#include<unordered_map>
typedef long long int lli;
using namespace std;
unordered_map<string,string> value;
deque<string> *q;
bool FULL=false;
int size;

string get(string key)
{
    auto itr1 = value.find(key);
    if(itr1 == value.end())
    {
        //invalid request. Nothing to do here
        return to_string(-1);
    }else
    {
        //latest reference. Pop the key and push_back it
        //cout<<itr1->second<<endl;
        q->removekey(key);
        q->push_back(key);
    }
    //q.p();
    return itr1->second;
}

void set(string key, string input)
{
    auto itr2 = value.find(key);
    if(itr2 == value.end())
    {
        //pop the least recently used one
        if(FULL)
        {
            value.erase(q->front());
            q->pop_front();
        }
        //push_back this new key
        q->push_back(key);
        value[key]=input;
        if(!FULL)
        {
            if(q->validSize() == size)
                FULL = true;
        }
    }else{
        //pop the input key
        q->removekey(key);
        value[key]=input;
        //push_back this new key
        q->push_back(key);
    }
    //q.p();
}

int main()
{
    string key;
    string input;
    char choice;
    cin>>size;
    int allowed_pushes = 0;
    int queries;
    cin>>queries;
    deque<string> dq(size+queries+2);
    q=&dq;
    while(queries--)
    {
        cin>>choice;
        switch(choice)
        {
            case 'G' :
            {
                cin>>key;
                cout<<get(key)<<endl;
            }
            break;
            case 'S' :
            {
                cin>>key;
                cin>>input;
                set(key,input);
            }
            break;
            case 3 :
            {
                return 0;
            }
            break;
            default :
            {

            }
            break;
        }
    }
    return 0;
}
