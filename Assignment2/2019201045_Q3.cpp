#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the runningMedian function below.
 */
#define LEFT 1
#define RIGHT 2
#define ROOT 0

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
    if(par==NULL)
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
    return node;
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
    if(node->val <= value)
    {
        turn1 = true;
        node=node->right;
    }else
    {
        node=node->left;
    }
    if(node->val <= value)
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
    int heightdiff;
    n* temp=NULL;
    if((node->left == NULL) && (node->right == NULL))       //node is a leaf
    {
        if(node->val > value)
        {
            temp = createnode(node,value,LEFT);
            node->left = temp;
        }
        if(node->val <= value)
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
    if(node->val <= value)
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
        //setHeightsAfterInsertion(temp);
        //setHeights(root);
        //heightdiff = 1;
        setHeight(node);
        setSubtreeCount(node);
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
            //setHeights(root);
        }
    setHeight(node);
    setSubtreeCount(node);
}
vector<double> runningMedian(vector<int> a) {
    /*
     * Write your code here.
     */
     vector<double> res;
    int input,t;
    t=a.size();
    input = a[0];
    double result=input;
    res.push_back(result);
    root = createnode(NULL,input,ROOT);
    t--;
    int i=1;
    while(t--){
        input=a[i];
        performStandardInsertion(root,input);
        double result;
        int nodes = root->left_count + root->right_count + 1;
        if(nodes%2==0)
        {
            double temp1 = findkthlargest(root,nodes/2)->val;
            double temp2 = findkthlargest(root,(nodes/2)+1)->val;
            result = (temp1 + temp2)/2;
        }else{
            result = findkthlargest(root,(nodes/2)+1)->val;
        }
        res.push_back(result);
        //cout<<"Enter number \n";
        i++;
    }
    return res;
}

int main()
{
    int input;
    cout<<"Enter number \n";
    cin>>input;
    root = createnode(NULL,input,ROOT);
    cout<<input<<endl;
    cout<<"Enter number \n";
    while(1){
        cin>>input;
        performStandardInsertion(root,input);
        double result;
        int nodes = root->left_count + root->right_count + 1;
        if(nodes%2==0)
        {
            double temp1 = findkthlargest(root,nodes/2)->val;
            double temp2 = findkthlargest(root,(nodes/2)+1)->val;
            result = (temp1 + temp2)/2;
        }else{
            result = findkthlargest(root,(nodes/2)+1)->val;
        }
        cout<<result<<endl;
        cout<<"Enter number \n";
    }

    /*
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;

    */
}
