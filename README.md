# Object Detection Using ESP32-CAM

This project is an object detection system that utilizes ESP32-CAM microcontroller and TensorFlow Lite. The system is capable of detecting objects in real-time and classifying them into categories. 

## Getting Started
This project leverages the Random Forest Classifier algorithm to detect objects using an ESP32 microcontroller. The data is collected using a Google Colab code, which is provided in the reference link. Currently, the system is designed to detect only three objects, but it can be extended to support multiple objects with more data. Although the accuracy is average, it can be improved significantly by increasing the amount of data used for training the model. The project is based on the pioneering work of [bharathsudharsan](https://github.com/bharathsudharsan/TinyML-CAM).
### Prerequisites

- ESP32-CAM microcontroller
- TensorFlow Lite
- Python 3.x

### Installation

1. Connect the ESP32-CAM to the computer and open the Arduino IDE.
2. Upload the CameraWebServer sketch and collect the data using Jupyter Notebook
3. Upload the required libraries to the ESP32-CAM.
4. Train the model on a dataset of images using TensorFlow Lite.
5. Compile and upload the code to the ESP32-CAM.[arduino-ESP32-code.ino]
6. Connect the ESP32-CAM to the Jupyter Notebook using a serial connection.
7. Run the Jupyter Notebook.

### Usage

Once the code is uploaded to the ESP32-CAM and the Jupyter Notebook is running, the object detection system can be used to detect and classify objects in real-time. The system can be used in a variety of applications, including security systems, automation, and robotics.

## Contributing

This project is open to contributions from the community. If you have any suggestions or would like to make any improvements to the project, please feel free to submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
