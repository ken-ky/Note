template <typename T> class shared_ptr {
  private:
    T *m_ptr;         // 内容指针
    int *m_ref_count; // 引用指针

  public:
    shared_ptr(T *ptr = nullptr) : m_ptr(ptr), m_ref_count(new int(1)) {}
    shared_ptr(const shared_ptr &other)
        : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count) {}
    ~shared_ptr() {
        (*m_ref_count)--;
        if (*m_ref_count == 0) {
            delete m_ptr;
            delete m_ref_count;
        }
    }

    shared_ptr &operator=(const shared_ptr &other) {
        // check self-assignment
        if (this != &other) {
            (*m_ref_count)--; // 若旧指针引用为1，则表示可以释放指向内容
            if (*m_ref_count == 0) {
                delete m_ptr;
                delete m_ref_count;
            }

            m_ptr = other.m_ptr;
            m_ref_count = other.m_ref_count;
            (*m_ref_count)++;
        }
        return *this;
    }
};