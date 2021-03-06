# PCA-cpp-MNIST-dataset

use Eigen library to apply PCA to MNIST dataset in C++.  
dataset: MNIST train set, label removed.  
dataset size: 60,000 * 784.  
After PCA: 60,000 * 154.  
source: https://www.kaggle.com/oddrationale/mnist-in-csv?select=mnist_train.csv. 

(1) read csv as MatrixXd  
(2) PCA   

Result (MNIST)
Execution time in C++: 7.4 seconds.  
Execution time in Python: 12.1 seconds 

### Test the code with larger dataset:
Result (COVID_19)
Run with a larger dataset: COVID_19  
source: https://www.kaggle.com/allen-institute-for-ai/CORD-19-research-challenge?   
cord_19_embeddings_2020-06-09.csv   
Remove the column "ug7v899j" (object type)
data shape: (138793, 768)  

Execution time in C++: 15.1 seconds.  
Execution time in Python: 25.3 seconds 

Update (July 24):
### New jupyter notebook: parallel computing with Cupy library  
Run the code with Google colab.  
Without Cupy: 12.1 seconds    
With Cupy: 0.39 seconds  
