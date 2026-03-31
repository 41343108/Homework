#include <iostream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}

    virtual bool IsEmpty() const = 0;

    virtual const T& Top() const = 0;

    virtual void Push(const T&) = 0;

    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int capacity;
    int size;

    void Swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void HeapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[parent] <= heap[index])
                break;

            Swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void HeapifyDown(int index) {
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;

            if (right < size && heap[right] < heap[left]) {
                smallest = right;
            }

            if (heap[index] <= heap[smallest]) {
                break;
            }

            Swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    MinHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return size == 0;
    }

    const T& Top() const override {
        if (IsEmpty()) {
            cerr << "Heap is empty!" << endl;
            exit(1);
        }
        return heap[0];
    }

    void Push(const T& value) override {
        if (size == capacity) {
            cerr << "Heap is full!" << endl;
            return;
        }

        heap[size] = value;
        HeapifyUp(size);
        size++;
    }

    void Pop() override {
        if (IsEmpty()) {
            cerr << "Heap is empty, cannot pop!" << endl;
            return;
        }

        heap[0] = heap[size - 1];
        size--;
        if (size > 0) {
            HeapifyDown(0);
        }
    }

    void PrintHeap() const {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap<int> h(20);

    h.Push(30);
    h.Push(10);
    h.Push(50);
    h.Push(5);
    h.Push(20);

    cout << "目前 MinHeap 內容: ";
    h.PrintHeap();

    cout << "最小元素 Top = " << h.Top() << endl;

    h.Pop();
    cout << "刪除最小元素後: ";
    h.PrintHeap();

    cout << "新的 Top = " << h.Top() << endl;

    return 0;
}
