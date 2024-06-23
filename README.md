# ChromaMatrix AI

## Project Overview
ChromaMatrix AI is an engaging web application that uses artificial intelligence to interpret images from a webcam. It utilizes `ml5.js` for image classification and controls an LED matrix via Bluetooth based on the video feed analysis. This interactive project combines web development, machine learning, and hardware integration to create a dynamic visual experience.

## Features
- **Real-time Image Classification**: Uses a pre-trained model to classify images from a webcam in real time.
- **LED Matrix Control**: Translates classification results into commands to control an LED matrix, creating visual feedback based on the input from the webcam.
- **Bluetooth Connectivity**: Allows seamless connection and communication with physical computing devices over Bluetooth.
- **Responsive Web Design**: The application is built to be used on various devices, ensuring a wide accessibility.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- A computer with a webcam
- A Controller with Bluetooth capability (ESP32/Arduino Nano 33)
- Modern web browser that supports JavaScript and HTML5

### Installation
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/ChromaMatrix-AI.git
   ```
2. Navigate to the project directory:
   ```
   cd ChromaMatrix-AI
   ```
3. Open the `index.html` file in a web browser to start the application.

## Usage
1. Click the "Connect" button to pair with a compatible Bluetooth-enabled LED matrix.
2. The webcam will automatically start capturing video.
3. The AI will classify the images, and the results will control the patterns displayed on the LED matrix.

## Contributing
Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Contact
Random Stuff We Make - randomstuffwemake@gmail.com
www.youtube.com/@randomstuffwemake

## Acknowledgments
- [p5.js](https://p5js.org/)
- [ml5.js](https://ml5js.org/)
- Thanks to everyone whose code was used
