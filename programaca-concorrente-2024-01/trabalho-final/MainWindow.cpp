#include "MainWindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui_MainWindow) 
{
    this->ui->setupUi(this);

    QObject::connect(this->ui->actionOpenFile, &QAction::triggered, this, &MainWindow::slotOpenFile);
    QObject::connect(this->ui->actionRun, &QAction::triggered, this, &MainWindow::slotRun);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        this->originalImage = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);

        if (this->originalImage.empty())
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open or find the image"));
            return;
        }

        this->DisplayOpenCvImage(this->ui->OriginalImage, this->originalImage, QImage::Format_RGB888);
    }
}

void MainWindow::slotRun() {
    // Verifica se há uma imagem carregada
    if (this->originalImage.empty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("No image loaded"));
        return;
    }

    // Converte a imagem para escala de cinza (BGR2GRAY)
    cv::cvtColor(this->originalImage, this->grayScaleImage, cv::COLOR_BGR2GRAY);

    this->histogramImage = this->BuildHistogramFromGrayScaledImage(this->grayScaleImage);

    // Imagem binária
    const float k = 100.0;
    cv::threshold(this->grayScaleImage, this->binaryImage, k, 255, cv::THRESH_BINARY_INV);

    // Aplica máscara
    cv::bitwise_and(this->originalImage, this->originalImage, this->resultImage, this->binaryImage);

    // Exibe imagem em escala de cinza
    this->DisplayOpenCvImage(this->ui->GrayScaleImage, this->grayScaleImage, QImage::Format::Format_Grayscale8);
    this->DisplayOpenCvImage(this->ui->Histogram, this->histogramImage, QImage::Format::Format_RGB888);
    this->DisplayOpenCvImage(this->ui->BinaryImage, this->binaryImage, QImage::Format::Format_Grayscale8);
    this->DisplayOpenCvImage(this->ui->ResultImage, this->resultImage, QImage::Format::Format_RGB888);
}

cv::Mat MainWindow::BuildHistogramFromGrayScaledImage(const cv::Mat grayScaledImage) {
    cv::Mat histogram;
    int histSize = 256;
    float range[] = {0.0, 256.0};
    const float *histRange[] = {range};
    cv::calcHist(&grayScaledImage, 1, 0, cv::Mat(), histogram, 1, &histSize, histRange);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    cv::Mat result(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::normalize(histogram, histogram, 0, result.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; i++)
    {
        cv::line(
            result, 
            cv::Point(bin_w * (i - 1), 
            hist_h - cvRound(histogram.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0
        );
    }

    return result;
}

void MainWindow::DisplayOpenCvImage(QLabel *container, const cv::Mat image, QImage::Format type) {
    QImage qImage(
        image.data, 
        static_cast<int>(image.cols), 
        static_cast<int>(image.rows), 
        static_cast<int>(image.step), 
        type
    );
    if (type == QImage::Format::Format_RGB888)
    {
        qImage = qImage.rgbSwapped(); // Inverte a ordem dos canais BGR para RGB
    }
    
    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmap = QPixmap::fromImage(
        qImage.scaled(container->size(), 
        Qt::KeepAspectRatio)
    );
    container->setPixmap(pixmap);
}
