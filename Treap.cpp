

#include <bits/stdc++.h>

using namespace std;

// Structure of Treap Node
struct TreapNode
{
    int key, priority;
    TreapNode *left, *right;
};

/* T1, T2 and T3 are subtrees of the tree rooted with y
(on left side) or x (on right side)
				y							 x
			/ \	 Right Rotation		 / \
			x T3 – – – – – – – >	 T1 y
			/ \	 < - - - - - - -		 / \
			T1 T2	 Left Rotation		 T2 T3 */

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
TreapNode *rightRotate(TreapNode *y)
{
    TreapNode *x = y->left, *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreapNode *leftRotate(TreapNode *x)
{
    TreapNode *y = x->right, *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Return new root
    return y;
}

/* A function to add/create a new key */
TreapNode* newNode(int key)
{
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}

/* Recursive implementation of insertion in Treap */
TreapNode* insert(TreapNode* root, int key)
{
    // If root is NULL, create a new node and return it
    if (!root)
        return newNode(key);

    // If key is smaller than root
    if (key <= root->key)
    {
        // Insert in left subtree
        root->left = insert(root->left, key);

        // Fix Heap property if it is violated
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else // If key is greater
    {
        // Insert in right subtree
        root->right = insert(root->right, key);

        // Fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}


// A function to search a given key in a given BST
TreapNode* search(TreapNode* root, int key)
{
    // 1st Case: if root is null or key is present at root

    if (root == NULL || root->key == key)
        return root;

    // 2nd case: Key is greater than root's key

    if (root->key < key)
        return search(root->right, key);

    // 3rd case: Key is smaller than root's key

    return search(root->left, key);
}


/* Recursive implementation of Delete() */
TreapNode* deleteNode(TreapNode* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);


    // If left is NULL
    else if (root->left == NULL)
    {
        TreapNode *temp = root->right;
        delete(root);
        root = temp; // Make right child as root
    }

    // If Right is NULL
    else if (root->right == NULL)
    {
        TreapNode *temp = root->left;
        delete(root);
        root = temp; // Make left child as root
    }

    // If key is at root and both left and right are not NULL
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }

    return root;
}


// A function to build tree.
void build(TreapNode* root)
{
    if (root)
    {
        build(root->left);
        cout << "key: "<< root->key << " | priority: "
             << root->priority;
        if (root->left)
            cout << " | left child: " << root->left->key;
        if (root->right)
            cout << " | right child: " << root->right->key;
        cout << endl;
        build(root->right);
    }
}



int main()
{
    srand(time(NULL));

    struct TreapNode *root = NULL;

    cout << "\n\t\t\t\t\aWELCOME TO THE TREAP MANAGEMENT PROJECT BY GROUP 5 \t\a\n\n";


   //Menu
    while(1) //infinity loop
    {
        cout << "1. INSERT\n";
        cout << "2. SEARCH\n";
        cout << "3. DELETE\n";
        cout << "4. RETURN TO MAIN MENU\n";
        cout << "5. EXIT\n";

        cout <<"\nEnter your choice:" <<endl;
        int input;
        cin >> input;


        switch(input)
        {
        case 1:

        {

            int tn, in;
            cout << "Enter total number of insertion: \n";
            cin >> tn;

            for(int i=1; i <= tn; i++)
            {
                cout << "Enter " << i << " number: ";
                cin >> in;
                root = insert(root, in);

            }
            cout << "\nBuilt Tree: \n";
            build(root);

            cout<<endl;
        }
        break;
        case 2:
            if (root == NULL)
            {
                cout<<"\nTree is empty, nothing to search\n\n"<<endl;
                continue;
            }

            {

                cout << "\nEnter number to search in treap: \n";  //Ask user for search an element/value
                int sec;
                cin >> sec;

                TreapNode *res = search(root, sec);
                (res == NULL)? cout << "\n" << sec << " Not Found\n": cout << "\n" << sec << " Found\n";
                cout<<endl;
            }
            break;

        case 3:
            if (root == NULL)
            {
                cout<<"\nTree is empty, nothing to delete\n\n"<<endl;
                continue;
            }
            {
                cout << "\nEnter number to delete: \n";  //Ask user for delete an element/value

                int del;
                cin >>  del;

                TreapNode *delt = search(root, del);
                (delt == NULL)? cout << "\n" << del << " Not Found\n": cout << "\n" << del << " Deleted\n";


                root = deleteNode(root, del);
                cout << "\nBuilt Tree: \n";
                build(root);
                cout<<endl;
            }
            break;

        case 4:
        {
            main(); //back to main menu
        }
        break;

        case 5:
        {

            cout <<"\nExiting."<< endl;
            cout <<"Thank you for using Treap Management System.\n";
            exit(0);
            cout<<endl;
        }
        break;
        default:
            cout << "\nWrong input. Please try again.\nThank you for using Treap Management System.\n";

            //code for continue the main function
            char c[1];
            printf("\nDo you want to continue (Y or N)? => ");
            cin >> c;
            if(strcmp(c,"Y")==0)
            {
                return main();
            }

            else
            {
                cout <<"\nExiting."<< endl;
                cout <<"Thank you for using Treap management system.\n";
                return EXIT_SUCCESS;
            }
        }

    }

}
