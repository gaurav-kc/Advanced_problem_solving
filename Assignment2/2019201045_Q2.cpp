#include<iostream>
#define LEFT 1
#define RIGHT 2
#define ROOT 0
using namespace std;

typedef struct no{
    int val;
    int height;
    int left_count;
    int right_count;
    struct no* left;
    struct no* right;
    struct no* parent;
    int child;
}n;

n* root;
int replace;
void print(n* root)
{
    cout<<"\n";
    if(root->val)
        cout<<"value is "<<root->val<<endl;
    else
        cout<<"Tushar"<<endl;
    cout<<"height is "<<root->height<<endl;
    if(root->left)
        cout<<"left pointing to "<<root->left->val<<endl;
    if(root->right)
        cout<<"right pointing to "<<root->right->val<<endl;
    if(root->parent)
        cout<<"parent pointing to "<<root->parent->val<<endl;
    cout<<"child is "<<root->child<<endl;
    cout<<"left sub tree has "<<root->left_count<<" nodes"<<endl;
    cout<<"right sub tree has "<<root->right_count<<" nodes"<<endl;
}


n* createnode(n* node,int value, int i)
{
    n *temp = new n;
    temp->val = value;
    temp->height=0;
    temp->left_count=0;
    temp->right_count=0;
    temp->left = NULL;
    temp->right=NULL;
    temp->parent=node;
    temp->child=i;
    return temp;
}


void setHeight(n* node)
{
    if(node->left==NULL && node->right==NULL)
        node->height=0;
    if(node->left==NULL && node->right!=NULL)
        node->height=node->right->height+1;
    if(node->left!=NULL && node->right==NULL)
        node->height=node->left->height+1;
    if(node->left!=NULL && node->right!=NULL)
    {
        int maxim = (node->left->height > node->right->height)?node->left->height:node->right->height;
        node->height = maxim+1;
    }
}

void setSubtreeCount(n* node)
{
    if(node->left==NULL && node->right==NULL)
    {
        node->left_count = 0;
        node->right_count = 0;
    }
    if(node->left==NULL && node->right!=NULL)
    {
        node->left_count = 0;
        node->right_count = node->right->left_count + node->right->right_count + 1;
    }
    if(node->left!=NULL && node->right==NULL)
    {
        node->right_count = 0;
        node->left_count = node->left->left_count + node->left->right_count + 1;
    }
    if(node->left!=NULL && node->right!=NULL)
    {
        node->left_count = node->left->left_count + node->left->right_count + 1;
        node->right_count = node->right->left_count + node->right->right_count + 1;
    }
}

n* rightRotate(n* node)
{
    //print(node);
    n* temp = node->left;
    //print(temp);
    //print(node->left->parent);
    node->left->parent = node->parent;
    temp->child = node->child;
    if(node->child == 1)
    {
        if(node->parent)
            node->parent->left = temp;
    }
    if(node->child == 2)
    {
        if(node->parent)
            node->parent->right = temp;
    }
    if(temp->right)
    {
        //print(temp);
        temp->right->parent = node;
        node->left = temp->right;
        temp->right->child = 1;
    }else{
        node->left=NULL;
    }
    temp->right = node;
    //print(temp->right);
    node->parent = temp;
    node->child = 2;

    setHeight(node);
    setSubtreeCount(node);
    setHeight(temp);
    setSubtreeCount(temp);
    return temp;
}

n* leftRotate(n* node)
{
    //print(node);
    n* temp = node->right;
    //print(temp);
    node->right->parent = node->parent;
    //print(node->right->parent);
    temp->child = node->child;
    if(node->child == 1)
    {
        if(node->parent)
            node->parent->left = temp;
    }
    if(node->child == 2)
    {
        if(node->parent)
            node->parent->right = temp;
    }
    if(temp->left)
    {
        temp->left->parent = node;
        node->right = temp->left;
        temp->left->child = 2;
    }else{
        node->right=NULL;
    }
    temp->left = node;
    //print(temp->left);
    node->parent=temp;
    node->child = 1;
    setHeight(node);
    setSubtreeCount(node);
    setHeight(temp);
    setSubtreeCount(temp);
    return temp;
}

void fixleftleft(n* node)
{
    //cout<<"lelel \n";
    //print(node);
    n* par = node->parent;
    /*if(par)
    {
        cout<<"hiihi \n";
        print(par);
    }*/
    n* newroot = rightRotate(node);
    //print(newroot);
    //cout<<"new root val "<<newroot->val<<endl;
    if(par==NULL)
    {
        root = newroot;
    }
}

void fixleftright(n* node)
{
    //print(node);
    n* par = node->parent;
    //print(par);
    n* newroot1 = leftRotate(node->left);
    //print(newroot1);
    n* newroot2 = rightRotate(node);
    //print(newroot2);
    if(par!=NULL)
    {
        root = newroot2;
    }
}

void fixrightleft(n* node)
{
    n* par = node->parent;
    n* newroot1 = rightRotate(node->right);
    n* newroot2 = leftRotate(node);
    if(par==NULL)
    {
        root=newroot2;
    }
}

void fixrightright(n* node)
{
    n* par = node->parent;
    n* newroot = leftRotate(node);
    if(par==NULL)
    {
        root=newroot;
    }
}

n* searchNode(n* node,int key)
{
    while(node!=NULL)
    {
        if(node->val == key)
            break;
        if(node->val > key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

n* findInorderSuccessor(n* node)
{
    if(node->right!=NULL)
        node=node->right;
    while(node->left!=NULL || node->right->left!=NULL)
    {
        if(node->left!=NULL)
            node=node->left;
        else
            node=node->right->left;
    }
    return node;
}

int findClosest(n* node,int value)
{
    int diff = node->val - value;
    int temp;
    if((value > node->val) && (node->right != NULL))
        temp = findClosest(node->right,value);
    if((value < node->val) && (node->left != NULL))
        temp = findClosest(node->left, value);
    int diffmod;
    if(diff >= 0)
        diffmod = diff;
    else
        diffmod = 0-diff;
    int tempmod;
    if(temp >= 0)
        tempmod = temp;
    else
        tempmod = 0-temp;
    if(diffmod <= tempmod)
        return diff;
    else
        return temp;
}

n* findkthlargest(n* node, int k)
{
    int temp = node->left_count + 1;
    if(temp == k)
        return node;
    if((node->left_count >= k) && (node->left != NULL))
        return findkthlargest(node->left,k);
    if(node->right!=NULL)
        return findkthlargest(node->right, k-temp);
}

int  setHeightsinTree(n* node)
{
    if((node->left == NULL) && (node->right == NULL))
    {
        node->height=0;
        return node->height;
    }
    if(node->left == NULL)
    {
        node->height = 1+setHeightsinTree(node->right);
        return node->height;
    }
    if(node->right == NULL)
    {
        node->height = 1+setHeightsinTree(node->left);
        return node->height;
    }
    node->height = 1+setHeightsinTree(node->left)+setHeightsinTree(node->right);
    return node->height;
}

int getCase(n* node,int value)
{
    bool turn1=false;
    bool turn2=false;
    //false == left
    //true == right
    //LL----1
    //LR----2
    //RL----3
    //RR----4
    if(node->val < value)
    {
        turn1 = true;
        node=node->right;
    }else
    {
        node=node->left;
    }
    if(node->val < value)
    {
        turn2 = true;
    }else
    {
    }
    if(turn1)
    {
        if(turn2)
        {
            return 4;
        }else{
            return 3;
        }
    }else{
        if(turn2)
        {
            return 2;
        }else{
            return 1;
        }
    }
}

void performStandardInsertion(n* node,int value)
{
    if(node->val == value)
    {
        cout<<"Element exists"<<endl;
        return;
    }
    int heightdiff;
    n* temp=NULL;
    if((node->left == NULL) && (node->right == NULL))       //node is a leaf
    {
        if(node->val > value)
        {
            temp = createnode(node,value,LEFT);
            node->left = temp;
        }
        if(node->val < value)
        {
            temp = createnode(node,value,RIGHT);
            node->right = temp;
        }
        heightdiff = 1;
    }else{
    if(node->val > value)
    {
        if(node->left!=NULL)
        {
            performStandardInsertion(node->left,value);
        }else{
            temp = createnode(node,value,LEFT);
            node->left=temp;
        }
    }else{
    if(node->val < value)
    {
        if(node->right!=NULL){
            performStandardInsertion(node->right,value);
        }else{
            temp = createnode(node,value,RIGHT);
            node->right=temp;
        }
    }
    }
    }
    if(temp!=NULL)
    {
        //setHeightsAfterInsertion(temp);
        //setHeights(root);
        //heightdiff = 1;
    }else{
        int lefth=-1,righth=-1;
        if(node->left!=NULL)
            lefth = node->left->height;
        if(node->right!=NULL)
            righth = node->right->height;
        heightdiff = lefth - righth;
        //cout<<"lefth "<<lefth<<" righth "<<righth<<"hdiff = "<<heightdiff<<endl;
        if(heightdiff > 1 || heightdiff < -1)
        {
            //imbalace spotted
            int imbalace = getCase(node,value);
            //cout<<"imabalanceeeeeee "<<imbalace<<endl;
            n* temp;
            switch(imbalace)
            {
                case 1 :    //LL
                {
                    //cout<<"\n"<<"in LL"<<endl;
                    fixleftleft(node);
                }
                break;
                case 2 :    //LR
                {
                    //cout<<"\n"<<"in LR"<<endl;
                    fixleftright(node);

                }
                break;
                case 3 :    //RL
                {
                    //cout<<"\n"<<"in RL"<<endl;
                    fixrightleft(node);
                }
                break;      //RR
                case 4 :
                {
                    //cout<<"\n"<<"in RR"<<endl;
                    fixrightright(node);
                }
                break;
            }
        }
    }
    setHeight(node);
    setSubtreeCount(node);
}

void removeNode(int val)
{

}

void printInorder(n* root)
{
    if(root == NULL)
        return;

    //print(root);

    printInorder(root->left);
    //print(root);
    cout<<root->val<<" ";
    printInorder(root->right);
}


void printInorderD(n* root)
{
    if(root == NULL)
        return;
    printInorderD(root->left);
    print(root);
    printInorderD(root->right);
}

n* lowestAncestor(n* node, int low, int high)
{
    if (node == NULL)
        return NULL;
    if (node->val > low && node->val > high)
        return lowestAncestor(node->left, low, high);
    if (node->val < low && node->val < high)
        return lowestAncestor(node->right, low, high);
    return node;
}

int getRange(n *root, int low, int high)
{
    n* temp1;
    n* temp2;
    n* temp3;
    temp1 = searchNode(root,low);
    temp2 = searchNode(root,high);
    temp3 = lowestAncestor(root,low,high);
    n* temp4 = temp3;
    n* temp5 = temp3;
    int count;
    if(temp3!=temp1 && temp3!=temp2)
    {

        int count1 = temp3->left_count;
        while(temp4!=temp1)
        {
            if(temp4->val > temp1->val)
            {
                temp4 = temp4->left;
            }else{
                count1 = count1 - temp4->left_count - 1;
                temp4 = temp4->right;
            }
        }
        count1 = count1 - temp4->left_count;
        int count2 = temp3->right_count;
        while(temp5!=temp2)
        {
            if(temp5->val < temp2->val)
            {
                temp5 = temp5->right;
            }else{
                count2 = count2 - temp5->right_count - 1;
                temp5 = temp5->left;
            }
        }
        count2 = count2 - temp5->right_count;
        count = count1 + count2;
    }else
    {
        if((temp3==temp1) && (temp3!=temp2))
        {
            count = temp3->right_count;
            while(temp3!=temp2)
            {
                if(temp3->val < temp2->val)
                {
                    temp3 = temp3->right;
                }else{
                    count = count - temp3->right_count - 1;
                    temp3 = temp3->left;
                }
            }
            count = count - temp3->right_count;
        }else{
            if((temp3!=temp1) && (temp3 == temp2))
            {
                count = temp3->left_count;
                while(temp3!=temp1)
                {
                    if(temp3->val > temp1->val)
                    {
                        temp3 = temp3->left;
                    }else{
                        count = count - temp3->left_count - 1;
                        temp3 = temp3->right;
                    }
                }
                count = count - temp3->left_count;
            }
        }
    }
    return count+1;
    return temp3->val;
}

n* removenode(n* node, int value)
{
    n* temp;
    if((node->left == NULL) && (node->right == NULL))
    {
        node->height=-1;
        node->left_count=-1;
        return node;
    }
    if(node->left)
    {
        temp = removenode(node->left,value);
        setHeight(node);
        setSubtreeCount(node);
        return temp;
    }else{
        if(node->right)
        {
            if(node->right->left)
            {
                temp = removenode(node->left,value);
                setSubtreeCount(node);
                setHeight(node);
                return temp;
            }else{
                node->parent->left = node->right;
                node->parent->left_count = 1;
                return node;
            }
        }
    }
}

void deleteNode(n* node,int value)
{
    if(node->val < value)
    {
        deleteNode(node->right,value);
    }
    if(node->val > value)
    {
        deleteNode(node->left,value);
    }
    if(node->val == value)
    {
        if((node->left == NULL) && (node->right == NULL))
        {
            node->height=-1;
            node->left_count=-1;
            if(node->parent->left == node)
            {
                node->parent->left = NULL;
            }
            if(node->parent->right == node)
            {
                node->parent->right = NULL;
            }
            setHeight(node->parent);
            free(node);
        }
        if((node->left != NULL) && (node->right == NULL))
        {
            if(node->parent->left == node)
            {
                node->parent->left = node->left;
                node->parent->left_count = node->parent->left_count-1;
                //warning
                free(node);
            }
            if(node->parent->right == node)
            {
                node->parent->right = node->left;
                node->parent->right_count = node->parent->right_count-1;
                free(node);
            }
        }
        if((node->left == NULL) && (node->right != NULL))
        {
            if(node->parent->left == node)
            {
                node->parent->left = node->right;
                node->parent->left_count = node->parent->left_count-1;
                free(node);
            }
            if(node->parent->right == node)
            {
                node->parent->right = node->right;
                node->parent->right_count = node->parent->right_count-1;
                free(node);
            }
        }
        if((node->left != NULL) && (node->right != NULL))
        {
            n* temp = removenode(node->right,value);
            cout<<"Successor "<<temp->val<<endl;
            if(node->parent->left == node)
            {
                temp->parent->left=NULL;
            }
            if(node->parent->right == node)
            {
                temp->parent->right=NULL;
            }
            setHeight(node);
            setSubtreeCount(node);
            node->val = temp->val;
            free(temp);
        }
    }

        int lefth = -1;
        if(node->left)
            lefth = node->left->height;
        int righth = -1;
        if(node->right)
            righth = node->right->height;
        int t1lefth = -1;
        int t1righth = -1;
        int diff = lefth-righth;
        int tdiff1;
        int tdiff2;
        int rcase;
        if(diff>1)
        {
            if(node->left->left)
                t1lefth = node->left->left->height;
            if(node->left->right)
                t1righth = node->left->right->height;
            tdiff1 = t1lefth - t1righth;
            if(tdiff1>0)
            {
                //LL
                rcase=1;
            }
            if(tdiff1<0)
            {
                //LR
                rcase=2;
            }
        }
        if(diff<-1)
        {
            if(node->right->left)
                t1lefth = node->right->left->height;
            if(node->right->right)
                t1righth = node->right->right->height;
            tdiff2 = t1lefth - t1righth;
            if(tdiff2 > 0)
            {
                //RL
                rcase=3;
            }
            if(tdiff2 < 0)
            {
                //RR
                rcase=4;
            }
        }
        switch(rcase)
        {
            case 1 :    //LL
            {
                //cout<<"\n"<<"in LL"<<endl;
                fixleftleft(node);
            }
            break;
            case 2 :    //LR
            {
                //cout<<"\n"<<"in LR"<<endl;
                fixleftright(node);

            }
            break;
            case 3 :    //RL
            {
                //cout<<"\n"<<"in RL"<<endl;
                fixrightleft(node);
            }
            break;      //RR
            case 4 :
            {
                //cout<<"\n"<<"in RR"<<endl;
                fixrightright(node);
            }
            break;
        }
        setHeight(node);
        setSubtreeCount(node);
}

void printmenu(){
    cout<<"\n1. Insert\n";
    cout<<"2. Search\n";
    cout<<"3. Closest value\n";
    cout<<"4. kth largest \n";
    cout<<"5. Count in range\n";
    cout<<"6. Delete\n";
    cout<<"7. Quit\n";
}
int main()
{
/*
    int input;
    //cout<<"Enter value"<<endl;
    //cin>>input;
    int arr[20]={7,25,3,4,29,8,13,17,42,1,33,32,34,31,19,23,52,63,64,65};
    root = createnode(NULL,arr[0],ROOT);
    char choice='p';
    int i=1;
    while(i<20)
    {
        //cout<<"Enter value"<<endl;
        //cin>>input;
        //cout<<"\n******************************************************";
        input = arr[i];
        //cout<<"input "<<arr[i]<<endl;
        performStandardInsertion(root,input);
        //cout<<"\n";
        //cout<<"lal";
        //setHeights(root);
        /*print(root);
        if(root->right)
            print(root->right);
        if(root->left)
            print(root->left);
        if(root->right)
        {
            if(root->right->left)
                print(root->right->left);
            if(root->right->right)
                print(root->right->right);
        }
        if(root->left)
        {
            if(root->left->left)
                print(root->left->left);
            if(root->left->right)
                print(root->left->right);
        }
        //printInorder(root);
        //cout<<"\n";
        //cout<<"******************************************************\n";
        i++;
    }
    //cout<<"hi";
    cout<<"\n############################################################\n";
    printInorder(root);
    cout<<"\n############################################################\n";
    /*while(1){
    cout<<"enter to search ";
    int ip;
    cin>>ip;
    if(searchNode(root,ip)!=NULL)
    {
        cout<<"Found"<<endl;
    }else
    {
        cout<<"Not Found"<<endl;
    }
    }*/
    /*
    while(1){
    cout<<"enter to find closest \n";
    int ip;
    cin>>ip;
    int result = findClosest(root,ip) + ip;
    cout<<result<<endl;
    }*/
    /*while(1){
    cout<<"enter k to find kth largest \n";
    int ip;
    cin>>ip;
    ip = root->left_count + root->right_count + 2 - ip;
    cout<<findkthlargest(root,ip)->val<<endl;
    }*/
    /*
    while(1){
    cout<<"enter a \n";
    int a,b;
    cin>>a;
    cout<<"\nenter b \n";
    cin>>b;
    cout<<endl;
    int count = getRange(root,a,b);
    cout<<count<<endl;
    }*/
    /*
    int p=1;
    while(1)
    {
        if(p==3)
            cout<<"";
        cout<<"Enter to delete \n";
        cin>>input;
        deleteNode(root,input);
        printInorderD(root);
        cout<<"\n############################################################\n";
        printInorder(root);
        cout<<"\n############################################################\n";
        p++;
    }*/
    int choice;
    int input;
    bool first=true;
    do{

        printmenu();
        cin>>choice;
        switch(choice)
        {
            case 1 :
            {
                cout<<"Enter to insert\n";
                cin>>input;
                if(first)
                {
                    root=createnode(NULL,input,ROOT);
                    first=false;
                }else{
                    performStandardInsertion(root,input);
                }
                printInorder(root);
            }
            break;
            case 2 :
            {
                cout<<"enter to search \n";
                int ip;
                cin>>ip;
                if(searchNode(root,ip)!=NULL)
                {
                    cout<<"Found"<<endl;
                }else
                {
                    cout<<"Not Found"<<endl;
                }
                printInorder(root);
            }
            break;
            case 3 :
            {
                cout<<"enter to find closest \n";
                int ip;
                cin>>ip;
                int result = findClosest(root,ip) + ip;
                cout<<result<<endl;
                printInorder(root);
            }
            break;
            case 4 :
            {
                cout<<"enter k to find kth largest \n";
                int ip;
                cin>>ip;
                ip = root->left_count + root->right_count + 2 - ip;
                cout<<findkthlargest(root,ip)->val<<endl;
                printInorder(root);
            }
            break;
            case 5 :
            {
                cout<<"enter a \n";
                int a,b;
                cin>>a;
                cout<<"\nenter b \n";
                cin>>b;
                cout<<endl;
                int count = getRange(root,a,b);
                cout<<count<<endl;
                printInorder(root);
            }
            break;
            case 6 :
            {
                cout<<"Enter to delete \n";
                cin>>input;
                deleteNode(root,input);
                printInorder(root);
            }
            break;
            case 7 :
            {
                return 0;
            }
            break;
        }

    }while(choice!=7);
}
