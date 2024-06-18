#ifndef MainWindow_H
#define MainWindow_H

#include "ui_MainWindow.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

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
  // void slotConvertToBWParts(); //converter para bw em partes
  // void processConvertToBW(); // processa a imagem separado
  // void printThreadOutput(const QString &text);

protected:
  Ui_MainWindow* ui;

  cv::Mat originalImage;
  cv::Mat grayScaleImage;
  cv::Mat histogramImage;
  cv::Mat binaryImage;
  cv::Mat resultImage;

  cv::Mat BuildHistogramFromGrayScaledImage(const cv::Mat grayScaledImage);
  void DisplayOpenCvImage(QLabel *container, const cv::Mat image, const QImage::Format type);

protected slots:

private:
};

#endif
