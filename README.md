# 内存池的简单实现
学习一下，基本都是抄的，其中内存块的实现封装在MemoryPage.h,内存池封装在MemoryPool.h
## 接口
## MemoryPool(int Unit,int Init=256,int Grow=1024)
**Unit:申请的内存单位大小**
**Init:初始分配内存大小**
**Grow:内存块后续增长速度**
内存池构造函数
## void* Allocate()
返回一个与构造函数对应的可用的指针
## void Free(void* pFree)
**pFree:指定的指针位置**
释放指定的内存
