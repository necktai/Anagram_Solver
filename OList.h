
//  Due 10/3/17
//  OList
//  CS20
//  Nick Tai

#ifndef OList_h
#define OList_h

#include <iostream>
#include <exception>
using namespace std;

#define DEBUG_ENABLE 1

#if (DEBUG_ENABLE == 1)
#define DEBUG cout << " ~ ~ ~ DEBUG - You are at line: " << __LINE__ << " ~ " << endl
#else
#define DEBUG
#endif

template <class T>
struct Node
{
	T data;
	Node<T> *next;
};

template <class T>
class OList
{
    friend ostream &operator<< (ostream & out, const OList<T> &rhs)
	{
		Node<T> *temp = rhs.head;
		cout << "{ ";
		while(temp != nullptr)
		{
			out << temp->data << " ";
			temp = temp->next;
		}
		cout << "}" << endl;
		return out;
	}
private:
    Node<T> *head;
    Node<T> *tail;
    int		size;
	void	printBHelper(Node<T> *p);
    void	sorted_insert(T temp, Node<T> *current, Node<T> *prev);
public:

    OList();                        // default constructor
    OList(const OList &copy);       // copy constructor
    OList(const T x[], int length);     // constructor for unsorted array parameter
    ~OList();                       // destructor

    void    print() const;
    void    printBackwards();
    int     getSize() const;
    T       getSmallest() const;
    T       getBiggest() const;

    OList&	operator=(const OList<T> &rhs);
    OList	operator+(const OList<T> &rhs) const;
    OList	operator+=(const OList<T> &rhs);
    bool	operator==(const OList<T> &rhs) const;
    bool	operator!=(const OList<T> &rhs) const;
    int		find(const T temp) const;
    void	insert(T temp);
    void	remove(T temp);
	void	remove(T temp, bool x);
    void	clear();
    bool	isEmpty() const;
};

template <class T>      // default constructor
OList<T>::OList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class T>
OList<T>::OList(const OList &copy)      // copy constructor
{
    head = nullptr;
    tail = nullptr;
    size = 0;
    *this = copy;
}

template <class T>
OList<T>::OList(const T x[], int length)     // array parameter   requires insert
{
	head = nullptr;
	tail = nullptr;
	size = 0; 
	for (int i = 0; i < length; i++)
		insert(x[i]);
}

template <class T>
OList<T>::~OList()                      // destructor       requires remove/clear
{
	clear();
}

template <class T>
void OList<T>::print() const
{
	Node<T> *temp = head;
	cout << "{ ";
	while(temp != nullptr)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "}";
}

template <class T>
void OList<T>::printBHelper(Node<T> *p)
{
    if (p != nullptr)
    {
		printBHelper(p->next);
		cout << p->data << " ";
    }
}

template <class T>
void OList<T>::printBackwards()
{
    cout << "{ ";
    printBHelper(head);
    cout << "} " << endl;
}

template <class T>
int OList<T>::getSize() const
{
    return size;
}

template <class T>
T OList<T>::getSmallest() const
{
    if (head == nullptr)
    {
        throw logic_error("List Empty");
    }
    else
        return(head->data);
//    try
//    {
//        if (size == 0)
//            throw runtime_error("empty list");
//        return head->data;
//    }
//    catch (const exception &e)
//    {
//        cout << e.what() << endl;
//    }
//    return ;
}

template <class T>
T OList<T>::getBiggest() const				// HOW TO DO LOGIC EXCEPTION
{
	if (head == nullptr)
	{
		cout << "List is currently empty" << endl;
		return(NULL);
	}
	else
		return(tail->data);
}

template <class T>
OList<T> &OList<T>::operator=(const OList<T> &rhs)
{
    if (&rhs == this)
    {
        cout << "Self assignment ignored" << endl;
        return (*this);
    }
    
    clear();

    if (rhs.isEmpty() == 1)
        return *this;

    Node<T> *current_rhs = rhs.head;
    Node<T> *tracker = nullptr;
    
    Node<T> *new_ptr = new Node<T>;
    new_ptr->next = nullptr;
    new_ptr->data = current_rhs->data;
    
    head = new_ptr;
    tail = new_ptr;
    ++size;

    tracker = head;
    
    if (rhs.size >= 2)
    {
        current_rhs = current_rhs->next;
        while (current_rhs->next != nullptr)        // this accounts for all the nodes between head and tail
        {
            new_ptr = new Node<T>;
            new_ptr->next = nullptr;
            new_ptr->data = current_rhs->data;
            
            tracker->next = new_ptr;
            tracker = new_ptr;

            current_rhs = current_rhs->next;
            ++size;
        }
        new_ptr = new Node<T>;
        new_ptr->next = nullptr;
        new_ptr->data = current_rhs->data;
        
        tracker->next = new_ptr;
        tail = tracker->next;
        ++size;
    }    

	return *this;
}

template <class T>
void OList<T>::insert(T temp)
{
	Node<T> *new_ptr = new Node<T>;
	new_ptr->next = nullptr;
	new_ptr->data = temp;
	
	if (head == nullptr && tail == nullptr) // inserting empty list
	{
		head = new_ptr;
		tail = new_ptr;
	}
	else
	{
		Node<T> *fake_head = head;
		Node<T> *prev_tracker = head;
		while (fake_head != nullptr && temp >= fake_head->data)		// have to have >= if only have > then something like 1 1 1 1 1 wont work
		{
			prev_tracker = fake_head;
			fake_head = fake_head->next;
		}
		if (fake_head == nullptr)               // we hit the end of the list which means that the data given is the largest
		{
			prev_tracker->next = new_ptr;
			new_ptr->next = nullptr;
			tail = new_ptr;
		}
		else if (fake_head->next == nullptr && fake_head == head)
		{
			head = new_ptr;
			head->next = fake_head;
			tail = fake_head;
		}
		else if (fake_head == head)
		{
			head = new_ptr;
			head->next = fake_head;
		}
		else                                // if the data is between two
		{
			prev_tracker->next = new_ptr;
			new_ptr->next = fake_head;
		}
	}
	size++;
}

template<class T>
void OList<T>::remove(T temp)
{
	int count = 0;
	Node<T> *fake_head = head;
	while (fake_head != nullptr)
	{
		if (fake_head->data == temp)
			++count;
		fake_head = fake_head->next;
	}
	for (int i = 0; i < count; i++)
		remove(temp, false);
}

template<class T>
void OList<T>::remove(T temp, bool x)
{
	if (x == false)
	{
		Node<T> *fake_head = head;
		Node<T> *prev_tracker = head;
		while (fake_head != nullptr && temp != fake_head->data)
		{
			prev_tracker = fake_head;
			fake_head = fake_head->next;
		}
		if (fake_head->next == nullptr && fake_head == head)		// if u needed to delete the first element and theres only one element
		{
			head = nullptr;
			tail = nullptr;
			delete fake_head;
		}
		else if (fake_head->next == nullptr) // unlike insert, this is set up so that it isnt directly on null ptr but just before being on top of null LAST
		{
			tail = prev_tracker;
			prev_tracker->next = nullptr;
			delete fake_head;
		}
		else if (fake_head == head)				// delete the head but theres more than just head
		{
			head = head->next;
			delete fake_head;
		}
		else									// if its in between numbers
		{
			prev_tracker->next = fake_head->next;
			delete fake_head;
		}
		size--;
	}
    if (x == true)
        remove(temp);
}

template<class T>
bool	OList<T>::isEmpty() const
{
	if (head == nullptr && tail == nullptr)
		return 1;
	return 0;
}

template<class T>
void	OList<T>::clear()
{
	Node <T> *temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
		--size;
	}
	head = nullptr;
	tail = nullptr;
}

template<class T>
int		OList<T>::find(const T temp) const      // FROM THE HASHTABLE ASSIGNMENT I'VE ADJUSTED THIS
{
//	int i = 0;
//	Node<T> *fake_head = head;
//	while (fake_head != nullptr && fake_head->data != temp)
//	{
//		++i;
//		fake_head = fake_head->next;
//	}
//	if (fake_head == nullptr)
//		return -1;
//	return i;
    
    Node<T> *fake_head = head;
    while (fake_head != nullptr)
    {
        if (fake_head->data == temp)
            return 1;
        fake_head = fake_head->next;
    }
    return 0;
}

template <class T>
bool OList<T>::operator==(const OList<T> &rhs) const
{
    if (this->getSize() != rhs.getSize())
        return 0;
    Node<T> *current_lhs = head;
    Node<T> *current_rhs = rhs.head;
    while (current_lhs != nullptr && current_rhs != nullptr)
    {
        if (current_rhs->data != current_lhs->data)
            return 0;
        current_lhs = current_lhs->next;
        current_rhs = current_rhs->next;
    }
    return 1;
}

template <class T>
bool OList<T>::operator!=(const OList<T> &rhs) const
{
    return (!(*this == rhs));
}

template <class T>
void OList<T>::sorted_insert(T temp, Node<T> *current, Node<T> *prev)
{
	Node<T> *new_ptr = new Node<T>;
	new_ptr->next = nullptr;
	new_ptr->data = temp;
	
	if (current == head && current->next == nullptr && temp <= current->data)		// IF WE NEED TO INSERT IN FRONT OF OLD HEAD BUT THATS OLD NODE IS ONLY NODE IN THE LIST
	{
		head = new_ptr;
		head->next = current;
		tail = current;
	}														// ALSO ADDED TEMP <= CURRENT->DATA FOR THE CASE WITH LHS = {1} AND RHS = {3}
	else if (current == head && temp <= current->data)		// IF WE NEED TO INSERT IN FRONT OF OLD HEAD AND THERES A NODE AFTER THE OLD HEAD
	{
		head = new_ptr;
		head->next = current;
	}														// ALSO ADDED TEMP <= CURRENT->DATA FOR THE CASE WITH LHS = {1} AND RHS = {3}
	else if (current->data <= temp && current->next == nullptr)
	{
		current->next = new_ptr;
		new_ptr->next = nullptr;
		tail = new_ptr;
	}
	else
	{
		prev->next = new_ptr;
		new_ptr->next = current;
	}
	++size;
}

template <class T>
OList<T> OList<T>::operator+=(const OList<T> &rhs)
{
    Node<T> *current_lhs = head;
    Node<T> *current_rhs = rhs.head;
	Node<T> *prev_tracker = head;

    int new_size = 0;
    new_size = size + rhs.getSize();
//    if (size == 0)    // need to change later
//    {
//        *this = rhs;
//        return *this;
//    }
    while (size != new_size)
    {
        while (current_lhs->data < current_rhs->data && current_lhs->next != nullptr)  // dont run if theres only one element
        {
			prev_tracker = current_lhs;
            current_lhs = current_lhs->next;
        }
        while (current_lhs->data >= current_rhs->data && (size != new_size) && current_lhs->next != nullptr)
        {
            if (current_rhs->next == nullptr)									// DON'T WANT TO GO TO A NULLPTR FOR CURRENT_RHS
                sorted_insert(current_rhs->data, current_lhs, prev_tracker);
            else if (current_lhs == head)										// WE INSERT INFRONT OF OLD HEAD BUT IF WE DO IT MULTIPLE TIMES WE HAVE TO POINT BACK TO HEAD																																	WITH CURRENT_LHS
            {
                sorted_insert(current_rhs->data, current_lhs, prev_tracker);
				current_lhs = head;
                current_rhs = current_rhs->next;
            }
			else
			{
				sorted_insert(current_rhs->data, current_lhs, prev_tracker);
				prev_tracker = prev_tracker->next;
				current_rhs = current_rhs->next;
			}
        }
		if (current_lhs->next == nullptr && current_lhs->data <= current_rhs->data && (size != new_size))	// FOR WHEN RHS IS BIGGER AND HAS EXTRA ELEMENTS TO PUT IN
		{
			while (current_rhs != nullptr && (size != new_size))
			{
				if (current_lhs == head)
				{
					sorted_insert(current_rhs->data, current_lhs, prev_tracker); // THIS IS FOR WHEN WE HAVE ONLY ONE ELMENT ON LHS BUT A BUNCH OF THE RHS
					current_rhs = current_rhs->next;
				}
				else
				{
					sorted_insert(current_rhs->data, current_lhs, prev_tracker);
					current_rhs = current_rhs->next;
					current_lhs = current_lhs->next;
				}
			}
		}
		else if (current_lhs->next == nullptr && current_lhs->data > current_rhs->data && (size != new_size))
		{
			while (current_rhs != nullptr)
			{
				sorted_insert(current_rhs->data, current_lhs, prev_tracker); // FOR WHEN WE HAVE THE BIGGEST DATA AS OUR LAST NODE ON LHS AND NEED TO INSERT FROM RHS
				prev_tracker = prev_tracker->next;
				current_rhs = current_rhs->next;
			}
		}
    }
	return (*this);
}

template <class T>
OList<T>	OList<T>::operator+(const OList<T> &rhs) const
{
	OList x = *this;
	x += rhs;
	return x;
}


#endif /* OList_h */
