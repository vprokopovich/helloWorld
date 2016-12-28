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

    // задаЄм высоту и ширину картинки
    int height = 620;
    int width = 440;
    // задаЄм точку дл€ вывода текста
    CvPoint pt = cvPoint(height / 4, width / 2);
    // —оздаЄи 8-битную, 3-канальную картинку
    IplImage* hw = cvCreateImage(cvSize(height, width), 8, 3);
    // заливаем картинку чЄрным цветом
    cvSet(hw, cvScalar(0, 0, 0));
    // инициализаци€ шрифта
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 1, CV_AA);
    // использу€ шрифт выводим на картинку текст
    cvPutText(hw, "OpenCV Step By Step", pt, &font, CV_RGB(150, 0, 150));

    // создаЄм окошко
    cvNamedWindow("Hello World", 0);
    // показываем картинку в созданном окне
    cvShowImage("Hello World", hw);
    // ждЄм нажати€ клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(&hw);
    cvDestroyWindow("Hello World");
    return 0;
}