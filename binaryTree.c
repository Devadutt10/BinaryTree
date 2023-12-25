#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

//Function for inserting the nodes

struct node* insertNode(struct node* root, int data){
    
    if(root == NULL){
        root = createNode(data);
    }
    else{
        if(data <= root->data){
            root->left = insertNode(root->left,data);
        }
        else if(data > root->data){
            root->right = insertNode(root->right,data);
        }
    }
    return root;
}

//Traversing the tree in inorder fashion...

void inorderTraversal(struct node* root){
    if (root != NULL) {
        // Traverse the left subtree
        inorderTraversal(root->left);
        
        // Visit the current node
        printf("%d ", root->data);

        // Traverse the right subtree
        inorderTraversal(root->right);
    }
}


//Traversing the node in pre order fashion..

void preorderTraversal(struct node* root){
    if(root != NULL){
        printf("%d ",root->data); //Printing the data

        preorderTraversal(root->left); //Traversing the left subtree
 
        preorderTraversal(root->right); //Traversing the right subtree
    }

}

//Traversing the tree in postorder fashion

void postorderTraversal(struct node* root){
    if(root != NULL){
        postorderTraversal(root->left);

        postorderTraversal(root->right);

        printf("%d ",root->data);
    }

}


//Function for finding the in-order successor of the root node (Smallest element in the right sub-tree)...
struct node* findInPre(struct node* root){
    while(root != NULL && root->left != NULL){
        root = root->left;
    }
    return root;
}

struct node* deleteNodeTree(struct node* root, int key){
    //Searching the node in the tree

   
    if(key < root->data){
        root->left = deleteNodeTree(root->left,key);
    }
    else if(key > root->data){
        root->right = deleteNodeTree(root->right,key);
    }
    else{
        //Key has been found, now deleting the node
        if(root == NULL){
            return root;
        }
        else{
            //Case1: If the node has no right or left child..
            if(root->right == NULL && root->left == NULL){
                free(root);
                root = NULL;
                return root;
            }
            //Case2: If the node has only one child, either right or left..
            if(root->right == NULL){
                struct node* temp = root->left;
                free(root);
                return temp;
            }
            else if(root->left == NULL){
                struct node* temp = root->right;
                free(root);
                return temp;
            }
            else{
                //Case3: If the node to be deleted has both right and left child...
                struct node* temp = findInPre(root->right);

                //Copying the data in the in-order successor to the current root...
                root->data = temp->data;

                //Deleting the in-order successor...
                root->right = deleteNodeTree(root->right, temp->data);
            }
        }

    }
    
}

//Function for seraching a node in the binary tree..

struct node* searchBinaryTree(struct node* root, int data){

    if(root == NULL){
        return NULL;
    }

    if(data < root->data){
        return searchBinaryTree(root->left,data); //Traversing the left sub-tree
    }
    else if(data > root->data){
        return searchBinaryTree(root->right,data); //Traversing the right sub-tree
    }
    else{
        //Key has been found..
        return root;
    }

   
}



void main(){

    int data, length,operation;
    struct node* root = NULL;
    char choice;

    printf("Enter the number of nodes:");
    scanf("%d",&length);

    printf("Start entering the nodes..\n");

    for(int i=0;i<length;i++){
        printf("Enetr the data of node %d:",i+1);
        scanf("%d",&data);
        root = insertNode(root,data);


    }

    do{
        printf("Enter an operation.\n 1.Traversal.\n 2.Insertion.\n 3.Deletion.\n 4.Searching.\n");
        scanf("%d",&operation);

        if(operation == 1){
            printf("The tree after in-order traversal is.\n");
            inorderTraversal(root);
            printf("\n");

            printf("The tree after pre-order traversla is.\n");
            preorderTraversal(root);
            printf("\n");

            printf("The tree after post-order traversal is.\n");
            postorderTraversal(root);
            printf("\n");
        }
        else if(operation == 2){
            printf("Enter the data of the node to be inserted:");
            scanf("%d",&data);

            root = insertNode(root,data);
            printf("The tree after insertion in in-order fashion is.\n");
            inorderTraversal(root);
        }
        else if(operation == 3){
            printf("Enter the data of the node to be deleted:");
            scanf("%d",&data);

            root = deleteNodeTree(root,data);
            printf("The tree after deleting the node in in-order fashion is.\n");
            inorderTraversal(root);
        }
        else if(operation == 4){
            printf("Enter the data of the node to be searched:");
            scanf("%d",&data);

            root = searchBinaryTree(root,data);

            if(root == NULL){
                printf("The key is not found in the tree\n");

            }
            else{
                printf("The key %d is found in the address %d of the tree.\n",root->data,root);
            }
        }
        else{
            printf("Enter a valid choice..\n");
        }
        printf("Do you want to continue?(y/n):");
        scanf(" %c",&choice);
        
    }while(choice != 'n');

}