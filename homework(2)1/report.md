# 41343108

作業一 *Max/Min Heap*

## 解題說明

本題要求實作一個最小優先佇列（Min Priority Queue），並以 C++ 抽象類別（ADT）與繼承的方式完成。

### 解題策略

1.首先定義一個抽象類別 MinPQ，其功能與題目給的 MaxPQ 類似，但邏輯改為「最小優先」。

2.接著建立 MinHeap 類別，繼承自 MinPQ，並使用陣列（array）實作完全二元樹。

## 程式實作

以下為主要程式碼: 

### Push

```cpp
while (index > 0) {
    int parent = (index - 1) / 2;

    if (heap[parent] <= heap[index]) break;

    swap(heap[parent], heap[index]);
    index = parent;
}
```

### Pop

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
(a) 實驗關鍵
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

| 操作           | 說明             | 時間複雜度          | 空間複雜度    |
| ------------ | -------------- | -------------- | -------- |
| 插入（Insert）   | 單次插入沿樹高比較      | O(h)           | O(1)     |
| 建立 BST       | 插入 n 次         | O(n log n)（平均） | O(n)     |
| 高度計算（Height） | 遍歷整棵樹          | O(n)           | O(h)（遞迴） |
| 計算 ratio     | height / log₂n | O(1)           | O(1)     |
| 搜尋節點 | 找到要刪除的節點 | O(h)  | O(1)     |
| 刪除節點 | 處理三種情況   | O(h)  | O(h)（遞迴） |
| 找最小值 | 找右子樹最小節點 | O(h)  | O(1)     |

## 測試與驗證

### 測試案例

(a)
| n     | Height | log₂(n) | Height / log₂(n) |
| ----- | -----: | ------: | ---------------: |
| 100   |     14 |    6.64 |             2.11 |
| 500   |     19 |    8.97 |             2.12 |
| 1000  |     21 |    9.97 |             2.11 |
| 2000  |     23 |   10.97 |             2.10 |
| 3000  |     24 |   11.55 |             2.08 |
| 5000  |     26 |   12.29 |             2.12 |
| 10000 |     28 |   13.29 |             2.11 |

(b)
| 測試編號 | 初始輸入                 | 刪除值 | 節點類型        | 預期中序輸出               |
| ---- | -------------------- | --- | ----------- | -------------------- |
| 1    | 50,30,70,20,40,60,80 | 20  | 葉節點         | 30 40 50 60 70 80    |
| 2    | 50,30,70,20,40,60,80 | 30  | 兩個子節點       | 20 40 50 60 70 80    |
| 3    | 50,30,70,20,40,60,80 | 70  | 兩個子節點       | 20 30 40 50 60 80    |
| 4    | 50,30,70,20,40,60,80 | 50  | 兩個子節點（root） | 20 30 40 60 70 80    |
| 5    | 50,30,70,20,40,60,80 | 100 | 不存在節點       | 20 30 40 50 60 70 80 |
| 6    | 50,30,70,20 | 30  | 只有一個左子節點 | 20 50 70 |

### 編譯與執行指令
(a)
```bash
g++ a.cpp -o a.exe
a.exe
```
(b)
```bash
g++ b.cpp -o b.exe
b.exe
```
### 結論

(a)透過隨機插入資料建立BST，並計算高度與 log₂ n 的比值，可以觀察到該比值大致維持在固定範圍。這表示在隨機情況下，BST的高度會隨著資料量成長而呈現 O(log n) 的趨勢。實驗結果驗證了理論分析，說明隨機建立的BST具有良好的平均效能。

(b)本題實作BST刪除節點的功能，並依據節點的不同情況（無子節點、一個子節點、兩個子節點）進行處理。其中在有兩個子節點時，透過取右子樹最小值進行替代，確保刪除後仍維持 BST 性質。整體操作時間複雜度為 O(h)，在平均情況下為 O(log n)，最壞情況為 O(n)，符合BST的理論特性。


## 申論及開發報告

本題要求設計一個程式，能輸入一個集合並輸出其所有子集合。

### 1. **系統設計與實驗方法**  

本題實作二元搜尋樹（Binary Search Tree），並透過均勻亂數產生器產生資料，從空樹開始逐一插入n個節點，建立隨機BST。為分析其結構特性，於每次實驗中計算樹的高度，並進一步求出高度與 log₂ n 的比值，以觀察其隨資料量增加的變化趨勢。

### 2. **資料結構與核心機制**  

BST採用遞迴方式進行插入與高度計算，並利用其「左子樹 < 根節點 < 右子樹」的性質維持資料有序。在刪除節點的設計中，依據節點結構分為三種情況處理：無子節點直接刪除；單一子節點則直接接回；若有兩個子節點，則以右子樹最小節點取代並遞迴刪除，以確保整體BST性質不被破壞。

### 3. **效能分析與驗證結果**

實驗結果顯示，隨機建立的BST其高度與 log n 成正比，使得 height / log₂ n 的比值大致維持在常數範圍（約 2 左右），驗證其平均時間複雜度為 O(log n)。在刪除操作方面，其時間複雜度為 O(h)，平均情況為 O(log n)，最壞情況為 O(n)。整體測試結果顯示，本系統在各種情況下皆能正確維持 BST 結構，並具有良好的效率與穩定性。
