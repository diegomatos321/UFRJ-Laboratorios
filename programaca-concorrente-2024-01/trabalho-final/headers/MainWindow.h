#ifndef MainWindow_H
#define MainWindow_H

#include "../forms/ui_MainWindow.h"
#include <vector>
#include <iostream>

//#include <QApplication>
#include <QtGui/QActionGroup>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtConcurrent>
#include <QDebug>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Ui_MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
  // Constructor/Destructor
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

public slots:

  void slotOpenFile(); //abrir a imagem
  // void slotExit(); // fechar o programa
  void slotRun(); //converter para bw
  void slotOpenReport();
  void slotSetSequencialAlgorithm();
  void slotSetConcorrentAlgorithm();
  void slotSetThresholding(int value);

protected:
  Ui_MainWindow* ui;

  cv::Mat originalImage;
  cv::Mat grayScaleImage;
  cv::Mat histogramImage;
  cv::Mat binaryImage;
  cv::Mat resultImage;

  bool IsConcurrent = false;
  int thresholding = 100;

  cv::Mat BuildHistogramFromGrayScaledImage(const cv::Mat grayScaledImage);
  void DisplayOpenCvImage(QLabel *container, const cv::Mat image, const QImage::Format type);

protected slots:

private:
};

#endif
