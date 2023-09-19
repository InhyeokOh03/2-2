#include <iostream>

using namespace std;

void mySort(int arr[], int n) {
    for (int i = 0; i < n; i++) { // The number of element is 7 (n = 7), then do 6 cycles.
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] <= arr[j + 1]) continue;
            else {
                int temp = arr[j];

                // cout << temp << arr[j] << arr[j + 1] << endl; // for check.

                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
}

int main() {
    int arr[] = { 3, 1, 2, 5, 6, 7, 10 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    mySort(arr, n);
    cout << "Sorted array: \n"; 
    printArray(arr, n);
    return 0;
}