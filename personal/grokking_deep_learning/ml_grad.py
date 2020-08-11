import numpy as np

np.random.seed(1) #Random generator

def relu(x): #if <0 -> 0
    return (x > 0) * x

def relu2deriv(output): #sign of output
    return output > 0

streetlights = np.array([[1, 0, 1],
                        [0, 1, 1],
                        [0, 0, 1],
                        [1, 1, 1]]) #data

walk_vs_stop = np.array([[1, 1, 0, 0]]).T  #data2

hidden_size = 4 #layer 1 - helper
alpha = 0.2 #alpha for neurals

weights_0_1 = 2 * np.random.random((3, hidden_size)) - 1 #random weights in [-1; 1]
weights_1_2 = 2 * np.random.random((hidden_size, 1)) - 1

for i in range(60):
    layer_2_error = 0 #errors are zero by default
    for j in range(len(streetlights)): 
        layer_0 = streetlights[j:j+1] #Elements from j to j+1; step: default = 1
        layer_1 = relu(np.dot(layer_0, weights_0_1)) #scalar multiplication, to make layer 1 from layer 0
        #positions with minus are equal to zero(powered off)
        layer_2 = np.dot(layer_1, weights_1_2) # the same idea, but this layer is the main, it can't be powered off

        layer_2_error += np.sum((layer_2 - walk_vs_stop[j:j+1]) ** 2) #squared mistake to reserve teaching

        layer_2_delta = walk_vs_stop[j:j+1] - layer_2
        layer_1_delta = layer_2_delta.dot(weights_1_2.T)*relu2deriv(layer_1)

        weights_1_2 += alpha * layer_1.T.dot(layer_2_delta)
        weights_0_1 += alpha * layer_0.T.dot(layer_1_delta)
    if(i % 10 == 9):
        print("Iteration: " + str(i) + " Error:" + str(layer_2_error))
