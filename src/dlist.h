//Meeshaan Shah
//CPSC 350
//Assignment 4
//Header file for generic doubly linked list, used initially for list of advisee
//now use BST for list of advisees

#ifndef DLIST_H
#define DLIST_H

//class for creating nodes for the linked list
template <typename T>
class ListNode
{
	public:
		//ListNode();			//default constructor
		ListNode(T d);			//constructor
		virtual ~ListNode();	//destructor
		T data;					//data for node
		ListNode<T> *next;		//nodes next pointer
		ListNode<T> *prev;		//nodes previous pointer
};

//default constructor
//template <typename T>
//ListNode<T>:: ListNode()
//{
//}

//constructor for the list node class, sets data and sets next and previous ponters to zero
template <typename T>
ListNode<T>:: ListNode(T d)
{
	data = d;
	next = 0;
	prev = 0;
}

//destructor for list node
template <typename T>
ListNode<T>:: ~ListNode()
{
	//data = NULL;
	delete next;
	delete prev;
}

//class for the doubly linked list
template <typename T>
class DList 
{
	public:
		DList();							//constructor
		virtual ~DList();					//destructor
		void addBack(T d);					//adds node to the back of the list
		void removeFront();					//removes node from front of the list
		void remove(T d);
		bool contains(T d);
		T getFront();						//gets item at the front of the list
		T getPos(int p);
		bool isEmpty(){return (size == 0);}	//checks if list is empty
		int getSize(){return size;}			//returns size of list
		void printList();
		
	private:
		ListNode<T>* front;
		ListNode<T>* back;
		int size;
};

//constructor, sets size, listnode front and back pointers to 0	
template <typename T>
DList<T>:: DList()
{
	size = 0;
	front = 0;
	back = 0;
}

//destructor for link list, uses removeFront until list is empty
template <typename T>
DList<T>:: ~DList()
{
	while (!isEmpty())
	{
		removeFront();
	}
}

//add nodes to the back of the list
template <typename T>
void DList<T>:: addBack(T d)
{
	ListNode<T>* newNode = new ListNode<T>(d);
	
	//if list is empty
	if (isEmpty())
	{
		front = newNode;
		back = newNode;
		++size;
	}
	//is list is not empty 
	else
	{
		back -> next = newNode;
		newNode -> prev = back;
		back = newNode;
		++size;
	}
}

//removes node from the front of the list
template <typename T>
void DList<T>:: removeFront()
{
	ListNode<T>* deleteNode = front;
	
	//if there is one node left in the list
	if (getSize() == 1)
	{
		front = deleteNode -> next;
		back = NULL;
		//delete deleteNode;
		--size;
	}
	//more than one nodes in the list
	else
	{
		front = deleteNode -> next;
		front -> prev = NULL;
		//delete deleteNode;
		--size;
	}
}

//removes node from the front of the list
template <typename T>
void DList<T>:: remove(T d)
{
	ListNode<T>* curr = front;
	if (getSize() == 1)
	{
		curr->next = 0;
		curr->prev = 0;
		--size;
	}
	//remove front if first in the list
	else if (curr->data == d)
	{
		//curr->next->prev = 0;
		front = curr->next;
		front -> prev = 0;
		//curr->next = 0;
		--size;
	}
	//remove back
	else if (back->data == d)
	{
		curr = back;
		curr->prev->next = 0;
		back = curr->prev;
		curr->prev = 0;
		--size;
	}
	else
	{
	    while (curr->data != d && curr->next != 0)
	    {
	        curr = curr->next;
	    }
	
		//delete middle if it is there
		if (curr->data == d)
		{
		    curr->next->prev = curr->prev;
		    curr->prev->next = curr->next;
		    curr->next = 0;
		    curr->prev = 0;
		    --size;
		}
	}
	delete curr;
}

//returns boolean if node is in the list
template <typename T>
bool DList<T>:: contains(T d)
{
	bool ret = false;
	ListNode<T>* curr = front;
	
	//check front
	if (curr->data == d)
	{
		ret = true;
	}
	//check back
	else if (back->data == d)
	{
		ret = true;
	}
	//checks middle
	else
	{
		while (curr->data != d && curr->next != 0)
		{
			curr = curr->next;
		}
		if (curr->data == d)
		{
			ret = true;
		}
	}
	return ret;
}

//returns the item in the front of the list
template <typename T>
T DList<T>:: getFront()
{
	ListNode<T>* frontNode = front;
	return frontNode -> data;	
}

//returns node at current postion
template <typename T>
T DList<T>::getPos(int p)
{
    int count = 0;

    ListNode<T>* curr = front;
    while (count != p && curr != 0)
    {
        curr = curr->next;
        count++;
    }
    return curr->data;
}

//prints the list, used for debugging purposes
template<typename T>
void DList<T>:: printList()
{
	if (isEmpty())
	{
		std::cout << "none" << std::endl;
	}
	else
	{
		ListNode<T>* printNode = front;
		while (printNode -> next != NULL)
		{
			std::cout << printNode -> data << " ";
			printNode = printNode -> next;
		}
		std::cout << printNode ->data << " ";
		std::cout << std::endl;
	}
}

#endif // DLIST_H