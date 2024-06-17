#include "MainWindow.h"
#include "iostream"

MainWindow::MainWindow():ui(new Ui_MainWindow) 
{
    this->ui->setupUi(this);

    connect(this->ui->actionOpenFile, &QAction::triggered, this, &MainWindow::slotOpenFile);
    connect(this->ui->convertButton, &QPushButton::clicked, this, &MainWindow::slotSequencialConvert);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        cv::Mat image = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);

        if (image.empty())
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open or find the image"));
            return;
        }

        // Convertendo a imagem do OpenCV para QImage
        QImage qImage(image.data, static_cast<int>(image.cols), static_cast<int>(image.rows), static_cast<int>(image.step), QImage::Format_RGB888);
        qImage = qImage.rgbSwapped(); // Inverte a ordem dos canais BGR para RGB

        // Redimensionar a imagem para se adequar ao QLabel imageInput
        QPixmap pixmap = QPixmap::fromImage(qImage.scaled(this->ui->ImageInput->size(), Qt::KeepAspectRatio));
        this->ui->ImageInput->setPixmap(pixmap);
        this->ui->ImageInput->setScaledContents(true);

        // Armazenar a imagem atual
        this->currentImage = image;
    }
}

void MainWindow::slotSequencialConvert() {
    // Verifica se há uma imagem carregada
    if (this->currentImage.empty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("No image loaded"));
        return;
    }

    // Converte a imagem para escala de cinza (BGR2GRAY)
    cv::Mat imageBW;
    cv::cvtColor(this->currentImage, imageBW, cv::COLOR_BGR2GRAY);

    // Converte a imagem do OpenCV para QImage (BGR2GRAY não altera a ordem dos canais)
    QImage qImageBW(imageBW.data, imageBW.cols, imageBW.rows, static_cast<int>(imageBW.step), QImage::Format_Grayscale8);

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapBW = QPixmap::fromImage(qImageBW.scaled(this->ui->ImageInput->size(), Qt::KeepAspectRatio));
    this->ui->ImageOutput->setPixmap(pixmapBW);
    this->ui->ImageOutput->setScaledContents(true);
}
