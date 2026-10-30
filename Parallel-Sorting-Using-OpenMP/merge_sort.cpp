
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

const int TASK_CUTOFF = 16384;

// Merge two sorted portions
void merge(int a[], int temp[], int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= r)
        temp[k++] = a[j++];

    for (int x = l; x <= r; x++)
        a[x] = temp[x];
}

// Sequential Merge Sort
void sequentialMergeSort(int a[], int temp[], int l, int r) {
    if (l >= r) return;

    int mid = l + (r - l) / 2;

    sequentialMergeSort(a, temp, l, mid);
    sequentialMergeSort(a, temp, mid + 1, r);

    merge(a, temp, l, mid, r);
}

// Parallel Merge Sort using OpenMP tasks
void parallelMergeSort(int a[], int temp[], int l, int r) {
    if (l >= r) return;

    // Avoid creating tasks for small subarrays
    if (r - l + 1 <= TASK_CUTOFF) {
        sequentialMergeSort(a, temp, l, r);
        return;
    }

    int mid = l + (r - l) / 2;

    #pragma omp task firstprivate(a, temp, l, mid)
    parallelMergeSort(a, temp, l, mid);

    #pragma omp task firstprivate(a, temp, mid, r)
    parallelMergeSort(a, temp, mid + 1, r);

    #pragma omp taskwait

    merge(a, temp, l, mid, r);
}

int main() {
    vector<int> sizes = {100000, 500000, 1000000};

    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 1000000);

    cout << "========================================\n";
    cout << " PARALLEL MERGE SORT USING OPENMP\n";
    cout << "========================================\n";
    cout << "OpenMP Threads: " << omp_get_max_threads() << "\n\n";

    for (int n : sizes) {
        vector<int> original(n);

        for (int &x : original)
            x = dist(rng);

        vector<int> seq = original;
        vector<int> par = original;

        vector<int> tempSeq(n);
        vector<int> tempPar(n);

        // Sequential execution
        auto start = high_resolution_clock::now();

        sequentialMergeSort(seq.data(), tempSeq.data(), 0, n - 1);

        auto stop = high_resolution_clock::now();

        double seqTime =
            duration<double, milli>(stop - start).count();

        // Parallel execution
        start = high_resolution_clock::now();

        #pragma omp parallel
        {
            #pragma omp single
            parallelMergeSort(par.data(), tempPar.data(), 0, n - 1);
        }

        stop = high_resolution_clock::now();

        double parTime =
            duration<double, milli>(stop - start).count();

        // Verify correctness
        bool correct = (seq == par) && is_sorted(par.begin(), par.end());

        double speedup = seqTime / parTime;

        cout << "Input Size: " << n << "\n";
        cout << "Sequential Time: " << seqTime << " ms\n";
        cout << "Parallel Time:   " << parTime << " ms\n";
        cout << "Speedup:         " << speedup << "x\n";
        cout << "Correctness:     "
             << (correct ? "PASSED" : "FAILED") << "\n";
        cout << "----------------------------------------\n";
    }

    return 0;
}

