#ifndef ALLOCATOR_DEFAULT_ALLOCATOR
#define ALLOCATOR_DEFAULT_ALLOCATOR

#include "allocator.h"
#include "singleton.h"

namespace allocator
{

class DefaultAllocator
{
public:
    class Instance : public Allocator
    {
    public:
        Instance(Allocator *allocator) : m_allocator(allocator)
        {
        }

        virtual void *malloc(size_t sz)
        {
            return m_allocator->malloc(sz);
        }
        virtual void free(void *mem)
        {
            m_allocator->free(mem);
        }

    private:
        Allocator *m_allocator;
    };

    static Instance *instance()
    {
        return Scoped::instance();
    }

    using Scoped = Singleton<Instance, Allocator *>;
};

} // namespace allocator

#endif
