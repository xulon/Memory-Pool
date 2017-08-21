#include "memopool.h"

memoPool::memoPool()
{
}

int memoPool::init(int count, int size)
{
    __in  = 0;
    __out = 0;
    __inposition = 0;
    __outposition = 0;
    m_size = size;

    for(int i=0;i<count;i++)
    {
        try
        {
            char* tmp = new char[size];
            m_memory.push_back(tmp);
        }
        catch ( const std::bad_alloc& e )
        {
            m_count = i;
            return i;
        }
    }
    m_count = count;
    return count;
}

void memoPool::uninit()
{

    for(int i=0;i<m_count;i++)
    {
         char* tmp = m_memory.at(i);
         delete []tmp;
         tmp = NULL;
    }

    m_memory.clear();
    __in  = 0;
    __out = 0;
    __inposition = 0;
    __outposition = 0;
    m_size = 0;
    m_count = 0;
}

void memoPool::clear()
{
    __in  = 0;
    __out = 0;
    __inposition = 0;
    __outposition = 0;
}
int memoPool::pushdata(char *data, int len)
{

    int length = 0;
    while(length < len)
    {
        char* tmp = m_memory.at(__in);
        int size = (len-length)>(m_size - __inposition)?m_size - __inposition:len-length;
        if(__in == __out&&__inposition + size> __outposition&& __inposition <__outposition)
        {
            return length;
        }
        memcpy(tmp + __inposition,data+length,size);
        length +=size;
        __in = (__in+(__inposition + size)/m_size)%m_count;
        __inposition = (__inposition + size)%m_size;
    }
    return length;
}

int memoPool::popdata(char *data, int len)
{

    int length = 0;
    while(length < len)
    {
        char* tmp = m_memory.at(__out);
        int size = (len-length)>(m_size - __outposition)?m_size - __outposition :len-length;
        if(__out == __in && __outposition + size> __inposition && __outposition <= __inposition)
        {
            return length;
        }
        memcpy(data+length,tmp+__outposition,size);
        length +=size;
        __out= (__out+(__outposition + size)/m_size)%m_count;
        __outposition = (__outposition + size)%m_size;
    }
    return length;
}


