#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class node{//A class node defining the node of the tree
    public:
        int bf;
        string word;
        node* left;
        node* right;
        node(){
            left=NULL;
            right=NULL;
        }
        node(string s){
            word=s;
            left=NULL;
            right=NULL;
        }
};

int strcompare(string s1, string s2){//A function that compares two strings and returns an integer accordingly
    int i=0;
    char c1=s1[i],c2=s2[i];
    while(c1!='\0'|| c2!='\0'){
        c1=s1[i];
        c2=s2[i];
        if(c1!=c2){
            break;
        }
        i+=1;
    }
    int x;
    x=(int)c1 - (int)c2;
    return x;
}

node* rotateRight(node* ptr){//A function that implements right rotation of an AVL tree
    node* tmp1,* tmp2;
    tmp1=ptr;
    ptr=ptr->left;
    tmp2=ptr->right;
    ptr->right=tmp1;
    tmp1->left=tmp2;
    return ptr;
}

node* rotateLeft(node* ptr){//A function that implements left rotation of an AVL tree
    node* tmp1,* tmp2;
    tmp1=ptr;
    ptr=ptr->right;
    tmp2=ptr->left;
    ptr->left=tmp1;
    ptr->left->right=tmp2;
    return ptr;
}

int height(node* ptr){//A function that calculates the height from the given node
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

int balanceFactor(node* ptr){//A function that calculate the balance factor of every node
    int b;
    b=height(ptr->left) - height(ptr->right);
    return b;
}

node* update(node* ptr){//A function that updates every node's balance factor and rotates them accordingly
    if(ptr==NULL){
        return NULL;
    }
    update(ptr->left);
    update(ptr->right);
    ptr->bf=balanceFactor(ptr);
    int l,r;
    if(ptr->bf<-1){
        r=height(ptr->right->right);
        l=height(ptr->right->left);
        if(l>r){
            ptr->right=rotateRight(ptr->right);
        }
        else if(r>l){
            ptr=rotateLeft(ptr);
        }
    }
    if(ptr->bf>1){
        r=height(ptr->left->right);
        l=height(ptr->left->left);
        if(l>r){
            ptr=rotateRight(ptr);
        }
        else if(r>l){
            ptr->left=rotateLeft(ptr->left);
        }
    }
    return ptr;
}

node* insertNode(string s, node* ptr){//A function that inserts new nodes in their appropriate position
    if(ptr==NULL){
        node* temp;
        temp=new node(s);
        return temp;
    }
    if(strcompare(s,ptr->word)<0){
        ptr->left=insertNode(s,ptr->left);
    }
    else if(strcompare(s,ptr->word)>0){
        ptr->right=insertNode(s,ptr->right);
    }
    ptr=update(ptr);
    return ptr;
}

void inorder(node* ptr){//A function that implements the in-order traversal of the tree
    if(ptr==NULL){
        return;
    }
    inorder(ptr->left);
    cout<<"  "<<ptr->word<<"  ";
    inorder(ptr->right);
}

int searchWord(string s, node* ptr){//A function that searches the given word in the implemented tree
    int result;
    if(ptr==NULL){
        return 0;
    }
    if(strcompare(s,ptr->word)==0){
        return 1;
    }
    else if(strcompare(s,ptr->word)>0){
        result=searchWord(s,ptr->right);
    }
    else if(strcompare(s,ptr->word)<0){
        result=searchWord(s,ptr->left);
    }
    return result;
}

int main(){//Main function that deals with reading the dictionary and user's text file and calling various functions
    node* root;
    root=NULL;
    ifstream dobj("dictionary.txt");
    string dword;
    while(dobj>>dword){
        cout<<"\ninserting"<<dword<<"\n";
        root=insertNode(dword,root);
    }
    dobj.close();
    cout<<"\n-------------------TRAVERSING-------------------\n";
    inorder(root);
    cout<<"\n";
    ifstream uobj("usertext.txt");
    string uword;
    int x;
    while(uobj>>uword){
        x=searchWord(uword,root);
        if(x==0){
            cout<<"\n\nThe word -> \""<<uword<<"\" is incorrect\n";
        }
        else{
            cout<<"\n"<<uword<<" Found!!\n";
        }
    }
    uobj.close();
}
