#ifndef MEMOPOOL_H
#define MEMOPOOL_H

#include<QVector>
class memoPool
{
public:
    memoPool();
    int init(int count,int size);
    void uninit();
    void clear();
    int pushdata(char*data,int len);
    int popdata(char*data,int len);


private:
    std::vector<char*> m_memory;
    int m_count;
    int m_size;
    int __in;
    int __out;
    int __inposition;
    int __outposition;
};

#endif // MEMOPOOL_H
