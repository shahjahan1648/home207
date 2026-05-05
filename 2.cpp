#include <iostream>
using namespace std;

// Function using Divide & Conquer
void findMinMax(int arr[], int low, int high, int &minVal, int &maxVal) {

    // Base Case 1: One element
    if (low == high) {
        minVal = maxVal = arr[low];
        return;
    }

    // Base Case 2: Two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            minVal = arr[low];
            maxVal = arr[high];
        } else {
            minVal = arr[high];
            maxVal = arr[low];
        }
        return;
    }

    // Divide
    int mid = (low + high) / 2;

    int min1, max1, min2, max2;

    // Conquer
    findMinMax(arr, low, mid, min1, max1);
    findMinMax(arr, mid + 1, high, min2, max2);

    // Combine
    minVal = (min1 < min2) ? min1 : min2;
    maxVal = (max1 > max2) ? max1 : max2;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int minVal, maxVal;

    findMinMax(arr, 0, n - 1, minVal, maxVal);

    cout << "Minimum element: " << minVal << endl;
    cout << "Maximum element: " << maxVal << endl;

    return 0;
}