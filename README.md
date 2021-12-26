# Handwritten digits recognition using STM32F429DISCOVERY

This educational project is directed to create Convolutional Neural Network using Keras, train the model and deploy it on the STM32 microcontroller

Although the training, testing and validation stages have been proceeded correctly, the deployed model still lacks accuracy due to rescaling and "pen" pressure that cannot be taken into account because of the limited touchscreen capabilities, so the dataset used for training mismatches real-time conditions on the development board.

Demonstration:
https://www.youtube.com/watch?v=j8C7RMajujY

References:
https://keras.io/examples/vision/mnist_convnet/
