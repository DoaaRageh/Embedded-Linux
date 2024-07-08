#include<iostream>
#include<string.h>
using namespace std;

int main() {
    int size,array_size;
    char temp_arr[100];

    cout << "Enter Number of strings" << endl;
    cin>>size;
    
    char **arr=(char **)malloc(sizeof(char*)*size);

    for(int i=0; i<size; i++)
    {
        cout <<"Enter the size of the string" << i+1 << ": "<<endl; 
        cin >> array_size;
        arr[i]=(char*)malloc(sizeof(char)*array_size);
        cout << "Enter the string" << endl; 
        cin >> temp_arr;
        strncpy(arr[i], temp_arr, array_size);
    }

    for (int i=0; i<size; i++) {
        cout << arr[i] << endl;
    }
    
    for (int i=0; i<size; i++) {
        free(arr[i]);
    }
    free(arr);

}