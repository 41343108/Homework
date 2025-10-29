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

以下為主要程式碼: 

(瘋狂程設)

```cpp

class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream &output, const Polynomial &Poly);
private:
	int exp;
	float coef;
};

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
	void newTerm(const float newcoef, const int newexp);

```
(Visual Studio)

```cpp
class Term {
    friend class Polynomial;
private:
    int exp;
    float coef;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

public:
    Polynomial();
    ~Polynomial();
    Polynomial Add(Polynomial b);
    Polynomial Mult(Polynomial b);
    float Eval(float x);
    void newTerm(const float newcoef, const int newexp);
};

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
| **解構子安全性**              | 可能重複 delete                    | 不會                                        | 因為每個物件都有獨立的記憶體                     |
| **Move semantics (可選)** | ❌ 無                            | ✅ 可加（非必須）                                   | 提升效能，減少不必要複製                       |

-------------------------------------------

作業二

## 解題說明

編寫 C++ 函數用於計算多項式的加法。

### 解題策略

在第一題的 Polynomial 類別基礎上，
去完成兩個功能：

	輸入多項式運算子	operator>>
	輸出多項式運算子	operator<<

再利用程式碼做出加法運算。
	
## 程式實作

以下為主要程式碼：

```cpp

istream& operator>>(istream& is, Polynomial& poly) {
//輸入運算子多載
	float coef;
	int exp, n;
	is >> n;
	while (n--) {
		is >> coef >> exp;
		poly.newTerm(coef, exp);
	}
	return is;
}


ostream& operator<<(ostream& out, const Polynomial& p) {
//輸出運算子多載
    if (p.terms == 0) {
        out << "0";
        return out;
    }
    for (int i = 0; i < p.terms; ++i) {
        if (i > 0) out << " + ";
        out << p.termArray[i].coef << "X^" << p.termArray[i].exp;
    }
    return out;
}

```

## 效能分析

| 函式名稱         | 時間複雜度 | 空間複雜度 |
| ------------ | ----- | ----- |
| `operator>>` | O(n)  | O(n)  |
| `operator<<` | O(n)  | O(1)  |

整體C++函式運作
| **時間複雜度** | **O(m + n)** |
| **空間複雜度** | **O(m + n)** |


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

1.使用者可輸入任意項數的多項式，每項的係數與指數皆能正確讀取並儲存。

2.輸出結果格式化清晰，能依序列印各項之係數與指數。

3.對於空多項式（項數為 0）的情況，能正確顯示為 0。

4.程式執行穩定，無記憶體錯誤或越界情形。

## 申論及開發報告

本題要求設計一個程式，能輸入兩個多項式(不限項數)做加法運算。

### 1. **類別宣告**  

為了讓運算子能夠直接存取類別內的私有成員 (termArray, terms)，
operator>> 與 operator<< 必須宣告為 friend function。

### 2. **輸入及輸出**  

透過 operator>> 讀入多項式的項數，並依序輸入每一項的係數與指數。

使用先前設計的 newTerm() 函式將資料新增至 termArray 動態陣列中。

透過 operator<< 將多項式以可讀性高的格式輸出。

### 3. **指數排序+合併策略**

依序比較兩多項式當前項的指數。

若指數相同 → 係數相加，結果插入新多項式。

若指數不同 → 將指數較大的項直接加入新多項式。

當其中一個多項式處理完後，將另一個剩餘的項全部加入結果。
