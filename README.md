#  Invisible Ink & Animated Frame Encoder
## Name: Shifat Jahan Shifa
## Roll No: 1301
## Supervisor: Dr. B M Mainul Hossain  
## Project Description:

“Invisible Ink & Animated Frame Encoder” is my project for SPL-01. In this project, I've mainly tried to manipulate images. My project is of two parts. First part “invisible ink” is identical to “Steganography”. The second part “Animated Frame Encoder” is identical to “GIF Encoder”.   

For image steganography, I used 24 bit BMP Image as cover media and text or message as hidden information. Any 24-bit BMP image with compression value "0" and colorplanes with "1" can be used as cover media. Any message with proper size, can be hidden into image. Worth to mention, I used LSB technique for Steganography. 

For GIF Encoder, user can provide a name and GIF file of that name will be created. For creating the GIF file, I used 8 sets of pixel values which will be used in this program randomly. Each time running the program a new GIF will be created with the name user provides. To maintain lossless compression in GIF file, implemented "LZW" algorithm using "Trie" data structure . 


## Lessons Learned


```bash
    * BMP image structure
    * Image read and write
    * GIF structure
    * LSB technique
    * LZW algorithm
    * Trie data structure
```
    
## Language used: C++

## Demo

https://drive.google.com/file/d/1i2_-HkA89l3lOoSxmGpVuHJRbLe4sCLU/view?usp=share_link
## Installation

It is easy to install my project
```bash
  * Download all .cpp file from each folder
  * Create a project in your preferable IDE
  * Include every Downloaded file into the project 
  * Also download .bin and .bmp file to test the project output
```
    
## Running Tests

```bash
  * just build and run the project on your IDE
  * to provide input, make sure the file is included in the same folder as the project 
  * to open images automatically using Windows Photos, change the path of the file in the module "openingImage.cpp".
  * to open GIFs automatically using Windows Photos, change the path of the file in the module "creatingGif.cpp".
```


## Acknowledgements

 - https://ieeexplore.ieee.org/document/9335027,  ieeexplore.iee.org/document, 27 February, 2023
 - https://en.wikipedia.org/wiki/Steganography, Wikipedia.org/ wiki/Steganography, 30 March, 2023
 - https://en.wikipedia.org/wiki/BMP_file_format, Wikipedia.org/wiki/BMP_file_format, 5 January, 2023
 - https://www.fileformat.info/format/gif/egff.htm, fileformat.info/format/gif/egff.htm, 15 March, 2023
 - https://en.wikipedia.org/wiki/Trie, Wikipedia.org/wiki/Trie, 23 March, 2023
 - https://en.wikipedia.org/wiki/GIF, Wikipedia.org/wiki/GIF, 31 March, 2023
 - https://www.scaler.com/topics/lzw-compression/, scaler.com/ topics/lzw-compression/, 2 April, 2023
 - https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch, Wikipedia.org/wiki/Lempel, 5 April, 2023



## Authors

- [@ShifatJahanShifa](https://github.com/ShifatJahanShifa)



