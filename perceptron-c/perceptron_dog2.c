#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int activation(s_dataset* dataset, int indice);
float update_weights(s_dataset* dataset, int indice, float learning_rate);
void trainPerceptron(s_dataset* dataset, float learning_rate, float max_iter);

int main (void)
{  
    // Init dataset with 4 observations and 2 variables
    s_dataset dataset;

    // Load memory and init bias
    loadDataset(&dataset);

    // Define a learning rate and maximum iterations
    float learning_rate = 0.05;
    float max_iter = 500; 

    // Fit Model
    trainPerceptron(&dataset, learning_rate, max_iter);

    printf("Weights: ");
    printWeights(&dataset.weights);
    printf("Equation: y = %fx + %f\n", - dataset.weights.w[1] / dataset.weights.w[0], - dataset.weights.w[2] / dataset.weights.w[0]);
    
    return EXIT_SUCCESS;
}

void trainPerceptron(s_dataset* dataset, float learning_rate, float max_iter)
{
    float error = 1;
    int iter = 0;

    while(error != 0 && iter != max_iter)
    {
        error = 0;
        for(int i = 0; i < dataset->size; i++)
            error += abs(update_weights(dataset, i, learning_rate));

        iter++;
    }

    if(error == 0)
        printf("Separable boundary\n");
    else
        printf("Non-separable boundary\n");
}

void loadDataset(s_dataset* dataset)
{
    dataset->size = 200;
    dataset->nb_attributes = 2;

    FILE *file;
    file = fopen("dataset/X.csv", "r");
    char* line = NULL;
    size_t len = 0;

    dataset->X = (float**) calloc(dataset->size, sizeof(float*));
    for(int i = 0; i < dataset->size; i++) {
        dataset->X[i] = (float*) calloc(dataset->nb_attributes + 1, sizeof(float));
        
        getline(&line, &len, file);

        dataset->X[i][1] = atof(strtok(line, ";"));
        dataset->X[i][2] = atof(strtok(NULL, ";"));

        // Init Bias to 1
        dataset->X[i][0] = 1;
    }

    dataset->y = (int*) calloc(dataset->size, sizeof(int));
    file = fopen("dataset/y_true.csv", "r");
    for(int i = 0; i < dataset->size; i++) {
        getline(&line, &len, file);
        dataset->y[i] = atoi(line);
    }

    dataset->weights.size = dataset->nb_attributes + 1;
    dataset->weights.w = (float*) calloc(dataset->weights.size, sizeof(float));

    fclose(file);
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

int activation(s_dataset* dataset, int indice)
{
    float sum = 0;

    for(int i = 0; i < dataset->weights.size; i++) 
        sum += dataset->X[indice][i] * dataset->weights.w[i];

    if(sum > 0)
        return 1;
    return 0; 
}

float update_weights(s_dataset* dataset, int indice, float learning_rate)
{
    int activate = activation(dataset, indice);
    float diff = dataset->y[indice] - activate;

    if(diff)
        for(int i = 0; i < dataset->weights.size; i++)
            dataset->weights.w[i] = dataset->weights.w[i] + learning_rate * diff * dataset->X[indice][i];
    return dataset->y[indice] - activate;
}

