#include <iostream>
#include <stdexcept>

// 栈数据结构实现，遵循后进先出(LIFO)原则
template <typename T>
class Stack {
private:
    T* data;       // 存储元素的动态数组
    int topIndex;  // 栈顶索引
    int capacity;  // 当前容量

    // 扩容函数，当栈满时自动扩容
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        
        // 复制元素到新数组
        for (int i = 0; i < capacity; ++i) {
            newData[i] = data[i];
        }
        
        // 释放旧数组内存
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // 构造函数
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("初始容量必须为正数");
        }
        data = new T[capacity];
    }

    // 析构函数
    ~Stack() {
        delete[] data;
    }

    // 拷贝构造函数
    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        data = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            data[i] = other.data[i];
        }
    }

    // 赋值运算符
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            topIndex = other.topIndex;
            data = new T[capacity];
            
            for (int i = 0; i <= topIndex; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 判断栈是否为空
    bool isEmpty() const {
        return topIndex == -1;
    }

    // 返回栈的大小
    int size() const {
        return topIndex + 1;
    }

    // 入栈操作
    void push(const T& item) {
        // 如果栈满则扩容
        if (topIndex == capacity - 1) {
            resize();
        }
        data[++topIndex] = item;
    }

    // 出栈操作
    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("栈为空，无法执行pop操作");
        }
        topIndex--;
    }

    // 获取栈顶元素
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("栈为空，无法获取栈顶元素");
        }
        return data[topIndex];
    }

    // 获取栈顶元素（const版本）
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("栈为空，无法获取栈顶元素");
        }
        return data[topIndex];
    }
};

// 测试栈的功能
int main() {
    try {
        Stack<int> stack;
        
        std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;
        std::cout << "栈的大小: " << stack.size() << std::endl;
        
        // 入栈操作
        stack.push(10);
        stack.push(20);
        stack.push(30);
        
        std::cout << "入栈后栈的大小: " << stack.size() << std::endl;
        std::cout << "栈顶元素: " << stack.top() << std::endl;
        
        // 出栈操作
        stack.pop();
        std::cout << "出栈后栈顶元素: " << stack.top() << std::endl;
        std::cout << "出栈后栈的大小: " << stack.size() << std::endl;
        
        // 再入栈几个元素
        stack.push(40);
        stack.push(50);
        
        std::cout << "再次入栈后栈的大小: " << stack.size() << std::endl;
        std::cout << "当前栈顶元素: " << stack.top() << std::endl;
        
        // 清空栈
        while (!stack.isEmpty()) {
            stack.pop();
        }
        std::cout << "清空栈后栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
    