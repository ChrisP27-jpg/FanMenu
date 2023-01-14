#ifndef _FANS_H_
#define _FANS_H_

#include <iostream>
#include <stdlib.h>
using namespace std;




class Phone {
private:
	string wholeNumber = "";
	string areaCode = ""; 
	string number = "";
public:
	void set(string num){
		wholeNumber = num;
		areaCode = num.substr(1,3);
		number = num.substr(5,8);
	}
	string getArea(){return areaCode;}
	string getWhole(){return wholeNumber;}
	string getNumber(){return number;}
};






class Email {
private:
	string wholeEmail = "";
	string name = ""; 
	string domain = "";
	string topLevel = "";
public:
	void set(string addr){
		wholeEmail = addr;
		name = addr.substr(1,addr.find('@')-1);
		string wholeDomain = addr.substr(addr.find('@')+1);
		domain = wholeDomain.substr(0, wholeDomain.find('.'));
		topLevel = wholeDomain.substr(wholeDomain.find('.')+1);
		
	}
	string getName(){return name;}
	string getWhole(){return wholeEmail;}
	string getDomain(){return domain;}
	string getTopLevel(){return topLevel;}
};




class Fan {
private:
	string lastName="";
	string firstName="";
	Phone phone;
	Email email;
	string seat = "";
	int concessions = -1;
public:
	void setLast(string last){lastName = last;}
	void setFirst(string first){firstName = first;}
	void setPhone(string phoneN){phone.set(phoneN);}
	void setEmail(string emailN){email.set(emailN);}
	void setSeat(string s){seat = s;}
	void setConc(int conc){concessions = conc;}
	void PrintFile(ofstream& fout){
		fout << lastName <<" "<< firstName <<" "<< phone.getWhole() <<" "<< email.getWhole() <<" "<< seat <<" "<< concessions << endl;
	}
	void PrintScreen(){
		cout << lastName <<" "<< firstName <<" "<< phone.getWhole() <<" "<< email.getWhole() <<" "<< seat <<" "<< concessions << endl;
	}
	Phone getPhone(){return phone;}
	Email getEmail(){return email;}
	void spend(int x){concessions-=x;}
	string getName(){return ("\n"+firstName+" "+lastName);}
	int getConcessions(){return concessions;}
	
};

class Node {
public:
    Fan fan;
    Node* next;
};

template <typename T>
class BSTNode{
public:
	T val;
	Node* LL;
	string x="";
	BSTNode<T>* left;
	BSTNode<T>* right;
};

template <typename T>
class BST{
public:
	BSTNode<T>* root=NULL;
	
	//functions
	void insert(T d, Node* n, string x);
	Node* search(string x);
	void remove(T d);
};

template <typename T>
void BST<T>::insert(T d, Node* n, string x)
{
	BSTNode<T>* t = new BSTNode<T>();
	BSTNode<T>* parent;
	t->LL = n;
	t->val = d;
	t->x = x;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;
	// is this a new tree?
	if(root==NULL) root = t;
	else
	{
		//Note: ALL insertions are as leaf nodes
		BSTNode<T>* curr;
		curr = root;
		// Find the Node's parent
		while(curr)
		{
			parent = curr;
			if(t->x > curr->x) curr = curr->right;
			else curr = curr->left;
		}

		if(t->x < parent->x)
			parent->left = t;
		else
			parent->right = t;
	}
}

template <typename T>
Node* BST<T>::search(string x)
{
	//Locate the element
	bool found = false;
	if(root==NULL)
	{
		cout<<" This Tree is empty! "<<endl;
		return NULL;
	}
	else{
		BSTNode<T>* curr;
		//BSTNode<T>* parent;
		curr = root;
		//parent = (BSTNode<T>*)NULL;
		while(curr != NULL)
		{
			if(curr->x == x)
			{
				found = true;
				break;
			}
			else
			{
				//parent = curr;
				if(x>curr->x) curr = curr->right;
				else curr = curr->left;
			}
		}
		if(!found)
		{
			return NULL;
		}
		else
		{
			return curr->LL;
		}

	}
}


template <typename T>
void BST<T>::remove(T d)
{
	bool found = false;
	if(root==NULL)
	{
		//cout<<" This Tree is empty! "<<endl;
		return;
	}
	BSTNode<T>* curr;
	BSTNode<T>* parent;
	curr = root;
	parent = new BSTNode<T>();
	parent->left = root;
	parent->right = root;
	while(curr != NULL)
	{
		if(curr->val.getWhole() == d.getWhole())
		{
			found = true;
			break;
		}
		else
		{
			parent = curr;
			if(d.getWhole()>curr->val.getWhole()) curr = curr->right;
			else curr = curr->left;
		}
	}
	if(!found)
	{
		//cout<<" Data not found! "<<endl;
		return;
	}

	// Node with single child
	if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL
		&& curr->right == NULL))
	{
		if(curr->left == NULL && curr->right != NULL)
		{			
			if(parent->left == curr)
			{
				parent->left = curr->right;
				delete curr;
			}
			else
			{
				parent->right = curr->right;
				delete curr;
			}
		}
		else // left child present, no right child
		{
			if(parent->left == curr)
			{
				parent->left = curr->left;
				delete curr;
			}
			else
			{
				parent->right = curr->left;
				delete curr;
			}
		}
		return;
	}

	//We're looking at a leaf node
	if( curr->left == NULL && curr->right == NULL)
	{
		if (parent == NULL)
		{
			delete curr;

		} else{
			if(parent->left == curr) {parent->left = NULL;}
			else {parent->right = NULL;}
			delete curr;
			return;
		}
	}


	//Node with 2 children
	// replace node with smallest value in right subtree
	if (curr->left != NULL && curr->right != NULL)
	{
		BSTNode<T>* chkr;
		chkr = curr->right;
		if((chkr->left == NULL) && (chkr->right == NULL))
		{
			curr = chkr;
			delete chkr;
			curr->right = NULL;
		}
		else // right child has children
		{
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element

			if((curr->right)->left != NULL)
			{
				BSTNode<T>* lcurr;
				BSTNode<T>* lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while(lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				curr->val = lcurr->val;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else
			{
				BSTNode<T>* tmp;
				tmp = curr->right;
				curr->val = tmp->val;
				curr->right = tmp->right;
				delete tmp;
			}

		}
		return;
	}

}

#endif
