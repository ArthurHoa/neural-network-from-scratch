# Neural network from scratch in Python and C

This is an implementation of the perceptron from scratch in C (and Python) and a neural network in Python, no library other than the standar C and common Python libs are used.
For example frameworks like Tensorflow or PyTorch are not used at all.

## The perceptron

The perceptron is an artiicial neuron, it is the smallest neural network model.  
It works for two-class linearly separable problems.  

<img href="https://commons.wikimedia.org/wiki/File:Perceptron_moj.png" src="perceptron-c/extra/Perceptron.png" width="400">

The multi-layer perceptron (aka. neural network) allows to bypass these two last hypothesis.

### AND Logic gate

We are trying to compute a logic AND door using a perceptron with the following dataset:  

&nbsp;| **TRUE** | **FALSE**
:--:|:--:|:--:
**TRUE**| TRUE | FALSE
**FALSE** | FALSE | FALSE

### Activation functions

Linear | ReLu | Heavyside | Sigmoid
:--:|:--:|:--:|:--:
<img src="perceptron-c/extra/linear.png" width="200"> | <img src="perceptron-c/extra/relu.png" width="200"> | <img src="perceptron-c/extra/heavyside.png" width="200"> | <img src="perceptron-c/extra/sigmoid.png" width="200">  

### Results

For computation, let's take:  

FALSE = 0 -> Represented in Blue  
TRUE = 1 -> represented in Red  

Linear | ReLu | Heavyside | Sigmoid
:--:|:--:|:--:|:--:
<img src="perceptron-c/extra/and_linear.png" width="200"> | <img src="perceptron-c/extra/and_relu.png" width="200"> | <img src="perceptron-c/extra/and_heavyside.png" width="200"> | <img src="perceptron-c/extra/and_sigmoid.png" width="200">  

### DOG-2 dataset (linear boundary)

Perceptron can be used for more complex datasets, such as the binary class dataset Dog-2.  
On the following picture, Brittany breed is in blue and Beagle breed is in red, the optimized perceptron boundary is also drawn:  

<img src="perceptron-c/extra/dog_2_heavyside.png" width="400">

## The Neural Network

The artificial neural network is a collection of connected artificial neurons. It is used in machine learning for both classification and regression tasks.

The implementation offers the possibility to add or remove hidden layers with any number of neurons. For the examples, the following architecture is used with a sigmoid activation fuction:


<img src="neural-network/extra/nnarchi.png" width="300">

### The Breast Cancer dataset

First, the neural network is trained on the Breast Cancer dataset. It is a classic and very easy binary classification dataset. Here are the following accuracies for the model, along with its errors.

<img src="neural-network/extra/breast-cancer.png" width="400">

### The MNIST Dataset

To perform digits visual recognition, I trained the neural network on the MNIST dataset. 

MNIST database is composed of handwritten digits, with a training set of 60,000 examples, and a test set of 10,000 examples. For the purpose of the experiment, and to run faster on my own computer I have restricted the problem to the first two digits 0 and 1. Also note that the proposed neural network is not a convolutional neural network.  
Fin the dataset [here](http://yann.lecun.com/exdb/mnist/).

<img src="neural-network/extra/MnistExamples.png" width="200">

Here are the accuracies for the model at each epoch, performing well at the end. Model errors are also represented:

<img src="neural-network/extra/mnist.png" width="400">
