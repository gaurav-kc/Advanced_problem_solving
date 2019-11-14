#include<iostream>

using namespace std;

int flag=0;

template<class X,class Y>
class node
{
    public:
    X key;
    Y value;
    node *left;
    node *right;
    int height;
};
node<int,string> *root;

template<class X,class Y>
class avlTree
{
    public:
           avlTree()
           {
               root = NULL;
           }
            Y search(X key)

            {
                node<X,Y> *temp = root,*parent = root;
                if(temp==NULL)
                    cout<<"\nThe AVL Tree is empty\n"<<endl;
                else
                {
                    while(temp!=NULL && temp->key!=key)
                    {
                        parent=temp;
                        if(temp->key<key)
                        {
                            temp=temp->right;
                        }
                        else
                        {
                            temp=temp->left;
                        }
                    }
                }

                if(temp==NULL)
                    cout<<"This element is NOT present in the tree!";
                else
                    {
                        return temp->value;
                    }

            }

            void destroy(node<X,Y> *p)
            {
                 if(!p) return;
                 destroy(p->left);
                 destroy(p->right);
                 delete p;
            }

            int max(int a, int b)
            {
                return (a > b)? a : b;
            }

            int height( node<X,Y> *N)
            {
                if (N == NULL)
                    return 0;
                return N->height;
            }

            node<X,Y>* newNode(X key,Y value)
            {
                node<X,Y> *node1 = new node<X,Y>;
                node1->key   = key;
                node1->value = value;
                node1->left   = NULL;
                node1->right  = NULL;
                node1->height = 1;
                return(node1);
            }

            node<X,Y>* rightRotate( node<X,Y> *y)
            {
                node<X,Y> *x = y->left;
                node<X,Y> *T2 = x->right;
                x->right = y;
                y->left = T2;
                 // Update heights
                y->height = max(height(y->left), height(y->right))+1;
                x->height = max(height(x->left), height(x->right))+1;
                return x;
            }

            node<X,Y>* leftRotate(node<X,Y> *x)
            {
                node<X,Y> *y = x->right;
                node<X,Y> *T2 = y->left;
                y->left = x;
                x->right = T2;
                //  Update heights
                x->height = max(height(x->left), height(x->right))+1;
                y->height = max(height(y->left), height(y->right))+1;
                return y;
            }

            int getBalance(node<X,Y> *N)
            {
                if (N == NULL)
                    return 0;
                return height(N->left) - height(N->right);
            }

            node<X,Y>* insert(node<X,Y>* node, X key, Y value)
            {
                if (node == NULL)
                    return(newNode(key,value));
                if (key < node->key)
                    node->left  = insert(node->left, key,value);
                else{
                if (key > node->key)
                    node->right = insert(node->right, key,value);
                else{
                    node->value = value;
                    return node;
                }
                }
                node->height = max(height(node->left), height(node->right)) + 1;
                int balance = getBalance(node);
                // 1.Left Left Case
                if (balance > 1 && key < node->left->key)
                    return rightRotate(node);
                // 2.Right Right Case
                if (balance < -1 && key > node->right->key)
                    return leftRotate(node);
                // 3.Left Right Case
                if (balance > 1 && key > node->left->key)
                {
                    node->left =  leftRotate(node->left);
                    return rightRotate(node);
                }
                // 4.Right Left Case
                if (balance < -1 && key < node->right->key)
                {
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
                return node;
            }

            node<X,Y>* minValueNode(node<X,Y>* node1)
            {
                node<X,Y> *current = node1;
                while (current->left != NULL)
                    current = current->left;
                return current;
            }

            node<X,Y>* deleteNode(node<X,Y>* root, X key)
            {
                //Perform standard BST delete
                if (root == NULL)
                    return root;
                if ( key < root->key )
                    root->left = deleteNode(root->left, key);
                else if( key > root->key )
                    root->right = deleteNode(root->right, key);
                else
                {
                    if( (root->left == NULL) || (root->right == NULL) )
                    {   node<X,Y> *temp = root->left ? root->left : root->right;
                        flag=1;
                        if(temp == NULL)
                        {
                            temp = root;
                            root = NULL;
                            flag=1;
                        }
                        else
                         {
                            *root = *temp;flag=1;
                         }
                    free(temp);
                    }
                    else
                    {
                        node<X,Y>* temp = minValueNode(root->right);
                        root->key = temp->key;
                        root->right = deleteNode(root->right, temp->key);
                    }
                }
                if (root == NULL)
                  return root;
                //Update the height
                root->height = max(height(root->left), height(root->right)) + 1;
                int balance = getBalance(root);
                // 1.Left Left Case
                if (balance > 1 && getBalance(root->left) >= 0)
                    return rightRotate(root);
                // 2.Left Right Case
                if (balance > 1 && getBalance(root->left) < 0)
                {
                    root->left =  leftRotate(root->left);
                    return rightRotate(root);
                }
                // 3.Right Right Case
                if (balance < -1 && getBalance(root->right) <= 0)
                    return leftRotate(root);
                // 4.Right Left Case
                if (balance < -1 && getBalance(root->right) > 0)
                {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
                return root;
            }
            void inorder(node<X,Y> *root)
            {
                if(root != NULL)
                {
                    inorder(root->left);
                    cout<<"("<<root->key<<","<<root->value<<")  ";
                    inorder(root->right);
                }
            }
};
main()
{
    int choice;
    int key;
    string value;
    avlTree<int,string> avl;
    while (1)
    {
        cout<<"1.Insert Element"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.Delete Element from tree"<<endl;
        cout<<"4.Search for an Element"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"\nEnter your Choice: ";
        cin>>choice;
        cout<<"\n";
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>key;
            cin>>value;
            root = avl.insert(root,key,value);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            avl.inorder(root);
            cout<<endl;
            break;
        case 3: cout<<"\nEnter value to be deleted: ";
             cin>>key;
             root = avl.deleteNode(root, key);
             if(flag==0)
                        cout<<"\nElement not found in this tree!";
             else
                 cout<<"\nElement deleted successfully!";
             break;
        case 4:
            cout<<"\nEnter element to search: ";
            cin>>key;
            cout<<avl.search(key);
            break;
        case 0:exit(1);
            break;
        default:
            cout<<"\nWrong Choice!"<<endl;
        }
    }
}

