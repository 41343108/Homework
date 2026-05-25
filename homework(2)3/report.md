# 41343108 / 41343114

## Sorting Project

### 一、作業目標

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

- 使用 C++ 實作四種排序法
- 測試排序結果是否正確
- 測試 n = 500、1000、2000、3000、4000、5000 時的執行時間
- 產生 worst-case 或近似 worst-case 測試資料
- 繪製排序時間比較圖
- 根據實驗結果設計 composite sorting function
- 繳交完整程式碼與實驗報告

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

- Insertion Sort 對小資料有較低的額外成本
- Merge Sort 在大型資料下具有穩定的 O(n log n) worst-case 效能
- 因此小資料使用 Insertion Sort，大資料使用 Merge Sort

---

### 五、時間複雜度分析

| Sorting Method | Best Case | Average Case | Worst Case |
|---|---:|---:|---:|
| Insertion Sort | O(n) | O(n²) | O(n²) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) |
| Composite Sort | 視 n 而定 | 視 n 而定 | 約 O(n log n) |

---

### 六、如何編譯與執行

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

### 七、輸出資料欄位

`sorting_result.csv` 包含以下欄位：

| 欄位 | 說明 |
|---|---|
| n | 資料筆數 |
| InsertionSortWorst | Insertion Sort worst-case time |
| QuickSortWorstApprox | Quick Sort 近似 worst-case time |
| MergeSortWorstApprox | Merge Sort 近似 worst-case time |
| HeapSortWorstApprox | Heap Sort 近似 worst-case time |
| CompositeSort | Composite Sort time |

---

### 八、實驗圖表

<img width="2400" height="1400" alt="composite_sort_flowchart" src="https://github.com/user-attachments/assets/535c67df-9217-413f-93f3-8a702fc75127" />

<img width="2000" height="1200" alt="sorting_runtime_chart" src="https://github.com/user-attachments/assets/e0d698d8-7992-4227-b821-baf3eadc0d6d" />

---

### 九、實驗結論

由理論與實驗結果可知，Insertion Sort 在小資料量時因為程式簡單、額外成本低，因此可能有不錯表現。但是當 n 增加時，Insertion Sort 的 O(n²) 成長速度會明顯變慢。

Quick Sort 使用 median-of-three 後，平均表現通常不錯，但 worst-case 仍可能達到 O(n²)。Merge Sort 與 Heap Sort 在 worst-case 下都能維持 O(n log n)，因此在 worst-time criterion 下較穩定。

本作業最後設計的 Composite Sort 在 n 較小時使用 Insertion Sort，在 n 較大時使用 Iterative Merge Sort，使整體排序效能更穩定，也符合 worst-case performance 的設計目標。
