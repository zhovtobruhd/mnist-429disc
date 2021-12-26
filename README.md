# Handwritten digits recognition using STM32F429DISCOVERY

This educational project is directed to learn how to create Convolutional Neural Networks using Keras, train and test the model and deploy it on STM32 microcontroller

Although the training, testing and validation stages have been proceeded correctly, the deployed model lacks accuracy due to rescalings and "pen" pressure that cannot be taken into account because of touchscreen, so the dataset used for training mismatches real-time conditons on this development board.

Demonstration:
https://www.youtube.com/watch?v=j8C7RMajujY

References:
https://keras.io/examples/vision/mnist_convnet/
