//
//  main.cpp
//  first_cpp
//
//  Created by Yuman Lin on 2020/6/12.
//  Copyright © 2020 Yuman Lin. All rights reserved.


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <eigen3/Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::RowVectorXd;
using Eigen::SelfAdjointEigenSolver;
using std::cout;
using std::endl;
using namespace Eigen;
using namespace std::chrono;

// declaration

// read csv to MatrixXd
template<typename M>
M load_csv(const std::string& path);

// PCA
void featurenormalize(MatrixXd& X);
void computeCov(MatrixXd& X, MatrixXd& C);
void computeEig(MatrixXd& C, MatrixXd& vec, MatrixXd& val);
void computeEig(MatrixXd& C, MatrixXd& vec, MatrixXd& val);
int computeDim(MatrixXd& val);

int main()
{
    MatrixXd vec, val;
    MatrixXd Cov;
    MatrixXd MNIST = load_csv<MatrixXd>("/Users/yumanlin/Desktop/MNIST/mnist_train_without_label.csv");
    
    cout << "load data finished" << endl;
    
    auto start = high_resolution_clock::now();
    featurenormalize(MNIST);
    // cout << "normalization finished" << endl;

    computeCov(MNIST, Cov);
    // cout << "cov finished" << endl;
    
    computeEig(Cov, vec, val);
    // cout << "eigen finished" << endl;

    int dim = computeDim(val);
    MatrixXd res = MNIST * vec.rightCols(dim);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;


    cout << "The size of reduced dateset is " << res.rows() << "x" << res.cols() << " after pca algorithm." << endl;
    return 0;
}


// function implementation
void featurenormalize(MatrixXd& X)
{
    //mean of each col
    MatrixXd meanval = X.colwise().mean();
    RowVectorXd meanvecRow = meanval;
    //mean = 0
    X.rowwise() -= meanvecRow;
}
void computeCov(MatrixXd& X, MatrixXd& C)
{
    
    C = X.transpose() * X;
    C = C.array() / X.rows() - 1;
}
void computeEig(MatrixXd& C, MatrixXd& vec, MatrixXd& val)
{
    //eigenvalue and eigenvector, in order
    SelfAdjointEigenSolver<MatrixXd> eig(C);

    vec = eig.eigenvectors();
    val = eig.eigenvalues();
}
int computeDim(MatrixXd& val)
{
    int dim;
    double sum = 0;
    for (int i = val.rows() - 1; i >= 0; --i)
    {
        sum += val(i, 0);
        dim = i;

        if (sum / val.sum() >= 0.95)
            break;
    }
    return val.rows() - dim;
}


template<typename M>
M load_csv(const std::string& path)
{
    std::ifstream indata;
    indata.open(path);
    std::string line;
    std::vector<double> values;
    int rows = 0;
    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }
    
    return Map<const Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, RowMajor>>(values.data(), rows, values.size() / rows);
}

