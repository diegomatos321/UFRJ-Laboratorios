#include "../headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui_MainWindow) 
{
    this->ui->setupUi(this);

    this->ui->thresholdingInput->setMaximum(255);
    this->ui->thresholdingInput->setValue(this->thresholding);

    QActionGroup *executionMode = new QActionGroup(this);
    executionMode->addAction(this->ui->actionSequencial);
    executionMode->addAction(this->ui->actionConcorrente);

    // connects da classe
    QObject::connect(this->ui->actionOpenFile, &QAction::triggered, this, &MainWindow::slotOpenFile);
    QObject::connect(this->ui->actionRun, &QAction::triggered, this, &MainWindow::slotRun);
    QObject::connect(this->ui->actionHelp, &QAction::triggered, this, &MainWindow::slotOpenReport);
    QObject::connect(this->ui->actionSequencial, &QAction::triggered, this, &MainWindow::slotSetSequencialAlgorithm);
    QObject::connect(this->ui->actionConcorrente, &QAction::triggered, this, &MainWindow::slotSetConcorrentAlgorithm);
    QObject::connect(this->ui->thresholdingInput, &QSlider::valueChanged, this, &MainWindow::slotSetThresholding);
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

    size_t startTime = cv::getTickCount();
    if (this->IsConcurrent)
    {
        // std::cout << "Running on Concurrent mode." << std::endl;
        this->ui->statusbar->showMessage("Running on Concurrent mode.");
        int numThreads = QThreadPool::globalInstance()->maxThreadCount();

        // calcula a altura de cada parte
        std::vector<cv::Mat> imageParts;
        int partHeight = this->originalImage.rows / numThreads;

        // Divide a imagem em partes com opencv / ROI (Region of Interest)
        // https://docs.opencv.org/3.4/js_basic_ops_roi.html
        for (int i = 0; i < numThreads; ++i)
        {
            int startY = i * partHeight;
            int endY = (i == numThreads - 1) ? this->originalImage.rows : startY + partHeight; // Handle the last part's height
            cv::Rect roi(0, startY, this->originalImage.cols, endY - startY);
            imageParts.push_back(this->originalImage(roi).clone());
        }

        QtConcurrent::blockingMap(imageParts, [](cv::Mat &imagePart) {   
            // qDebug() << "Thread ID:" << QThread::currentThreadId(); // Imprime o número da thread
            cv::cvtColor(imagePart, imagePart, cv::COLOR_BGR2GRAY); // converte imagem para escala de cinza
        });
        cv::vconcat(imageParts, this->grayScaleImage); // Junta as regiões numa única imagem.

        this->histogramImage = this->BuildHistogramFromGrayScaledImage(this->grayScaleImage);

        QtConcurrent::blockingMap(imageParts, [&](cv::Mat &imagePart) {   
            cv::threshold(imagePart, imagePart, this->thresholding, 255, cv::THRESH_BINARY_INV); // aplica metodo limite para gerar imagem binaria
        });
        cv::vconcat(imageParts, this->binaryImage); // Junta as regiões numa única imagem.

        // Aplica máscara
        cv::bitwise_and(this->originalImage, this->originalImage, this->resultImage, this->binaryImage);

    } else {
        // std::cout << "Running on Sequencial mode." << std::endl;
        this->ui->statusbar->showMessage("Running on Sequencial mode.");
        int numThreads = QThreadPool::globalInstance()->maxThreadCount();
        
        // calcula a altura de cada parte
        std::vector<cv::Mat> imageParts;
        int partHeight = this->originalImage.rows / numThreads;

        // Divide a imagem em partes com opencv / ROI (Region of Interest)
        // https://docs.opencv.org/3.4/js_basic_ops_roi.html
        for (int i = 0; i < numThreads; ++i)
        {
            int startY = i * partHeight;
            int endY = (i == numThreads - 1) ? this->originalImage.rows : startY + partHeight; // Handle the last part's height
            cv::Rect roi(0, startY, this->originalImage.cols, endY - startY);
            imageParts.push_back(this->originalImage(roi).clone());
        }

        // Converte a imagem para escala de cinza (BGR2GRAY)
        for (size_t i = 0; i < imageParts.size(); i++)
        {
            cv::cvtColor(imageParts[i], imageParts[i], cv::COLOR_BGR2GRAY); // converte imagem para escala de cinza
        }
        cv::vconcat(imageParts, this->grayScaleImage); // Junta as regiões numa única imagem.

        this->histogramImage = this->BuildHistogramFromGrayScaledImage(this->grayScaleImage);

        // Imagem binária
        for (size_t i = 0; i < imageParts.size(); i++)
        {
            cv::threshold(imageParts[i], imageParts[i], this->thresholding, 255, cv::THRESH_BINARY_INV); // aplica metodo limite para gerar imagem binaria
        }
        cv::vconcat(imageParts, this->binaryImage); // Junta as regiões numa única imagem.

        // Aplica máscara
        cv::bitwise_and(this->originalImage, this->originalImage, this->resultImage, this->binaryImage);
    }

    size_t endTime = cv::getTickCount();
    double elapsedTime = (endTime - startTime) / cv::getTickFrequency();
    // std::cout << "Elapsed time: " << elapsedTime << std::endl;
    QString message = "Elapsed time: ";
    message.append(std::to_string(elapsedTime));
    this->ui->statusbar->showMessage(message);

    // Exibe imagens
    this->DisplayOpenCvImage(this->ui->GrayScaleImage, this->grayScaleImage, QImage::Format::Format_Grayscale8);
    this->DisplayOpenCvImage(this->ui->Histogram, this->histogramImage, QImage::Format::Format_RGB888);
    this->DisplayOpenCvImage(this->ui->BinaryImage, this->binaryImage, QImage::Format::Format_Grayscale8);
    this->DisplayOpenCvImage(this->ui->ResultImage, this->resultImage, QImage::Format::Format_RGB888);
}

void MainWindow::slotOpenReport() {
    QString appDir = QApplication::applicationDirPath();
    QUrl reportPath = QUrl::fromLocalFile(appDir.append("/Relatorio_Trabalho_Programacao_Concorrente_2024_01.pdf"));
    QDesktopServices::openUrl(reportPath);
}

// https://docs.opencv.org/3.4/d8/dbc/tutorial_histogram_calculation.html
cv::Mat MainWindow::BuildHistogramFromGrayScaledImage(const cv::Mat grayScaledImage) {
    cv::Mat histogram;
    int histSize = 255;
    float range[] = {0.0, 255.0};
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
            cv::Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0
        );
    }

    return result;
}

void MainWindow::DisplayOpenCvImage(QLabel *container, cv::Mat image, QImage::Format type) {
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
        qImage.scaled(container->size(), Qt::KeepAspectRatio)
    );
    container->setPixmap(pixmap);
}

void MainWindow::slotSetSequencialAlgorithm() {
    this->IsConcurrent = false;
}

void MainWindow::slotSetConcorrentAlgorithm() {
    this->IsConcurrent = true;
}

void MainWindow::slotSetThresholding(int value) {
    this->thresholding = value;
}