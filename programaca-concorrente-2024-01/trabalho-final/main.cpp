#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main() {
    std::string image_path = "./assets/letreiro-sistemas-digitais.jpg";

    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    cv::imshow("Window", img);
    cv::waitKey(0);

    return 0;
}