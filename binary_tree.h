#pragma once

#include <string>
template <class T>
class BinaryTree
{
private:
	struct node
	{
		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		T elem;
	};
	node* root = nullptr;
	int size = 0;
    bool (*cmp)(T, T) = asc;
	
private:
	void destructor(node* nodePtr)
	{
		if (nodePtr == nullptr) 
			return;
		if (nodePtr->left != nullptr)
		{
			destructor(nodePtr->left);
			delete nodePtr->left;
		}

		if (nodePtr->right != nullptr)
		{
			destructor(nodePtr->right);
			delete nodePtr->right;
		}
	}
	
	void erase(node* delNode_)
	{
		node* delNode = delNode_;
		if (delNode == nullptr) 
			return;
		if (delNode->right == nullptr && delNode->left == nullptr)
		{
			if (delNode == this->root)
			{
				delete delNode;
				this->root = nullptr;
			}
			else
			{
				if (delNode->parent->right == delNode) delNode->parent->right = nullptr;
				else delNode->parent->left = nullptr;
				delete delNode;
			}
		}
		else if (delNode->right != nullptr && delNode->left == nullptr)
		{
			if (delNode == this->root)
			{
				delNode->right->parent = nullptr;
				this->root = delNode->right;
			}
			else
			{
				if (delNode->parent->left == delNode) delNode->parent->left = delNode->right;
				else delNode->parent->right = delNode->right;
				delNode->right->parent = delNode->parent;
			}
			delete delNode;
		}
		else if (delNode->right == nullptr && delNode->left != nullptr)
		{
			if (delNode == this->root)
			{
				delNode->left->parent = nullptr;
				this->root = delNode->left;
			} else
			{
				if (delNode->parent->left == delNode) delNode->parent->left = delNode->left;
				else delNode->parent->right = delNode->left;
				delNode->left->parent = delNode->parent;
			}
			delete delNode;
		}
		else if (delNode->right != nullptr && delNode->left != nullptr)
		{
			node* swapNode = next(delNode);
			T tmp_value = delNode->elem;
			delNode->elem = swapNode->elem;
			swapNode->elem = tmp_value;
			this->erase(swapNode);
		}
	}
	
	node* next(node* nodePtr)
	{
		if (nodePtr == nullptr) return nullptr;
		if (nodePtr->right != nullptr)
		{
			nodePtr = nodePtr->right;
			while (nodePtr->left != nullptr)
				nodePtr = nodePtr->left;
			return nodePtr;
		}
		else 
			if (nodePtr->parent->left == nodePtr)
				return nodePtr->parent;
		else return nullptr;
	}

	void printAll(node* nodePtr)
	{
		if (nodePtr == nullptr) 
			return;
		if (nodePtr->left != nullptr)
			printAll(nodePtr->left);
		std::cout << nodePtr->elem;
        std::cout << endl;
		if (nodePtr->right != nullptr)
			printAll(nodePtr->right);
	}

public:
	BinaryTree() = default;

	BinaryTree(const T rootElem, bool (*cmp) (T, T))
	{
		this->root = new node;
		this->root->elem = rootElem;
		this->size = 1;
		this->cmp = cmp;
	}
	
	~BinaryTree()
	{
		destructor(this->root);
		size = 0;
		delete this->root;
	}
	
	void Add(const T elem)
	{
		node* nodePtr = this->root;
		this->size++;
		if(this->root == nullptr)
		{
			this->root = new node;
			this->root->elem = elem;
			return;
		}
	
		while(nodePtr != nullptr)
		{
			if(!this->cmp(nodePtr->elem, elem))
			{
				if(nodePtr->left != nullptr)
					nodePtr = nodePtr->left;
				else
				{
					nodePtr->left = new node;
					nodePtr->left->elem = elem;
					nodePtr->left->parent = nodePtr;
					break;
				}
			} 
			else
			{
				if(nodePtr->right != nullptr)
					nodePtr = nodePtr->right;
				else
				{
					nodePtr->right = new node;
					nodePtr->right->elem = elem;
					nodePtr->right->parent = nodePtr;
					break;
				}
			}
		}
	}
	
	void Erase(T elem)
	{
		node* delNode = Search(elem);
		if(delNode == nullptr) return;
		
		erase(delNode);
		--this->size;
	}
	
	bool Exist(const T elem)
	{
		if(Search(elem) != nullptr)
			return true;
		else return false;
	}

	void printAll()
	{
		if (this->root == nullptr) return;
		printAll(this->root);
		std::cout << endl;
	}

	T next(const T elem)
	{
		node* nodePtr = Search(elem);
		nodePtr = next(nodePtr);
		if (nodePtr == nullptr) return 0;
		return nodePtr->elem;
	}
	
	int GetSize() const
	{
		return this->size;
	}
	    
	node* Search(const T elem)
    {
        node* nodePtr = this->root;
        while(nodePtr != nullptr)
        {
            if(!this->cmp(nodePtr->elem, elem))
                nodePtr = nodePtr->left;
            else if(!this->cmp(elem, nodePtr->elem))
                nodePtr = nodePtr->right;
            else 
				return nodePtr;
        }
        return nullptr;
    }
    
	T GetElem(node* cur)
    {
        return cur->elem;
    }
    
	void SetElem(node* cur, T elem)
    {
	    cur->elem = elem;
    }

};