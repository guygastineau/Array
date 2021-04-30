// We should always import our headers first, so we don't
// accidentally satify dependencies for out headers
// unwittingly thorugh includes in our implementation files.
#include "array.h"

// We will at least need the standard library for the allocator functions.
#include <stdlib.h>


// Creation/Allocation

Array *mkArray();

Array *mkArrayWithCap(size_t initial_cap);

Array *arrayFromCArray(size_t len, data_t *buff);

Slice arrayGetSlice(Array *from, size_t start, size_t end);


// Mutation

int arrayAppendS(Array *to, Slice from);

int arrayPrependS(Array *to, Slice from);

int arrayAppend(Array *to, Array *from);

int arrayPrepend(Array *to, Array *from);

int arrayPushF(Array *to, data_t val);

int arrayPushB(Array *to, data_t val);


// Destruction

int arrayDeleteF(Array *from, size_t n);

int arrayDeleteB(Array *from, size_t n);

void arrayClear(Array *target);

void arrayDestroy(Array *target);
