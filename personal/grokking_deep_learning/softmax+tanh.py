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

#activations
def tanh(x):
    return np.tanh(x)
def tanh2deriv(output):
    return 1 - (output ** 2)
def softmax(x):
    temp = np.exp(x)
    return temp/np.sum(temp, axis = 1, keepdims=True)

#stohastic method
batch_size = 100

alpha, iterations, hidden_size, pixels_per_image, num_labels = (2, 300, 100, 784, 10)

weights_0_1 = 0.02 * np.random.random((pixels_per_image, hidden_size)) - 0.01 
weights_1_2 = 0.2 * np.random.random((hidden_size, num_labels)) - 0.1
#structure of neural network:
#layer_0 - matrix 100x784
#weights_0_1 - matrix 784x40
#layer_1 - matrix 100x100(100 - maybe paths of common numbers)
#weights_1_2 - matrix 100x10
#layer_2 - matrix 100x10 - output

for j in range(iterations):
    correct_cnt = 0

    for i in range(int(len(images)/batch_size)):
        batch_start = i*batch_size
        batch_end = batch_start + batch_size

        layer_0 = images[batch_start:batch_end]    
        layer_1 = tanh(np.dot(layer_0, weights_0_1))
        dropout_mask = np.random.randint(2, size = layer_1.shape)
        layer_1 *= dropout_mask * 2 
        layer_2 = softmax(np.dot(layer_1, weights_1_2))
        
        for k in range(batch_size):
            correct_cnt += int(np.argmax(layer_2[k:k+1]) == np.argmax(labels[batch_start+k:batch_start+k+1]))

        layer_2_delta = (labels[batch_start:batch_end] - layer_2)/(batch_size*layer_2.shape[0])
        layer_1_delta = layer_2_delta.dot(weights_1_2.T) * tanh2deriv(layer_1)
        
        layer_1_delta *= dropout_mask

        weights_1_2 += alpha * layer_1.T.dot(layer_2_delta)
        weights_0_1 += alpha * layer_0.T.dot(layer_1_delta)
    
    test_correct_cnt = 0

    for i in range(len(test_images)):
        layer_0 = test_images[i:i+1]
        layer_1 = tanh(np.dot(layer_0, weights_0_1))
        layer_2 = np.dot(layer_1, weights_1_2)         
        test_correct_cnt += int(np.argmax(test_labels[i:i+1]) == np.argmax(layer_2))
   
    if(j%10 == 0):
        sys.stdout.write("\n" + "I:"+str(j) + " Test-correct:" + str(test_correct_cnt/float(len(test_images))) + " Correct:" + str(correct_cnt/float(len(images))))

