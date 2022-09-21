#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

cv::Point_<int> findBiggestBlob(Mat img) {
    int max=-1;

    Point maxPt;

    for(int y=0;y<img.size().height;y++)
    {
        uchar *row = img.ptr(y);
        for(int x=0;x<img.size().width;x++)
        {
            // in practice, this can be anything other than 1
            if(row[x]>=128)
            {

                int area = floodFill(img, Point(x,y), CV_RGB(0,0,64));

                if(area>max)
                {
                    maxPt = Point(x,y);
                    max = area;
                }
            }
        }
    }

    return maxPt;
}

int main(int argc, char** argv) {
    Mat sudoku = imread(SUDOKU_IMG_PATH, 0);
    Mat outerBox = Mat(sudoku.size(), CV_8UC1);

    // blur the image to reduce noise from paper texture
    GaussianBlur(sudoku, sudoku, Size(11,11), 0);

    // threshold the image to capture the outerbox which we care about - too much going on to do the rest atm
    adaptiveThreshold(sudoku, outerBox, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);

    // flip the bits so that the stuff we want to select (the lines) are white
    bitwise_not(outerBox, outerBox);

    // fill in any gaps that have formed
    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
    dilate(outerBox, outerBox, kernel);

    Point biggestBlob = findBiggestBlob(outerBox);
    floodFill(outerBox, biggestBlob, CV_RGB(255, 255, 255));

    // switch non-white pixels with black to hide them
    for(int y=0;y<outerBox.size().height;y++)
    {
        uchar *row = outerBox.ptr(y);
        for(int x=0;x<outerBox.size().width;x++)
        {
            if(row[x]==64 && x!=biggestBlob.x && y!=biggestBlob.y)
            {
                floodFill(outerBox, Point(x,y), CV_RGB(0,0,0));
            }
        }
    }

    // show stuff
    const char *origWindowName = "Input";
    namedWindow(origWindowName, 1);
    imshow(origWindowName, sudoku);

    const char *outputWindownName = "Outer box";
    namedWindow(outputWindownName, 1);
    moveWindow(outputWindownName, 0, 500);
    imshow(outputWindownName, outerBox);

    waitKey(0);
}

