#ifndef ALLOCATOR_SYSTEM_ALLOCATOR
#define ALLOCATOR_SYSTEM_ALLOCATOR

#include "allocator.h"

namespace allocator
{

class SystemAllocator : public Allocator
{
    virtual void *malloc(size_t sz);
    virtual void free(void *mem);
};

} // namespace allocator

#endif
