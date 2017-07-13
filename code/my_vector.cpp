#include <iostream>
#include <assert.h>
#define DOUBLE_SIZE
using namespace std;

template <typename T>
class Vector {
private:
    const int ADD_SIZE = 64;
    T *array;
    unsigned int vsize;
    unsigned int vcapacity;
    T *allocator(unsigned int size);
    void destory(T *array);
public:
    Vector():array(0), vsize(0), vcapacity(0){}
    Vector(const T& t, unsigned int n);
    Vector(const Vector<T>& other);
    Vector<T>& operator =(Vector<T>& other);
    T &operator[](unsigned int pos);
    unsigned int size();
    unsigned int capacity();
    bool empty();
    void clear();
    void push_back(const T& t);
    void insert_after(int pos, const T& t);
    void push_front(const T& t);
    void insert_before(int pos, const T& t);
    void erase(unsigned int pos);
    void print();
    ~Vector() {
        clear();
    }
};
template <typename T> Vector<T>::Vector(const T& t, unsigned int n):array(0), vsize(0), vcapacity(0) {
    while(n--) {
        push_back(t);
    }
}
template <typename T> Vector<T>::Vector(const Vector<T>& other) {
    array = other.array;
    vsize = other.vsize;
    vcapacity = other.vcapacity;
}
template <typename T> unsigned int Vector<T>::size() {
    return vsize;
}
template <typename T> unsigned int Vector<T>::capacity() {
    return vcapacity;
}
template <typename T> bool Vector<T>::empty() {
    return (vsize == 0);
}
template <typename T> void Vector<T>::clear() {
    destory(array);
    array = 0;
    vsize = 0;
    vcapacity = 0;
}
template <typename T> void Vector<T>::push_back(const T& t) {
    insert_after(vsize - 1, t);
}
template <typename T> void Vector<T>::insert_after(int pos, const T& t) {
    insert_before(pos + 1, t);
}
template <typename T> void Vector<T>::push_front(const T& t) {
    insert_before(0, t);
}
template <typename T> void Vector<T>::insert_before(int pos, const T& t) {
    if(vsize == vcapacity) {
        T *old_array = array;
#ifdef DOUBLE_SIZE
        if(vcapacity == 0)
            vcapacity = 1;
        vcapacity = vcapacity << 1;
#else
        vcapacity += ADD_SIZE;
#endif
        array = allocator(vcapacity);
        for (unsigned int i = 0; i < vsize; ++i)
            array[i] = old_array[i];
        destory(old_array);
    }
    for(int i = (int)vsize++; i > pos; --i)
        array[i] = array[i - 1];
    array[pos] = t;
}
template <typename T> void Vector<T>::erase(unsigned int pos) {
    if(pos < vsize) {
        --vsize;
        for(unsigned int i = pos; i < vsize; ++i)
            array[i] = array[i + 1];
    }
}
template <typename T> void Vector<T>::print() {
    for(unsigned int i = 0; i < size(); ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Real time size = " << size() << endl;
    cout << "The capacity = " << capacity() << endl << endl;
}
template <typename T>T* Vector<T>::allocator(unsigned int size){
    return new T[size];
}
template <typename T> void Vector<T>::destory(T *array) {
    if(array)
        delete[] array;
}
template <typename T> Vector<T>& Vector<T>::operator =(Vector<T>& other) {
    /* 1. 判断是否为同一个对象
     * 2. 清空本身变量、释放申请的内存
     * 3. 重新申请内存
     * 4. 逐字节复制（深拷贝）
     */
    if(this == &other)
        return *this;
    clear();
    vsize = other.size();
    vcapacity = other.capacity();
    array = new T[vcapacity];
    for(unsigned int i = 0; i < vsize; ++i) {
        array[i] = other[i];
    }
    return *this;
}
template <typename T> T& Vector<T>::operator[](unsigned int pos) {
    assert(pos < vsize);
    return array[pos];
}

int main() {
    Vector<int> my_vector;
    // 插入元素
    my_vector.push_back(1);
    my_vector.push_back(2);
    my_vector.push_back(3);
    my_vector.push_front(0);
    if(my_vector.size() == 4)
        my_vector.print();

    // 删除元素(i为下标)
    my_vector.erase(1);
    if((!my_vector.empty()) && my_vector.capacity() == 64)
        my_vector.print();

    // 清空
    my_vector.clear();
    if(my_vector.empty())
        cout << "Vector is empty !" << endl << endl;

    // 测试动态扩展
    for(int i = 0; i < 100; i++)
        my_vector.push_back(i);
    my_vector.print();

    // 测试拷贝构造函数(浅拷贝)
    Vector<int> my_vector_2(my_vector);
    /*
     * my_vector.clear();
     * 调用此句会出错，my_vector指向的内存被释放
     * my_vector_2中array指针为野指针
     */
    my_vector_2.print();

    // 测试=重载运算符
    Vector<int> my_vector_1(0, 10);
    my_vector_1 = my_vector;
    my_vector_1.print();

    // 测试[]重载运算符
    int n;
    cin >> n;
    cout << "The " << n << "th element = " << my_vector[n] << endl << endl;

    return 0;
}