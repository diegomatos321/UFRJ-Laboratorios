#include "MainWindow.h"
#include "iostream"

MainWindow::MainWindow():ui(new Ui_MainWindow) 
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
        this->ui->OriginalImage->setScaledContents(true);
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

    // Converte a imagem do OpenCV para QImage (BGR2GRAY não altera a ordem dos canais)
    QImage qImageBW(
        this->grayScaleImage.data, 
        this->grayScaleImage.cols, 
        this->grayScaleImage.rows, 
        static_cast<int>(this->grayScaleImage.step), 
        QImage::Format_Grayscale8
    );

    // Redimensiona a imagem para se adequar ao QLabel imageInput
    QPixmap pixmapBW = QPixmap::fromImage(qImageBW.scaled(this->ui->OriginalImage->size(), Qt::KeepAspectRatio));
    this->ui->GrayScaleImage->setPixmap(pixmapBW);
    this->ui->GrayScaleImage->setScaledContents(true);
}
