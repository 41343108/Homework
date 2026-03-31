# 41343108

作業一 *Max/Min Heap*

## 解題說明

本題要求實作一個最小優先佇列（Min Priority Queue），並以 C++ 抽象類別（ADT）與繼承的方式完成。

### 解題策略

1.首先定義一個抽象類別 MinPQ，其功能與題目給的 MaxPQ 類似，但邏輯改為「最小優先」。

2.接著建立 MinHeap 類別，繼承自 MinPQ，並使用陣列（array）實作完全二元樹。

## 程式實作

以下為主要程式碼: 

### Push 核心

```cpp
while (index > 0) {
    int parent = (index - 1) / 2;

    if (heap[parent] <= heap[index]) break;

    swap(heap[parent], heap[index]);
    index = parent;
}
```

### Pop 核心

```cpp
while (2 * index + 1 < size) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = left;

    if (right < size && heap[right] < heap[left])
        smallest = right;

    if (heap[index] <= heap[smallest]) break;

    swap(heap[index], heap[smallest]);
    index = smallest;
}
```

## 效能分析
| 函式          | 時間複雜度    | 空間複雜度 |
| ----------- | -------- | ----- |
| `Push()`    | O(log n) | O(1)  |
| `Pop()`     | O(log n) | O(1)  |

## 測試與驗證

### 測試案例

| 測試編號 | 測資（Push順序）        | 操作            | 預期輸出              | 實際輸出              |
| ---- | ----------------- | ------------- | ----------------- | ----------------- |
| 1    | 30, 10, 50, 5, 20 | Top()         | 5                 | 5                 |
| 2    | 30, 10, 50, 5, 20 | Pop() → Top() | 10                | 10                |
| 3    | 5, 10, 15, 20, 25 | Top()         | 5                 | 5                 |
| 4    | 25, 20, 15, 10, 5 | Top()         | 5                 | 5                 |
| 5    | 30, 10, 50, 5, 20 | 連續 Pop()      | 5, 10, 20, 30, 50 | 5, 10, 20, 30, 50 |
| 6    | 空 Heap            | IsEmpty()     | true              | true              |
| 7    | 空 Heap            | Pop()         | 無錯誤         | 無錯誤               |
| 8    | 空 Heap            | Top()         | 顯示錯誤              | 顯示錯誤              |



### 編譯與執行指令

```bash
# 編譯
g++ minheap.cpp -o minheap.exe

# 執行
minheap.exe
```

### 結論

1.使用抽象類別 MinPQ 定義最小優先佇列。

2.以陣列實作完全二元樹（MinHeap）。

3.透過 HeapifyUp / HeapifyDown 維持 Heap 性質。

4.插入與刪除時間複雜度為 O(log n)。

## 申論及開發報告

### 1. **系統設計與架構**  
	本題透過抽象類別 MinPQ 定義最小優先佇列的基本操作（IsEmpty、Top、Push、Pop），並以 MinHeap 類別繼承實作。此設計採用物件導向概念，使程式具有良好的模組化與擴充性，不同實作方式可共用相同介面。

### 2. **資料結構與核心機制**  
	本系統使用陣列實作完全二元樹，並利用索引關係快速定位父節點與子節點。為維持 MinHeap（父節點 ≤ 子節點）的性質，在插入時透過 HeapifyUp（上濾）將較小元素往上移動，在刪除時透過 HeapifyDown（下濾）將較大元素往下調整，使最小值始終位於根節點。

### 3. **效能與驗證結果**  
	插入與刪除操作時間複雜度皆為 O(log n)，而查詢最小值與判斷是否為空為 O(1)，符合效率要求。經多組測試（隨機、遞增、遞減與邊界情況）驗證，結果皆正確，且可依序輸出由小到大的資料，證明本系統具備良好的正確性與穩定性。


-------------------------------------------


作業二 *Binary Search Tree*

## 解題說明

(a) 隨機建立 BST 並分析高度。

(b) BST 刪除節點之實作。

### 解題策略

1.利用 BST 性質（左 < 根 < 右）快速搜尋。

2.刪除後仍需維持 BST 結構。

3.所有操作都沿著樹高進行。

## 程式實作

以下為主要程式碼：

(a) BTS插入
```cpp
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

```
(a) 計算高度
```cpp
int height(Node* node) {
    if (node == nullptr)
        return 0;

    return 1 + max(height(node->left), height(node->right));
}
```
(a)實驗關鍵
```cpp
int h = tree.height();
double ratio = h / log2(n);

```

(b) BST 刪除核心
```cpp
Node* deleteNode(Node* node, int k) {
    if (node == nullptr)
        return nullptr;

    if (k < node->key)
        node->left = deleteNode(node->left, k);
    else if (k > node->key)
        node->right = deleteNode(node->right, k);
    else {
        // 情況1：沒有子節點
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // 情況2：只有一個子節點
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // 情況3：兩個子節點
        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->right = deleteNode(node->right, temp->key);
    }

    return node;
}

```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 **O(n2^n)**。
2. 空間複雜度：空間複雜度為 **O(n)**。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入集合 (S)       | 期望輸出冪集                                                                              |
| ---- | -------------- | ----------------------------------------------------------------------------------- |
| 1    | {a}          | { {}, {a} }                                                                       |
| 2    | {a, b}       | { {}, {a}, {b}, {a, b} }                                                          |
| 3    | {a, b, c}    | { {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} }                               |

### 編譯與執行指令

```bash
$ g++ powerset.cpp -o powerset

powerset.exe

```

### 結論

1. 問題性質:
	
	本題是要列舉一個集合的 冪集 (Powerset)。
	
	若集合大小為𝑛，則必須產生2^n個子集合。 

2. 測試案例:
	
	驗證公式：輸出數量必須等於2^𝑛。
	
	已提供多組測試（空集合、單元素、兩元素、三元素等）。 

3. 程式碼中利用 push_back + pop_back 保證正確回溯，不影響其他分支。

## 申論及開發報告

本題要求設計一個程式，能輸入一個集合並輸出其所有子集合。

### 1. **程式邏輯簡單直觀**  

   *選取該元素*
   
   *不選取該元素*
   
	因此整個解空間為一棵深度為𝑛的二元遞迴樹，節點數為 2^(𝑛+1) −1。

### 2. **易於理解與實現**  

採用 遞迴 + 回溯法 (recursion + backtracking)：
	
	遞迴參數包含：集合、目前子集合、當前索引。
	
	每層分為「選取」與「不選取」兩種情況。
	
	遞迴到底 (index == n) 時輸出子集合。
	
	使用回溯 (push_back / pop_back) 保持正確狀態。

### 3. **遞迴的語意清楚**

1.冪集列舉問題本質上具有 指數級複雜度。

2.遞迴回溯法程式碼簡潔直觀。

3.在 n 較大時，應避免完整列舉，改採數學公式、條件篩選或統計方法處理。
