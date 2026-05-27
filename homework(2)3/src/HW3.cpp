#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Insertion Sort
void insertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Quick Sort - Median of Three
int medianOfThree(vector<int>& a, int left, int right) {
    int mid = left + (right - left) / 2;

    if (a[left] > a[mid]) swap(a[left], a[mid]);
    if (a[left] > a[right]) swap(a[left], a[right]);
    if (a[mid] > a[right]) swap(a[mid], a[right]);

    swap(a[mid], a[right - 1]);
    return a[right - 1];
}

void quickSortRec(vector<int>& a, int left, int right) {
    if (left + 10 <= right) {
        int pivot = medianOfThree(a, left, right);
        int i = left;
        int j = right - 1;

        while (true) {
            while (a[++i] < pivot) {}
            while (a[--j] > pivot) {}

            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }

        swap(a[i], a[right - 1]);

        quickSortRec(a, left, i - 1);
        quickSortRec(a, i + 1, right);
    } else {
        insertionSort(a);
    }
}

void quickSort(vector<int>& a) {
    if (!a.empty()) {
        quickSortRec(a, 0, (int)a.size() - 1);
    }
}

// Iterative Merge Sort
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
                if (a[i] <= a[j])
                    temp[k++] = a[i++];
                else
                    temp[k++] = a[j++];
            }

            while (i < mid)
                temp[k++] = a[i++];

            while (j < right)
                temp[k++] = a[j++];

            for (int t = left; t < right; t++) {
                a[t] = temp[t];
            }
        }
    }
}

// Heap Sort
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = (int)a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// Composite Sort
void compositeSort(vector<int>& a) {
    if (a.size() <= 32) {
        insertionSort(a);
    } else {
        mergeSortIterative(a);
    }
}

// Generate reverse data
vector<int> generateReverseData(int n) {
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        a[i] = n - i;
    }

    return a;
}

// Generate ordered data
vector<int> generateOrderedData(int n) {
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    return a;
}

// Generate random permutation
vector<int> generateRandomPermutation(int n) {
    vector<int> a = generateOrderedData(n);

    random_device rd;
    mt19937 gen(rd());

    for (int i = n - 1; i >= 1; i--) {
        uniform_int_distribution<> dist(0, i);
        int j = dist(gen);
        swap(a[i], a[j]);
    }

    return a;
}

// Check sorted
bool isSorted(const vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i - 1] > a[i])
            return false;
    }

    return true;
}

// Measure runtime
template <typename SortFunction>
double measureTimeMilliseconds(SortFunction sortFunc, vector<int> data, int repeat) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < repeat; i++) {
        vector<int> copy = data;
        sortFunc(copy);

        if (!isSorted(copy)) {
            cout << "Sorting Error!" << endl;
            exit(1);
        }
    }

    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;

    return elapsed.count() / repeat;
}

// Choose repeat times
int chooseRepeat(int n) {
    if (n <= 500)
        return 200;
    else if (n <= 1000)
        return 100;
    else if (n <= 2000)
        return 50;
    else
        return 20;
}

int main() {
    vector<int> sizes = {500, 1000, 2000, 3000, 4000, 5000};
    int randomTrials = 10;

    ofstream fout("sorting_result.csv");

    fout << "n,InsertionSortWorst,QuickSortWorstApprox,MergeSortWorstApprox,HeapSortWorstApprox,CompositeSort\n";

    cout << fixed << setprecision(6);
    cout << "Sorting Runtime Experiment" << endl;
    cout << "Clock: C++ chrono high_resolution_clock" << endl;
    cout << "Random permutations for Quick Sort and Heap Sort: "
         << randomTrials << endl << endl;

    for (int n : sizes) {
        int repeat = chooseRepeat(n);

        vector<int> insertionData = generateReverseData(n);
        vector<int> mergeData = generateReverseData(n);

        double insertionTime =
            measureTimeMilliseconds(insertionSort, insertionData, repeat);

        double mergeTime =
            measureTimeMilliseconds(mergeSortIterative, mergeData, repeat);

        double compositeTime =
            measureTimeMilliseconds(compositeSort, mergeData, repeat);

        double quickMaxTime = 0.0;
        double heapMaxTime = 0.0;

        for (int t = 0; t < randomTrials; t++) {
            vector<int> randomData = generateRandomPermutation(n);

            double qTime =
                measureTimeMilliseconds(quickSort, randomData, repeat);

            double hTime =
                measureTimeMilliseconds(heapSort, randomData, repeat);

            quickMaxTime = max(quickMaxTime, qTime);
            heapMaxTime = max(heapMaxTime, hTime);
        }

        fout << n << ","
             << insertionTime << ","
             << quickMaxTime << ","
             << mergeTime << ","
             << heapMaxTime << ","
             << compositeTime << "\n";

        cout << "n = " << n
             << " | Insertion = " << insertionTime << " ms"
             << " | Quick = " << quickMaxTime << " ms"
             << " | Merge = " << mergeTime << " ms"
             << " | Heap = " << heapMaxTime << " ms"
             << " | Composite = " << compositeTime << " ms"
             << endl;
    }

    fout.close();

    cout << endl;
    cout << "Result saved to sorting_result.csv" << endl;

    return 0;
}
