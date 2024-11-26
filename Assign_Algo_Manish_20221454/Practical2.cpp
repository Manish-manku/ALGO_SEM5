#include <iostream>
#include <cstdlib> 

using namespace std;
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

// Randomized Select function
int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1; // Number of elements in the left partition

    if (i == k) {
        return arr[pivotIndex]; // Pivot is the ith smallest element
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i); // Recur on the left subarray
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k); // Recur on the right subarray
    }
}

int main() {
    int n, i;

    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array:\n";
    for (int j = 0; j < n; j++) {
        cin >> arr[j];
    }

    cout << "Enter the value of i (1 <= i <= n): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid value of i. Please enter a value between 1 and " << n << ".\n";
        return 1;
    }

    int ithSmallest = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "th smallest element is: " << ithSmallest << endl;

    return 0;
}
