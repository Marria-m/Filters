// File:CS112_A3_Part2_Section25_20231160_20231089_20231056.cpp

// Purpose:This program allows the user to enter a file name of an image and display a menu for them
//         to choose the filter they want to apply on the image and continue letting him enter a file name
//         of an image and apply doing a filter on it till the user choose to end the program or save the new image.

// Author: Mariam Ehab Hassan
//         Doha Yasser Saeed
//         Rahma Bahgat Mohammed

// Section: 25

// Emails: mariamehab135721@gmail.com
//         dohayasser362@gmail.com
//         rahmabahgat455@gmail.com

// ID1: 20231160 – Invert filter, Flip filter, Rotate filter, Frames filter, Blur filter, Natural Sunlight filter.

// ID2: 20231089 – Black and white filter, Crop filter, Resize filter, Skew filter.  

// ID3: 20231056 – Grayscale filter, Merge filter, Lighten filter, Darken filter, Edges filter, Purple filter, Infrared filter. 


#include "Image_Class.h"
using namespace std;


// Mariam Ehab
void valid_name(string& file_name){
    // Check if the input filename contains a valid image extension
    // If not, prompt the user to enter a valid filename until they enter a valid one
    while(file_name.find(".jpg") == string::npos && file_name.find(".bmp") == string::npos && file_name.find(".png") == string::npos && file_name.find(".jpeg") == string::npos && file_name.find(".tga") == string::npos) {
        cout << "Please enter a valid image name with one of the following extensions: .jpg, .bmp, .png, .jpeg, .tga\n";
        cin >> file_name; // Also make sure to prompt for input inside the loop
    }
}


void saving(Image& img){
    // Function to save the edited image

    string file_name;
    // Prompt the user to enter the image name and extension
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png , .jpeg , .tga: ";
    cin >> file_name;

    valid_name(file_name);

    img.saveImage(file_name);  // Save the edited image

    // Display the saved image using the system command
    system(file_name.c_str());
}


// Rahma Bahgat
void GrayScale(Image& img) {
    // Grayscale Filter
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
}


// Doha Yasser
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
}


// Mariam Ehab
void invert_filter(Image& img){
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // subtract the colour from 255 to get the complement of the colour
            img(i, j, 0) = 255 - img(i, j, 0);
            img(i, j, 1) = 255 - img(i, j, 1);
            img(i, j, 2) = 255 - img(i, j, 2);
        }
    }
}


// Rahma Bahgat
void resizeMerge(Image& img, Image& resizedImg, int width, int height) {
    resizedImg = Image(width, height);

    for (int i = 0; i < resizedImg.width; ++i) {
        for (int j = 0; j < resizedImg.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int x = i * img.width / resizedImg.width;
                int y = j * img.height / resizedImg.height;
                resizedImg(i, j, k) = img(x, y, k);
            }
        }
    }
}


void mergeOption1(Image& firstImage, Image& secondImage) {
    // Function for Option 1: Merge by resizing the smaller image or both images to the biggest height and width

    // Calculate the dimensions of the merged image
    int maxWidth = max(firstImage.width, secondImage.width);
    int maxHeight = max(firstImage.height, secondImage.height);

    Image resizedFirstImage, resizedSecondImage;
    resizeMerge(firstImage, resizedFirstImage, maxWidth, maxHeight);
    resizeMerge(secondImage, resizedSecondImage, maxWidth, maxHeight);

    Image mergedImage(maxWidth, maxHeight);
    for (int i = 0; i < maxWidth; ++i) {
        for (int j = 0; j < maxHeight; ++j) {
            for (int k = 0; k < 3; ++k) {
                mergedImage(i, j, k) = (resizedFirstImage(i, j, k) + resizedSecondImage(i, j, k)) / 2;
            }
        }
    }

    firstImage = mergedImage;
}


void mergeOption2(Image& firstImage, Image& secondImage) {
    // Function for Option 2: Merge by resizing the common area of the smaller width and height

    // Calculate the dimensions of the merged image
    int minWidth = min(firstImage.width, secondImage.width);
    int minHeight = min(firstImage.height, secondImage.height);

    Image resizedFirstImage, resizedSecondImage;
    resizeMerge(firstImage, resizedFirstImage, minWidth, minHeight);
    resizeMerge(secondImage, resizedSecondImage, minWidth, minHeight);

    Image mergedImage(minWidth, minHeight);
    for (int i = 0; i < minWidth; ++i) {
        for (int j = 0; j < minHeight; ++j) {
            for (int k = 0; k < 3; ++k) {
                mergedImage(i, j, k) = (resizedFirstImage(i, j, k) + resizedSecondImage(i, j, k)) / 2;
            }
        }
    }
    firstImage = mergedImage;
}


// Mariam Ehab
void rotate90Degrees(Image& img, Image& new_img){
    // Loop through each pixel of the original image
    for (int i = 0; i < img.height - 1; ++i){
        for (int j = 0; j < img.width - 1; ++j){
            for (int k = 0; k < 3; ++k){
                // Swap pixel data to perform 90 degree clockwise rotation
                swap(new_img(i, j, k), img(j, i, k));
            }
        }
    }

    // Loop through each row of the new image
    for (int t = 0; t < new_img.height - 1; ++t){
        // Initialize left and right pointers for horizontal flipping
        int l = 0;
        int r = new_img.width - 1;

        while (l < r){  // flip until the left pointer crosses the right pointer
            // Swap pixel data to perform horizontal flip
            swap(new_img(l, t, 0), new_img(r, t, 0));
            swap(new_img(l, t, 1), new_img(r, t, 1));
            swap(new_img(l, t, 2), new_img(r, t, 2));
            // Move the left pointer to the right and the right pointer to the left
            l++;
            r--;
        }
    }
    Image temp = img;
    img = new_img;
    new_img = temp;
}


// Rahma Bahgat
void lightenImage(Image& img) {
    // Function to lighten the image

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
}


void darkenImage(Image& img) {
    // Function to darken the image

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
}


// Doha Yasser
void crop(Image& img){
    int wid , hght ,x ,y ;
//    insert the new width and new height
    cout << "Enter the dimension of the point to start with as 200 100 (200 is width , 100 is height):";
    cin >> wid >> hght;

    Image img1(img);
//    check if new width and new height are valid
    while (wid > img1.width || hght > img1.height || wid <= 0 || hght <= 0) {
        cout << "Error: Enter a valid  dimensions\n";
        cin >> wid >> hght;
    }
    cout << "Enter the area to cut as 600 600 (600*600)";
    cin >> x >> y;
    // check if in range
    while(wid + x > img1.width || wid + x <= 0 || hght + y > img1.height || hght + y <= 0 || x <= 0 || y <= 0){
        cout << "Out Of Range , please enter a valid area\n";
        cin >> x >> y;
    }
//    create a new image to store the editing image
    Image img2(x, y);

    // loop on pixels
    for(int i = 0 ; i < x ; i++){
        for(int j = 0 ; j < y; j++){
            for(int k = 0 ; k < 3 ; k++) {
                // to make the first pixel in new image as the starting point in the original image
                img2(i, j, k) = img1(wid + i, hght + j, k);
            }
        }

    }
    img = img2;
}


// Mariam Ehab
void RightLeft_frame(Image& img, int w, int R, int G, int B){
    // Create a new image with extended width to accommodate the frame
    Image img2 (img.width + (w * 2), img.height);

    // Fill the entire new image with the specified color for the frame
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0; j < img2.height; j++){
            img2(i, j, 0) = R;
            img2(i, j, 1) = G;
            img2(i, j, 2) = B;
        }
    }
    // Copy the original image onto the new image, leaving space for the frame
    for (int i = 0; i < img.height - 1; ++i){
        for (int j = 0; j < img.width - 1; ++j){
            for (int k = 0; k < 3; ++k){
                // Shift pixel data to the right by w pixels to create space for the left frame
                swap(img2(j + w, i, k), img(j, i, k));
            }
        }
    }
    img = img2;
}


void TopBot_frame(Image& img, int w, int R, int G, int B){
    // Create a new image with extended height
    Image img2 (img.width, img.height + (w * 2));

    // Fill the entire new image with the specified color for the frame
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0; j < img2.height; j++){
            img2(i, j, 0) = R;
            img2(i, j, 1) = G;
            img2(i, j, 2) = B;
        }
    }
    // Copy the original image onto the new image, leaving space for the frame
    for (int i = 0; i < img.height - 1; ++i){
        for (int j = 0; j < img.width - 1; ++j){
            for (int k = 0; k < 3; ++k){
                // Shift pixel data downwards by w pixels to create space for the top frame
                swap(img2(j, i + w, k), img(j, i, k));
            }
        }
    }
    img = img2;
}


void simple_frame(Image& img,Image& img2, int w, int R, int G, int B){
    // Fill the entire new image with the specified color for the frame
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0; j < img2.height; j++){
            img2(i, j, 0) = R;
            img2(i, j, 1) = G;
            img2(i, j, 2) = B;
        }
    }

    // Copy the original image onto the new image, leaving space for the frame
    for (int i = 0; i < img.height - 1; ++i){
        for (int j = 0; j < img.width - 1; ++j){
            for (int k = 0; k < 3; ++k){
                // Shift pixel data to the right and downwards by w pixels to create space for the frame
                swap(img2(j + w, i + w, k), img(j, i, k));
            }
        }
    }
}


void fancy_frame(Image& img, Image& img2, int R, int G, int B) {
    // Create a simple frame around the original image
    simple_frame(img, img2, 50, R, G, B);

    // Variables for left, top, right positions of the frame
    int l = 10;
    int t = 12;
    int r = img2.width - 11;

    // Loop to create a fancy pattern on the top and bottom sides of the frame
    for (int j = 0; j < 50 / 15; j++) {
        for (int i = 0; i < img2.height - 1; i++) {
            // Adjust frame positions for the fancy pattern
            if (t > 6) {
                l--;
                r++;
                t--;
            } else if (t == 0) {
                t = 12;
            } else {
                l++;
                r--;
                t--;
            }
            for (int k = 0; k < 3; k++) {
                // Invert colors of selected pixels, so it will appear whatever the color is
                img2(l, i, k) = 255 - img2(l, i, k);
                img2(r, i, k) = 255 - img2(r, i, k);
                img2(l + 10, i, k) = 255 - img2(l + 10, i, k);
                img2(r - 10, i, k) = 255 - img2(r - 10, i, k);
            }
        }
        // Adjust frame positions for the next iteration
        l += 5 / 2;
        r -= 5 / 2;
    }

    // Variables for top and bottom positions of the frame
    int top = 10;
    int bot = img2.width - 1;
    t = 12;

    // Loop to create a fancy pattern on the left and right sides of the frame
    for (int j = 0; j < 50 / 15; j++) {
        for (int i = 0; i < img2.width - 1; i++) {
            // Adjust frame positions for the fancy pattern
            if (t > 6) {
                top--;
                bot++;
                t--;
            } else if (t == 0) {
                t = 12;
            } else {
                top++;
                bot--;
                t--;
            }

            for (int k = 0; k < 3; k++) {
                // Invert colors of selected pixels
                img2(i, top, k) = 255 - img2(i, top, k);
                img2(i, top + 10, k) = 255 - img2(i, top + 10, k);
                img2(i, bot, k) = 255 - img2(i, bot, k);
                img2(i, bot - 10, k) = 255 - img2(i, bot - 10, k);

            }
        }
        // Adjust frame positions for the next iteration
        top += 5 / 2;
        bot -= 5 / 2;
    }

    img = img2;
}


void wight_input(int& wi_f){
    // Function to prompt the user to input the width of the frame
    cout << "plz enter the width of the frame: ";
    cin >> wi_f;
}


void colour_choice(int& r, int& g, int& b){
    // Function to prompt the user to choose a color for the frame
    cout << "colours u can choose from...\n";
    cout << "1.Black\n2.wight\n3.Gray\n4.red\n5.blue\n6.green\n";
    cout << "enter the colour u want: ";
    string col;
    cin >> col;

    // Set the RGB values based on the user's color choice
    if (col == "1")  // Black
        r = g = b = 0;
    else if (col == "2")  // white
        r = g = b = 255;
    else if (col == "3")  // gray
        r = g = b = 155;
    else if (col == "4"){  // red
        r = 255;
        g = 0;
        b = 0;
    }
    else if (col == "5"){  // blue
        r = 0;
        g = 0;
        b = 255;
    }
    else if (col == "6"){  // green
        r = 0;
        g = 255;
        b = 0;
    }
    else {
        cout << "wrong choice";
    }
}


void frame_filter(Image& img){
    // Function to apply frame filters to the image based on user choice
    int r, g, b;
    colour_choice(r, g, b);  // Prompt user to choose frame color

    string choice;
    cout << "choose the frame...\n";
    cout << "1.top and bottom frame\n";
    cout << "2.right and left frame\n";
    cout << "3.Simple frame\n";
    cout << "4.Fancy frame\n";

    cin >> choice;

    if (choice == "1"){
        int wight;
        wight_input(wight);  // Prompt user to input frame width
        TopBot_frame(img, wight, r, g, b);  // Apply top and bottom frame
    }
    else if (choice == "2"){
        int wight;
        wight_input(wight);
        RightLeft_frame(img, wight, r, g, b);  // Apply right and left frame
    }
    else if (choice == "3"){
        int wight;
        wight_input(wight);
        // Create a new image with a simple frame and save it
        Image img2(img.width + (wight * 2), img.height + (wight * 2));
        simple_frame(img, img2, wight, r, g, b);  // apply simple frame
        img = img2;
    }
    else if (choice == "4"){
        // Create a new image with a fancy frame and save it
        Image img2(img.width + 100, img.height + 100);
        fancy_frame(img, img2, r, g, b);
    }
    else {
        cout << "Invalid please enter a valid choice\n";
    }
}


// Doha Yasser
void resize(Image& img){
//    take new dimension from user
    std::cout << "Enter the dimension you want as 200 100 (200 is width , 100 is height): ";
    int wid , hght ;
    std::cin >> wid >> hght;

    Image img1(img);
    //    check if new width and new height are valid
    while(wid <= 0 || hght <= 0){
        std::cout << "Error: Enter a valid  dimensions\n";
        std::cin >> wid >> hght;
    }
    //    create a new image to store the editing image
    Image img2(wid, hght);
    // loop on pixels
    for(int i = 0 ; i < wid ; i++){
        for(int j = 0 ; j < hght ; j++){
            for(int k = 0 ; k < 3 ; k++) {

                int x = i * img1.width / wid;
                int y = j * img1.height / hght;
                img2(i, j, k) = img1(x, y, k);
            }
        }

    }
    img = img2;
}


// Mariam Ehab
void top_left_corner(Image& image) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;
    for (int x = 0; x <= 1; x++) {   // from 0 to reach 1 (what is after this pixel)
        red += image(x, 0, 0);
        green += image(x, 0, 1);
        blue += image(x, 0, 2);
        count++;

    }

    image(0, 0, 0) = red / count;
    image(0, 0, 1) = green / count;
    image(0, 0, 2) = blue / count;

}


void top_right_corner(Image &image) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;

    for (int x = 0; x <= 1; x++) {   // from 0 to reach 1 (what is after this pixel)
        for (int y = 0; y <= 1; y++) {  // same as the first loop
            red += image(image.width - 1 - x, y, 0);
            green += image(image.width - 1 - x,  y, 1);
            blue += image(image.width - 1 - x,  y, 2);
            count++;
        }
    }

    image(image.width - 1, 0, 0) = red / count;
    image(image.width - 1, 0, 1) = green / count;
    image(image.width - 1, 0, 2) = blue / count;

}


void down_right_corner(Image &image) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;

    for (int x = -1; x < 1; x++) {   // from -1 (what before this pixel) to reach 0
        for (int y = -1; y < 1; y++) {  // same as the first loop
            red += image(image.width - 1 - x, image.height - 1 - y, 0);
            green += image(image.width - 1 - x, image.height - 1 - y, 1);
            blue += image(image.width - 1 - x, image.height - 1 - y, 2);
            count++;
        }
    }

    image(image.width - 1, image.height - 1, 0) = red / count;
    image(image.width - 1, image.height - 1, 1) = green / count;
    image(image.width - 1, image.height - 1, 2) = blue / count;

}


void down_left_corner(Image &image) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;

    for (int x = 0; x <= 1; x++) {   // from 0 to reach 1 (what is after this pixel)
        for (int y = -1; y < 1; y++) {  // from -1 (what is before the pixel) till the exist pixel
            red += image(x, image.height - 1 + y, 0);
            green += image(x, image.height - 1 + y, 1);
            blue += image(x, image.height - 1 + y, 2);
            count++;
        }
    }

    image(0, image.height - 1, 0) = red / count;
    image(0, image.height - 1, 1) = green / count;
    image(0, image.height - 1, 2) = blue / count;
}


void top(Image &image) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;
    for (int i = 1; i < image.width - 2; i++) {
        for (int j = 0; j < 1; j++) {

            for (int x = -1; x <= 1; x++) {   // from -1 (what before this pixel) to reach 1 (what is after this pixel)
                for (int y = 0; y <= 1; y++) {  // from 0 to reach 1 (what is after this pixel)
                    red += image(i + x, j + y, 0);
                    green += image(i + x, j + y, 1);
                    blue += image(i + x, j + y, 2);
                    count++;
                }
            }


            image(i, j, 0) = red / count;
            image(i, j, 1) = green / count;
            image(i, j, 2) = blue / count;
        }
    }
}


void apply_blur(Image &image) {
    int rd;
    int grn;
    int bl;
    int cnt;

    for (int i = 1; i < image.width - 1; i++) {
        for (int j = 1; j < image.height - 1; j++) {
            rd = 0;
            grn = 0;
            bl = 0;
            cnt = 0;

            // get all pixel values around this pixel
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    rd += image(i + x, j + y, 0);
                    grn += image(i + x, j + y, 1);
                    bl += image(i + x, j + y, 2);
                    cnt++;
                }
            }

            // Average of the sum
            image(i, j, 0) = rd / cnt;
            image(i, j, 1) = grn / cnt;
            image(i, j, 2) = bl / cnt;
        }
    }

    top_right_corner(image);
    top_left_corner(image);
    down_right_corner(image);
    down_left_corner(image);
    top(image);

}


void blur_filter(Image& img){
    cout << "choose from the next...\n";
    cout << "1) blur by 20%\n";
    cout << "2) blur by 50%\n";
    cout << "3) blur by 100% (this will take time, please wait ^-^)\n";
    cout << "Enter your choice here: ";
    string nBlurring;
    cin >> nBlurring;

    while (nBlurring != "1" && nBlurring != "2" && nBlurring != "3"){
        cout << "please enter a right choice: ";
        cin >> nBlurring;
    }

    if (nBlurring == "1"){
        for (int n = 0; n < 10; n++) {
            apply_blur(img);
        }
    }
    else if (nBlurring == "2"){
        for (int n = 0; n < 40; n++) {
            apply_blur(img);
        }
    }
    else if (nBlurring == "3"){
        for (int n = 0; n < 60; n++) {
            apply_blur(img);
        }
    }

}


void NaturalSunlight(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; // Initialize average value

            // Calculate the average intensity
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            // Adjust pixel intensities to simulate natural sunlight
            int red = image(i, j, 0) + 30;  // Increase red channel intensity
            int green = image(i, j, 1) + 30;  // Increase green channel intensity
            int blue = image(i, j, 2) - 30;  // Decrease blue channel intensity

            // ensure intensity doesn't go out of range from 0 to 255
            if (red > 255){
                red = 255;
            }
            if (green > 255){
                green = 255;
            }
            if (blue < 0){
                blue = 0;
            }

            // Update the pixel intensities
            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }

}


// Rahma Bahgat
void Purple(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Increase the intensity of red and blue channels and decrease the green
            unsigned int red = img(i, j, 0) * 1.5; // Increase red channel
            unsigned int green = img(i, j, 1) * 0.7; // Decrease green channel
            unsigned int blue = img(i, j, 2) * 1.5; // Increase blue channel

            // Ensure that values are in the valid range (0 to 255)
            if (red > 255){
                red = 255;
            }
            if (blue > 255){
                blue = 255;
            }

            // Set the new color channels
            img(i, j, 0) = red;
            img(i, j, 1) = green;
            img(i, j, 2) = blue;
        }
    }
}


void Infrared(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Setting new values for green and blue channels
            unsigned int red = 255 ;
            unsigned int green = 255 - img(i, j, 2); // Green equals 225 minus blue
            unsigned int blue = 255 - img(i, j, 1);  // Blue equals 225 minus green

            // Ensure that values are in the valid range (0 to 255)
            if (green > 255) {
                green = 255;
            }
            if (blue > 255) {
                blue = 255;
            }
            // Set the new color channels
            img(i, j, 0) = red;
            img(i, j, 1) = green;
            img(i, j, 2) = blue;
        }
    }
}


// Doha Yasser
void skew(Image& img){
    //store an original image
    Image img1(img);
    //  create a new image to store the editing image
    Image img2(int(1.5*img1.width), img1.height);
    // loop on pixels
    for(int i = 0 ; i < img1.width ; i++){
        for(int j = 0 ; j < img1.height ; j++){
            for(int k = 0 ;k < 3 ; k++){
                // width of pixel + half of height
                int skew = i + int(j*0.5);
                if(skew < img1.width){
                    img1(skew,j,k) = img1(i,j,k);
                }
            }
        }
    }
    img = img1;
}



int main() {

    // let user enter the image file name
    string file_name;
    cout << "plz enter the name of the image: \n";
    cin >> file_name;
    valid_name(file_name);
    Image original_img(file_name);

    while (original_img.imageData == nullptr) {
        // Error handling for failed image loading
        cout << "Failed to load image." << endl;
    }

    cout << "loaded successfully..\n";

    // Create a new image 'new_img' that the height of 'img' is the width of 'new_img' and width of 'img' is the height of 'new_img'
    Image new_img(original_img.height, original_img.width);

    // Fill the 'new_img' with black pixels
    for (int i = 0; i < new_img.width; i++) {
        for (int j = 0; j < new_img.height; j++) {
            for (int k = 0; k < 3; k++) {
                new_img(i, j, k) = 0;
            }
        }
    }


    while (true) {
        string choice, rotate;

        // Display a list of the supported operations to the user
        cout << "choose what u wanna apply on the Picture\n";
        cout << "1)Grayscale\n2)Black and White\n3)Invert Image\n";
        cout << "4)merge two images\n5)Flip Image\n6)Rotate Image\n";
        cout << "7)Darken Image\n8)Lighten Image\n9)Crop Image\n";
        cout << "10)Adding a Frame\n11)Detect Image Edges\n12)Resize Image\n";
        cout << "13)Blur Image\n14)Natural Sunlight\n15)Purple Filter\n16)Infrared Filter\n";
        cout << "17)Image Skewing\n18)Save the image\n19)Display without saving\n";
        cout << "enter ur choice: ";

        // let user enter their choice
        cin >> choice;

        if (choice == "1") {
            GrayScale(original_img);  // Call grayscale function
        }
        else if (choice == "2") {
            black_white(original_img);  // Call black and white conversion function
        }
        else if (choice == "3") {
            // invert color channels
            invert_filter(original_img);
        }
        else if (choice == "4") {
            string firstImageName, secondImageName, filename;
            int mergeOption;

            // Get the paths of the images to be merged
            cout << "Enter the name of the second image: ";
            cin >> secondImageName;
            valid_name(secondImageName);

            // Choose merge option
            while (true) {
                cout << "Choose merge option:\n";
                cout << "1. Merge by resizing the smaller image or both images to the biggest height and width\n";
                cout << "2. Merge by resizing the common area of the smaller width and height\n";
                cin >> mergeOption;

                if (mergeOption == 1 || mergeOption == 2) {
                    break;
                } else {
                    cout << "Invalid merge option. Please enter a valid option.\n";
                }
            }

            // Load the second image
            Image secondImage(secondImageName);

            // Perform merge operation based on the chosen option
            if (mergeOption == 1) {
                mergeOption1(original_img, secondImage);
            }
            else if (mergeOption == 2) {
                mergeOption2(original_img, secondImage);
            }
        }
        else if (choice == "5") {
            // allow user to choose horizontal or vertical flip
            cout << "Flip the image...\n1)Vertical\n2)Horizontal\n";
            cin >> rotate;
            if (rotate == "1") {
                // Flip vertically
                for (int t = 0; t < original_img.width - 1; ++t) {  // loop on image width to flip each column
                    // initialize 2 variables 'top' is the top of the image in one column and 'bot' is the last pixel in one column
                    int top = 0;
                    int bot = original_img.height - 1;
                    while (top < bot) {  // stop if top = bot
                        swap(original_img(t, top, 0), original_img(t, bot, 0));
                        swap(original_img(t, top, 1), original_img(t, bot, 1));
                        swap(original_img(t, top, 2), original_img(t, bot, 2));
                        top++;
                        bot--;
                    }
                }
            }
            else if (rotate == "2") {
                // flip image horizontally
                for (int t = 0; t < original_img.height - 1; ++t) {  // loop on image height to flip each row
                    // initialize 2 variables 'l' is the left pixel of the image in one row and 'r' is the right pixel in one row
                    int l = 0;
                    int r = original_img.width - 1;
                    while (l < r) {
                        swap(original_img(l, t, 0), original_img(r, t, 0));
                        swap(original_img(l, t, 1), original_img(r, t, 1));
                        swap(original_img(l, t, 2), original_img(r, t, 2));
                        l++;
                        r--;
                    }
                }
            }
            else {  // if the user entered wrong choice
                cout << "wrong! please enter a valid choice\n";
            }
        }
        else if (choice == "6") {
            // display a menu to let the user choose the degree they want to rotate by
            cout << "rotate the image clockwise by..\n1)90 degree\n2)180 degree\n3)270 degree\n";

            // let the user choose the degree
            cin >> rotate;

            if (rotate == "1") {
                // rotate image by 90 degrees
                rotate90Degrees(original_img, new_img);  // call deg90 function
            }
            else if (rotate == "2") {
                // rotate image by 180 degrees by rotating the original image 90 degrees for two times

                // call deg90 function 2 times
                rotate90Degrees(original_img, new_img);
                rotate90Degrees(original_img, new_img);
            }
            else if (rotate == "3") {
                // rotate image by 270 degrees by rotating the original image 90 degrees for three times

                // call deg90 function 3 times
                rotate90Degrees(original_img, new_img);
                rotate90Degrees(original_img, new_img);
                rotate90Degrees(original_img, new_img);
            }
            else {  // if the user entered wrong choice
                cout << "wrong! please enter a valid choice\n";
            }
        }
        else if (choice == "7") {
            // darken the image by 50%
            darkenImage(original_img);  // call darkenImage
        }
        else if (choice == "8") {
            // lighten the image by 50%
            lightenImage(original_img);  // call lightenImage
        }
        else if (choice == "9") {
            // crop image
            crop(original_img);
        }
        else if (choice == "10") {
            frame_filter(original_img);  // apply frame filter
        }
        else if (choice == "11"){
            cout << "Rahma, put the edges filter here ^-^\n";
        }
        else if (choice == "12") {
            // resize img
            resize(original_img);
        }
        else if (choice == "13"){
            blur_filter(original_img);  // apply blur frame
        }
        else if (choice == "14"){
            NaturalSunlight(original_img);  // call natural sunlight function
        }
        else if (choice == "15") {
            //Purple Filter
            Purple(original_img);  // call Purple
        }
        else if (choice == "16") {
            //Infrared Filter
            Infrared(original_img);  // call Infrared
        }
        else if (choice == "17") {
            //Skewing Filter
            skew(original_img); //call Skew
        }
        else if (choice == "18") {
            saving(original_img);
            cout << "Thanks for using the app";
            break;
        }
        else if (choice == "19") {
            system(file_name.c_str());
            cout << "Thanks for using the app";
            break;
        }
        else {
            // if the user entered a wrong choice display an error message
            cout << "wrong! please enter a valid choice\n";
        }
    }

    return 0;
}


/*algorithm for crop filter*/
// take the dimension of starting point from user.
// check if the dimensions are smaller than or equal to the original image.
// take the dimensions of the area to cut.
// check if the dimensions of the area is valid.
// This area is cut and stored in a new image.

