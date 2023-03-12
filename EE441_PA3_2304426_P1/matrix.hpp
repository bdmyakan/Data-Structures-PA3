//
//  matrix.h
//  pa3
//
//  Created by Bahadır on 3.01.2023.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#define MAXSIZE 20;
using namespace std;

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

//Matrix declaration begins

class Matrix{
    private:

    public:
        int matrix[20][20];
        int N;
        Matrix();       //default constructor 0x0
        Matrix(int size);  // constructor with size N Identity matrix
        void set_element(int data, int row, int column);
        int const get_element(int row, int column);
        bool operator == (Matrix &second);
        bool operator < (Matrix &second);
};

/**//**//**//**//**//**//**/

Matrix::Matrix(){
    N = 0;
    for(int i=0 ; i<20 ; i++){
        for(int j=0 ; j<20 ; j++){
            matrix[i][j] = 0;
        }
    }
};

/**//**//**//**//**//**//**/

Matrix::Matrix(int size){
    N = size;
    for(int i=0 ; i<20 ; i++){
        for(int j=0 ; j<20 ; j++){
            if(i<N && j<N){
                if(i==j)
                    matrix[i][j]=1;
                else
                    matrix[i][j]=0;
            }
            else
                matrix[i][j] = 0;
        }
    }
};

/**//**//**//**//**//**//**/

void Matrix::set_element(int data, int row, int column){
    //if row and column number is given greater than the size
    if(row >= N || column >= N){
        cerr<<"Not appropriate"<<endl;
        exit(1);
    }
    matrix[row][column]=data;
};

/**//**//**//**//**//**//**/

int const Matrix::get_element(int row, int column){
    //if row and column number is given greater than the size
    if(row >= N || column >= N){
        cerr<<"Not appropriate"<<endl;
        exit(1);
    }
    return matrix[row][column];
};

/**//**//**//**//**//**//**/

bool Matrix::operator== (Matrix &second){
    if(N == second.N){
        for(int i = 0; i<N ; i++){
            for(int j=0; j<N; j++){
                if(matrix[i][j] != second.matrix[i][j])
                    return false;
            }
        }
    }
    else
        return false;

    return true;
};

/**//**//**//**//**//**//**/

bool Matrix::operator < (Matrix &second){
    if(N<second.N)
        return true;
    else if(N == second.N){
        for(int i = 0; i<N ; i++){
            for(int j=0; j<N; j++){
                if(matrix[i][j] < second.matrix[i][j])
                    return true;
            }
        }
    }

    return false;
};


/**//**//**//**//**//**//**/

//Matrix declaration ends

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

// BST_Node declaration begins

class BST_Node {
    public :
        BST_Node();
        BST_Node* left;
        BST_Node* right;
        // Determinant of key matrix is value
        Matrix key;
        long value;
        bool key_exists(Matrix A);
        long search(Matrix A);
        void insert(Matrix A, long detA);
};

/**//**//**//**//**//**//**/

BST_Node::BST_Node(){
    left = nullptr;
    right = nullptr;
    key = Matrix();
}

bool BST_Node::key_exists(Matrix A){
    bool ans=false;
    if(A==key){
        ans = true;
    }
    else if(A<key){
        if(left != nullptr)
            ans = left->key_exists(A);
    }
    else if(key<A){
        if(right != nullptr)
            ans = right->key_exists(A);
    }
    return ans;
};

/**//**//**//**//**//**//**/

long BST_Node::search(Matrix A){
    long ans=0;
    if(A==key){
        ans = value;
    }
    else if(A<key){
        if(left != nullptr)
            ans = left->search(A);
    }
    else if(key<A){
        if(right != nullptr)
            ans = right->search(A);
    }
    return ans;

/*
 // Checking if the key exists in storage
    if(key_exists(A)){
        if(A==key){
            ans = value;
        }
        else if(A<key){
            ans = left->search(A);
        }
        else if(key<A){
            ans = right->search(A);
        }
        return ans;
    }
    else{
        cerr<<"No such Matrix in storage"<<endl;
        exit(2);
    }
 */
};

/**//**//**//**//**//**//**/

void BST_Node::insert(Matrix A,long detA){
    Matrix m = Matrix();
    int i,j;
    if(left == nullptr && right == nullptr && key == m ){
        for(i=0; i<A.N;i++)
            for(j=0; j<A.N ; j++)
                key.matrix[i][j] = A.matrix[i][j];
        key.N=A.N;
        value = detA;
        i=0;
    }
    else if(A<key){
        if(left == nullptr){
            BST_Node *new_node = new BST_Node();
            for(i=0; i<A.N;i++)
                for(j=0; j<A.N ; j++)
                    new_node->key.matrix[i][j] = A.matrix[i][j];
            new_node->key.N=A.N;
            new_node->value = detA;
            left = new_node;
        }
        else
            left->insert(A,detA);
    }
    else if(A==key){
        value = detA;
    }
    else{

        if(right == nullptr){
            BST_Node *new_node = new BST_Node();
            for(i=0; i<A.N;i++)
                for(j=0; j<A.N ; j++)
                    new_node->key.matrix[i][j] = A.matrix[i][j];
            new_node->key.N=A.N;
            new_node->value = detA;
            right = new_node;
        }
        else
            right->insert(A,detA);
    }

};

/**//**//**//**//**//**//**/

// BTS_Node declaration ends

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

//Determinant Function declaration

/*
function determinant of Matrix M
    if M exists in storage
        return result corresponding to M from storage
    else
        calculate result recursively using cofactor method store (M, result) in storage
        return result
*/

long determinant(Matrix &M, BST_Node* storage){
    long result = 0;
    // search the storage for the key
    if(storage->key_exists(M)){
        cout<<"Founded in storage"<<endl;
        result = storage->search(M);
        return result;
    }
    // if the matrix is not in the storage
    else{
        // calculate result recursively using cofactor method
        if(M.N == 1){
            result = M.matrix[0][0];
        }
        else if(M.N == 2){
            result = M.matrix[0][0] * M.matrix[1][1] - M.matrix[1][0] * M.matrix[0][1];
        }
        else{
            int i,j,k,icofactor,jcofactor;
            for(k=0;k<M.N;k++){
                Matrix cofactor;
                cofactor.N = M.N-1;
                icofactor = 0;
                for(i=1; i<M.N; i++){
                    jcofactor = 0;
                    for(j=0;j<M.N;j++){
                        if(j == k) continue;
                        cofactor.matrix[icofactor][jcofactor] = M.matrix[i][j];
                        jcofactor++;
                    }
                    icofactor++;
                }
                result = result + pow(-1,k)*M.matrix[0][k]*determinant(cofactor, storage);
            }
        }
        // store (M,result) and return
        storage->insert(M, result);
        cout<<"Calculated and stored"<<endl;
        return result;
    }
};



