#include <iostream>
#include <stdexcept>

// 队列节点结构
template <typename T>
struct QueueNode {
    T data;           // 节点数据
    QueueNode* next;  // 指向下一个节点的指针
    
    // 构造函数
    QueueNode(const T& value) : data(value), next(nullptr) {}
};

// 队列数据结构实现，遵循先进先出(FIFO)原则
template <typename T>
class Queue {
private:
    QueueNode<T>* frontNode;  // 队头指针
    QueueNode<T>* rearNode;   // 队尾指针
    int elementCount;         // 元素数量

public:
    // 构造函数
    Queue() : frontNode(nullptr), rearNode(nullptr), elementCount(0) {}

    // 析构函数
    ~Queue() {
        // 清空队列
        clear();
    }

    // 拷贝构造函数
    Queue(const Queue& other) : frontNode(nullptr), rearNode(nullptr), elementCount(0) {
        QueueNode<T>* current = other.frontNode;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // 赋值运算符
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            // 清空当前队列
            clear();
            
            // 复制元素
            QueueNode<T>* current = other.frontNode;
            while (current != nullptr) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // 判断队列是否为空
    bool isEmpty() const {
        return elementCount == 0;
    }

    // 返回队列的大小
    int size() const {
        return elementCount;
    }

    // 入队操作
    void enqueue(const T& item) {
        // 创建新节点
        QueueNode<T>* newNode = new QueueNode<T>(item);
        
        // 如果队列为空，新节点既是队头也是队尾
        if (isEmpty()) {
            frontNode = newNode;
            rearNode = newNode;
        } else {
            // 否则添加到队尾
            rearNode->next = newNode;
            rearNode = newNode;
        }
        
        elementCount++;
    }

    // 出队操作
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无法执行dequeue操作");
        }
        
        // 保存队头节点指针
        QueueNode<T>* temp = frontNode;
        
        // 移动队头指针到下一个节点
        frontNode = frontNode->next;
        
        // 如果队头指针为空，说明队列已空，队尾指针也置为空
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        
        // 释放原队头节点内存
        delete temp;
        elementCount--;
    }

    // 获取队头元素
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无法获取队头元素");
        }
        return frontNode->data;
    }

    // 获取队头元素（const版本）
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无法获取队头元素");
        }
        return frontNode->data;
    }

    // 清空队列
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// 测试队列的功能
int main() {
    try {
        Queue<int> queue;
        
        std::cout << "队列是否为空: " << (queue.isEmpty() ? "是" : "否") << std::endl;
        std::cout << "队列的大小: " << queue.size() << std::endl;
        
        // 入队操作
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        
        std::cout << "入队后队列的大小: " << queue.size() << std::endl;
        std::cout << "队头元素: " << queue.front() << std::endl;
        
        // 出队操作
        queue.dequeue();
        std::cout << "出队后队头元素: " << queue.front() << std::endl;
        std::cout << "出队后队列的大小: " << queue.size() << std::endl;
        
        // 再入队几个元素
        queue.enqueue(40);
        queue.enqueue(50);
        
        std::cout << "再次入队后队列的大小: " << queue.size() << std::endl;
        std::cout << "当前队头元素: " << queue.front() << std::endl;
        
        // 清空队列
        queue.clear();
        std::cout << "清空队列后队列是否为空: " << (queue.isEmpty() ? "是" : "否") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
    