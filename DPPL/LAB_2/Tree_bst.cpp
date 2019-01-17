#include<iostream>
using namespace std;
class Tree_node{ //structure of a node in a tree.
    public:
    int key;
    Tree_node *left;
    Tree_node *right;
    Tree_node(){
        key=-1;
        left=NULL;
        right=NULL;
    }
};
class Tree{
    public:
    Tree(){}
    Tree_node *root=NULL;
    Tree_node* create_node(int key){ //creates a node.
        Tree_node *temp=new Tree_node;
        temp->key=key;
        temp->left=NULL;
        temp->right=NULL;
        cout<<"new key "<<temp->key<<endl;
        return temp;
    }
   Tree_node* Tree_creation(Tree_node* temp1){
        int T,value;
        cout<<"Enter the Value of  node\n";
        cin>>value;
        temp1=create_node(value);

        cout<<"Do You Still want to create child\nIf yes please enter 1\n";
        cin>>T;
        if(T==1){
        temp1->left=Tree_creation(temp1->left);
        temp1->right=Tree_creation(temp1->right);
        }
        return temp1;
    }
    Tree_node* insert(int data,Tree_node * root){
        if(root==NULL){
            root=create_node(data);
        }
        else {
            if(data>root->key){
               root->right= insert(data,root->right);
            }
            else if(data<root->key){
               root->left = insert(data,root->left);
            }
        }
        return root;
    }   
    void Tree_Traversal(Tree_node* temp2){ //traverses a tree and print the key of a node.
        if(temp2==NULL){
            return;
        }
        
        Tree_Traversal(temp2->left);
		cout<<temp2->key<<"\n";
        Tree_Traversal(temp2->right);
        return;
    }
	
	int check_tree_identical(Tree_node* tree1,Tree_node* tree2){
		if(tree1 == NULL && tree2 == NULL)
			return 1;
		else if(tree1 == NULL && tree2 != NULL)
			return 0;
		else if(tree1 != NULL && tree2 == NULL)
			return 0;
		else if(tree1->key==tree2->key){
			if(check_tree_identical(tree1->left,tree2->left)){
				if(check_tree_identical(tree1->right,tree2->right)){
					return 1;
				}
			}
			else{
				return 0;
			}
		}	
	}
	
	int check_tree_structure(Tree_node* tree1,Tree_node* tree2){
	if(tree1 == NULL && tree2 == NULL){
		return 1;
	}
	else if(tree1 == NULL && tree2 != NULL){
		return 0;
	}
	else if(tree1 != NULL && tree2 == NULL){
		return 0;
	}
	else{
		if(check_tree_structure(tree1->left,tree2->left)){
			if(check_tree_structure(tree1->right,tree2->right)){
				return 1;
			}
		}
		else{
			return 0;
		}
	}
}
	
};
int main(){
    Tree t1,t2;
    int data,n;
    cout<<"Enter number of the nodes in tree"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>data;
        t1.root=t1.insert(data,t1.root);
    }
	cout<<"\n\n\n\n";
	cout<<"Enter number of the nodes in tree"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>data;
        t2.root=t2.insert(data,t2.root);
    }
	
    cout<<"\n\n\n\n";
    t1.Tree_Traversal(t1.root);
	t2.Tree_Traversal(t2.root);
	if(t1.check_tree_identical(t1.root,t2.root)){
		cout<<"The trees are identical\n";
	}
	else{
		cout<<"Trees are not identical\n";
	}
	if(t1.check_tree_structure(t1.root,t2.root)){
		cout<<"Tree is structurally identical\n";
	}   
	else{
		cout<<"Tree is not sturcturally identical\n";
	}
	return 0;
}