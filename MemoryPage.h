#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<windows.h>
using namespace std;
class MemoryPage{
    public:
        int nSize;
        int nFree;
        int nFirst;
        void* operator new(size_t,int Unitsize,int Unitnum);
        void operator delete(void*,int Unitsize,int Unitnum){};
        void operator delete(void* pBlock);
        MemoryPage(int Unitsize,int Unitnum);
        ~MemoryPage(){};
        MemoryPage* pNext;
        char aData[1];
    
};
MemoryPage::MemoryPage(int Unitsize,int Unitnum):
            nSize(Unitsize*Unitnum),
            nFree(Unitnum-1),
            pNext(NULL),
            nFirst(1)
        {
            char* pData=aData;
            for(int i=1;i<Unitnum-1;i++){
                *pData=i;
                pData+=Unitsize;
            }
        };
void* MemoryPage::operator new(size_t,int Unitsize,int Unitnum){
    return ::operator new(sizeof(MemoryPage)+Unitnum*Unitsize);
}void MemoryPage::operator delete(void* pBlock){
    ::operator delete(pBlock);
}