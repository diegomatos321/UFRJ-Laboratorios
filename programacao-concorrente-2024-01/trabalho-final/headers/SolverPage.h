#ifndef SolverPage_H
#define SolverPage_H

#include "../forms/ui_SolverPage.h"
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

class SolverPage : public QWidget
{
    Q_OBJECT
public:
  // Constructor/Destructor
  SolverPage(QWidget *parent = nullptr);
  ~SolverPage() override;

public slots:

  void slotOpenFile(); //abrir a imagem
  // void slotExit(); // fechar o programa
  void slotRun(); //converter para bw
  void slotOpenReport();
  void slotSetSequencialAlgorithm();
  void slotSetConcorrentAlgorithm();
  void slotSetThresholding(int value);
  void slotSaveResultImage();

protected:
  Ui::SolverPage* ui;

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
