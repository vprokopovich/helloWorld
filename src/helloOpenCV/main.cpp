#include <cv.h>
#include <highgui.h>

#include "example1.h"

// OPENCV HELLO WORLD

int main(int argc, char** argv)
{
    const std::string testImg1("A:\\temp\\res\\Funny-People.jpg");
    const std::string testImgHomography1("A:\\temp\\res\\homography\\book1.jpg");
    const std::string testImgHomography2_1("A:\\temp\\res\\homography\\first-image.jpg");
    const std::string testImgHomography2_2("A:\\temp\\res\\homography\\times-square.jpg");

    Example1 ex1;
    ex1.HomographyExample1(testImgHomography1);
    ex1.HomographyExample2(testImgHomography2_1, testImgHomography2_2);

    // ����� ������ � ������ ��������
    int height = 620;
    int width = 440;
    // ����� ����� ��� ������ ������
    CvPoint pt = cvPoint(height / 4, width / 2);
    // ������ 8-������, 3-��������� ��������
    IplImage* hw = cvCreateImage(cvSize(height, width), 8, 3);
    // �������� �������� ������ ������
    cvSet(hw, cvScalar(0, 0, 0));
    // ������������� ������
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 1, CV_AA);
    // ��������� ����� ������� �� �������� �����
    cvPutText(hw, "OpenCV Step By Step", pt, &font, CV_RGB(150, 0, 150));

    // ������ ������
    cvNamedWindow("Hello World", 0);
    // ���������� �������� � ��������� ����
    cvShowImage("Hello World", hw);
    // ��� ������� �������
    cvWaitKey(0);

    // ����������� �������
    cvReleaseImage(&hw);
    cvDestroyWindow("Hello World");
    return 0;
}