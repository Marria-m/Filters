#include "Image_Class.h"
using namespace std;


void black_white(){
    int gray ;
    Image img("luffy.jpg") ;
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
    img.saveImage("newImage.png");
}

int main(){

    string file_name;
    cout << "plz enter name of the image: \n";
    cin >> file_name;
    Image img(file_name), new_img;

    new_img(img.width, img.height, 0);


    string choice, rotate;
    cout << "choose what u wanna apply on the Picture\n1)Invert Image\n2)Rotate Image\n3)Adding a Frame to the Picture\n4)Black and white\n";
    cin >> choice;

    if (choice == "1"){
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {

                img(i, j, 0) = 255 - img(i, j, 0);
                img(i, j, 1) = 255 - img(i, j, 1);
                img(i, j, 2) = 255 - img(i, j, 2);

            }
        }
    }

    else if (choice == "2"){
        cout << "rotate the image clockwise by..\n1)90 degree\n2)180 degree\n3)270 degree\n";
        cin >> rotate;
        if (rotate == "1"){
            cout << "haha" << endl;
            for (int i = 0; i < img.width; ++i) {
                cout << "jdj" << endl;
                for (int j = 0; j < img.height; ++j) {
                    cout << "mama" << endl;

                    img(j, img.width - i - 1, 0) = img(i, j, 0);
                    img(j, img.width - i - 1, 1) = img(i, j, 1);
                    img(j, img.width - i - 1, 2) = img(i, j, 2);
                    cout << i << endl << j << endl;

                }

            }
        }
    }

    else if(choice == 4){
        black_white();
    }


    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png : ";

    cin >> file_name;
    img.saveImage(file_name);

    cout << "hello world";

    return 0;
}
