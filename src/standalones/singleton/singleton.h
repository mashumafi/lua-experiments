#ifndef SINGLETON_H
#define SINGLETON_H

template <class T, class... U>
class Singleton
{
public:
    Singleton(U... u) : m_instance(u...)
    {
        m_old = s_instance;
        s_instance = &m_instance;
    }
    ~Singleton()
    {
        s_instance = m_old;
    }

    static T *instance()
    {
        return s_instance;
    }

private:
    T m_instance;
    T *m_old;

    static T *s_instance;
};

template <class T, class... U>
T *Singleton<T, U...>::s_instance(nullptr);

#endif