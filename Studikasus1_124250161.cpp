#include <iostream> 
using namespace std;
int main() {
    
    int arr[] = {15, 42, 7, 89, 23, 56, 10}; 
    int n = sizeof(arr) / sizeof(arr[0]);
    int *ptr = arr;                         

    cout << "Elemen array: ";                
    for (int i = 0; i < n; i++) {           
        cout << *(ptr + i) << " ";           
    }
    cout << endl;                           
    int max_val = *(ptr + 0);                
    int min_val = *(ptr + 0);                

    for (int i = 1; i < n; i++) {            
        if (*(ptr + i) > max_val) {        
            max_val = *(ptr + i);
        }
        if (*(ptr + i) < min_val) {          
            min_val = *(ptr + i);         
        }
    }

    
    cout << "Nilai Maximum: " << max_val << endl;
    cout << "Nilai Minimum: " << min_val << endl; 	
    int sum = 0;                            
    for (int i = 0; i < n; i++) {            
        sum += *(ptr + i);   
    }
    double average = (double)sum / n;       
    cout << "Jumlah elemen: " << sum << endl;     
    cout << "Rata-rata:     " << average << endl; 

    return 0;
}
