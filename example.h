#ifndef USB_H
#define USB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QProgressBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QInputDialog>

class ApexBootableUsbCreator : public QWidget {
    Q_OBJECT
public:
    ApexBootableUsbCreator(QWidget *parent = nullptr) : QWidget(parent), burnProcess(nullptr) {
        // Set up the main layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Set the background color to teal
        QPalette pal = palette();
        pal.setColor(QPalette::Window, QColor(0, 128, 128)); // Teal color
        setAutoFillBackground(true);
        setPalette(pal);

        // Add the images in a horizontal layout with no space between them
        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setSpacing(0); // No space between images
        imageLayout->setContentsMargins(0, 0, 0, 0); // No margins

        QLabel *apexImageLabel = new QLabel(this);
        QPixmap apexPixmap(":/images/ApexBrowser.png"); // Load from resource system
        if (!apexPixmap.isNull()) {
            apexImageLabel->setPixmap(apexPixmap.scaled(200, 100, Qt::KeepAspectRatio));  // Adjust size as needed
        } else {
            apexImageLabel->setText("ApexBrowser.png not found!");
        }
        imageLayout->addWidget(apexImageLabel);

        QLabel *usbImageLabel = new QLabel(this);
        QPixmap usbPixmap(":/images/usb.png"); // Load from resource system
        if (!usbPixmap.isNull()) {
            usbImageLabel->setPixmap(usbPixmap.scaled(100, 100, Qt::KeepAspectRatio)); // Adjust size as needed
        } else {
            usbImageLabel->setText("usb.png not found!");
        }
        imageLayout->addWidget(usbImageLabel);

        // Wrap the image layout in a QWidget to center it
        QWidget *imageWidget = new QWidget(this);
        imageWidget->setLayout(imageLayout);
        layout->addWidget(imageWidget, 0, Qt::AlignCenter); // Center the widget

        // Add the title label with gold color
        QLabel *titleLabel = new QLabel("Apex Bootable Usb Creator v1.0", this);
        titleLabel->setStyleSheet("QLabel { color : teal; font-size: 20px; font-weight: bold; }");
        layout->addWidget(titleLabel, 0, Qt::AlignCenter);

        // Add the ISO selection button
        QPushButton *isoButton = new QPushButton("Select ISO File", this);
        isoButton->setStyleSheet("QPushButton { background-color: gold; color: black; }");
        layout->addWidget(isoButton);

        // Add the drive selection dropdown
        QComboBox *driveComboBox = new QComboBox(this);
        driveComboBox->setStyleSheet("QComboBox { background-color: white; color: black; }");
        layout->addWidget(driveComboBox);

        // Add a status label
        QLabel *statusLabel = new QLabel("Ready", this);
        statusLabel->setStyleSheet("QLabel { color : gold; font-size: 14px; }");
        layout->addWidget(statusLabel, 0, Qt::AlignCenter);

        // Add the progress bar (hidden initially)
        QProgressBar *progressBar = new QProgressBar(this);
        progressBar->setStyleSheet("QProgressBar { color : gold; background-color: white; }");
        progressBar->setRange(0, 100);
        progressBar->setValue(0);
        progressBar->setVisible(false); // Hidden initially
        layout->addWidget(progressBar);

        // Add the burn button
        QPushButton *burnButton = new QPushButton("Burn ISO to Drive", this);
        burnButton->setStyleSheet("QPushButton { background-color: gold; color: black; }");
        layout->addWidget(burnButton);

        // Add the Back button
        QPushButton *backButton = new QPushButton("Back to Main Application", this);
        backButton->setStyleSheet("QPushButton { background-color: gold; color: black; }");
        layout->addWidget(backButton);

        // Connect signals and slots
        connect(isoButton, &QPushButton::clicked, this, [this, driveComboBox, burnButton]() {
            QString isoPath = QFileDialog::getOpenFileName(this, "Select ISO File", QDir::homePath(), "ISO Files (*.iso)");
            if (!isoPath.isEmpty()) {
                isoFilePath = isoPath;
                QMessageBox::information(this, "ISO Selected", "ISO file selected: " + isoFilePath);
                populateDriveList(driveComboBox);
                burnButton->setEnabled(true);
            }
        });

        connect(burnButton, &QPushButton::clicked, this, [this, driveComboBox, progressBar, statusLabel, burnButton]() {
            if (isoFilePath.isEmpty() || driveComboBox->currentText().isEmpty()) {
                QMessageBox::warning(this, "Error", "Please select an ISO file and a drive.");
                return;
            }

            // Ask for sudo password before proceeding
            bool ok;
            QString password = QInputDialog::getText(this, "Authentication Required", "Enter sudo password:", QLineEdit::Password, "", &ok);
            if (!ok || password.isEmpty()) {
                QMessageBox::critical(this, "Error", "Password is required to continue.");
                return;
            }

            // Verify the sudo password
            QProcess verifyProcess;
            verifyProcess.start("sudo", QStringList() << "-S" << "echo" << "Password verified");
            verifyProcess.write(password.toUtf8() + "\n");
            verifyProcess.waitForFinished();
            if (verifyProcess.exitCode() != 0) {
                QMessageBox::critical(this, "Error", "Incorrect password. Operation will abort.");
                return;
            }

            // Hide the burn button and show the progress bar
            burnButton->setVisible(false);
            progressBar->setVisible(true);

            QString selectedDrive = driveComboBox->currentText().split(" ").first(); // Extract drive name (e.g., sda)

        // Wipe the drive using wipefs
        statusLabel->setText("Wiping drive...");
        QProcess *wipeProcess = new QProcess(this);
        wipeProcess->start("sudo", QStringList() << "-S" << "wipefs" << "--all" << QString("/dev/%1").arg(selectedDrive));
        wipeProcess->write(password.toUtf8() + "\n");
        if (!wipeProcess->waitForFinished()) {
            QMessageBox::critical(this, "Error", "Failed to wipe the drive.");
            wipeProcess->deleteLater();
            return;
        }
        if (wipeProcess->exitCode() != 0) {
            QMessageBox::critical(this, "Error", "Failed to wipe the drive.");
            wipeProcess->deleteLater();
            return;
        }

        // Burn the ISO using dd with status=progress
        statusLabel->setText("Burning ISO...");
        progressBar->setRange(0, 100); // Set range for determinate progress
        progressBar->setValue(0);     // Start at 0%

        QFile isoFile(isoFilePath);
        qint64 isoSize = isoFile.size(); // Get the size of the ISO file

        // Start the dd process
        burnProcess = new QProcess(this);
        burnProcess->setProcessChannelMode(QProcess::MergedChannels); // Combine stdout and stderr
        burnProcess->start("sudo", QStringList() << "-S" << "dd" << QString("if=%1").arg(isoFilePath) << QString("of=/dev/%1").arg(selectedDrive) << "bs=4M" << "status=progress");
        burnProcess->write(password.toUtf8() + "\n");
        burnProcess->waitForBytesWritten(); // Ensure the password is fully written

        // Connect to the readyReadStandardOutput signal to parse progress
        connect(burnProcess, &QProcess::readyReadStandardOutput, this, [this, progressBar, statusLabel, isoSize]() {
            QString output = burnProcess->readAllStandardOutput(); // Read the output
            QRegularExpression regex(R"((\d+)\s+bytes\s+\(.*\))"); // Match bytes written
                QRegularExpressionMatch match = regex.match(output);

                if (match.hasMatch()) {
                    bool ok;
                    qint64 bytesWritten = match.captured(1).toLongLong(&ok); // Extract bytes written
                    if (ok && isoSize > 0) {
                        int percentage = static_cast<int>((bytesWritten * 80) / isoSize); // Calculate percentage (up to 80%)
                        progressBar->setValue(percentage); // Update progress bar
                        statusLabel->setText(QString("Burning ISO: %1%").arg(percentage)); // Update status label
                    }
                }
        });

            // Handle process completion
            connect(burnProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this, progressBar, statusLabel]() {
                if (burnProcess->exitCode() == 0) {
                    progressBar->setValue(100); // Set to 100% on success
                    statusLabel->setText("Complete");
                    QMessageBox::information(this, "Success", "ISO burned successfully!");
                } else {
                    progressBar->setValue(0); // Reset progress
                    statusLabel->setText("Failed");
                    QMessageBox::critical(this, "Error", "Failed to burn ISO.");
                }
                burnProcess->deleteLater();
                burnProcess = nullptr; // Clear the pointer
            });
        });

        // Connect the Back button to close the USB tab and return to the main page
        connect(backButton, &QPushButton::clicked, this, [this]() {
            emit backToMainRequested(); // Emit signal to return to the main page
        });

        // Disable burn button initially
        burnButton->setEnabled(false);
    }

signals:
    void backToMainRequested(); // Signal to request going back to the main page

private:
    QString isoFilePath;
    QProcess *burnProcess;

    void populateDriveList(QComboBox *comboBox) {
        comboBox->clear();

        // Use lsblk to list USB drives and their names
        QProcess lsblkProcess;
        lsblkProcess.start("lsblk", QStringList() << "-o" << "NAME,SIZE,MODEL" << "-d" << "-n");
        lsblkProcess.waitForFinished();
        QString output = lsblkProcess.readAllStandardOutput();
        QStringList lines = output.split("\n", Qt::SkipEmptyParts);

        for (const QString &line : lines) {
            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() >= 2) {
                QString driveName = parts[0]; // e.g., sda
                QString driveSize = parts[1]; // e.g., 14.9G
                QString driveModel = parts.mid(2).join(" "); // e.g., SanDisk Ultra

                // Filter out system drives (e.g., root, boot) and partitions (e.g., sda1)
                if (!driveName.contains(QRegularExpression("\\d")) && !isSystemDrive(driveName)) {
                    QString displayText = QString("%1 - %2 (%3)").arg(driveName).arg(driveModel).arg(driveSize);
                    comboBox->addItem(displayText);
                }
            }
        }
    }

    bool isSystemDrive(const QString &driveName) {
        // Check if the drive is a system drive (e.g., root, boot)
        QProcess findmntProcess;
        findmntProcess.start("findmnt", QStringList() << "-n" << "-o" << "SOURCE" << "--target=/");
        findmntProcess.waitForFinished();
        QString rootDrive = findmntProcess.readAllStandardOutput().trimmed();
        return rootDrive.contains(driveName);
    }
};

#endif // USB_H
