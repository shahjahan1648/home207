#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of files: ";
    cin >> n;

    int files[n];

    cout << "Enter file sizes:\n";
    for (int i = 0; i < n; i++) {
        cin >> files[i];
    }

    // Greedy step: sort in ascending order
    sort(files, files + n);

    cout << "\nOptimal order of storing files:\n";
    for (int i = 0; i < n; i++) {
        cout << files[i] << " ";
    }

    // Calculate Mean Retrieval Time (MRT)
    int sum = 0, total = 0;

    for (int i = 0; i < n; i++) {
        sum += files[i];
        total += sum;
    }

    float mrt = (float)total / n;

    cout << "\nMean Retrieval Time: " << mrt << endl;

    return 0;
}