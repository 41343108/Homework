# 41343108

作業一

## 解題說明

本題要求以 C++ 類別 Polynomial 表示一元多項式，並實作多項式的   
輸入、輸出 / 加法、減法、乘法 / 拷貝建構、指定運算子 / 解構子（並回收節點）/ Evaluate(x) 計算值。

### 解題策略

#### 1️.資料結構選擇

● 使用 header node 的 circular linked list 表示多項式

● 每個節點儲存 (coef, exp)

● 空多項式判斷：header->link == header

#### 2.節點管理

● 使用 available-space list（free list）

● 刪除節點 → 回收至 free list

● 建立節點 → 優先從 free list 取得

● 減少 new / delete 次數

#### 3.排序與合併

● 串列永遠依指數遞減排序

● 保證多項式維持正規化

#### 4.加法 / 減法

● 兩條已排序串列 merge

● 指數相同 → 係數加 / 減

● 指數不同 → 較大者先放入

#### 5.乘法

● 使用 雙迴圈展開

● 係數相乘、指數相加

● 插入時自動合併同次方

● 最多產生 m × n 項

#### 6.輸入 / 輸出與計算

● 輸入：n c1 e1 ... cn en

● 輸出：同樣 external format

● Evaluate(x)：逐項計算並加總

## 程式實作

以下為主要程式碼：

節點結構＋Circular Linked List
```cpp
struct Node {
    int coef;      // 係數
    int exp;       // 指數
    Node* link;    // 下一個節點
};

Node* header;     // header node（循環串列）
static Node* avail; // available-space list

```

Available-Space List
```cpp
static Node* GetNode(int c = 0, int e = 0) {
    Node* p;
    if (avail) {
        p = avail;
        avail = avail->link;
    } else {
        p = new Node;
    }
    p->coef = c;
    p->exp = e;
    p->link = nullptr;
    return p;
}

static void RetNode(Node* p) {
    p->link = avail;
    avail = p;
}

```

插入並合併同次方
```cpp
void AddTerm(int c, int e) {
    if (c == 0) return;

    Node* prev = header;
    Node* cur = header->link;

    while (cur != header && cur->exp > e) {
        prev = cur;
        cur = cur->link;
    }

    if (cur != header && cur->exp == e) {
        cur->coef += c;
        if (cur->coef == 0) {
            prev->link = cur->link;
            RetNode(cur);
        }
        return;
    }

    Node* n = GetNode(c, e);
    prev->link = n;
    n->link = cur;
}

```

多項式加法
```cpp
Polynomial operator+(const Polynomial& b) const {
    Polynomial r;
    Node* p = header->link;
    Node* q = b.header->link;

    while (p != header && q != b.header) {
        if (p->exp == q->exp) {
            r.AddTerm(p->coef + q->coef, p->exp);
            p = p->link; q = q->link;
        } else if (p->exp > q->exp) {
            r.AddTerm(p->coef, p->exp);
            p = p->link;
        } else {
            r.AddTerm(q->coef, q->exp);
            q = q->link;
        }
    }
    return r;
}

```

多項式乘法
```cpp
Polynomial operator*(const Polynomial& b) const {
    Polynomial r;
    for (Node* p = header->link; p != header; p = p->link) {
        for (Node* q = b.header->link; q != b.header; q = q->link) {
            r.AddTerm(p->coef * q->coef, p->exp + q->exp);
        }
    }
    return r;
}

```

Evaluate
```cpp
float Evaluate(float x) const {
    double sum = 0;
    for (Node* p = header->link; p != header; p = p->link) {
        sum += p->coef * pow(x, p->exp);
    }
    return (float)sum;
}

```

Copy Constructor
```cpp
Polynomial(const Polynomial& a) {
    header = GetNode(0, 0);
    header->link = header;
    for (Node* p = a.header->link; p != a.header; p = p->link) {
        AddTerm(p->coef, p->exp);
    }
}

```

## 效能分析

| 操作       | 時間複雜度  | 空間複雜度 |
| -------- | ------ | ----- |
| 輸入 / 輸出  | O(m)   | O(m)  |
| 加法 / 減法  | O(m+n) | O(m+n)  |
| 乘法       | O(mn)  | O(mn) |
| Evaluate | O(m)   | O(1)  |


## 測試與驗證

### 測試案例

| 測資一    | 內容                         |
| ----- | -------------------------- |
| 多項式 A | `3 5 4 -2 2 7 0`           |
| 多項式 B | `2 3 1 1 0`                |
| A 表示  | (5x^4 - 2x^2 + 7)          |
| B 表示  | (3x + 1)                   |
| A + B | `4 5 4 -2 2 3 1 8 0`       |
| A - B | `4 5 4 -2 2 -3 1 6 0`      |
| A × B | `6 15 5 5 4 -6 3 -2 2 21 1 7 0` |
| 測試 x  | `2`                        |
| A(2)  | `79`                       |

| 測資二    | 內容                                  |
| ----- | ----------------------------------- |
| 多項式 A | `3 3 3 2 2 -5 0`                    |
| 多項式 B | `3 -3 3 4 1 1 0`                    |
| A 表示  | (3x^3 + 2x^2 - 5)                   |
| B 表示  | (-3x^3 + 4x + 1)                    |
| A + B | `3 2 2 4 1 -4 0`                    |
| A - B | `4 6 3 2 2 -4 1 -6 0`               |
| A × B | `7 -9 6 -6 5 12 4 26 3 2 2 -20 1 -5 0` |
| 測試 x  | `1`                                 |
| A(1)  | `0`                                 |



### 編譯與執行指令

```shell
g++ -std=c++17 -O2 -Wall -Wextra HW3.cpp -o hw3.exe
hw3.exe
```

### 結論

1. 本作業以具 header node 的循環鏈結串列實作一元多項式之內部表示。  
2. 透過排序插入與同次方合併策略，完成多項式加、減、乘及數值計算功能。  
3. 程式結合 available-space list 管理記憶體，兼顧正確性與效率。

## 申論及開發報告

本作業要求以 C++ 實作一元多項式（Polynomial）之表示與運算，並限制必須使用 具有 header node 的循環鏈結串列（circular linked list） 作為內部資料結構。
程式需支援多項式的輸入與輸出，以及加法、減法、乘法與數值計算，並正確處理記憶體管理問題。

1. **設計理念**  
   由於多項式的項數不固定，且需要頻繁進行插入、刪除與合併同次方項，因此本作業選擇以鏈結串列作為資料結構。
   為簡化串列操作並避免處理尾端空指標，本設計採用 header node 的循環鏈結串列，使所有節點操作邏輯保持一致。
   此外，為提升記憶體使用效率，實作 available-space list（free list），將不再使用的節點回收再利用，以降低動態配置成本。
   
2. **資料結構與實作方法**  
   每一個多項式項以一個節點表示，包含係數（coef）、指數（exp）與指向下一節點的指標（link）。整個多項式以指數遞減順序儲存在循環鏈結串列中。
   程式設計一個統一的插入函式，負責依指數順序插入新項，並在遇到相同指數時合併係數；若合併後係數為零，則刪除該節點並回收記憶體。

5. **多項式運算策略**  
   加法與減法運算採用合併兩條已排序串列的方式進行，透過同時走訪兩個多項式，依指數大小決定插入順序，在指數相同時直接進行係數加減。
   乘法運算則使用雙迴圈展開法，將兩多項式的所有項兩兩相乘，並將結果透過插入函式加入結果多項式中，由插入機制自動合併同次方項。數值計算（Evaluate）則逐項計算並加總結果。


本作業以 header node 的 circular linked list 作為多項式內部表示，並透過 AddTerm 實作依指數遞減排序插入與同次方合併，確保多項式維持正規化。加減法採用兩已排序串列的 merge 策略，乘法以雙迴圈展開並透過插入機制自動合併同次方項；Evaluate 則逐項計算並加總。另以 available-space list（free list）回收並重複利用節點，降低頻繁 new/delete 的配置成本，使程式在正確性與效能間取得良好平衡。
