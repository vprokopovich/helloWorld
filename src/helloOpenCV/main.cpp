#include <cv.h>
#include <highgui.h>

// OPENCV HELLO WORLD

int main(int argc, char** argv)
{
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