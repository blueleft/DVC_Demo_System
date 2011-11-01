#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    VideoCapture cap(0);
    if(!cap.isOpened()) {
        return -1;
    }
    Mat frame;
    VideoWriter writer;
    writer.open(argv[1], CV_FOURCC('I','4','2','0'), 30, Size(176, 144));
    if(!writer.isOpened()) {
        cout << "fall to open test"<< endl;
        return -1;
    }
    namedWindow("input", 1);
    while(true) {
        cap >> frame;
        writer << frame;
        imshow("input", frame);
        if(waitKey(30) >= 0) break;
    }
    cap.release();
    return 0;
}
