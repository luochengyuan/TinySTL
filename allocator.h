#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include<new>
#include<cstddef>
#include<cstdlib>
#include<climits>
#include<iostream>
#include<utility>
namespace MYSTL{

    template<typename T>
    inline T* _allocate(size_t size){
        if(size==0)
            return nullptr;
        //set_new_handler(0);
        T* tmp = static_cast<T*>(::operator new(size * sizeof(T)));
        if(tmp==0){
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }
    template<typename T>
    inline T* _allocate(){
        //set_new_handler(0);
        T* tmp=static_cast<T*>(::operator new(sizeof(T)));
        if(tmp==0){
            std::cerr<<"out of memory"<<std::endl;
            exit(0);
        }
        return tmp;
    }

    template<typename T>
    inline void _deallocate(T* buffer){
        if(buffer==nullptr)
            return;
        ::operator delete(buffer);
    }

    template<typename T>
    inline void _construct(T* p){
        new(p)T();
    }
    template<typename T>
    inline void _construct(T* p,const T& value){
        new(p) T (value);
    }

    template<typename T,typename... Args>
    inline void _construct(T* p,const Args... args){
        int i=0;
        int a[]{(_construct(p+i,args),++i)...};
    }
    template<typename T>
    inline void _destroy(T* p){
        p->~T();
    }

    template<typename T>
    inline void _destroy(T* first,T* last){
        while(first!=last){
            auto tmp=first;
            ++first;
            _destroy(first);
        }
    }


    template<typename T>
    class allocator{
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& cconst_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template<class U>
        struct rebind
        {
            typedef allocator<U> other;
        };
        pointer allocate(size_t n){
            return _allocate<T>(n);
        }
        pointer allocate(){
            return _allocate<T>();
        }
        void deallocate(pointer buffer){
            _deallocate(buffer);
        }
        void deallocate(pointer first,pointer last){
            _deallocate(first,last);
        }
        void construct(pointer p,cconst_reference val){
            _construct<T>(p,val);
        }
        template<typename... Args>
        void construct(pointer p,const Args... args){
            _construct<T>(p,args...);
        }
        void destroy(pointer p){
            _destroy(p);
        }
        void destroy(pointer first,pointer last){
            _destroy(first,last);
        }
    };

}
#endif