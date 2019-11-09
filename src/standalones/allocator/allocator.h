#ifndef ALLOCATOR_H
#define ALLOCATOR_H

namespace allocator
{

class Allocator
{
public:
    virtual void *malloc(size_t) = 0;
    virtual void free(void *) = 0;
};

} // namespace allocator

#endif
