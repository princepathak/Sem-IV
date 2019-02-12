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
    static Tree_node* create_node(int key){ //creates a node.
        Tree_node *temp=new Tree_node;
        temp->key=key;
        temp->left=NULL;
        temp->right=NULL;
        cout<<"new key "<<temp->key<<endl;
        return temp;
    }
    static Tree_node* Tree_creation(Tree_node* temp1){
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
    static Tree_node* insert(int data,Tree_node * root){
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
    static void Tree_Traversal(Tree_node* temp2){ //traverses a tree and print the key of a node.
        if(temp2==NULL){
            return;
        }
        
        Tree_Traversal(temp2->left);
		cout<<temp2->key<<"\n";
        Tree_Traversal(temp2->right);
        return;
    }
	
	static int check_tree_identical(Tree_node* tree1,Tree_node* tree2){
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
		if(check_tree_identical(tree1->left,tree2->left)){
				if(check_tree_identical(tree1->right,tree2->right)){
					return 1;
				}
			}
			else{
				return 0;
			}
	}
	static void mirror_image(Tree_node* parent){
		if(parent!=NULL){
			Tree_node* temp=parent->left;
			parent->left=parent->right;
			parent->right=temp;
			mirror_image(parent->left);
			mirror_image(parent->right);
			return;
		}
		else
			return;
	}
	
	static int check_tree_structure(Tree_node* tree1,Tree_node* tree2){
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
static void print(Tree_node* parent,int i){
	if(parent == NULL){
		return;
	}	
	print(parent->right,i+1);
	for(int x=0;x<i;x++){
		cout<<"\t";
	}
	cout<<parent->key<<"\n";	
	print(parent->left,i+1);
}
static int  sum_root(Tree_node *parent,int sum){
	if(parent==NULL){
		if(sum==0){
			return 1;
		}
		return 0;
	}
	return sum_root(parent->left,sum-parent->key) || sum_root(parent->right,sum-parent->key);
}
static int check_bst(Tree_node * parent){
	if(parent==NULL)
		return 1;
	if(parent->left!=NULL){
		if(parent->key<parent->left->key)
			return 0;
	}
	if(parent->right!=NULL){
		if(parent->key>parent->right->key)
			return 0;
	}
	return check_bst(parent->left) && check_bst(parent->right);
}
void print_path(int value,Tree_node *parent){
	if(parent->key == value){
		printf("%d",parent->key);
		return;
	}
	else{
		if(value<parent->key){
			printf("%d->",parent->key);
			print_path(value,parent->left);
		}
		else{
			printf("%d->",parent->key);
			print_path(value,parent->right);
		}
	}
}
void traverse(Tree_node *parent,Tree_node *parent1){
	if(parent==NULL)
		return;
	else if(parent->left ==NULL &&parent->right==NULL){
		print_path(parent->key,parent1);
		printf("\n");
		return;
	}
	else if(parent->left ==NULL &&parent->right!=NULL)
		traverse(parent->right,parent1);
	else if(parent->left !=NULL &&parent->right==NULL)
		traverse(parent->left,parent1);
	else{
		traverse(parent->left,parent1);
		traverse(parent->right,parent1);
	}
	return;
}	
	static int no_of_struct(int n){
		if(n==0||n==1){
			return 1;
		}
		int c = 0;
		for( int i = 0 ; i < n ; i++ ){
			c = c + no_of_struct(i)*no_of_struct(n - 1- i);
		}
		return c;
	}
	static int count(Tree_node * parent){
		if(parent==NULL)
			return 0;
		int sum =0;
		if(parent->left!=NULL)
			sum++;
		if(parent->right!=NULL)
			sum++;
		return sum + count(parent->right) + count(parent->left);
	}
};
int main(){
    Tree t1,t2;
    int data,n;
    cout<<"Enter number of the nodes in tree"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>data;
        t1.root=Tree::insert(data,t1.root);
    }
	cout<<"\n\n\n\n";
	
	cout<<"Enter number of the nodes in tree"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>data;
        t2.root=Tree::insert(data,t2.root);
    }
    cout<<"\n\n\n\n";
	Tree::print(t1.root,0);
	Tree::print(t2.root,0);
	if(Tree::check_tree_identical(t1.root,t2.root))
		cout<<"The trees are identical\n";
	else
		cout<<"Trees are not identical\n";
	if(Tree::check_tree_structure(t1.root,t2.root))
		cout<<"Tree is structurally identical\n"; 
	else
		cout<<"Tree is not sturcturally identical\n";
	Tree::mirror_image(t1.root);
	Tree::print(t1.root,0);
	cout<<"\n";
	if(Tree::check_bst(t2.root)){
		printf("Tree is BST\n");
	}
	else{
		printf("Tree is not BST\n");
	}
	t1.traverse(t2.root,t2.root);
	if(Tree::sum_root(t2.root,35)){
		printf("Such leaf exist");
	}
	else{
		printf("Such Leaf does not exist");
	}
	printf("\nNo. of possible bst for the given tree is %d",Tree::no_of_struct(Tree::count(t2.root)));
	return 0;
	
}