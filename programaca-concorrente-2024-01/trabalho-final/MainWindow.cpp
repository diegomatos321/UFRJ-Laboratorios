#include "MainWindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui_MainWindow) 
{
    this->ui->setupUi(this);

    QObject::connect(this->ui->actionOpenFile, &QAction::triggered, this, &MainWindow::slotOpenFile);
    QObject::connect(this->ui->actionRun, &QAction::triggered, this, &MainWindow::slotSequencialConvert);
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

        // Convertendo a imagem do OpenCV para QImage
        QImage qImage(
            this->originalImage.data, 
            static_cast<int>(this->originalImage.cols), 
            static_cast<int>(this->originalImage.rows), 
            static_cast<int>(this->originalImage.step), 
            QImage::Format_RGB888
        );
        qImage = qImage.rgbSwapped(); // Inverte a ordem dos canais BGR para RGB

        // Redimensionar a imagem para se adequar ao QLabel imageInput
        QPixmap pixmap = QPixmap::fromImage(
            qImage.scaled(this->ui->OriginalImage->size(), 
            Qt::KeepAspectRatio
        ));
        this->ui->OriginalImage->setPixmap(pixmap);
    }
}

void MainWindow::slotSequencialConvert() {
    // Verifica se há uma imagem carregada
    if (this->originalImage.empty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("No image loaded"));
        return;
    }

    // Converte a imagem para escala de cinza (BGR2GRAY)
    cv::cvtColor(this->originalImage, this->grayScaleImage, cv::COLOR_BGR2GRAY);

    // Constroi histograma
    cv::Mat histogram;
    int histSize = 256;
    float range[] = {0.0, 256.0};
    const float *histRange[] = {range};
    cv::calcHist(&this->grayScaleImage, 1, 0, cv::Mat(), histogram, 1, &histSize, histRange);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    //cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    this->histogramImage = cv::Mat(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::normalize(histogram, histogram, 0, this->histogramImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; i++)
    {
        cv::line(
            this->histogramImage, 
            cv::Point(bin_w * (i - 1), 
            hist_h - cvRound(histogram.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0
        );
    }

    // Imagem binária
    const float k = 100.0;
    cv::threshold(this->grayScaleImage, this->binaryImage, k, 255, cv::THRESH_BINARY_INV);

    cv::bitwise_and(this->originalImage, this->originalImage, this->resultImage, this->binaryImage);

    // Exibe imagem em escala de cinza
    QImage qGrayImage(
        this->grayScaleImage.data, 
        static_cast<int>(this->grayScaleImage.cols), 
        static_cast<int>(this->grayScaleImage.rows), 
        static_cast<int>(this->grayScaleImage.step), 
        QImage::Format_Grayscale8
    );

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapGrayImage = QPixmap::fromImage(
        qGrayImage.scaled(this->ui->GrayScaleImage->size(), 
        Qt::KeepAspectRatio)
    );
    this->ui->GrayScaleImage->setPixmap(pixmapGrayImage);

    // Exibe o histograma
    QImage qHistogram(
        this->histogramImage.data, 
        static_cast<int>(this->histogramImage.cols), 
        static_cast<int>(this->histogramImage.rows), 
        static_cast<int>(this->histogramImage.step), 
        QImage::Format_RGB888
    );
    qHistogram = qHistogram.rgbSwapped(); // Inverte a ordem dos canais BGR para RGB

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapHistogram = QPixmap::fromImage(
        qHistogram.scaled(this->ui->Histogram->size(), 
        Qt::KeepAspectRatio)
    );
    this->ui->Histogram->setPixmap(pixmapHistogram);

    // Exibe a imagem binária
    QImage qBinary(
        this->binaryImage.data, 
        static_cast<int>(this->binaryImage.cols), 
        static_cast<int>(this->binaryImage.rows), 
        static_cast<int>(this->binaryImage.step), 
        QImage::Format_Grayscale8
    );

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapBinary = QPixmap::fromImage(qBinary.scaled(this->ui->BinaryImage->size(), Qt::KeepAspectRatio));
    this->ui->BinaryImage->setPixmap(pixmapBinary);

    QImage qResultImage(
        this->resultImage.data, 
        static_cast<int>(this->resultImage.cols), 
        static_cast<int>(this->resultImage.rows), 
        static_cast<int>(this->resultImage.step), 
        QImage::Format_RGB888
    );
    qResultImage = qResultImage.rgbSwapped(); // Inverte a ordem dos canais BGR para RGB

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapResultImage = QPixmap::fromImage(
        qResultImage.scaled(this->ui->ResultImage->size(), 
        Qt::KeepAspectRatio)
    );
    this->ui->ResultImage->setPixmap(pixmapResultImage);
}
