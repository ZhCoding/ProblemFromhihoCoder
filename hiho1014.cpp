#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef struct node{
    char value; //结点的值
    int childNum; //子结点数目
    struct node* child; //子结点
    struct node* nextSibling; //兄弟结点
}Node;

Node* buildNode( char value ){
    Node* newNode = new Node;
    newNode->value = value;
    newNode->childNum = 0;
    newNode->child = NULL;
    newNode->nextSibling = NULL;
	return newNode;
}

Node* buildTree( Node* root, string word ){
	Node* p, *parent;
	p = root;
	int caseNum = 0;
	parent = root;
	unsigned int matchLength = word.length(); 
	//计算匹配部分的长度
	for( unsigned int i = 0; i < word.length();  ){
		if(  p != NULL ){
			if( p->value == word[i] ){
				p->childNum ++;
				parent = p;
				p = p->child;
				i ++;
				caseNum = 1; //用于在插入结点时确定插入的位置是子结点还是兄弟结点
			}
			else{
				parent = p;
				p = p->nextSibling;
				caseNum = 2;
			}
		}
		else{
			matchLength = i;
			break;
		}
	}

	//添加未匹配部分进入树中
	if( matchLength < word.length() ){
		p = buildNode( word[matchLength] );
		if( parent != NULL ){
			if( matchLength > 0 &&  caseNum == 1 ){
			    parent->child = p;
		    }
		    else{
				parent->nextSibling = p;
		    }
		}
		else{
			root = p;
		}
		parent = p;
		for( unsigned int i = matchLength + 1; i < word.length(); i++ ){
			p = buildNode( word[i] );
			parent->child = p;
			parent->childNum ++;
			parent = p;
		}
		parent->childNum ++;
	}
    return root;
}

int getChildNum( Node* root, string word ){
	//获取以word开头的单词的数目
	Node* p, *parent;
	p = root;
	parent = p;
	for( unsigned int i = 0; i < word.length();  ){
		if(  p != NULL ){
			if( p->value == word[i] ){
				parent = p;
				p = p->child;
				i ++;
			}
			else{
				parent = p;
				p = p->nextSibling;
			}
		}
		else{
			return 0;
		}
	}
	return parent->childNum;
}

void deleteTree( Node* root ){
	//先序遍历树并释放结点
	if( root == NULL ){
		return;
	}
	else
	{
		Node *pc = root->child;
		Node *ps = root->nextSibling;
		delete root;
		deleteTree( pc );
		deleteTree( ps );
	}
}

int main()
{
    int n;
	cin >> n;
	Node* root = NULL;
	for( int i = 0; i < n; i++ ){
		string word;
		cin >> word;
		root = buildTree( root, word );
	}
	cin >> n;
	for( int i = 0; i < n; i++ ){
		string word;
		cin >> word;
		cout<<getChildNum( root, word )<<endl;
	}
	deleteTree( root );
	system("pause");
    return 0;
}
