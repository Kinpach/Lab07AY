template<typename T, typename... Args>

class uniq {
    T* ptr = nullptr;
public:
    explicit uniq(T* ptr) : ptr(ptr) {} // Запрет неочевидных преобразований
    
    ~uniq() {
        delete ptr;
    }
    
    uniq(const uniq&) = delete;
    uniq& operator=(const uniq&) = delete;
    
    uniq(uniq&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    // Оператор присваивания перемещения
    uniq& operator=(uniq&& other)  {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    T* get() const {
        return ptr;
    }
    
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
};

template<typename T, typename... Args>
uniq<T> мake_uniq(Args... args) {
    return uniq<T>(new T(args...));
}

template<class T>
class share {
    T* ptr = nullptr;
    size_t* count = nullptr;
    
    void cleanup() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }
    
public:
    explicit share(T* ptr = nullptr) : ptr(ptr), count(ptr ? new size_t(1) : nullptr) {}
    
    ~share() {
        cleanup();
    }
    
    share(const share& other) : ptr(other.ptr), count(other.count) {
        if (count) {
            ++(*count);
        }
    }
    
    share& operator=(const share& other) {
        if (this != &other) {
            cleanup();
            ptr = other.ptr;
            count = other.count;
            if (count) {
                ++(*count);
            }
        }
        return *this;
    }
    
    share(share&& other) : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }
    
    share& operator=(share&& other) {
        if (this != &other) {
            cleanup();
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }
    
    T* get() const {
        return ptr;
    }
    
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
    
    size_t use_count() const {
        return count ? *count : 0;
    }
};

template<typename T, typename... Args>
share<T> make_share(Args... args) {
    return share<T>(new T(args...));
}
