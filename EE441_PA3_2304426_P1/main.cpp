//
//  main.cpp
//  pa3
//
//  Created by Bahadır on 3.01.2023.
//
#include "matrix.hpp"
int main() {
    bool ans,ans1;
    long a;
    Matrix m;
    Matrix j;
    j = Matrix(3);
    j.set_element(5, 1, 0);
    j.set_element(2, 0, 1);
    j.set_element(6, 2, 0);
    j.set_element(7, 0, 2);
    j.set_element(8, 1, 1);
    m = Matrix(4);
    ans = m==j;
    cout<< ans <<endl;
    ans1 = m<j;
    cout<< ans1 <<endl;
    BST_Node storage;
    storage.left=nullptr;
    a = determinant(j, &storage);
    cout<<a<<endl;

    a = determinant(j, &storage);
    cout<<a<<endl;

    return 0;
}
// insert error in BST
