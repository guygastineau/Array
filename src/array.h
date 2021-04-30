#ifndef ARRAY_H
#define ARRAY_H

// We only include headers in our headers if they are required
// in order for this header to compile correctly. That is,
// header-in-header includes are restricted to hard dependencies
// only. Any other headers needed in the implementation should
// be included in the array.c file itself afte inclusion of this header.
#include <stddef.h>

// Set the minimum capacity for arrays.
#define ARRAY_MIN_CAP 16
// When deleting elements, should the count/capcity ratio
// fall to ARRAY_SHRINK_RATIO we need to shrink
// the Array->cap by half (also using `realloc').
#define ARRAY_SHRINK_RATIO 0.25

// A nice way to abstract our data.
// Still this is specialized and not polymorphic.
typedef int data_t;

// Starting out this should be exposed as such.
// This will make testing and implementation simpler.
// A second look at this exercise will make this opaque
// , ie. an abstract data type. That will allow us to
// expose only safe functions as its interface, but the
// Slice type should also be made available.
typedef struct Array {
  size_t cap;
  size_t count;
  data_t *data;
} Array;

// Const window into a dynamic array.
// Use for read only access to sublists of a dynamic array.
typedef struct Slice {
  size_t count;
  const data_t *data;
} Slice;


/***

  Notes:

    The following interface is fairly minimal, but it provides enough
    functionality to be useful. Moreover, it is small enough and
    straightforward enough that implementation is manageable while
    still aquiring the skills necessary to complete it. This means,
    that upon satisfaction of the accompanying test harness, the
    programmer should be ready for a more advanced and complete
    interface that leverages opaque types as a way to enforce invariants
    and expose a safe interface that will make the library easier
    to use and indeed a better alternative to raw c arrays.

    All that said, the initial interface is not entirely trivial. Care
    must be taken to handle pointers and pointer memory state safely and
    effectively. This will likely be harder than other exercises/projects
    heretofore accomplished by the programmer. As such, there is much
    opportunity to grow and be frustrated even implementing the initial
    interface. Have fun ;)

 ***/


// Creation/Allocation

// Allocate Array with default initial capacity.
Array *mkArray();
// Allocate array with given capacity
// (unless `initial_cap' is less than `ARRAY_MIN_CAP').
Array *mkArrayWithCap(size_t initial_cap);
// Create new array with contents from existing c array (pointer and length)
Array *arrayFromCArray(size_t len, data_t *buff);
// Get subslice of array. Notice, the Slice is a struct not a pointer.
// If `end' is beyond the length of `from' just truncate the slice.
Slice arrayGetSlice(Array *from, size_t start, size_t end);

// Mutation

// These *pend functions that take a slice for `from' can be
// used to implement the Array -> Array *pend functions below.
int arrayAppendS(Array *to, Slice from);
int arrayPrependS(Array *to, Slice from);

// Append (mutates `to')
int arrayAppend(Array *to, Array *from);
// Prepend (mutates `to')
int arrayPrepend(Array *to, Array *from);

// Push to front or back (instead of push and unshift, because
// we will not be implementing the list ops pop and unshift (yet)).
//
// Regardless, arrayPushF is pretty useless, because the whole array
// needs to be compied.  It is just here for symmetry.
//
// Hint, you can use the *pendS functions to implement these.
int arrayPushF(Array *to, data_t val);
int arrayPushB(Array *to, data_t val);

// Destruction

// Once again operations on the fron will be very costly.
int arrayDeleteF(Array *from, size_t n);
int arrayDeleteB(Array *from, size_t n);

// Trivial to implement with either of the above functions.
void arrayClear(Array *target);

// Completely deallocate the target Array.
// Remember to free the internal buffer before freeing the struct itself.
void arrayDestroy(Array *target);


#endif // ARRAY_H
