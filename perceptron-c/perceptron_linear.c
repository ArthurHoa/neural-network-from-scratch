#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int size;
    float* w;
} s_weights;

typedef struct {
    int size;
    int nb_attributes;
    float** X;
    int* y;
    s_weights weights;
} s_dataset;

void loadDataset(s_dataset* dataset);
void printDataset(s_dataset* dataset);
void printWeights(s_weights* weights);
float activation(s_dataset* dataset, int indice);
void update_weights(s_dataset* dataset, float learning_rate);
void trainPerceptron(s_dataset* dataset, float learning_rate, float max_iter);

int main (void)
{  
    // Init dataset with 4 observations and 2 variables
    s_dataset dataset;
    dataset.size = 4;
    dataset.nb_attributes = 2;

    // Load memory and init bias
    loadDataset(&dataset);

    // {1, 1}, {1, 0}, {0, 1}, {1, 1}
    dataset.X[0][1] = 1;
    dataset.X[0][2] = 1;
    dataset.X[1][1] = 1;
    dataset.X[2][2] = 1;

    // 1, 0, 0, 0
    dataset.y[0] = 1;

    // Print the X,y dataset
    printDataset(&dataset);

    // Define a learning rate and maximum iterations
    float learning_rate = 0.05;
    float max_iter = 500; 

    // Fit Model
    trainPerceptron(&dataset, learning_rate, max_iter);

    printf("Weights: ");
    printWeights(&dataset.weights);
    printf("Equation: y = %fx + %f\n", - dataset.weights.w[1] / dataset.weights.w[2], - dataset.weights.w[0] / dataset.weights.w[2]);
    
    return EXIT_SUCCESS;
}

void trainPerceptron(s_dataset* dataset, float learning_rate, float max_iter)
{
    float error = 1;
    int iter = 0;

    while(error != 0 && iter != max_iter)
    {   
        update_weights(dataset, learning_rate);

        error = 0;
        for(int i = 0; i < dataset->size; i++)
            error += (dataset->y[i] - activation(dataset, i)) * (dataset->y[i] - activation(dataset, i));
        error = error / dataset->size;

        iter++;
    }

    if(error < 0.0001)
        printf("Null error\n");
    else
        printf("Non-null error\n");
}

void loadDataset(s_dataset* dataset)
{
    dataset->X = (float**) calloc(dataset->size, sizeof(float*));
    for(int i = 0; i < dataset->size; i++) {
        dataset->X[i] = (float*) calloc(dataset->nb_attributes + 1, sizeof(float));
        
        // Init Bias to 1
        dataset->X[i][0] = 1;
    }

    dataset->y = (int*) calloc(dataset->size, sizeof(int));

    dataset->weights.size = dataset->nb_attributes + 1;
    dataset->weights.w = (float*) calloc(dataset->weights.size, sizeof(float));
}

void printDataset(s_dataset* dataset)
{
    for(int i = 0; i < dataset->size; i++) {
        for(int j = 1; j < dataset->nb_attributes + 1; j++)
            printf("%f ", dataset->X[i][j]);
        printf("\tClass : %d\n", dataset->y[i]);
    }
}

void printWeights(s_weights* weights)
{
    for(int i = 0; i < weights->size; i++)
            printf("%f ", weights->w[i]);
    printf("\n");
}

float activation(s_dataset* dataset, int indice)
{
    float sum = 0;

    for(int i = 0; i < dataset->weights.size; i++) 
        sum += dataset->X[indice][i] * dataset->weights.w[i];

    return sum;
}

// This implementation does not update simultaneously all weights
void update_weights(s_dataset* dataset, float learning_rate)
{
    for(int i = 0; i < dataset->weights.size; i++){
        float buffer = 0;
        for(int j = 0; j < dataset->size; j++){
            buffer += (activation(dataset, j) - dataset->y[j]) * dataset->X[j][i];
        }
        buffer = buffer / dataset->size;
        dataset->weights.w[i] = dataset->weights.w[i] - learning_rate * buffer;
    }
}

