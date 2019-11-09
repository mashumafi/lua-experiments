#include "system_allocator.h"

#include <stdlib.h>

namespace allocator
{

void *SystemAllocator::malloc(size_t sz)
{
    return ::malloc(sz);
}
void SystemAllocator::free(void *mem)
{
    ::free(mem);
}

} // namespace allocator
