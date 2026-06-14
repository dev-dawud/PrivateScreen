# Private Screen

This project protects your screen by using people detection to count how many people are within the webcam's range
and then locks the screen as soon as there is more than one person.

## Requirements
- C++ 13 or later
- OpenCV 5.0.0 or later
- A webcam

## Installation
Use ``git clone`` to download the project. Make sure OpenCV is properly installed and linked in your IDE.

```bash 
git clone https://github.com/dev-dawud/PrivateScreen.git
```
Before you run and test the project, make sure the compiler in Visual Studio is set to **“Release (x64)”** to ensure smooth real time performance of the program. 
If dozens error messages suddenly appear when you switch to **“Release (x64),”** the release profile is missing the OpenCV paths.

1. Copy the include and library directories from your Debug project properties to the Release properties.
2. Under Linker -> Input -> Additional Dependencies, you must remove the “d” at the end of the library file. For example, use ``opencv_world500.lib`` instead of ``opencv_world500d.lib``

(Make sure to have a suitable model file for DNN face detection in the project directory like in me ``yolov8n.onnx``)

## Usage
1. Compile and run the program.
2. The program will access your webcam and display the video feed in a window. (automatic)
3. The program will detect persons in the video feed and counts the number of detected persons. (automatic)
4. If more than one person is detected, the program will lock the screen to protect your privacy. (automatic)
5. To exit the program, press the 'esc' key.

## Contributing
Contributions are welcome! (But please follow the existing code style and write me an E-mail to david_wahab@icloud.com for permission)
If you have any suggestions or improvements, please feel free to submit a pull request.

## Acknowledgments
- Thanks to Gemini for the idea and for helping with debugging (lines 24 and 56 were created using Gemini)
- DeepL for helping with the translation of the README files and git commits into English
- OpenCv for providing the tools and libraries for computer vision tasks

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


