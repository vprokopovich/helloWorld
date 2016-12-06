#include "example1.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

namespace
{
    bool IsFileExist(const std::string& name)
    {
        if (FILE *file = fopen(name.c_str(), "r"))
        {
            fclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }

    struct userdata
    {
        Mat im;
        vector<Point2f> points;
    };

    void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
    {
        if (event == EVENT_LBUTTONDOWN)
        {
            userdata *data = ((userdata *)data_ptr);
            circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, CV_AA);
            imshow("Image", data->im);
            if (data->points.size() < 4)
            {
                data->points.push_back(Point2f(x, y));
            }
        }
    }
}

void Example1::OpenImage(const std::string imgPath)
{
    using namespace cv;

    if (!IsFileExist(imgPath))
    {
        return;
    }

    // Read input image and convert to float
    Mat img1 = imread(imgPath);
    img1.convertTo(img1, CV_32FC3, 1 / 255.0);
    
    const std::string windowName1("Image1");
    cvNamedWindow(windowName1.c_str(), 0);
    // показываем картинку в созданном окне
    cvShowImage(windowName1.c_str(), &img1);
    // ждём нажатия клавиши
    cvWaitKey(0);
    
}

void Example1::HomographyExample1(const std::string& imgPath)
{
    if (!IsFileExist(imgPath))
    {
        return;
    }

    // Read source image.
    Mat im_src = imread(imgPath);

    // Destination image. The aspect ratio of the book is 3/4
    Size size(300, 400);
    Mat im_dst = Mat::zeros(size, CV_8UC3);

    // Create a vector of destination points.
    vector<Point2f> pts_dst;

    pts_dst.push_back(Point2f(0, 0));
    pts_dst.push_back(Point2f(size.width - 1, 0));
    pts_dst.push_back(Point2f(size.width - 1, size.height - 1));
    pts_dst.push_back(Point2f(0, size.height - 1));

    // Set data for mouse event
    Mat im_temp = im_src.clone();
    userdata data;
    data.im = im_temp;

    cout << "Click on the four corners of the book -- top left first and" << endl
        << "bottom left last -- and then hit ENTER" << endl;

    const char* windowName="Image";

    // Show image and wait for 4 clicks. 
    imshow(windowName, im_temp);

    // Set the callback function for any mouse event
    setMouseCallback(windowName, mouseHandler, &data);
    waitKey(0);

    // Calculate the homography
    Mat h = findHomography(data.points, pts_dst);

    // Warp source image to destination
    warpPerspective(im_src, im_dst, h, size);

    // Show image
    imshow(windowName, im_dst);
    waitKey(0);

    cvDestroyWindow(windowName);
}

void Example1::HomographyExample2(const std::string & imgPathSrc, const std::string & imgPathDst)
{
    if (!IsFileExist(imgPathSrc) || !IsFileExist(imgPathDst))
    {
        return;
    }

    // Read in the image.
    Mat im_src = imread(imgPathSrc);
    Size size = im_src.size();

    // Create a vector of points.
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(0, 0));
    pts_src.push_back(Point2f(size.width - 1, 0));
    pts_src.push_back(Point2f(size.width - 1, size.height - 1));
    pts_src.push_back(Point2f(0, size.height - 1));

    // Destination image
    Mat im_dst = imread(imgPathDst);


    // Set data for mouse handler
    Mat im_temp = im_dst.clone();
    userdata data;
    data.im = im_temp;


    //show the image
    imshow("Image", im_temp);

    cout << "Click on four corners of a billboard and then press ENTER" << endl;
    //set the callback function for any mouse event
    setMouseCallback("Image", mouseHandler, &data);
    waitKey(0);

    // Calculate Homography between source and destination points
    Mat h = findHomography(pts_src, data.points);

    // Warp source image
    warpPerspective(im_src, im_temp, h, im_temp.size());

    imshow("Image", im_src);
    waitKey(0);
    imshow("Image", im_temp);
    waitKey(0);

    // Extract four points from mouse data
    Point pts_dst[4];
    for (int i = 0; i < 4; i++)
    {
        pts_dst[i] = data.points[i];
    }

    // Black out polygonal area in destination image.
    fillConvexPoly(im_dst, pts_dst, 4, Scalar(0), CV_AA);
    imshow("Image", im_dst);
    waitKey(0);

    // Add warped source image to destination image.
    im_dst = im_dst + im_temp;

    // Display image.
    imshow("Image", im_dst);
    waitKey(0);
}
