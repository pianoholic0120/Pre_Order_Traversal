#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

struct TreeNode{ // binary tree structure
    char data; // operand or operator
    TreeNode* left;
    TreeNode* right; 
    TreeNode(char value){ // constructor
    	data=value;
    	left=nullptr;
    	right=nullptr;
	}
    ~TreeNode() { // destructor
        delete left;
        delete right;
    }
};

int IsOperand(char c){
	if(c>='A'&&c<='Z'){
		return 1;
	}
	else return 0;
}

int Precedence(char op){ // those with higher values have higher priority
    if(op=='+'||op=='-'){
        return 2;
    }
	else if(op=='*'||op=='/'){
        return 3;
    }
    return 1;
}

TreeNode* ExpressionTree(const string& infix){ // reference to string without modifying it
    stack<TreeNode*> al; // stack for alphabet
    stack<char> op; // stack for operators
    for(int i=0;i<infix.length();i++){ 
        if(IsOperand(infix[i])){
            al.push(new TreeNode(infix[i]));
        } 
		else if(infix[i]=='('){
            op.push(infix[i]);
        }
		else if(infix[i]==')'){
            while(!op.empty()&&op.top()!='('){ // pop operators and create nodes until '(' is found 
                char op_new=op.top();
                op.pop();
                TreeNode* op_r=al.top(); // take right child first
                al.pop();
                TreeNode* op_l=al.top();
                al.pop();
                TreeNode* newNode=new TreeNode(op_new);
                newNode->left=op_l;
                newNode->right=op_r;
                al.push(newNode);
            }
            op.pop(); // remove '('
        } 
		else{
            while(!op.empty()&&(Precedence(op.top())>=Precedence(infix[i]))&&op.top()!='('){
                char op_top=op.top();
                op.pop();
                TreeNode* op_r=al.top();
                al.pop();
                TreeNode* op_l=al.top();
                al.pop();
                TreeNode* newNode=new TreeNode(op_top);
                newNode->left=op_l;
                newNode->right=op_r;
                al.push(newNode);
            }
            op.push(infix[i]);
        }
    }
    while(!op.empty()){
        char op_top=op.top();
        op.pop();
        TreeNode* op_r=al.top();
        al.pop();
        TreeNode* op_l=al.top();
        al.pop();
        TreeNode* newNode=new TreeNode(op_top);
        newNode->left=op_l;
        newNode->right=op_r;
        al.push(newNode);
    }
    return al.top();
}

void PreOrderTraversal(TreeNode* root){
    if(root!=nullptr){
        cout<<root->data;
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

void PostOrderTraversal(TreeNode* root) {
    if(root!=nullptr){
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        cout<<root->data;
    }
}

int MaxHeight(TreeNode* root){ // recursive 
    if(root==nullptr){
        return 0;
    } 
	else{
		return 1+max(MaxHeight(root->left),MaxHeight(root->right));
	}
}

int main(){
    string infix;
    getline(cin,infix);
    TreeNode* root=ExpressionTree(infix);
    PreOrderTraversal(root);
    cout<<endl;
    PostOrderTraversal(root);
    cout<<endl;
    cout<<MaxHeight(root)<<endl;
    return 0;
}
