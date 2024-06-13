#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    std::string image_path = "./assets/letreiro-sistemas-digitais.jpg";
    cv::Mat originalImg = cv::imread(image_path, cv::IMREAD_COLOR);

    cv::Mat imgGray;
    cv::cvtColor(originalImg, imgGray, cv::COLOR_BGR2GRAY);

    cv::Mat histogram;
    int histSize = 256;
    float range[] = {0.0, 256.0};
    const float *histRange[] = {range};
    cv::calcHist(&imgGray, 1, 0, cv::Mat(), histogram, 1, &histSize, histRange);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(histogram, histogram, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; i++)
    {
        cv::line(
            histImage, 
            cv::Point(bin_w * (i - 1), 
            hist_h - cvRound(histogram.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0
        );
    }

    cv::imshow("Histograma", histImage);

    cv::Mat binaryImg;
    cv::threshold(imgGray, binaryImg, 100, 255, cv::THRESH_BINARY);

    cv::imshow("Window", binaryImg);
    cv::waitKey(0);

    return 0;
}