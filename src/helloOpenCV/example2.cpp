/*
#include "example2.h"

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


    // Old mouse handler from Homography example
    void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
    {
        if (event == EVENT_LBUTTONDOWN)
        {
            userdata* data = reinterpret_cast<userdata*>(data_ptr);
            circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, CV_AA);
            imshow("Image", data->im);
            if (data->points.size() < 4)
            {
                data->points.push_back(Point2f(x, y));
            }
        }
    }

    // mouse handler from LK demo example
    static void onMouse(int event, int x, int y, int flags, void* param)
    {
        if (event == CV_EVENT_LBUTTONDOWN)
        {
            //point = Point2f((float)x, (float)y);
            //addRemovePt = true;
        }
    }
}

// TODO: remove
void HomographyExample2(const std::string & imgPathSrc, const std::string & imgPathDst)
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

void Example2::LkDemo()
{

}
*/