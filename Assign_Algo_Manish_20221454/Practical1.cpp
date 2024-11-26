#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int comparison = 0;

void swap(int &a,int &b) { // function to swap two elements
    int temp = a;
    a=b;
    b=temp;
}
// Partition Function
int Partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low -1;

    for (int j = low; j<high; j++){
        comparison++; //counting comparison 
        if (arr[j] <pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}
// randomized partition function 
int randomizedPartition(int arr[],int low, int high){
    int randomIndex = low + rand() % (high - low +1);
    swap(arr[randomIndex], arr[high]); //swap random element with the last element
    return Partition(arr,low,high);
}
// Randomized Quick sort function
void randomizedQuickSort(int arr[],int low, int high){
    if (low <high){
        int pivotIndex = randomizedPartition(arr, low, high);
        randomizedPartition(arr,low,pivotIndex - 1);
        randomizedPartition(arr,pivotIndex + 1, high);
    }
}
int main() {
    srand(time(0)); // Seed for random number generation
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    // Sort the array
    randomizedQuickSort(arr, 0, n - 1);
    // Output sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // Output number of comparisons
    cout << "Number of comparisons: " << comparison << endl;
    return 0;
}