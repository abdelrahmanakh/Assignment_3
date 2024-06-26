/*
 * FCAI – Structured Programming – 2024 - Assignment 3 - Part 2-B
 * Program Name: CS112_A3_Part2B_S3_S4_20230593_20230587_20230794.cpp
 * Program Description: Image Filter Program
 * Last Modification Date: 15/04/2024
 * Authors: Abdelrahman Ahmed Samir Mohamed Ali, 20230593, Group:A, Sec.no:3
 *          Saleem Sami Saleem Aljerjawi, 20230794, Group:A, Sec.no:4
 *          Mazen Mohamed Abdelsalam Ali Elsheikh, 20230587, Group:A, Sec.no:4
 * TA:      Ahmed Foad Lotfy
 * Who did what: Mazen: The Menu of the previous delivery & Print function & Grayscale Filter & Lighten and Darken filter & Edge detection & Merge filter
 *               Abdelrahman: the menu of this delivery & flip & black_and_white & Crop & Resize & Purple Filters
 *               Saleem: Invert & Rotate & Frame & Blur & Infrared Filters
 * Emails:
 *        Mazen: 11410120230587@stud.cu.edu.eg
 *        Abdelrahman: 20230593@stud.fci-cu.edu.eg
 *        Saleem: 20230794@stud.fci-cu.edu.eg
 *
 *  Diagram scheme: https://drive.google.com/file/d/1L_iB-lvYQEwGHlE6Cb8cBRx88ubM7oru/view?usp=drive_link
 *  Repo link: https://github.com/abdelrahmanakh/Assignment_3.git
*/
#include <iostream>
#include <cstdlib>
#include "Image_Class.h"
#include "vector"

using namespace std;

void printImage(Image image, string imageName) {
    string option;
    cout << "A: Modify on the current image\n";
    cout << "B: Modify in a new image\n";
    while (true) {
        getline(cin, option);
        if (option == "A" || option == "a") {
            image.saveImage(imageName);
            cout << "The filter is applied successfully\n";
            return;
        } else if (option == "B" || option == "b") {
            while (true) {
                string newName;
                cout << "Enter the image file name of the new file\n";
                getline(cin, newName);
                try {
                    image.saveImage(newName);
                    cout << "The filter is applied successfully!\n";
                }
                catch (const invalid_argument &e) {
                    continue;
                }
                return;
            }
        } else {
            cout << "Enter a valid option\n";
            continue;
        }
    }
}

Image grayscale_conversion(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int value = 0.299 * image(i, j, 0) + 0.587 * image(i, j, 1) + 0.114 * image(i, j, 2);
            for (int k = 0; k < image.channels; ++k)
                image(i, j, k) = value;
        }
    }
    return image;
}

Image black_and_white(Image image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3;
            if (avg >= 128)
                avg = 255;
            else
                avg = 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    return image;
}

Image flip_horizontally(Image image) {
    Image img = image, img2 = image;
    for (int i = 0, x = img2.width - 1; i < img2.width; i++, x--) {
        for (int j = 0; j < img2.height; j++) {
            for (int k = 0; k < 3; k++) {
                int v = img2(x, j, k);
                img(i, j, k) = v;
            }
        }
    }
    return img;
}

Image flip_vertically(Image image) {
    Image img = image, img2 = image;
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0, y = img.height - 1; j < img2.height; j++, y--) {
            for (int k = 0; k < 3; k++) {
                int v = img2(i, y, k);
                img(i, j, k) = v;
            }
        }
    }
    return img;
}

Image flip(Image image) {
    cout << "Enter the type of flipping you want\n";
    cout << "A: Horizontal\n";
    cout << "B: Verticel\n";
    while (true) {
        string option;
        getline(cin, option
        );
        if (option == "A" || option == "a")
            image = flip_horizontally(image
            );
        else if (option == "B" || option == "b")
            image = flip_vertically(image
            );
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return image;
}

Image invert_image(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int inv_r = 255 - image(i, j, 0);
            unsigned int inv_g = 255 - image(i, j, 1);
            unsigned int inv_b = 255 - image(i, j, 2);

            image(i, j, 0) = inv_r;
            image(i, j, 1) = inv_g;
            image(i, j, 2) = inv_b;
        }
    }

    return image;
}

Image rotateImage90(Image image) {
    Image adjusted_img(image.height, image.width);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = j;
                int new_j = image.width - 1 - i;


                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    return adjusted_img;
}

Image rotateImage180(Image image) {
    Image adjusted_img(image.width, image.height);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = image.width - 1 - i;
                int new_j = image.height - 1 - j;

                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    return adjusted_img;
}

Image rotateImage270(Image image) {
    Image adjusted_img(image.height, image.width);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = image.height - 1 - j;
                int new_j = i;

                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    return adjusted_img;
}

Image rotate(Image image) {
    cout << "Enter the degree of rotation you want\n";
    cout << "A: 90\n";
    cout << "B: 180\n";
    cout << "C: 270\n";
    while (true) {
        string degree;
        getline(cin, degree);
        if (degree == "A" || degree == "a")
            image = rotateImage90(image);
        else if (degree == "B" || degree == "b")
            image = rotateImage180(image);
        else if (degree == "C" || degree == "c")
            image = rotateImage270(image);
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return image;
}

Image lighten_image(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 1.5 * image(i, j, k);
                newValue = min(newValue, 255);
                image(i, j, k) = newValue;
            }
        }
    }
    return image;
}

Image darken_image(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 0.5 * image(i, j, k);
                newValue = max(newValue, 0);
                image(i, j, k) = newValue;
            }
        }
    }
    return image;
}

Image edge_detection(Image image) {
    image = grayscale_conversion(image);
    Image modified_image = image;

    int dx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int dy[3][3] = {{1,  2,  1},
                    {0,  0,  0},
                    {-1, -2, -1}};

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                modified_image(i, j, k) = 255;
            }
        }
    }

    int threshold = 110;
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {

            int x_value = 0;
            for (int l = 0; l < 3; ++l) {
                for (int r = 0; r < 3; ++r) {
                    x_value += dx[l][r] * image(i + r - 1, j + l - 1, 0);
                }
            }

            int y_value = 0;
            for (int l = 0; l < 3; ++l) {
                for (int r = 0; r < 3; ++r) {
                    y_value += dy[l][r] * image(i + r - 1, j + l - 1, 0);
                }
            }

            int r_value = sqrt(x_value * x_value + y_value * y_value);
            if (r_value > threshold) {
                for (int k = 0; k < 3; ++k)
                    modified_image(i, j, k) = 0;
            } else {
                for (int k = 0; k < 3; ++k)
                    modified_image(i, j, k) = 255;
            }

        }
    }

    return modified_image;
}

Image blurImage(Image image) {
    Image blurredImage(image.width, image.height);
    int blurSize = 100;

    vector<vector<vector<int>>> pref(
            vector<vector<vector<int>>>(image.width + 1, vector<vector<int>>(image.height + 1, vector<int>(3, 0))));

    for (int i = 1; i <= image.width; ++i) {
        for (int j = 1; j <= image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                pref[i][j][k] = pref[i - 1][j][k] + pref[i][j - 1][k] - pref[i - 1][j - 1][k] + image(i - 1, j - 1, k);
            }
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int startX = max(0, i - blurSize / 2) + 1;
            int startY = max(0, j - blurSize / 2) + 1;
            int endX = min(image.width - 1, i + blurSize / 2) + 1;
            int endY = min(image.height - 1, j + blurSize / 2) + 1;

            int sumR = 0, sumG = 0, sumB = 0;
            int numPixels = (endX - startX + 1) * (endY - startY + 1);

            sumR = pref[endX][endY][0] - pref[startX - 1][endY][0] - pref[endX][startY - 1][0] +
                   pref[startX - 1][startY - 1][0];
            sumG = pref[endX][endY][1] - pref[startX - 1][endY][1] - pref[endX][startY - 1][1] +
                   pref[startX - 1][startY - 1][1];
            sumB = pref[endX][endY][2] - pref[startX - 1][endY][2] - pref[endX][startY - 1][2] +
                   pref[startX - 1][startY - 1][2];

            int avgR = sumR / numPixels;
            int avgG = sumG / numPixels;
            int avgB = sumB / numPixels;

            blurredImage(i, j, 0) = avgR;
            blurredImage(i, j, 1) = avgG;
            blurredImage(i, j, 2) = avgB;
        }
    }
    return blurredImage;
}

Image crop(Image img, bool print = true, int w0 = 0, int h0 = 0) {
    int x, y, w, h;
    if(print) {
        string sx, sy, sw, sh;
        while (true) {
            while (true) {
                cout << "the image size is " << img.width << " X " << img.height
                     << "\nEnter the position x,y where you want to start cropping:\n";
                cin >> sx >> sy;
                try {
                    x = stoi(sx);
                    y = stoi(sy);
                }
                catch (invalid_argument const &e) {
                    cout << "Please enter a number!\n";
                    continue;
                }
                if (x > img.width || y > img.height) {
                    cout << "This exceeds image dimensions!!\n";
                    continue;
                }
                if(x < 0 || y<0){
                    cout<<"Negative numbers in not acceptable!!!"<<endl;
                    continue;
                }
                break;
            }
            while (true) {
                cout << "the image size is " << img.width << " X " << img.height
                     << "\nEnter the dimensions of the new image:\n";
                cin >> sw >> sh;
                try {
                    w = stoi(sw);
                    h = stoi(sh);
                }
                catch (invalid_argument const &e) {
                    cout << "Please enter a number!\n";
                    continue;
                }
                if (w > img.width || h > img.height) {
                    cout << "This exceeds image dimensions!!\n";
                    continue;
                }
                if(w <= 0 || h<= 0){
                    cout<<"non positive numbers in not acceptable!!!"<<endl;
                    continue;
                }
                break;
            }
            if(w+x>img.width||h+y>img.height){
                cout << "This exceeds image dimensions!!\n";
                continue;
            }
            break;
        }
        cin.ignore();
    }
    else
        x = 0, y = 0, w = w0, h = h0;

    Image img2(w, h);
    for (int i = 0, a = x; i < w; i++, a++) {
        for (int j = 0, b = y; j < h; j++, b++) {
            for (int k = 0; k < 3; k++) {
                int v = img(a, b, k);
                img2(i, j, k) = v;
            }
        }
    }

    return img2;
}

Image resize(Image image, bool print = true, int mx_width = 0, int mx_height = 0) {
    string choice;
    float w, h;
    string sw, sh;
    if (print) {
        while (true) {
            cout << "Do you want to enter\n1) A scale\n2) New dimensions\n";
            cin >> choice;
            if (choice == "1") {
                while (true) {
                    float scale;
                    string sscale;
                    cout << "the image size is " << image.width << " X " << image.height
                         << "\nEnter the scale of the new image:\n";
                    cin >> sscale;
                    try {
                        scale = stof(sscale);
                    }
                    catch (invalid_argument const &e) {
                        cout << "Please enter a number!\n";
                        continue;
                    }
                    if(scale<=0){
                        cout<<"There is no Negative scale!!"<<endl;
                        continue;
                    }

                    w = scale * image.width;
                    h = scale * image.height;

                    break;
                }
            } else if (choice == "2") {
                while (true) {
                    cout << "the image size is " << image.width << " X " << image.height
                         << "\nEnter the dimensions of the new image:\n";
                    cin >> sw >> sh;
                    try {
                        w = stoi(sw);
                        h = stoi(sh);
                    }
                    catch (invalid_argument const &e) {
                        cout << "Please enter a number!\n";
                        continue;
                    }
                    if(w<=0||h<=0){
                        cout<<"Make sure the dimension is only positive numbers!!"<<endl;
                        continue;
                    }
                    break;
                }
            } else {
                cout << "Enter a valid option!\n";
                continue;
            }
            break;
        }
        cin.ignore();
    } else
        w = mx_width, h = mx_height;

    Image img2(w, h);
    float scale_width = w / image.width, scale_height = h / image.height;
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0; j < img2.height; j++) {
            for (int k = 0; k < 3; k++) {
                int x = i / scale_width, y = j / scale_height;
                img2(i, j, k) = image(x, y, k);
            }
        }
    }
    return img2;
}

Image type_1_merge_resize(Image img1, Image img2) {
    int mx_width = max(img1.width, img2.width);
    int mx_height = max(img1.height, img2.height);
    img1 = resize(img1, false, mx_width, mx_height);
    img2 = resize(img2, false, mx_width, mx_height);

    Image merged_image(mx_width, mx_height);
    for (int i = 0; i < mx_width; ++i) {
        for (int j = 0; j < mx_height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merged_image(i, j, k) = 0.5 * img1(i, j, k) + 0.5 * img2(i, j, k);
            }
        }
    }

    return merged_image;
}

Image type_2_merge_crop(Image img1, Image img2) {
    int mn_width = min(img1.width, img2.width);
    int mn_height = min(img1.height, img2.height);
    img1 = crop(img1, false, mn_width, mn_height);
    img2 = crop(img2, false, mn_width, mn_height);

    Image merged_image(mn_width, mn_height);
    for (int i = 0; i < mn_width; ++i) {
        for (int j = 0; j < mn_height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merged_image(i, j, k) = 0.5 * img1(i, j, k) + 0.5 * img2(i, j, k);
            }
        }
    }

    return merged_image;
}

Image merge(Image img1) {
    Image img2;
    while (true) {
        string imageName;
        cout << "Enter the image file name of the other image\n";
        cout << "Or type \'E\' to exit\n";
        getline(cin, imageName);
        if (imageName == "E")
            return img1;
        try {
            img2.loadNewImage(imageName);
        }
        catch (const invalid_argument &e) {
            continue;
        }
        break;
    }
    Image result;
    while (true) {
        string option;
        cout << "Enter the merge type you want:\n";
        cout << "A: Resize the smallest dimensions of them to the largest dimensions of them\n";
        cout << "B: Merge the common area of the smallest width and smallest height among them\n";
        getline(cin, option);
        if (option == "A" || option == "a")
            result = type_1_merge_resize(img1, img2);
        else if (option == "B" || option == "b")
            result = type_2_merge_crop(img1, img2);
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return result;
}

Image simple_frame(Image image) {
    int modified_width = image.width + 30; // The frame size is 15 So Adding 15 on both sides
    int modified_height = image.height + 30;

    Image framedImage(modified_width, modified_height);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                framedImage(i + 15, j + 15, k) = image(i, j, k);
            }
        }
    }

    for (int i = 0; i < framedImage.width; ++i) {
        for (int j = 0; j < framedImage.height; ++j) {
            if ((i < 15 || i >= image.width + 15) || (j < 15 || j >= image.height + 15)) {
                framedImage(i, j, 0) = 0;
                framedImage(i, j, 1) = 0;
                framedImage(i, j, 2) = 255;
            }
        }
    }

    return framedImage;
}

Image fancy_frame(const Image &image) {
    int modified_width = image.width + 30;
    int modified_height = image.height + 30;

    Image framedImage(modified_width, modified_height);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                framedImage(i + 15, j + 15, k) = image(i, j, k);
            }
        }
    }

    for (int i = 0; i < framedImage.width; ++i) {
        for (int j = 0; j < framedImage.height; ++j) {
            if ((i < 15 || i >= image.width + 15) || (j < 15 || j >= image.height + 15)) {
                framedImage(i, j, 0) = 0;
                framedImage(i, j, 1) = 0;
                framedImage(i, j, 2) = 0;
            }
        }
    }

    for (int i = 0; i < framedImage.width / 2; ++i) {
        for (int j = 0; j < framedImage.height / 2; ++j) {
            if ((i < 15 || i >= image.width + 15) || (j < 15 || j >= image.height + 15)) {
                framedImage(i, j, 0) = 255;
                framedImage(i, j, 1) = 0;
                framedImage(i, j, 2) = 0;
            }
        }
    }

    for (int i = framedImage.width / 2; i < framedImage.width; ++i) {
        for (int j = framedImage.height / 2; j < framedImage.height; ++j) {
            if ((i < 15 || i >= image.width + 15) || (j < 15 || j >= image.height + 15)) {
                framedImage(i, j, 0) = 255;
                framedImage(i, j, 1) = 0;
                framedImage(i, j, 2) = 0;
            }
        }
    }

    return framedImage;
}

Image frame_filter(Image image) {
    cout << "Enter the frame type you want\n";
    cout << "A: Simple Frame\n";
    cout << "B: Fancy Frame\n";
    while (true) {
        string ans;
        getline(cin, ans);
        if (ans == "A" || ans == "a")
            image = simple_frame(image);
        else if (ans == "B" || ans == "b")
            image = fancy_frame(image);
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return image;
}

Image sunlight_filter(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 2) = image(i, j, 2) * 0.75;
        }
    }
    return image;
}

Image purple_filter(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 1) *= 0.65;
        }
    }
    return image;
}

Image infrared_filter(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int r = image(i, j, 0) = 200;
            unsigned int inv_g = 255 - image(i, j, 1);
            unsigned int inv_b = 255 - image(i, j, 2);

            image(i, j, 0) = r;
            image(i, j, 1) = inv_g;
            image(i, j, 2) = inv_b;
        }
    }
    return image;
}

int main() {
    string imageName;
    Image image;
    while (true) {
        cout << "A: Choose an image to edit\nB: Exit\n";
        string option;
        getline(cin, option);
        if (option == "B" || option == "b")
            return 0;
        if (option != "A" && option != "a") {
            cout << "Enter a valid option\n";
            continue;
        }
        cout << "Enter the image file name you want to upload\n";
        getline(cin, imageName);
        try {
            image.loadNewImage(imageName);
        }
        catch (const invalid_argument &e) {
            continue;
        }
        break;
    }
    while (true) {
        cout << "0: Load A new Image\n";
        cout << "1: Grayscale Conversion\n";
        cout << "2: Black and White\n";
        cout << "3: Invert Image\n";
        cout << "4: Flip Image\n";
        cout << "5: Rotate Image\n";
        cout << "6: Lighten Image\n";
        cout << "7: Darken Image\n";
        cout << "8: Detect Image Edges\n";
        cout << "9: Blur Image\n";
        cout << "10: Crop Image\n";
        cout << "11: Resize Image\n";
        cout << "12: Sunlight Image\n";
        cout << "13: Purple filter\n";
        cout << "14: Infrared filter\n";
        cout << "15: Frame filter\n";
        cout << "16: Merge filter\n";
        cout << "17: Save Image\n";
        cout << "18: Exit\n";
        bool r = false;
        while (true) {
            string filter;
            getline(cin, filter);
            if (filter == "0") {
                while (true) {
                    cout << "Enter the image file name you want to upload\n";
                    getline(cin, imageName);
                    try {
                        image.loadNewImage(imageName);
                    }
                    catch (const invalid_argument &e) {
                        continue;
                    }
                    break;
                }
            } else if (filter == "1")
                image = grayscale_conversion(image);
            else if (filter == "2")
                image = black_and_white(image);
            else if (filter == "3")
                image = invert_image(image);
            else if (filter == "4")
                image = flip(image);
            else if (filter == "5")
                image = rotate(image);
            else if (filter == "6")
                image = lighten_image(image);
            else if (filter == "7")
                image = darken_image(image);
            else if (filter == "8")
                image = edge_detection(image);
            else if (filter == "9")
                image = blurImage(image);
            else if (filter == "10")
                image = crop(image);
            else if (filter == "11")
                image = resize(image);
            else if (filter == "12")
                image = sunlight_filter(image);
            else if (filter == "13")
                image = purple_filter(image);
            else if (filter == "14")
                image = infrared_filter(image);
            else if (filter == "15")
                image = frame_filter(image);
            else if (filter == "16")
                image = merge(image);
            else if (filter == "17")
                printImage(image, imageName);
            else if (filter == "18"){
                while (true){
                    string option;
                    cout<<"Do you want to save before exit?\n1)Yes\n2)No\n3)Return\n";
                    getline(cin,option);
                    if(option=="1"){
                        printImage(image, imageName);
                        return 0;
                    }
                    else if(option =="2")
                        return 0;
                    else if(option =="3"){
                        r = true;
                        break;
                    }
                    else{
                        cout << "Enter a valid option\n";
                        continue;
                    }
                }
            }
            else {
                cout << "Enter a valid option\n";
                continue;
            }
            break;
        }
        if(r){
            continue;
        }
    }
}
