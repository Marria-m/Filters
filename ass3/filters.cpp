#include "Image_Class.h"
using namespace std;


void saving(Image& img){
    // Function to save the edited image with user-defined filename
    string file_name;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png : ";

    cin >> file_name;
    img.saveImage(file_name);  // Save the edited image
}


// Grayscale Filter
void GrayScale(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0; // Initialization of the average

            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
            }

            avg = avg / 3; // Get average
            for (int k = 0; k < 3; ++k) {
                // Set all channels to the average value
                img(i, j, 0) = avg;
                img(i, j, 1) = avg;
                img(i, j, 2) = avg;
            }
        }
    }
    saving(img);
}


void black_white(Image& img){
    int gray ;
    for(int i = 0 ; i < img.width ; i++){
        for(int j = 0 ; j < img.height ; j++){
            // 3 as 0 -> Red , 1 -> Green , 2 -> Blue
            gray = (img(i , j , 0) + img(i , j , 1) + img(i , j , 2))/3 ; // convert to gray
            for(int k = 0 ; k < 3 ; k++){
                if(gray < 150){
                    img(i ,j , k) = 40 ;// 0 to be white
                }
                else if(gray > 150)
                    img(i ,j , k) = 240 ;// 255 to be black
            }
        }
    }
    saving(img);
}


void deg90(Image& img, Image& new_img){
    for (int i = 0; i < img.height - 1; ++i){
        for (int j = 0; j < img.width - 1; ++j){
            for (int k = 0; k < 3; ++k){
                // Swap pixel data to perform 90 degree counter-clockwise rotation
                swap(new_img(i, j, k), img(j, i, k));
            }
        }
    }
    for (int t = 0; t < new_img.height - 1; ++t){
        int l = 0;
        int r = new_img.width - 1;
        while (l < r){
            // Swap pixel data to perform horizontal flip
            swap(new_img(l, t, 0), new_img(r, t, 0));
            swap(new_img(l, t, 1), new_img(r, t, 1));
            swap(new_img(l, t, 2), new_img(r, t, 2));
            l++;
            r--;
        }
    }
}


// Function to lighten the image
void lightenImage(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Adjust intensity of each channel
            for (int k = 0; k < 3; ++k) {
                int brightness = img(i, j, k);
                brightness *= 1.5; // Increase brightness by 50%
                if (brightness > 255) {
                    brightness = 255; // Making sure that intensity isn't greater than the maximum value
                }
                img(i, j, k) = brightness;
            }
        }
    }
    saving(img);
}


// Function to darken the image
void darkenImage(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Adjust intensity of each channel
            for (int k = 0; k < 3; ++k) {
                int darkness = img(i, j, k);
                darkness -= 127; // Decrease brightness by 50 units
                if (darkness < 0) {
                    darkness = 0; // Ensure intensity doesn't go below minimum value
                }
                img(i, j, k) = darkness; //// Making sure that intensity isn't smaller than the minimum value
            }
        }
    }
    
    saving(img);
}


int main(){

    while(true){
        // let user enter the image file name
        string file_name;
        cout << "plz enter the name of the image: \n";
        cin >> file_name;

        // Read the image and store it to 'img'
        Image img(file_name);

        // Create a new image 'new_img' that the height of 'img' is the width of 'new_img' and width of 'img' is the height of 'new_img'
        Image new_img(img.height, img.width);

        // Fill the 'new_img' with black pixels
        for (int i = 0; i < new_img.width; i++) {
            for (int j = 0; j < new_img.height; j++){
                for (int k = 0; k < 3; k++){
                    new_img(i, j, k) = 0;
                }
            }
        }

        string choice, rotate;

        // Display a list of the supported operations to the user
        cout << "choose what u wanna apply on the Picture\n1)Grayscale\n2)Black and White\n3)Invert Image\n4)Flip Image\n5)Rotate Image\n6)Darken Image\n7)Lighten Image\n8)Exit ^-^\n";
        
        // let user enter their choice
        cin >> choice;

        if (choice == "1"){
            GrayScale(img);  // Call grayscale function
        }
        else if (choice == "2"){
            black_white(img);  // Call black and white conversion function
        }
        else if (choice == "3"){
            // invert color channels
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    // subtract the colour from 255 to get the complement of the colour
                    img(i, j, 0) = 255 - img(i, j, 0);
                    img(i, j, 1) = 255 - img(i, j, 1);
                    img(i, j, 2) = 255 - img(i, j, 2);

                }
            }
            saving(img);
        }

        else if(choice == "4"){
            // allow user to choose horizontal or vertical flip
            cout << "Flip the image...\n1)Vertical\n2)Horizontal\n";
            cin >> rotate;
            if (rotate == "1"){
                // Flip vertically
                for (int t = 0; t < img.width - 1; ++t){  // loop on image width to flip each colomn
                    // initialize 2 variables 'top' is the top of the image in one colomn and 'bot' is the last pixel in one colomn
                    int top = 0;
                    int bot = img.height - 1;
                    while (top < bot){  // stop if top = bot
                        swap(img(t, top, 0), img(t, bot, 0));
                        swap(img(t, top, 1), img(t, bot, 1));
                        swap(img(t, top, 2), img(t, bot, 2));
                        top++;
                        bot--;
                    }
                }
                saving(img);
            }
            else if (rotate == "2"){
                // flip image horizontally
                for (int t = 0; t < img.height - 1; ++t){  // loop on image hight to flip each row
                    // initialize 2 variables 'l' is the left pixel of the image in one row and 'r' is the right pixel in one row
                    int l = 0;
                    int r = img.width - 1;
                    while (l < r){
                        swap(img(l, t, 0), img(r, t, 0));
                        swap(img(l, t, 1), img(r, t, 1));
                        swap(img(l, t, 2), img(r, t, 2));
                        l++;    
                        r--;
                    }
                }
                saving(img);
            }
            else {
                cout << "wrong! please enter a valid choice\n";
            }
        }
        
        else if (choice == "5"){
            cout << "rotate the image clockwise by..\n1)90 degree\n2)180 degree\n3)270 degree\n";

            // let the user choose the degree
            cin >> rotate;
        
            if (rotate == "1"){
                // rotate image by 90 degrees
                deg90(img, new_img);  // call deg90 function
                saving(new_img);
            }
                
            else if (rotate == "2"){
                // Rotate 180 degrees
                // Flip the original image vertically and then horizontally
                for (int t = 0; t < img.width - 1; ++t){  // vertically
                    int top = 0;
                    int bot = img.height - 1;
                    while (top < bot){
                        swap(img(t, top, 0), img(t, bot, 0));
                        swap(img(t, top, 1), img(t, bot, 1));
                        swap(img(t, top, 2), img(t, bot, 2));
                        top++;
                        bot--;
                    }
                }
                
                for (int t = 0; t < img.height - 1; ++t){  // horizontally
                    int l = 0;
                    int r = img.width - 1;
                    while (l < r){
                        swap(img(l, t, 0), img(r, t, 0));
                        swap(img(l, t, 1), img(r, t, 1));
                        swap(img(l, t, 2), img(r, t, 2));
                        l++;
                        r--;
                    }
                }
                saving(img);
            }
                
            else if (rotate == "3"){
                // rotate image by 270 degrees
                
                // rotate the original image 90 degree
                deg90(img, new_img);

                // flip the new image after rotating vertically and horizontally
                for (int t = 0; t < img.width - 1; ++t){  // vertically
                    int top = 0;
                    int bot = img.height - 1;
                    while (top < bot){
                        swap(img(t, top, 0), img(t, bot, 0));
                        swap(img(t, top, 1), img(t, bot, 1));
                        swap(img(t, top, 2), img(t, bot, 2));
                        top++;
                        bot--;
                    }
                }
                
                for (int t = 0; t < img.height - 1; ++t){  // horizontally
                    int l = 0;
                    int r = img.width - 1;
                    while (l < r){
                        swap(img(l, t, 0), img(r, t, 0));
                        swap(img(l, t, 1), img(r, t, 1));
                        swap(img(l, t, 2), img(r, t, 2));
                        l++;
                        r--;
                    }
                }
                saving(new_img);
            }
            else {
                cout << "wrong! please enter a valid choice\n";
            }
        }
        else if (choice == "6"){
            // darken the image by 50%
            darkenImage(img);  // call darkenImage 
        }
        else if (choice == "7"){
            // lighten the image by 50%
            lightenImage(img);  // call lightenImage
        }
        else if (choice == "8"){
            // end the program after displaying the statement
            cout << "Thx for using the app\n";
            break;
        }
        else {  // if the user entered a wrong choice display an error message
            cout << "wrong! please enter a valid choice\n";
        }
    }

    return 0;
}
