
/*#include <iostream>
#include <string.h>

using namespace std;

main(){
const string s="good";
const char* x="goop";
cout<<s;
}*/



#include <iostream>
#include <string.h>

using namespace std;

class node{
    public:
        int bf;
        char* word;
        node* left;
        node* right;
        node(){
        }
        node(char* s){
            word=s;
            left==NULL;
            right==NULL;
        }
};

node* rotateRight(node* ptr){
    node* tmp1,* tmp2;
    tmp1=ptr;
    ptr=ptr->left;
    tmp2=ptr->right;
    ptr->right=tmp1;
    tmp1->left=tmp2;
    return ptr;
}

node* rotateLeft(node* ptr){
    node* tmp1,* tmp2;
    tmp1=ptr;
    ptr=ptr->right;
    tmp2=ptr->left;
    ptr->left=tmp1;
    tmp1->right=tmp2;
    return ptr;
}

int height(node* ptr){//calculates the height from the given node
    if(ptr==NULL){
        return 0;
    }
    int l,r;
    l=height(ptr->left);
    r=height(ptr->right);
    if(l>r){
        return l+1;
    }
    else{
        return r+1;
    }
}

int balanceFactor(node* ptr){//calculate the balance factor of every node
    int b;
    b=height(ptr->left) - height(ptr->right);
}

void update(node* ptr){//updates every nodes balance factor and rotates them accordingly
    if(ptr==NULL){
        return;
    }
    update(ptr->left);
    update(ptr->right);
    ptr->bf=balanceFactor(ptr);
    int l,r;
    if(ptr->bf<-1){
        r=height(ptr->right->right);
        l=height(ptr->right->left);
        if(l>r){
            rotateRight(ptr->right);
        }
        else if(r>l){
            rotateLeft(ptr->right);
        }
        else{
            cout<<"ERROR 1";
        }
    }
    if(ptr->bf>1){
        r=height(ptr->left->right);
        l=height(ptr->left->left);
        if(l>r){
            rotateRight(ptr->left);
        }
        else if(r>l){
            rotateLeft(ptr->left);
        }
        else{
            cout<<"ERROR 2";
        }
    }
    return;
}

node* insertNode(const char* s, node* ptr){
    if(ptr==NULL){
        node* temp;
        temp=new node;
        strcpy(temp->word,s);
        return temp;
    }
    (const char*)ptr->word;
    if(strcmp(s,ptr->word)<0){
        insertNode(s,ptr->left);
    }
    else if(strcmp(s,ptr->word)>0){
        insertNode(s,ptr->right);
    }
    update(ptr);
    return ptr;
}

void inorder(node* ptr){
    if(ptr==NULL){
        return;
    }
    inorder(ptr->left);
    cout<<ptr->word;
    inorder(ptr->right);
}

int main()
{
    node* root=new node();
    root=insertNode("wake",root);
    root=insertNode("get",root);
    root=insertNode("sleep",root);
    inorder(root);
}

