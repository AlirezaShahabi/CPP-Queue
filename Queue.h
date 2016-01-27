// front: begining of array
// back:  end of array
#include <iostream>

template <typename T> class Queue {

    friend void print(const Queue& obj, std::ostream& os) {
        if (obj.is_empty()) {
            os << "Queue is empty\n";
        } else {
            for (size_t i = obj.cap_front; i <= obj.cap_back; ++i) {
                os << obj.data[i] << " ";
            }
            os << "\n\n";
        }
    }
public:
    // constructor - operator - destrucor
    Queue();
    Queue(const Queue&);
    Queue& operator=(Queue);
    ~Queue();
    // swap
    Queue& swap(Queue&);
    // add-remove-access-modify
    Queue& push(const T&); // add to back
    Queue& pop();          // remove from front
    T& back();
    T& front();
    // get information
    size_t size() const;
    bool is_empty() const;
    
private:
    T* data;
    size_t cap_back;  // index of element at back
    size_t cap_front; // index of element at front
    size_t length;
    // private utility functions
    void check_n_alloc();
    void reallocate();
    void free_up();
};


// constructor
template <typename T> Queue<T>::Queue():data(nullptr), cap_back(-1),
cap_front(-1), length(0) {}

// copy constructor
template <typename T> Queue<T>::Queue(const Queue& rhs):
data(rhs.is_empty() ? nullptr:(new T[rhs.length])), cap_back(rhs.cap_back),
cap_front(rhs.cap_front), length(rhs.length) {
    if (!rhs.is_empty()) {
        std::copy(rhs.data + rhs.cap_front, rhs.data + rhs.cap_back + 1,
                  data);
    }
}

// assignment operator
template <typename T> Queue<T>& Queue<T>::operator=(Queue rhs) {
    swap(rhs);
    return *this;
}

// destructor
template <typename T> Queue<T>::~Queue() {free_up();}

// swap
template <typename T> Queue<T>& Queue<T>::swap(Queue& rhs) {
    using std::swap;
    swap(data, rhs.data);
    swap(cap_back, rhs.cap_back);
    swap(cap_front, rhs.cap_front);
    swap(length, rhs.length);
    return *this;
}

// add new element to back
template <typename T> Queue<T>& Queue<T>::push(const T& obj) {
    check_n_alloc();
    data[++cap_back] = obj;
    return *this;
}

// remove an element from front
template <typename T> Queue<T>& Queue<T>::pop() {
    if (is_empty()) {
        std::cerr << "Queue is empty\n";
    } else if (cap_back == cap_front) {
        free_up();
        cap_back = -1;
        cap_front = -1;
        length = 0;
    } else if (cap_back > cap_front) {
        ++cap_front;
    }
    return *this;
}

// return a reference to the elemnt at back
template <typename T> T& Queue<T>::back() {return data[cap_back];}

// return a reference to the element at front
template <typename T> T& Queue<T>::front() {return data[cap_front];}

// return the number of element in the Queue
template <typename T> size_t Queue<T>::size() const {
    return is_empty() ? 0 : (cap_back - cap_front + 1);
}

// check if Queue is empty
template <typename T> bool Queue<T>::is_empty() const {
    return (cap_back == -1 && cap_front == -1) ? 1:0;
}


// private utility functions


// check if Queue is full (or nullptr)
template <typename T> void Queue<T>::check_n_alloc() {
    if (cap_back == length - 1) {reallocate();}
}

// allocate new space for Queue 
template <typename T> void Queue<T>::reallocate() {
    if (is_empty()) {
        length = 1;
        data = new T[length];
        cap_front = 0;
    } else {
        length = 2 * size();
        T* new_data = new T[length];
        std::copy(data + cap_front, data + cap_back + 1, new_data);
        free_up();
        data = new_data;
        // cap_back() must be initialized before cap_front!
        cap_back = size() - 1;
        cap_front = 0;
    }
}

// free up memory
template <typename T> void Queue<T>::free_up() {
    if (!is_empty()) {
        delete[] data;
        data = nullptr;
    }
}

