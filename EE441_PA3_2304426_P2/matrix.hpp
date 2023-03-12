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
        int const hash_func(void);
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

int const Matrix::hash_func(void){
    int i,j,hash_value = N;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            hash_value = (61 * hash_value + matrix[i][j]);
    return ((hash_value) % 65536);
};


/**//**//**//**//**//**//**/

//Matrix declaration ends

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

// HT_Item and HT_Table declarations begin

class HT_Item {
    public :
        // Determinant of key matrix is value
        HT_Item();
        Matrix key;
        long value;
};

/**//**//**//**//**//**//**/

HT_Item::HT_Item(){
    key = Matrix();
};

/**//**//**//**//**//**//**/

class HT_Table {
    public :
        int count;
        HT_Item* Hash_Table[65536] = {nullptr};
        HT_Table();
        bool key_exists(Matrix A);
        long search(Matrix A);
        void insert(Matrix A, long detA);
};

/**//**//**//**//**//**//**/

HT_Table::HT_Table(){
    count = 0;
};

/**//**//**//**//**//**//**/

bool HT_Table::key_exists(Matrix A){

    int hash_value = A.hash_func();
    hash_value = (hash_value+65536) % 65536;

    if(Hash_Table[hash_value] == nullptr)
        return false;

    else if (A == Hash_Table[hash_value]->key )
        return true;

    else{
        int i,search_hash_value;
        for(i=1;i<65536;i++){
            search_hash_value = ((hash_value+i)%65536);
            if(Hash_Table[search_hash_value] == nullptr)
                return false;
            else if (Hash_Table[search_hash_value]->key == A)
                return true;
        }
    }
    return false;
};

/**//**//**//**//**//**//**/

long HT_Table::search(Matrix A){
    int hash_value = A.hash_func();
    hash_value = (hash_value+65536) % 65536;

    if (Hash_Table[hash_value]->key == A)
        return Hash_Table[hash_value]->value;

    else{
        int i,search_hash_value;
        for(i=1;i<65536;i++){
            search_hash_value = ((hash_value+i)%65536);
            if (Hash_Table[search_hash_value]->key == A)
                return Hash_Table[hash_value]->value;
        }
    }
    return 0;
};

/**//**//**//**//**//**//**/

void HT_Table::insert(Matrix A, long detA){
    int i,j,hash_value = A.hash_func();
    HT_Item* new_item = new HT_Item();

    for(i=0; i<A.N;i++)
        for(j=0; j<A.N ; j++)
            new_item->key.matrix[i][j] = A.matrix[i][j];
    new_item->key.N=A.N;
    new_item->value = detA;

    if(Hash_Table[hash_value] == nullptr)
        Hash_Table[hash_value] = new_item;

    //probing
    else{
        int probing_hash_value;
        for(i=1;i<65536;i++){
            probing_hash_value = ((hash_value+i)%65536);
            if (Hash_Table[probing_hash_value] == nullptr){
                Hash_Table[probing_hash_value] = new_item;
                break;
            }
        }
    }

};

/**//**//**//**//**//**//**/

// HT_Item and HT_Table declarations end

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

long determinant(Matrix &M, HT_Table* storage){
    long result = 0;
    // search the storage for the key
    if(storage->key_exists(M)){
//        cout<<"Founded in storage"<<endl;
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
//            cout<<"Calculated and stored"<<endl;


        return result;
    }
};



