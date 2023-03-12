//
//  main.cpp
//  pa3
//
//  Created by Bahadır on 3.01.2023.
//
#include "matrix.hpp"
int main() {

    long a;
    Matrix j;
    j = Matrix(3);
    j.set_element(5, 1, 0);
    j.set_element(2, 0, 1);
    j.set_element(6, 2, 0);
    j.set_element(7, 0, 2);

    HT_Table Hash_Table = HT_Table();

    a = determinant(j, &Hash_Table);
    cout<<a<<endl;

    a = determinant(j, &Hash_Table);
    cout<<a<<endl;

    return 0;
}
// insert error in BST
