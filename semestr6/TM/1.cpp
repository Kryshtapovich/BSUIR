#include<iostream>
using namespace std;

int main(){
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 120};
    int key = 1;
    int l = 0;
    int r = 10;
    int mid;

    while (l < r) {
        mid = (l + r) / 2;
        if(a[mid] == key) break;
        if (a[mid] > key) r = mid - 1;
        else l = mid + 1;
    }

    if (a[mid] == key) cout << "Element " << key << " has index " << --r;
    else cout << "There's no such element in array";
    cout << endl;
}
