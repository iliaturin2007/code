#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, a=0, b=1;
    cin >> n;
    if (n <= 12){
        vector<int> number(n);
        for (int i=0; i<n; i++){
            cin >> number[i];
        }
        for (int i=0; i<n; i++){
            if (number[i] % 2)
                b *= number[i];
            else
                a += number[i];
        }
        cout << "Amount of even number: " << a << endl << "Multiplication of add number: " << b;
    }

    else
        cout << "Mistake";
        
    return 0;
}
