#include "Image_Class.h"
using namespace std;


void saving(Image& img){
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png : ";

    cin >> file_name;
    img.saveImage(file_name);
}



void black_white(Image img){
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
                swap(new_img(i, j, k), img(j, i, k));
            }
        }
    }
    for (int t = 0; t < new_img.height - 1; ++t){
        int l = 0;
        int r = new_img.width - 1;
        while (l < r){
            swap(new_img(l, t, 0), new_img(r, t, 0));
            swap(new_img(l, t, 1), new_img(r, t, 1));
            swap(new_img(l, t, 2), new_img(r, t, 2));
            l++;
            r--;
        }
    }

}


int main(){

    string file_name;
    cout << "plz enter the name of the image: \n";
    cin >> file_name;
    Image img(file_name);

    Image new_img(img.height, img.width);
    for (int i = 0; i < new_img.width; i++) {
        for (int j = 0; j < new_img.height; j++){
            for (int k = 0; k < 3; k++){
                new_img(i, j, k) = 0;
            }
        }
    }

    string choice, rotate;
    cout << "choose what u wanna apply on the Picture\n1)Grayscale\n2)Black and White\n3)Invert Image\n4)Flip Image\n5)Rotate Image\n6)Darken Image\n7)Lighten Image\n8)Adding a Frame to the Picture\n";
    cin >> choice;

    if (choice == "1"){
        cout << "Rahma, put ur  Grayscale code in here";
    }
    else if (choice == "2"){
        black_white(new_img);
    }
    else if (choice == "3"){
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {

                img(i, j, 0) = 255 - img(i, j, 0);
                img(i, j, 1) = 255 - img(i, j, 1);
                img(i, j, 2) = 255 - img(i, j, 2);

            }
        }
        saving(img);
    }

    else if(choice == "4"){
        cout << "Flip the image...\n1)Vertical\n2)Horizontal\n";
        cin >> rotate;
        if (rotate == "1"){
            for (int t = 0; t < img.width - 1; ++t){
                int l = 0;
                int r = img.height - 1;
                while (l < r){
                    swap(img(t, l, 0), img(t, r, 0));
                    swap(img(t, l, 1), img(t, r, 1));
                    swap(img(t, l, 2), img(t, r, 2));
                    l++;
                    r--;
                }
            }
            saving(img);
        }
        else if (rotate == "2"){
             for (int t = 0; t < img.height - 1; ++t){
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
    }
        
    else if (choice == "5"){
        cout << "rotate the image clockwise by..\n1)90 degree\n2)180 degree\n3)270 degree\n";
        cin >> rotate;
        if (rotate == "1"){
            deg90(img, new_img);
            saving(new_img);
        }
        else if (rotate == "2"){
            for (int t = 0; t < img.width - 1; ++t){
                int l = 0;
                int r = img.height - 1;
                while (l < r){
                    swap(img(t, l, 0), img(t, r, 0));
                    swap(img(t, l, 1), img(t, r, 1));
                    swap(img(t, l, 2), img(t, r, 2));
                    l++;
                    r--;
                }
            }
            for (int t = 0; t < img.height - 1; ++t){
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
            deg90(img, new_img);
            for (int t = 0; t < new_img.width - 1; ++t){
                int l = 0;
                int r = new_img.height - 1;
                while (l < r){
                    swap(new_img(t, l, 0), new_img(t, r, 0));
                    swap(new_img(t, l, 1), new_img(t, r, 1));
                    swap(new_img(t, l, 2), new_img(t, r, 2));
                    l++;
                    r--;
                }
            }
            for (int t = 0; t < new_img.height - 1; ++t){
                int l = 0;
                int r = new_img.width - 1;
                while (l < r){
                    swap(new_img(l, t, 0), new_img(r, t, 0));
                    swap(new_img(l, t, 1), new_img(r, t, 1));
                    swap(new_img(l, t, 2), new_img(r, t, 2));
                    l++;
                    r--;
                }
            }
            saving(new_img);
        }
    }
    else if (choice == "6"){
        cout << "Rahma, put ur  Darken code in here";
    }
    else if (choice == "7"){
        cout << "Rahma, put ur  Lighten code in here";
    }
    else {
        cout << "wrong! please enter a valid number\n";
    }


    return 0;
}
