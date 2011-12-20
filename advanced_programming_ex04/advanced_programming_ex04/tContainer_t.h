/******************************************************************************
 * Exercise 04 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * tContainer_t.
 *****************************************************************************/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>
#include <ostream>
using namespace std;

// Compare Class.
template <class T> class compare
{
public:
	compare(T t):value(t) {}
	bool operator()(T* ip) const { return *ip == value; }
private:
	T value;
};

// Container Class.
template <class T, class Container> class tContainer_t
{
	typedef typename Container::iterator iter_t;

	public:
		// CTORs, DTOR:
		tContainer_t(void) { };

		~tContainer_t(void) { };


		// Methods:

		/* T* find(const T& value)
		/* returns the first element in the container with the given value or NULL if no such element exists. */
		T* find(const T& value) { 
			iter_t iter = find_if(container.begin(), container.end(), compare<T>(value));
			return (iter != container.end()) ? *iter : NULL; 
		}
		
		/* void insert(T* element)
		/* inserts the given element to the container. */
		void insert(T* element) { 
			container.push_back(element); 		
		}

		/* T* remove(const T& value)
		/* removes the first element with the given value from the container and returns it.
		/* if no such element exists, returns NULL. */
		T* remove(const T& value) { 
			iter_t iter = find_if(container.begin(), container.end(), compare<T>(value));
			if (iter != container.end())
			{
				T* rv = *iter;
				container.erase(iter);
				return rv;
			}
			return NULL;
		}

		/* void removeAndDelete(const T& value)
		/* removes the first element with the given value from the container and deletes it. */
		void removeAndDelete(const T& value) {
			T* deleted = remove(value);
			delete deleted;
		}

		/* void removeAll()
		/* removes all elements in the container without deleting them. */
		void removeAll() {
			container.clear();
		}


		// Queries:

		/* bool isEmpty(void) const
		/* returns true iff the container is empty. */
		bool isEmpty(void) const { 
			return container.empty(); 
		}


		// Getters:

		/* int getLength(void) const
		/* returns the current size of the container. */
		int getLength(void) const { 
			return (int) container.size(); 
		}

		/* T* getFirst(void) const
		/* returns the first element in the container or NULL if the container is empty. */
		T* getFirst(void) const { 
			return container.empty() ? NULL : container.front();
		}

		/* T* getLast(void) const
		/* returns the last element in the container or NULL if the container is empty. */
		T* getLast(void) const { 
			return container.empty() ? NULL : container.back(); 
		}


		// Operators:
	
		/* T* operator[](int index)
		/* overriding operator [], returns the element in the given i'th position.
		/* throws exception if index is out of bounds. */
		T* operator[](int index) { 
			if (index >= (int) container.size() || index < 0)
			{
				throw std::out_of_range("Index out of container range");
			}
			iter_t iter = container.begin();
			advance(iter, index);
			return *iter;
		}

		/* tContainer_t & operator+=(tContainer_t & addedContainer)
		/* overriding operator +=, merges given container into this container and empties the given container. */
		tContainer_t & operator+=(tContainer_t & addedContainer) {
			for (int i = 0; i < addedContainer.getLength(); i++)
			{
				this->insert(addedContainer[i]);
			}
			addedContainer.removeAll();
			return *this;
		}

	protected:
		// Members:
		Container container;


	private:
		// Copy CTOR (disallow copy)
		tContainer_t(tContainer_t & copy);
		tContainer_t & operator=(const tContainer_t &);
};
