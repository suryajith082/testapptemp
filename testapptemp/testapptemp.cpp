// testapptemp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <utility>
#include <limits.h>
#include <chrono>

static int match_method;

using namespace std;
using namespace cv;
using namespace std::chrono;
char* a;
char* b;
int main(int argc, char* argv[])
{   
    //char* a;
    //char* b;

    string a=argv[1];
    string b=argv[2];
    auto start = high_resolution_clock::now();
    Mat img = imread(a);
    cout << a << endl;
    //cout << img;
    Mat temp = imread(b);
    cout << b << endl;
    //cout << temp;
    namedWindow("image_window", WINDOW_AUTOSIZE);
    namedWindow("result_window", WINDOW_AUTOSIZE);
    Mat img_display;
    img.copyTo(img_display);
    Mat result;
    /// Creating the result matrix
    int result_cols = img.cols + temp.cols - 1;
    int result_rows = img.rows + temp.rows - 1;
    result.create(result_cols, result_rows, CV_32FC1);
    matchTemplate(img, temp, result, TM_CCOEFF_NORMED);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    static Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    {
        matchLoc = maxLoc;
    }
    else
    {
        matchLoc = minLoc;
    }

    rectangle(img_display, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), Scalar(0, 0, 0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), Scalar(0, 0, 0), 2, 8, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;
    imshow("image_window", img_display);
    imshow("result_window", result);
    //cout << matchLoc;
    //cout << img;
    //cout << temp;
    waitKey(0);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
