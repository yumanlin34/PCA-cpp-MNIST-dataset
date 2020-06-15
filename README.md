# PCA-cpp-MNIST-dataset

use Eigen library to apply PCA to MNIST dataset in C++.  
dataset: MNIST train set, label removed.  
dataset size: 60,000 * 784.  
After PCA: 60,000 * 154.  
source: https://www.kaggle.com/oddrationale/mnist-in-csv?select=mnist_train.csv. 

(1) read csv as MatrixXd  
(2) PCA   

Execution time in C++: 8.8 seconds.  
Execution time in Python: 14.8 seconds   

