import sys, numpy as np
from keras.datasets import mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data()

images = x_train[0:1000].reshape(1000, 28*28) / 255
labels = y_train[0:1000]
#images = input; labels = output

one_hot_labels = np.zeros((len(labels), 10))

for i, l in enumerate(labels):
    one_hot_labels[i][l] = 1
labels = one_hot_labels #Correct answers into matrix with 1 in correct positions

test_images = x_test.reshape(len(x_test), 28*28) / 255
test_labels = np.zeros((len(y_test), 10))
for i, l in enumerate(y_test):
    test_labels[i][l] = 1

np.random.seed(1)
def relu(x):
    return (x>0) * x

def relu2deriv(output):
    return output>0

alpha, iterations, hidden_size, pixels_per_image, num_labels = (0.005, 300, 100, 784, 10)

weights_0_1 = 0.2 * np.random.random((pixels_per_image, hidden_size)) - 0.1 #matrix 784x40(40 - len of helpaer-layer for correct correlation)
weights_1_2 = 0.2 * np.random.random((hidden_size, num_labels)) - 0.1 #matrix 40x10
#structure of neural network:
#layer_0 - vector 784
#weights_0_1 - matrix 784x40
#layer_1 - vector 40(40 - maybe paths of common numbers)
#weights_1_2 - matrix 40x10
#layer_2 - vector 10 - output

for j in range(iterations):
    error = 0.0
    correct_cnt = 0

    for i in range(len(images)):
        layer_0 = images[i:i+1]
        
        layer_1 = relu(np.dot(layer_0, weights_0_1))
        
        dropout_mask = np.random.randint(2, size = layer_1.shape) #mask for regulization - random weights are powered off

        layer_1 *= dropout_mask * 2 #in dropout_mask only 50% are 0, others are 1, for correct teaching layer_1 is multiplicated on 2
        
        layer_2 = np.dot(layer_1, weights_1_2)
        error += np.sum((labels[i:i+1] - layer_2) ** 2)
        correct_cnt += int(np.argmax(layer_2) == np.argmax(labels[i:i+1]))

        layer_2_delta = labels[i:i+1] - layer_2
        layer_1_delta = layer_2_delta.dot(weights_1_2.T) * relu2deriv(layer_1)
        
        layer_1_delta *= dropout_mask #the same idea

        weights_1_2 += alpha * layer_1.T.dot(layer_2_delta)
        weights_0_1 += alpha * layer_0.T.dot(layer_1_delta)
    
    if(j%10 == 0): #testing network in new datasets
        test_error = 0.0
        test_correct_cnt = 0

        for i in range(len(test_images)):
            layer_0 = test_images[i:i+1]
            layer_1 = relu(np.dot(layer_0, weights_0_1))
            #dropout_mask = np.random.randint(2, size = layer_1.shape)
            #layer_1 *= dropout_mask * 2
            
            layer_2 = np.dot(layer_1, weights_1_2)
            
            #layer_2_delta = test_labels[i:i+1] - layer_2
            #layer_1_delta = layer_2_delta.dot(weights_1_2.T) * relu2deriv(layer_1)
            #layer_1_delta *= dropout_mask


            test_error += np.sum((test_labels[i:i+1] - layer_2) ** 2)
            test_correct_cnt += int(np.argmax(test_labels[i:i+1]) == np.argmax(layer_2))
           
            #weights_1_2 += alpha * layer_1.T.dot(layer_2_delta)
            #weights_0_1 += alpha * layer_0.T.dot(layer_1_delta)
    
        sys.stdout.write("\n" + "I:"+str(j) + " Test - Error:" + str(test_error/float(len(test_images)))[0:5] + " Test - Correct:" + str(test_correct_cnt/float(len(test_images))) + " Error:" + str(error/float(len(images)))[0:5] + " Correct:" + str(correct_cnt/float(len(images))))

