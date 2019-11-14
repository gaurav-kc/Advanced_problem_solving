#include <iostream>
#include <string.h>
using namespace std;

typedef struct node{
    char *c;
    struct node *next;
};

class stringBuilder{
    public:
    struct node *root;

    stringBuilder(char *input)
    {
        int i=0;
        struct node *temp = new struct node;
        temp->c = input;
        temp->next = NULL;
        root = temp;
    }

    stringBuilder(stringBuilder input1, stringBuilder input2)
    {
        struct node *temproot = new struct node;
        root = temproot;
        temproot->c = input1.root->c;
        struct node *tp1 = input1.root;
        while(tp1->next)
        {
            struct node *tpnew = new struct node;
            temproot->next = tpnew;
            tpnew->c = tp1->next->c;
            tpnew->next = tp1->next->next;
            tp1 = tp1->next;
            temproot = temproot->next;
        }
        tp1 = input2.root;
        struct node *tpnew = new struct node;
        tpnew->c = tp1->c;
        tpnew->next = tp1->next;
        temproot->next = tpnew;
        temproot = temproot->next;
        while(tp1->next)
        {
            struct node *tpnew = new struct node;
            temproot->next = tpnew;
            tpnew->c = tp1->next->c;
            tpnew->next = tp1->next->next;
            tp1 = tp1->next;
            temproot = temproot->next;
        }
    }

    void print()
    {
        struct node* temp = root;
        while(temp)
        {
            cout<<temp->c;
            temp=temp->next;
        }
    }

    char* getCharArray()
    {
        struct node* temp = root;
        int i=0,len=0;
        while(temp)
        {
            i=0;
            while(temp->c[i] != '\0')
            {
                len++;
                i++;
            }
            temp=temp->next;
        }
        char* tp = new char[len+1];
        i=0;
        len=0;
        temp = root;
        while(temp)
        {
            i=0;
            while(temp->c[i] != '\0')
            {
                tp[len]=temp->c[i];
                i++;
                len++;
            }
            temp=temp->next;
        }
        tp[len]='\0';
        return tp;
    }
};

stringBuilder stringInitialize(char *input)
{
    stringBuilder s1(input);
    return s1;
}

int kmpSearch(char *str, char *word, int *ptr)
{
    int i=0,j=0;
    while((i+ j)<strlen(str))
    {
        if (word[j]==str[i+j])
        {
            if(j==(strlen(word)-1))
            {
                return ++i;
            }
            j++;
        }else
        {
            i=i+j-ptr[j];
            if(ptr[j] > -1)
            {
                j=ptr[j];
            }else
            {
                j=0;
            }
        }
    }
    return -1;
}

void findOverlap(char *word, int *ptr)
{
    int i=2,j=0,len=strlen(word);
    ptr[0]=-1;
    ptr[1]=0;
    while(i<len)
    {
        if(word[i-1]==word[j])
        {
            j++;
            ptr[i]=j;
            i++;
        }else{
        if(j>0)
        {
            j=ptr[j];
        }else
        {
            ptr[i]=0;
            i++;
        }
        }
    }
    return;
}

int findSubstring(stringBuilder s2, char *search)
{
    int* ptr = new int[strlen(search)]{1};
    findOverlap(search,ptr);
    char* chararray = s2.getCharArray();
    return kmpSearch(chararray,search,ptr);
}

stringBuilder stringAppend(stringBuilder s1, stringBuilder s2)
{
    stringBuilder s3(s1,s2);
    return s3;
}

int main()
{
    stringBuilder s1 = stringInitialize("Gaurav");
    s1.print();
    cout<<endl;
    stringBuilder s2 = stringInitialize("Sagar");
    s2.print();
    cout<<endl;
    stringBuilder s3 = stringAppend(s1,s2);
    s3.print();
    cout<<endl;
    stringBuilder s4 = stringInitialize("Tushar");
    s4.print();
    cout<<endl;
    stringBuilder s5 = stringInitialize("Jatin");
    s5.print();
    cout<<endl;
    stringBuilder s6 = stringAppend(s4,s5);
    s6.print();
    cout<<endl;
    stringBuilder s7 = stringAppend(s3,s6);
    s7.print();
    cout<<endl;
    stringBuilder s8 = stringAppend(s6,s3);
    s8.print();
    cout<<endl;
    s1.print();
    cout<<endl;
    s2.print();
    cout<<endl;
    s3.print();
    cout<<endl;
    s4.print();
    cout<<endl;
    s5.print();
    cout<<endl;
    s6.print();
    cout<<endl;
    s7.print();
    cout<<endl;
    s8.print();
    cout<<endl;
    cout<<"Test case\n";
    stringBuilder b1 = stringInitialize("Tushar");
    stringBuilder b2 = stringInitialize("Patil");
    stringBuilder b3 = stringAppend(b2,b1);
    stringBuilder b4 = stringInitialize("Gaurav");
    stringBuilder b5 = stringAppend(b3,b4);
    stringBuilder b6 = stringAppend(b5,b3);
    b6.print();
    findSubstring(b6,"Tusha");
    return 0;
}
