#include "Image_Class.h"
using namespace std;


void validname(string& file_name){
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

    validname(file_name);

    img.saveImage(file_name);  // Save the edited image

    // Display the saved image using the system command
    system(file_name.c_str());
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
}


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
}

void crop(Image& img){
    int wid , hght ,x ,y ;
//    insert the new width and new heigth
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
                // to make the first pixel in new image as the starting point in the origanal image
                img2(i, j, k) = img1(wid + i, hght + j, k);
            }
        }

    }
    img = img2;
}


void rightleft_frame(Image& img, int w, int R, int G, int B){
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


void topbot_frame(Image& img, int w, int R, int G, int B){
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


void colourchoice(int& r, int& g, int& b){
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
    colourchoice(r, g, b);  // Prompt user to choose frame color

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
        topbot_frame(img, wight, r, g, b);  // Apply top and bottom frame
    }
    else if (choice == "2"){
        int wight;
        wight_input(wight);
        rightleft_frame(img, wight, r, g, b);  // Apply right and left frame
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
            } else if (green < 0) {
                green = 0;
            }

            if (blue > 255) {
                blue = 255;
            } else if (blue < 0) {
                blue = 0;
            }

            // Set the new color channels
            img(i, j, 0) = red;
            img(i, j, 1) = green;
            img(i, j, 2) = blue;
        }
    }
}


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
            if (green < 0){
                green = 0;
            }

            // Set the new color channels
            img(i, j, 0) = red;
            img(i, j, 1) = green;
            img(i, j, 2) = blue;
        }
    }
}


void skew(Image& img){
    //store an original image
    Image img1(img);
    //  create a new imgae to store the editting image
    Image img2("newImage.png");
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



int main(){

    // let user enter the image file name
    string file_name;
    cout << "plz enter the name of the image: \n";
    cin >> file_name;
    validname(file_name);
    Image original_img(file_name);

    while (original_img.imageData == nullptr) {
        // Error handling for failed image loading
        cout << "Failed to load image." << endl;
    }

    cout << "loaded successfully..\n";

    while(true){
        // Create a new image 'new_img' that the height of 'img' is the width of 'new_img' and width of 'img' is the height of 'new_img'
        Image new_img(original_img.height, original_img.width);

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
        cout << "choose what u wanna apply on the Picture\n1)Grayscale\n2)Black and White\n3)Invert Image\n4)merge two images\n5)Flip Image\n6)Rotate Image\n7)Darken Image\n8)Lighten Image\n9)Crop Image\n10)Adding a Frame\n11)Detect Image Edges\n12)Resize Image\n13)Blur Image\n14)Natural Sunlight\n15)Purple Filter\n16)Infrared Filter\n17)Image Skewing\n18)Save the image\n19)Exit without saving\n";
        cout << "enter ur choice: ";
        // let user enter their choice
        cin >> choice;

        if (choice == "1"){
            GrayScale(original_img);  // Call grayscale function
        }
        else if (choice == "2"){
            black_white(original_img);  // Call black and white conversion function
        }
        else if (choice == "3"){
            // invert color channels
            invert_filter(original_img);
        }

        else if(choice == "4"){
            // allow user to choose horizontal or vertical flip
            cout << "Flip the image...\n1)Vertical\n2)Horizontal\n";
            cin >> rotate;
            if (rotate == "1"){
                // Flip vertically
                for (int t = 0; t < original_img.width - 1; ++t){  // loop on image width to flip each colomn
                    // initialize 2 variables 'top' is the top of the image in one colomn and 'bot' is the last pixel in one colomn
                    int top = 0;
                    int bot = original_img.height - 1;
                    while (top < bot){  // stop if top = bot
                        swap(original_img(t, top, 0), original_img(t, bot, 0));
                        swap(original_img(t, top, 1), original_img(t, bot, 1));
                        swap(original_img(t, top, 2), original_img(t, bot, 2));
                        top++;
                        bot--;
                    }
                }
            }
            else if (rotate == "2"){
                // flip image horizontally
                for (int t = 0; t < original_img.height - 1; ++t){  // loop on image hight to flip each row
                    // initialize 2 variables 'l' is the left pixel of the image in one row and 'r' is the right pixel in one row
                    int l = 0;
                    int r = original_img.width - 1;
                    while (l < r){
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

        else if (choice == "5"){
            // display a menu to let the user choose the degree they want to rotate by
            cout << "rotate the image clockwise by..\n1)90 degree\n2)180 degree\n3)270 degree\n";

            // let the user choose the degree
            cin >> rotate;

            if (rotate == "1"){
                // rotate image by 90 degrees
                rotate90Degrees(original_img, new_img);  // call deg90 function
            }

            else if (rotate == "2"){
                // rotate image by 180 degrees by rotating the original image 90 degrees for two times

                // call deg90 function 2 times
                rotate90Degrees(original_img, new_img);
                rotate90Degrees(original_img, new_img);
            }

            else if (rotate == "3"){
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
        else if (choice == "6"){
            // darken the image by 50%
            darkenImage(original_img);  // call darkenImage
        }
        else if (choice == "7"){
            // lighten the image by 50%
            lightenImage(original_img);  // call lightenImage
        }
        else if (choice == "8"){
            // crop image
            crop(original_img);
        }
        else if(choice == "9"){
            // resize img
            resize(original_img);
        }
        else if(choice == "10"){
            frame_filter(original_img);  // apply frame filter
        }
        else if (choice == "14") {
            //Purple Filter
            Purple(original_img);  // call Purple
        }
        else if (choice == "15") {
            //Infrared Filter
            Infrared(original_img);  // call Infrared
        }
        else if(choice == "16"){
            //Skewing Filter
            skew(original_img); //call Skew
        }
        else if(choice == "17"){
            saving(original_img);
            cout << "Thanks for using app";
            break;
        }
        else if (choice == "18"){
            cout << "Thanks for using app";
            break;
        }
        else {
            // if the user entered a wrong choice display an error message
            cout << "wrong! please enter a valid choice\n";
        }
    }

    return 0;
}


/*algorthim for crop filter*/
// take the dimension of starting point from user.
// check if the dimensions are smaller than or equal to the original image.
// take the dimensions of the area to cut.
// check if the dimensions of the area is valid.
// This area is cut and stored in a new image.

