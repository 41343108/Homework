# 41343108 / 41343114

## Sorting Project

### 一、解題說明

本作業的目標是使用 C++ 實作四種排序法，並根據 worst-time criterion 比較它們在不同資料大小下的執行時間，最後設計一個 composite sorting function，使其在不同 n 值下能選擇較適合的排序方法。

本專案實作的排序法包含：

1. Insertion Sort
2. Quick Sort
3. Iterative Merge Sort
4. Heap Sort
5. Composite Sort

其中 Quick Sort 使用 median-of-three 方法，Merge Sort 使用 iterative method。

---

### 二、作業要求整理

根據題目要求，本作業需要完成以下項目：

* 使用 C++ 實作四種排序法
* 測試排序結果是否正確
* 測試 n = 500、1000、2000、3000、4000、5000 時的執行時間
* 產生 worst-case 或近似 worst-case 測試資料
* 繪製排序時間比較圖
* 根據實驗結果設計 composite sorting function
* 繳交完整程式碼與實驗報告

---

### 三、Worst-Case 測試資料產生方式

#### 1. Insertion Sort

Insertion Sort 的 worst-case 是完全反序資料。

例如 n = 5 時：

```text
5 4 3 2 1
```

因為每次插入都需要往前比較與搬移，因此時間複雜度為 O(n²)。

---

#### 2. Quick Sort

Quick Sort 使用 median-of-three 方法後，真正的 worst-case 不容易直接產生。

因此本專案使用 random permutation 隨機排列資料，對每一個 n 值產生至少 10 組不同的隨機資料，測量每次排序時間，最後取最大值作為近似 worst-case time。

---

#### 3. Merge Sort

Merge Sort 的 worst-case 可由反向推導產生。為了讓實驗設計簡潔，本專案使用反序資料作為測試資料，並觀察其 O(n log n) 的穩定趨勢。

本專案採用 iterative merge sort，避免遞迴呼叫造成額外成本。

---

#### 4. Heap Sort

Heap Sort 的 worst-case 較難直接產生，因此本專案依照題目建議，使用 random permutation 隨機排列資料。

對每個 n 值產生至少 10 組隨機資料，測量 Heap Sort 的執行時間，並取最大值作為近似 worst-case time。

---

### 四、Composite Sort 設計

Composite Sort 的概念是根據資料大小選擇適合的排序法。

本專案設計如下：

```cpp
void compositeSort(vector<int>& a) {
    if (a.size() <= 32) {
        insertionSort(a);
    } else {
        mergeSortIterative(a);
    }
}
```

設計原因：

* Insertion Sort 對小資料有較低的額外成本
* Merge Sort 在大型資料下具有穩定的 O(n log n) worst-case 效能
* 因此小資料使用 Insertion Sort，大資料使用 Merge Sort

---

### 五、主要程式碼

#### Insertion Sort

```cpp
void insertionSort(vector<int>& a) {
    int n = (int)a.size();

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}
```

---

#### Quick Sort：Median-of-Three

```cpp
int medianOfThree(vector<int>& a, int left, int right) {
    int mid = left + (right - left) / 2;

    if (a[left] > a[mid]) swap(a[left], a[mid]);
    if (a[left] > a[right]) swap(a[left], a[right]);
    if (a[mid] > a[right]) swap(a[mid], a[right]);

    swap(a[mid], a[right - 1]);
    return a[right - 1];
}
```

---

#### Iterative Merge Sort

```cpp
void mergeSortIterative(vector<int>& a) {
    int n = (int)a.size();
    vector<int> temp(n);

    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n; left += 2 * width) {
            int mid = min(left + width, n);
            int right = min(left + 2 * width, n);

            int i = left;
            int j = mid;
            int k = left;

            while (i < mid && j < right) {
                if (a[i] <= a[j]) temp[k++] = a[i++];
                else temp[k++] = a[j++];
            }

            while (i < mid) temp[k++] = a[i++];
            while (j < right) temp[k++] = a[j++];

            for (int t = left; t < right; t++) {
                a[t] = temp[t];
            }
        }
    }
}
```

---

#### Heap Sort

```cpp
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}
```

---

#### Composite Sort

```cpp
void compositeSort(vector<int>& a) {
    if (a.size() <= 32) {
        insertionSort(a);
    } else {
        mergeSortIterative(a);
    }
}
```

---

### 六、時間複雜度分析

| Sorting Method |  Best Case | Average Case |   Worst Case |
| -------------- | ---------: | -----------: | -----------: |
| Insertion Sort |       O(n) |        O(n²) |        O(n²) |
| Quick Sort     | O(n log n) |   O(n log n) |        O(n²) |
| Merge Sort     | O(n log n) |   O(n log n) |   O(n log n) |
| Heap Sort      | O(n log n) |   O(n log n) |   O(n log n) |
| Composite Sort |     視 n 而定 |       視 n 而定 | 約 O(n log n) |

---

### 七、測試與驗證

#### 測試案例

| 測試編號 | 測資型態               | n    | 測試排序法          | 預期結果   | 實際結果 |
| ---- | ------------------ | ---- | -------------- | ------ | ---- |
| 1    | 反序資料               | 500  | Insertion Sort | 由小到大排序 | 正確   |
| 2    | 反序資料               | 1000 | Merge Sort     | 由小到大排序 | 正確   |
| 3    | Random Permutation | 2000 | Quick Sort     | 由小到大排序 | 正確   |
| 4    | Random Permutation | 3000 | Heap Sort      | 由小到大排序 | 正確   |
| 5    | 反序資料               | 4000 | Composite Sort | 由小到大排序 | 正確   |
| 6    | Random Permutation | 5000 | Composite Sort | 由小到大排序 | 正確   |

---

#### Runtime 範例表

| n    | Insertion Sort | Quick Sort | Merge Sort | Heap Sort | Composite Sort |
| ---- | -------------: | ---------: | ---------: | --------: | -------------: |
| 500  |       0.041 ms |   0.018 ms |   0.029 ms |  0.036 ms |       0.030 ms |
| 1000 |       0.166 ms |   0.038 ms |   0.064 ms |  0.079 ms |       0.065 ms |
| 2000 |       0.670 ms |   0.084 ms |   0.142 ms |  0.173 ms |       0.143 ms |
| 3000 |       1.512 ms |   0.136 ms |   0.226 ms |  0.270 ms |       0.227 ms |
| 4000 |       2.690 ms |   0.191 ms |   0.316 ms |  0.378 ms |       0.317 ms |
| 5000 |       4.195 ms |   0.249 ms |   0.407 ms |  0.492 ms |       0.408 ms |

---

### 八、實驗圖表

#### Composite Sort Flowchart

<img width="2400" height="1400" alt="composite_sort_flowchart" src="https://github.com/user-attachments/assets/535c67df-9217-413f-93f3-8a702fc75127" />

---

#### Sorting Runtime Chart

<img width="2000" height="1200" alt="sorting_runtime_chart" src="https://github.com/user-attachments/assets/e0d698d8-7992-4227-b821-baf3eadc0d6d" />

---

### 九、如何編譯與執行

#### Windows / MinGW

```bash
g++ src/SortingProject.cpp -o SortingProject.exe
SortingProject.exe
```

#### macOS / Linux

```bash
g++ src/SortingProject.cpp -o SortingProject
./SortingProject
```

執行後會產生：

```text
data/sorting_result.csv
```

此 CSV 檔可用 Excel 匯入並繪製折線圖。

---

### 十、實驗結論

由理論與實驗結果可知，Insertion Sort 在小資料量時因為程式簡單、額外成本低，因此可能有不錯表現。但是當 n 增加時，Insertion Sort 的 O(n²) 成長速度會明顯變慢。

Quick Sort 使用 median-of-three 後，平均表現通常不錯，但 worst-case 仍可能達到 O(n²)。Merge Sort 與 Heap Sort 在 worst-case 下都能維持 O(n log n)，因此在 worst-time criterion 下較穩定。

本作業最後設計的 Composite Sort 在 n 較小時使用 Insertion Sort，在 n 較大時使用 Iterative Merge Sort，使整體排序效能更穩定，也符合 worst-case performance 的設計目標。

---

## 申論及開發報告

### 1. 系統設計與架構

本作業以 C++ 實作四種排序方法，包含 Insertion Sort、Quick Sort、Merge Sort 與 Heap Sort，並額外設計 Composite Sort 作為綜合排序函式。程式架構分為排序函式、測資產生函式、時間測量函式與主程式實驗流程，使整體設計具有良好的模組化與可讀性。

---

### 2. 資料結構與核心機制

本系統使用 `vector<int>` 儲存整數資料。Insertion Sort 透過逐步插入方式完成排序；Quick Sort 使用 median-of-three 選擇 pivot，以降低切割不平均的機率；Merge Sort 使用 iterative method 進行區間合併，避免遞迴造成額外成本；Heap Sort 則利用最大堆積結構，反覆將最大值移至陣列尾端完成排序。Composite Sort 則根據資料大小決定使用 Insertion Sort 或 Merge Sort。

---

### 3. 效能與驗證結果

實驗結果顯示，Insertion Sort 在小資料時有較低的額外成本，但隨著 n 增加，其 O(n²) 的成長趨勢會使執行時間快速上升。Merge Sort 與 Heap Sort 在 worst-case 下皆能維持 O(n log n)，因此較適合作為大型資料的穩定排序方法。Quick Sort 在 median-of-three 的設計下平均表現良好，但 worst-case 仍可能退化。整體而言，Composite Sort 透過小資料使用 Insertion Sort、大資料使用 Merge Sort 的策略，能取得較穩定且有效率的排序表現。
