# 41343108

作業一

## 解題說明

實作整個Polynomial類別(ADT)

### 解題策略

1.建構子
  Add( )
  Mult( )
  Eval( )

2.管理Term陣列( termArray / capacity / terms )

## 程式實作

以下為主要程式碼: (瘋狂程設)

```cpp

class Polynomial {
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial() :capacity(2), terms(0) {
		termArray = new Term[capacity];
	}
	~Polynomial() { delete[] termArray; }

	Polynomial Add(Polynomial b);

	Polynomial Mult(Polynomial b);

	float Eval(float x);

```

## 效能分析

| 函式       | 時間複雜度    | 空間複雜度         |
| -------- | -------- | ------------- |
| `Add()`  | O(m + n) | O(m + n)      |
| `Mult()` | O(m × n) | O(m + n)（或更多） |
| `Eval()` | O(m)     | O(1)          |


## 測試與驗證

### 測試案例

| 第一項 | 第二項 | 輸出結果 |
| - | - | --------- |
| 3 5 2 3 1 7 0 | 2 3 2 -5 0 | 8X^ + 3X^1 + 2X^0 |
| 3 3 4 2 2 -5 0 | 3 -1 3 4 1 -1 0 | 3X^4 + -1X^3 + 2X^2 + 4X^1 + -6X^0 |
| 2 4 3 2 1 | 2 3 3 5 0 | 7X^3 + 2X^1 + 5X^0 |

### 編譯與執行指令

```bash
# 編譯
g++ Source.cpp -o polynomial.exe

# 執行
Polynomial.exe
```

### 結論

1.使用Visual Studio編譯測試會導致多個 Polynomial 共用同一塊記憶體。

2.因此使用Visual Studio更改一些程式在輸入大項數（>10）時能自動擴充記憶體，未發生崩潰。

3.輸入與輸出格式清晰，執行穩定，無記憶體錯誤。

## 申論及開發報告

| 功能                      | 瘋狂程設                             | Visual Studio                                    | 差異說明                               |
| ----------------------- | ------------------------------ | ------------------------------------------- | ---------------------------------- |
| **拷貝建構子**               | ❌ 無                            | ✅ 加入                                        | 保證複製時新建一份 termArray，不共用同一記憶體       |
| **指派運算子 =**             | ❌ 無                            | ✅ 加入                                        | 避免 result = polyA.Add(polyB) 時重複刪除 |
| **newTerm 擴充機制**        | ❌ 沒有 `reserve()`               | ✅ 新增自動擴充                                    | 防止 termArray 滿時寫出界導致 crash         |
| **Add 函式宣告**            | `Polynomial Add(Polynomial b)` | `Polynomial Add(const Polynomial& b) const` | 改成以常量參考傳入，避免多餘複製                   |
| **解構子安全性**              | 可能重複 delete                    | 新版不會                                        | 因為每個物件都有獨立的記憶體                     |
| **Move semantics (可選)** | ❌ 無                            | ✅ 可加（非必須）                                   | 提升效能，減少不必要複製                       |

-------------------------------------------

作業二 *powerset*

## 解題說明

本題要求實作冪集。

### 解題策略

	1.是否選擇a
	2.是否選擇b
	3.是否選擇c
	4.最後印出結果

## 程式實作

以下為主要程式碼：

```cpp

// 遞迴生成冪集
void powerset(vector<char>& set, vector<char>& subset, int index) {
    if (index == set.size()) {   // 遞迴到底：輸出子集合
        cout << "{ ";
        for (char c : subset) cout << c << " ";
        cout << "}" << endl;
        return;
    }
    powerset(set, subset, index + 1);       // 不選當前元素
    subset.push_back(set[index]);           // 選當前元素
    powerset(set, subset, index + 1);
    subset.pop_back();                      // 回溯
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
