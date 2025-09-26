#include"MemoryPage.h"
class MemoryPool{
    public:
        MemoryPool(int Unit,int Init=256,int Grow=1024);
        ~MemoryPool();
        void* Allocate();
        void Free(void* pFree);
    private:
        int Unitsize;
        int Initsize;
        int Growsize;
        MemoryPage* pBlock;
};
MemoryPool::MemoryPool(int Unit=4,int Init,int Grow):
    Unitsize(Unit),
    Initsize(Init),
    Growsize(Grow),
    pBlock(NULL)
{
    if(Unit>4)Unitsize=(Unit+7)&~7;
    else if(Unit>2)Unitsize=4;
    else Unitsize=2;
}
MemoryPool::~MemoryPool(){
    MemoryPage* tmp=pBlock;
    while(tmp!=NULL){
        MemoryPage* Del=tmp;
        tmp=tmp->pNext;
        delete(Del);
    }
}
void* MemoryPool::Allocate(){
    if(pBlock==NULL){
        pBlock=(MemoryPage*)new(Unitsize,Initsize) MemoryPage(Unitsize,Initsize);
        return pBlock->aData;
    }MemoryPage* tmp=pBlock;
    while(!tmp->nFree)tmp=tmp->pNext;
    if(tmp==NULL){
        if(Growsize==0)return NULL;
        tmp->pNext=(MemoryPage*)new(Unitsize,Growsize) MemoryPage(Unitsize,Growsize);
        tmp=tmp->pNext;
        return (void*)tmp->aData;
    }tmp->nFree--;
    char* ptmp=tmp->aData+tmp->nFirst*Unitsize;
    tmp->nFirst=*ptmp;
    return (void*)ptmp;
}void MemoryPool::Free(void* pFree){
    MemoryPage* ptmp=pBlock;
    MemoryPage* pre=NULL;
    while(ptmp!=NULL&&(ptmp->aData>pFree||ptmp->aData+ptmp->nSize<pFree)){
        pre=ptmp;
        ptmp=ptmp->pNext;
    }if(ptmp==NULL){
        throw "404";
        return;
    }*(int*)pFree=ptmp->nFirst;
    ptmp->nFirst=((char*)pFree-ptmp->aData)/Unitsize;
    ptmp->nFree++;
    if(ptmp->nFree==ptmp->nSize/Unitsize){
        if(pre==NULL)pBlock=ptmp->pNext;
        else pre->pNext=ptmp->pNext;
        delete ptmp;
    }else{
        pre->pNext=ptmp->pNext;
        ptmp->pNext=pBlock->pNext;
        pBlock=ptmp;
    }
}