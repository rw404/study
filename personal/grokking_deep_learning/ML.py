import numpy as np

weight = 0.5
goal_pred = 0.8
inp = 2
alpha = 0.1
pred = 0

for i in range(55):
    pred = inp*weight
    error = (pred - goal_pred) ** 2
    delta = pred - goal_pred
    weight_delta = delta * inp
    weight = weight - (alpha * weight_delta)

    print("Iteration: " + str(i) + " Error:" + str(error) + " Prediction:" + str(pred))
