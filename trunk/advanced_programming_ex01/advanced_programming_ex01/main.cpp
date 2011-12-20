/******************************************************************************
 * Exercise 01 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 *****************************************************************************/

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

/************************* CLASS DEFINITION **********************************/
/* NOTES:
    1) As was mentioned in the QA, we do not reduce the capacity of
        the array due to any variant of a remove method. We reset it only
        when the function deleteAll() is called.
   2) We assumed that the same element can appear more than once
        in an array, thus when we delete (not remove) a certain element,
        we check whether it appears already in the array and remove
        it by address (and not by value. There is further explanation
        in the deleteAll function.
   3) We use delete[] and not delete for elements since these can be
       arrays as well.
 */

class intArray_t
{
    public:
        // CTOR & DTOR:
            intArray_t();
            intArray_t(int);
            ~intArray_t();
        // Methods (requested in exercise):
            int getNumberOfElements() const;
            int getCapacity() const;
            int *getHead() const;
            int *getTail() const;
            int *find(int) const;
            void insert(const int*);
            int *removeByValue(int);
            void removeAll();
            void deleteAllByValue(int);
            void deleteAll();
            int append(int,const int*);
            int prepend(int,const int*);
		// Methods (unrequested in exercise):
            void print();
    private:
        // Class members:
        int **arr, numOfElements, capacity;
        static const int EXPAND_VALUE = 16;
        static const int DEFAULT_CAPACITY = 16;

        // Disable copying for intArray_t:
        intArray_t(const intArray_t &);
        intArray_t & operator = (const intArray_t &);

        // For inner use only:
        void pushBackward(int);
        void removeAllByAddress(int*);
        void checkAndExpandCapacity();
        int appOrPrep(int, const int*, int);
};
/********************** END CLASS DEFINITION *********************************/

/*********************** METHODS DEFINITIONS *********************************/
/* CTOR - Default ************************************************************/
intArray_t::intArray_t():
    arr(NULL),
    numOfElements(0),
    capacity(DEFAULT_CAPACITY)
    {
        arr = new int* [DEFAULT_CAPACITY];
    }

/* CTOR - With initial number of elements ************************************/
/* Allocates new intArray_t with given number of elements.
 * If given number of elements equals or less than 0, acts like default CTOR
 */
intArray_t::intArray_t(int initNumOfElements):
    arr(NULL),
    numOfElements(0),
    capacity((initNumOfElements>0)?initNumOfElements:DEFAULT_CAPACITY)
{
    arr = new int* [(initNumOfElements>0)?initNumOfElements:DEFAULT_CAPACITY];
}

/* DTOR **********************************************************************/
intArray_t::~intArray_t()
{
    if (numOfElements != 0)
    {
        delete[] arr;
    }
}

/* getNumberOfElements() *****************************************************/
/* Returns number of elements in the array
 */
int intArray_t::getNumberOfElements() const
{
    return numOfElements;
}

/* getCapacity() *************************************************************/
/* Returns the capacity of the array
 */
int intArray_t::getCapacity() const
{
    return capacity;
}

/* getHead() *****************************************************************/
/* Returns the first element in the array.
 * If the array is empty, return a NULL value.
 */
int *intArray_t::getHead() const
{
    if (numOfElements == 0)
    {
        return NULL;
    }
    else
    {
        return arr[0];
    }
}

/* getTail() *****************************************************************/
/* Returns the last element in the array.
 * If the array is empty, return a NULL value.
 */
int *intArray_t::getTail() const
{
    if (numOfElements == 0)
    {
        return NULL;
    }
    else
    {
        return arr[numOfElements - 1];
    }
}

/* find(int value) ***********************************************************/
/* returns an element with the given value
 * or 0 (NULL) if fails to find such one.
 */
int* intArray_t::find(int value) const
{
    for(int i = 0; i < numOfElements; i++)
    {
        if (value == *arr[i])
        {
            return arr[i];
        }
    }
    return (int*) 0;
}

 /* insert(int *elem) ********************************************************/
 /* Inserts new element to the array.
  * If new number of elements exceeds capacity,
  * then capacity is expanded by EXPAND_VALUE.
  */
void intArray_t::insert(const int* elem)
{
    // Check whether to expand capacity.
    checkAndExpandCapacity();

    // Insert the new element and modify properties accordingly.
    arr[numOfElements] = (int*) elem;
    numOfElements++;
}

 /* removeByValue(int value) *************************************************/
 /* Removes the first element in the array with the given value
  * If there is no element with the given value return 0 (NULL).
  * Otherwise, return the removed element.
  */
 int* intArray_t::removeByValue(int value)
 {
     int i, *rv = NULL;
     for (i = 0; i < numOfElements; i++)
     {
         if (value == *arr[i])
         {
             rv = arr[i];
             break;
         }
     }
     if (rv == NULL)
     {
         return (int*) 0;
     } else
     {
         pushBackward(i+1); // Push back elements starting
						// from where element was removed.
     }
     return rv;
 }

/* removeAll() ***************************************************************/
/* Removes all the elements from the array,
 * yet doesn't destroy them.
 */
void intArray_t::removeAll()
{
    for (int i = 0; i < numOfElements; i++)
    {
       arr[i] = NULL;
    }
    numOfElements = 0;
 }

/* deleteAllByValue(int value) ***********************************************/
/* Removes all the elements from the array with the given value,
 * yet doesn't destroy them.
 */
void intArray_t::deleteAllByValue(int value)
 {
      /* NOTE: We remove all elements with the same address found since
     * if a specific element appears more than once in the array,
     * it'll become garbage after it was first deallocated
     * (thus ending in an error). Also, there's a possibility that there are
     * different elements with the same value
     * (thus removeByValue won't work). */
     int i;
     int *temp;
     for (i= 0; i < numOfElements; i++)
     {
         if (value == *arr[i])
         {
             temp = arr[i];
             removeAllByAddress(arr[i]);
             delete[] temp;
             --i; // Since we pushed back, we need to 'stay in place'.
         }
     }
}

/* deleteAll() ******************************************************/
/* Removes all the elements from the array,
 * and also deletes them from the memory.
 * We assume capacity becomes 0, and arr is deallocated.
 */
void intArray_t::deleteAll()
{
    /* NOTE: We use removeAllByAddress() again for the same reasons above */
    int *temp; 
    while (numOfElements != 0)
    {
        temp = arr[0];
        removeAllByAddress(arr[0]);
        delete[] temp;
    }
    capacity = 0;
    delete[] arr;
}

/* append(int index, int *elem) **********************************************/
/* Appends element after index in the array.
 * Returns 1 on success and 0 on failure.
 */
int intArray_t::append(int index, const int* elem)
{
    return appOrPrep(index, elem, 0);
}

/* prepend(int index, int *elem) *********************************************/
/* Appends elem before index in the array.
 * Returns 1 on success and 0 on failure.
 */
int intArray_t::prepend(int index, const int* elem)
{
    return appOrPrep(index, elem, 1);
}

/* appOrPrep(int index, int* elem, int prep) *********************************/
/* Used to implement append and prepend.
 * prep is 1 if used for prepend and 0 if used for append.
 */
int intArray_t::appOrPrep(int index, const int* elem, int prep){
    // check for validity of arguments first
    if (index >= numOfElements || index < 0)
        return 0;

    // check whether to expand capacity
    checkAndExpandCapacity();

    // move all elements and insert new element in place
    index -= prep;
    for(int i=numOfElements-1; i>index; i--){
        arr[i+1] = arr[i];
    }
    arr[index+1] = (int*) elem;
    numOfElements++;
    return 1;
}

/* print() *******************************************************************/
/* Prints the array for testing purposes. */
void intArray_t::print()
{
    cout << "[";
    for (int i = 0; i < numOfElements; i++)
    {
        cout << " " << *arr[i];
    }
    cout << "]. ELEMENTS: " << numOfElements << ", CAPACITY: " << capacity;
             
    if (numOfElements != 0)
    {
        cout << ", HEAD: " << *getHead() << ", TAIL: " << *getTail() << ".\n";
    }
    else
    {
        cout << ".\n";
    }
}

/* pushBackward(int index) ***************************************************/
/* Pushes elements 1 index back starting from given value. */
void intArray_t::pushBackward(int index)
{
    for(int i=index; i< numOfElements; i++ )
    {
        arr[i-1] = arr[i];
    }
    arr[numOfElements-1] = NULL;
    numOfElements--;
}

/* removeAllByAddress(int *address) ******************************************/
/* Removes all the elements from the array with the given address. */
void intArray_t::removeAllByAddress(int* address)
 {
     int i;
     for (i= 0; i < numOfElements; i++)
     {
         if (address == arr[i])
         {
             pushBackward(i+1);
             --i; // Since we pushed back, we need to 'stay in place'.
         }
     }
}

/* checkAndExpandCapacity() **************************************************/
/* checks weather to expand capacity in case of an element insertion
 * and expands by EXPAND_VALUE if needed
 */
void intArray_t::checkAndExpandCapacity(){
     if (numOfElements == capacity)
    {
        int **newArr = new int* [capacity + EXPAND_VALUE];
        for (int i = 0; i < numOfElements; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity += EXPAND_VALUE;
    }
}
/*********************** END METHODS DEFINITIONS *****************************/

/*************************** MAIN TEST PROGRAM *******************************/
int main(void)
{
    // Initialize test elements and array.
        intArray_t *array = new intArray_t;
        int iTest;
        int* i1 = new int;
        int* i2 = new int;
        int* i3 = new int;
        int* i4 = new int;
        int* i5 = new int;
        int* i6 = new int;
        int* i7 = new int;
        int* i8 = new int;
        int* i2a = new int;
        *i1 = 1;
        *i2 = 2;
        *i3 = 3;
        *i4 = 4;
        *i5 = 5;
        *i6 = 6;
        *i7 = 7;
        *i8 = 8;
        *i2a = 2;

    // Tests.
        cout << "Welcome to the test routine of Exercise 01.\n";
        cout << "getNumberOfElements, getCapacity, getHead and getTail will not be checked individually since they are included in every printout.\n";

        // Test #1.
            cout << "\nTest #1: Insert Elements.\n";
            cout << "Inserting by order: i1, i2, i3 and i4..\n";
            array->insert(i1);
            array->insert(i2);
            array->insert(i3);
            array->insert(i4);
            array->print();

        // Test #2.
            cout << "\nTest #2: Append Elements.\n";
            cout << "Appending i5 after index 0, i6 after index 2, i7 after index 5, and i8 after index 10 (which is an invalid index)\n";
            array->append(0,i5);
            array->append(2,i6);
            array->append(5,i7);
            array->append(10,i8);
            array->print();

         // Test #3.
             cout << "\nTest #3: Remove All Elements (without deleting).\n";
             array->removeAll();
             array->print();

        // Test #4.
            cout << "\nTest #4: Prepend Elements.\n";
            cout << "This test uses first recreates the array of Test #1\n";
            cout << "Prepending i5 before index 0, i6 before index 2, i7 before index 5, and i8 before index 10 (which is an invalid index)\n";
            array->insert(i1);
            array->insert(i2);
            array->insert(i3);
            array->insert(i4);
            array->prepend(0,i5);
            array->prepend(2,i6);
            array->prepend(5,i7);
            array->prepend(10,i8);
            array->print();
    
        // Test #5.
            cout << "\nTest #5: Capacity Increase.\n";
            cout << "This test inserts more elements to the array to show capacity changes.\n";
            array->insert(i8);
            for (iTest = 0; iTest < 16; iTest++)
            {
                array->insert(i1);
            }
            cout << "First expansion: \n";
            array->print();

             for (iTest = 0; iTest < 16; iTest++)
            {
                array->insert(i2);
            }
            cout << "Second expansion: \n";
            array->print();

        // Test #6.
            cout << "\nTest #6: Find.\n";
            cout << "Finding 1 and comparing addresses.\n";
            cout << "Address outside of array: " << i1 << ".\n";
            cout << "Address from find: " << array->find(1) << ".\n";
            
        // Test #7.
            cout << "\nTest #7: Remove by Value.\n";
            cout << "Removing first element with value 2 from array.\n";
            array->removeByValue(2);
            array->print();

        // Test #8.
            cout << "\nTest #8: Delete All by Value.\n";
            cout << "Removing and deleting all elements with the value 2.\n";
            cout << "Notice that we have two different elements with the value 2 (i2 & i2a), and both are removed.\n";
            array->prepend(4,i2a);
            array->deleteAllByValue(2);
            array->print();
            cout << "Showing that contents of both elements are deallocated, i2: " << *i2 << ", and i2a: " << *i2a << ".\n";

        // Test #9:
            cout << "\nTest #9: Delete All.\n";
            cout << "Removing and deleting all elements from the array.\n";
            array->deleteAll();
            array->print();
            cout << "Showing that all elements that were in the array are deallocated: \n";
            cout << "i1: " << *i1 << ".\n";
            cout << "i2: " << *i2 << ".\n";
            cout << "i3: " << *i3 << ".\n";
            cout << "i4: " << *i4 << ".\n";
            cout << "i5: " << *i5 << ".\n";
            cout << "i6: " << *i6 << ".\n";
            cout << "i7: " << *i7 << ".\n";
            cout << "i8: " << *i8 << ".\n";

    // End test and delete array.
        delete array;
        cout << "\nAll tests are completed.\n";
        return (EXIT_SUCCESS);
}
/**************************** END MAIN TEST PROGRAM **************************/
