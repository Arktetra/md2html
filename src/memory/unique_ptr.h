#ifndef UNIQUE_PTR_
#define UNIQUE_PTR_

/// `UniquePtr` can be used for creating unique pointers.
///
/// Things to consider when creating unique pointers:
/// 
/// 1. Make sure there is only one unique_pointer for a block of memory.
/// 2. `UniquePtr` doesn't solve the dangling pointer problem.
///
/// # Example
/// ```c++
/// int a = 1;
/// UniquePtr<int> ptr = UniquePtr<int>(&a);
/// ```
template <typename T>
class UniquePtr {
    T* ptr;

    public:
        UniquePtr() noexcept : ptr(nullptr) {}
        explicit UniquePtr(T* p) noexcept: ptr(p) {}
        ~UniquePtr() noexcept { delete ptr; }

        UniquePtr(UniquePtr const&) = delete;               // copy constructor
        UniquePtr(UniquePtr&& o) noexcept {                 // move constructor      
            delete ptr;
            ptr = o.ptr;
            o.ptr = nullptr;
        } 
        UniquePtr& operator=(UniquePtr const&) = delete;    // copy assignment operator
        UniquePtr& operator=(UniquePtr&& o) noexcept {      // move assignment operator
            delete ptr;
            ptr = o.ptr;
            o.ptr = nullptr;
            return *this;
        }

        T& operator*() const noexcept {
            return *ptr;
        }

        T* operator->() const noexcept {
            return ptr;
        }

        T* release() noexcept {
            T* old = ptr;
            ptr = nullptr;
            return old;
        }

        void reset(T* p = nullptr) noexcept {
            delete ptr;
            ptr = p;
        }

        T* get() const noexcept {
            return ptr;
        }

        explicit operator bool() const noexcept {
            return ptr != nullptr;
        }
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T (std::forward<Args>(args)...));
}

#endif