#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"


int main(int argc, char** argv) {

    //create a gui window:
    cv::namedWindow("Output",1);
    cv::moveWindow("output", -1000, 0);

    //initialize a 120X350 matrix of black pixels:
    cv::Mat output = cv::Mat::zeros( 120, 350, CV_8UC3 );

    //write text on the matrix:
    cv::putText(output,
            "Hello World :)",
            cv::Point(15,70),
            cv::FONT_HERSHEY_PLAIN,
            3,
            cv::Scalar(0,255,0),
            4);

    //display the image:
    cv::imshow("Output", output);

    //wait for the user to press any key:
    cv::waitKey(0);

    return 0;

}