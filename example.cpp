#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QGridLayout>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QProgressBar>
#include <QFile>
#include <QRegularExpression>
#include <QFileDialog>
#include <QScrollArea>
#include <QWindow>
#include <QGuiApplication>
#include <QScreen>
#include <QTemporaryDir>
#include "squashfs.h"
#include "usb.h"
#include "isocreator.h"

class ISOCreator : public QWidget {
public:
    ISOCreator(QWidget *parent = nullptr) : QWidget(parent), stackedWidget(new QStackedWidget(this)) {
        // Set the background color of the application to gold
        this->setStyleSheet("background-color: gold;");

        // Create the main layout and add the stacked widget
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(stackedWidget);

        // Create the main page
        QWidget *mainPage = createMainPage();
        stackedWidget->addWidget(mainPage);

        // Create the SquashFS tab
        QWidget *squashfsTab = createSquashfsTab();
        stackedWidget->addWidget(squashfsTab);

        // Create the ISO tab
        QWidget *isoTab = createIsoTab();
        stackedWidget->addWidget(isoTab);

        // Create the Apex Iso Tester tab
        QWidget *isoTesterTab = createIsoTesterTab();
        stackedWidget->addWidget(isoTesterTab);

        // Show the main page initially
        stackedWidget->setCurrentIndex(0);
    }

private:
    QStackedWidget *stackedWidget;
    QProcess *emulatorProcess = nullptr; // To manage the emulator process

    // Create the main page
    QWidget *createMainPage() {
        QWidget *mainPage = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(mainPage);

        // Create a horizontal layout for the top buttons
        QHBoxLayout *topButtonLayout = new QHBoxLayout();

        // Create the "Claudemods Iso Script News" button
        QPushButton *newsButton = new QPushButton("Apex Arch Iso Script News", mainPage);
        newsButton->setFixedSize(250, 40);
        newsButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        topButtonLayout->addWidget(newsButton);

        // Create the "Download Updates" button
        QPushButton *updatesButton = new QPushButton("Download Updates", mainPage);
        updatesButton->setFixedSize(250, 40);
        updatesButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(updatesButton, &QPushButton::clicked, this, &ISOCreator::downloadUpdates);
        topButtonLayout->addWidget(updatesButton);

        // Add the top button layout to the main layout
        mainLayout->addLayout(topButtonLayout);

        // Create a horizontal layout for the images
        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setSpacing(0); // No space between the images
        imageLayout->setContentsMargins(0, 0, 0, 0); // Remove margins

        // Load and display the ApexBrowser.png image
        QLabel *apexBrowserLabel = new QLabel(mainPage);
        QPixmap apexBrowserPixmap(":/images/ApexBrowser.png");
        if (!apexBrowserPixmap.isNull()) {
            apexBrowserLabel->setPixmap(apexBrowserPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qWarning() << "Failed to load ApexBrowser.png";
        }
        apexBrowserLabel->setAlignment(Qt::AlignCenter);
        imageLayout->addWidget(apexBrowserLabel);

        // Load and display the burn.png image (replacing machine.png)
        QLabel *burnLabel = new QLabel(mainPage);
        QPixmap burnPixmap(":/images/burn.png");
        if (!burnPixmap.isNull()) {
            burnLabel->setPixmap(burnPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qWarning() << "Failed to load burn.png";
        }
        burnLabel->setAlignment(Qt::AlignCenter);
        imageLayout->addWidget(burnLabel);

        // Center the image layout within the main layout
        QWidget *imageContainer = new QWidget();
        imageContainer->setLayout(imageLayout);
        imageContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        mainLayout->addWidget(imageContainer, 0, Qt::AlignCenter);

        // Add the pirate-ship.png image below the other two images
        QLabel *pirateShipLabel = new QLabel(mainPage);
        QPixmap pirateShipPixmap(":/images/pirate-ship.png");
        if (!pirateShipPixmap.isNull()) {
            pirateShipLabel->setPixmap(pirateShipPixmap.scaled(128, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qWarning() << "Failed to load pirate-ship.png";
        }
        pirateShipLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(pirateShipLabel, 0, Qt::AlignCenter);

        // Combine Title, Additional Text, Date/Time, and Disk Usage into a single QLabel
        QLabel *combinedLabel = new QLabel(mainPage);
        combinedLabel->setTextFormat(Qt::RichText); // Enable HTML formatting
        combinedLabel->setAlignment(Qt::AlignCenter);

        // Update the combined label initially
        updateCombinedLabel(combinedLabel);

        // Set up a timer to update the combined label every second
        QTimer *timer = new QTimer(mainPage);
        connect(timer, &QTimer::timeout, this, [this, combinedLabel]() { updateCombinedLabel(combinedLabel); });
        timer->start(1000); // Update every 1000 milliseconds (1 second)

        mainLayout->addWidget(combinedLabel);

        // Create a grid layout for the version labels
        QGridLayout *versionLayout = new QGridLayout();

        // Create and style the SquashFS version label (top-left)
        QLabel *squashfsVersionLabel = new QLabel("Apex Squashfs Creator v1.05.3", mainPage);
        QFont versionFont("Arial", 12, QFont::Bold);
        squashfsVersionLabel->setFont(versionFont);
        squashfsVersionLabel->setStyleSheet("color: blue;");
        squashfsVersionLabel->setAlignment(Qt::AlignLeft);
        versionLayout->addWidget(squashfsVersionLabel, 0, 0);

        // Add Apex Iso Tester v1.0 below SquashFS version (bottom-left)
        QLabel *isoTesterVersionLabel = new QLabel("Apex Iso Tester v1.0", mainPage);
        isoTesterVersionLabel->setFont(versionFont);
        isoTesterVersionLabel->setStyleSheet("color: blue;");
        isoTesterVersionLabel->setAlignment(Qt::AlignLeft);
        versionLayout->addWidget(isoTesterVersionLabel, 1, 0);

        // Create and style the ISO version label (top-right)
        QLabel *isoVersionLabel = new QLabel("Apex ISO Creator v1.03.1", mainPage);
        isoVersionLabel->setFont(versionFont);
        isoVersionLabel->setStyleSheet("color: blue;");
        isoVersionLabel->setAlignment(Qt::AlignRight);
        versionLayout->addWidget(isoVersionLabel, 0, 2); // Moved to column 2 (far right)

        // Add Apex Bootable Usb Creator v1.0 below ISO version (bottom-right)
        QLabel *usbVersionLabel = new QLabel("Apex Bootable Usb Creator v1.0", mainPage);
        usbVersionLabel->setFont(versionFont);
        usbVersionLabel->setStyleSheet("color: blue;");
        usbVersionLabel->setAlignment(Qt::AlignRight);
        versionLayout->addWidget(usbVersionLabel, 1, 2); // Moved to column 2 (far right)

        // Add Apex Iso Creator Setup Script v1.01 in the center
        QLabel *setupScriptLabel = new QLabel("Apex Iso Creator Setup Script v1.01", mainPage);
        setupScriptLabel->setFont(versionFont);
        setupScriptLabel->setStyleSheet("color: blue;");
        setupScriptLabel->setAlignment(Qt::AlignCenter);
        versionLayout->addWidget(setupScriptLabel, 0, 1, 2, 1); // Span across two rows and center

        // Add the version layout to the main layout
        mainLayout->addLayout(versionLayout);

        // Create a grid layout for the remaining buttons
        QGridLayout *buttonGridLayout = new QGridLayout();

        // Create the "Guide And Setup Scripts" button
        QPushButton *setupScriptsButton = new QPushButton("Guide And Setup Scripts", mainPage);
        setupScriptsButton->setFixedSize(250, 40);
        setupScriptsButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(setupScriptsButton, &QPushButton::clicked, this, &ISOCreator::openGuideAndSetupScriptsDialog);
        buttonGridLayout->addWidget(setupScriptsButton, 0, 0);

        // Create the "Creator Tools" button
        QPushButton *creatorToolsButton = new QPushButton("Apex Creator Tools", mainPage);
        creatorToolsButton->setFixedSize(250, 40);
        creatorToolsButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(creatorToolsButton, &QPushButton::clicked, this, &ISOCreator::openCreatorToolsDialog);
        buttonGridLayout->addWidget(creatorToolsButton, 0, 1);

        // Create the "Exit" button and place it in the center
        QPushButton *exitButton = new QPushButton("Exit", mainPage);
        exitButton->setFixedSize(250, 40);
        exitButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
        buttonGridLayout->addWidget(exitButton, 1, 0, 1, 2, Qt::AlignCenter); // Center alignment

        // Add the grid layout to the main layout
        mainLayout->addLayout(buttonGridLayout);

        return mainPage;
    }

    // Create the SquashFS tab
    QWidget *createSquashfsTab() {
        QWidget *squashfsTab = new QWidget();
        QVBoxLayout *squashfsLayout = new QVBoxLayout(squashfsTab);
        SquashFSGui *squashfsGui = new SquashFSGui(stackedWidget); // Pass the stacked widget to SquashFSGui
        squashfsLayout->addWidget(squashfsGui);
        return squashfsTab;
    }

    // Create the ISO tab
    QWidget *createIsoTab() {
        QWidget *isoTab = new QWidget();
        QVBoxLayout *isoLayout = new QVBoxLayout(isoTab);

        // Create the ISOCreatorTab widget
        ISOCreatorTab *isoCreatorTab = new ISOCreatorTab(isoTab);
        isoLayout->addWidget(isoCreatorTab);

        // Connect the backToMainRequested signal to switch back to the main page
        connect(isoCreatorTab, &ISOCreatorTab::backToMainRequested, this, [this, isoTab]() {
            stackedWidget->removeWidget(isoTab); // Remove the ISO tab
            stackedWidget->setCurrentIndex(0);   // Switch to the main page
            delete isoTab;                       // Clean up the ISO tab
        });

        return isoTab;
    }

    // Create the Apex Iso Tester tab
    QWidget *createIsoTesterTab() {
        QWidget *isoTesterTab = new QWidget();
        QVBoxLayout *isoTesterLayout = new QVBoxLayout(isoTesterTab);

        // Add the images (ApexBrowser.png and machine.png) centered with no space between them
        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setSpacing(0); // No space between images
        imageLayout->setContentsMargins(0, 0, 0, 0); // Remove margins

        // Load and display ApexBrowser.png
        QLabel *apexBrowserLabel = new QLabel(isoTesterTab);
        QPixmap apexBrowserPixmap(":/images/ApexBrowser.png");
        if (!apexBrowserPixmap.isNull()) {
            apexBrowserLabel->setPixmap(apexBrowserPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qWarning() << "Failed to load ApexBrowser.png";
        }
        apexBrowserLabel->setAlignment(Qt::AlignCenter);
        imageLayout->addWidget(apexBrowserLabel);

        // Load and display machine.png
        QLabel *machineLabel = new QLabel(isoTesterTab);
        QPixmap machinePixmap(":/images/machine.png");
        if (!machinePixmap.isNull()) {
            machineLabel->setPixmap(machinePixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qWarning() << "Failed to load machine.png";
        }
        machineLabel->setAlignment(Qt::AlignCenter);
        imageLayout->addWidget(machineLabel);

        // Add the image layout to the ISO Tester tab
        isoTesterLayout->addLayout(imageLayout);

        // Add the text "Apex Iso Tester v1.0" in blue above the buttons
        QLabel *isoTesterLabel = new QLabel("Apex Iso Tester v1.0", isoTesterTab);
        isoTesterLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: blue;");
        isoTesterLabel->setAlignment(Qt::AlignCenter);
        isoTesterLayout->addWidget(isoTesterLabel);

        // Add a button to select the ISO file
        QPushButton *selectISOButton = new QPushButton("Select ISO File", isoTesterTab);
        selectISOButton->setFixedSize(250, 40);
        selectISOButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        isoTesterLayout->addWidget(selectISOButton, 0, Qt::AlignCenter);

        // Add a button to start the virtual machine
        QPushButton *startVMButton = new QPushButton("Start Virtual Machine", isoTesterTab);
        startVMButton->setFixedSize(250, 40);
        startVMButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        startVMButton->setEnabled(false); // Disabled until an ISO is selected
        isoTesterLayout->addWidget(startVMButton, 0, Qt::AlignCenter);

        // Add a back button to return to the main page
        QPushButton *backButton = new QPushButton("Back to Main Application", isoTesterTab);
        backButton->setFixedSize(250, 40);
        backButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(backButton, &QPushButton::clicked, this, [this, isoTesterTab]() {
            stackedWidget->removeWidget(isoTesterTab); // Remove the Apex Iso Tester tab
            stackedWidget->setCurrentIndex(0);         // Switch to the main page
            delete isoTesterTab;                       // Clean up the tab
        });
        isoTesterLayout->addWidget(backButton, 0, Qt::AlignCenter);

        // Connect the select ISO button to open a file dialog
        connect(selectISOButton, &QPushButton::clicked, this, [this, startVMButton]() {
            QString isoFilePath = QFileDialog::getOpenFileName(this, "Select ISO File", "", "ISO Files (*.iso)");
            if (!isoFilePath.isEmpty()) {
                startVMButton->setEnabled(true); // Enable the Start VM button
                startVMButton->setProperty("isoFilePath", isoFilePath); // Store the ISO file path
            }
        });

        // Connect the Start VM button to run the emulator
        connect(startVMButton, &QPushButton::clicked, this, [this, isoTesterTab, startVMButton]() {
            QString isoFilePath = startVMButton->property("isoFilePath").toString();
            if (!isoFilePath.isEmpty()) {
                // Create a new widget for the emulator display
                QWidget *emulatorDisplay = new QWidget();
                QVBoxLayout *emulatorLayout = new QVBoxLayout(emulatorDisplay);

                // Add a "Shutdown" button to stop the emulator
                QPushButton *shutdownButton = new QPushButton("Shutdown", emulatorDisplay);
                shutdownButton->setFixedSize(250, 40);
                shutdownButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
                connect(shutdownButton, &QPushButton::clicked, this, [this, emulatorDisplay]() {
                    if (emulatorProcess) {
                        emulatorProcess->terminate(); // Stop the emulator
                        emulatorProcess->waitForFinished();
                        delete emulatorProcess;
                        emulatorProcess = nullptr;
                    }
                    stackedWidget->removeWidget(emulatorDisplay); // Remove the emulator display
                    stackedWidget->setCurrentIndex(0);            // Switch to the main page
                    delete emulatorDisplay;                       // Clean up the display
                });
                emulatorLayout->addWidget(shutdownButton, 0, Qt::AlignCenter);

                // Start the emulator process with a graphical display
                emulatorProcess = new QProcess(this);
                emulatorProcess->setProgram("qemu-system-x86_64");
                emulatorProcess->setArguments({
                    "-m", "4000",
                    "-smp", "2",
                    "-accel", "kvm",
                    "-cdrom", isoFilePath,
                    "-display", "gtk" // Use Qt for embedded display
                });
                emulatorProcess->start();

                // Add the emulator display to the stacked widget
                stackedWidget->addWidget(emulatorDisplay);
                stackedWidget->setCurrentWidget(emulatorDisplay); // Switch to the emulator display
            }
        });

        return isoTesterTab;
    }

    void downloadUpdates() {
        QDesktopServices::openUrl(QUrl("https://www.pling.com/p/2204600"));
    }

    void updateCombinedLabel(QLabel *combinedLabel) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("dd-MM-yyyy hh:mm:ss"); // UK date format

        QProcess process;
        process.start("df", QStringList() << "-h" << "/");
        process.waitForFinished();

        QString output = process.readAllStandardOutput();
        QStringList lines = output.split("\n");

        QString usedSpace;
        QString availableSpace;

        // Parse the output to extract used and available space for the root filesystem
        for (const QString &line : lines) {
            if (line.contains("/")) { // Look for the root filesystem
                QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts); // Use QRegularExpression
                if (parts.size() >= 5 && parts.last() == "/") { // Ensure the line corresponds to the root filesystem
                    usedSpace = parts[2];      // Used space
                    availableSpace = parts[3]; // Available space
                }
                break;
            }
        }

        // Format the combined label with HTML to preserve individual font sizes, colors, and alignment
        combinedLabel->setText(QString(
            "<span style='font-size: 18px; font-weight: bold; color: blue;'>Sailing the 7 seas like Penguin's Eggs, Remastersys, Refracta, Systemback and father Knoppix!</span><br>"
            "<span style='font-size: 20px; font-weight: bold; color: blue;'>Apex Arch Iso Creator Gui Beta v1.0 Build 20-02-2025</span><br>"
            "<span style='font-size: 16px; font-weight: bold; color: blue;'>Date/Time: %1</span><br>"
            "<span style='font-size: 16px; font-weight: bold; color: blue;'>Used System Space: %2</span><br>"
            "<span style='font-size: 16px; font-weight: bold; color: blue;'>Available System Space: %3</span>")
        .arg(dateTimeString)
        .arg(usedSpace.isEmpty() ? "N/A" : usedSpace)
        .arg(availableSpace.isEmpty() ? "N/A" : availableSpace));
    }

    void openGuideAndSetupScriptsDialog() {
        // Path to the embedded .zip file in the Qt resource system
        QString zipPath = ":/config/scripts.zip";

        // Create a temporary directory to extract the .zip file
        QTemporaryDir tempDir;
        if (!tempDir.isValid()) {
            QMessageBox::critical(this, "Error", "Failed to create a temporary directory.");
            return;
        }

        // Copy the embedded .zip file to the temporary directory
        QString tempZipPath = tempDir.path() + "/scripts.zip";
        QFile embeddedZip(zipPath);
        if (!embeddedZip.copy(tempZipPath)) {
            QMessageBox::critical(this, "Error", "Failed to copy the embedded .zip file to the temporary directory.");
            return;
        }

        // Extract the .zip file using the 'unzip' command
        QProcess unzipProcess;
        unzipProcess.setProgram("unzip");
        unzipProcess.setArguments({"-d", tempDir.path(), tempZipPath});
        unzipProcess.start();
        if (!unzipProcess.waitForFinished()) {
            QMessageBox::critical(this, "Error", "Failed to extract the .zip file: " + unzipProcess.errorString());
            return;
        }

        // Path to the extracted SetupScripts binary
        QString setupScriptsPath = tempDir.path() + "/SetupScripts.bin";

        // Check if the extracted binary exists
        QFile setupScriptsFile(setupScriptsPath);
        if (!setupScriptsFile.exists()) {
            QMessageBox::critical(this, "Error", "The extracted binary 'SetupScripts' was not found.");
            return;
        }

        // Make the extracted binary executable
        if (!setupScriptsFile.setPermissions(QFileDevice::ExeUser | QFileDevice::ReadUser | QFileDevice::WriteUser)) {
            QMessageBox::critical(this, "Error", "Failed to set executable permissions for the binary.");
            return;
        }

        // Execute the binary using QProcess
        QProcess process;
        process.setProgram(setupScriptsPath);
        process.startDetached();

        // Optionally, notify the user that the binary is being executed
        QMessageBox::information(this, "Info", "Executing the extracted binary...");
    }

    void openCreatorToolsDialog() {
        // Create a dialog for Creator Tools
        QDialog *creatorToolsDialog = new QDialog(this);
        creatorToolsDialog->setWindowTitle("Creator Tools");
        QVBoxLayout *dialogLayout = new QVBoxLayout(creatorToolsDialog);

        // Create the "Apex Squashfs Creator" button
        QPushButton *squashfsButton = new QPushButton("Apex Squashfs Creator", creatorToolsDialog);
        squashfsButton->setFixedSize(250, 40);
        squashfsButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(squashfsButton, &QPushButton::clicked, this, [this, creatorToolsDialog]() {
            creatorToolsDialog->close(); // Close the dialog
            stackedWidget->setCurrentIndex(1); // Switch to SquashFS tab
        });
        dialogLayout->addWidget(squashfsButton, 0, Qt::AlignCenter);

        // Create the "Apex Iso Creator" button
        QPushButton *isoButton = new QPushButton("Apex Iso Creator", creatorToolsDialog);
        isoButton->setFixedSize(250, 40);
        isoButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(isoButton, &QPushButton::clicked, this, [this, creatorToolsDialog]() {
            creatorToolsDialog->close(); // Close the dialog
            stackedWidget->setCurrentIndex(2); // Switch to ISO tab
        });
        dialogLayout->addWidget(isoButton, 0, Qt::AlignCenter);

        // Create the "Apex Iso Tester" button
        QPushButton *isoTesterButton = new QPushButton("Apex Iso Tester", creatorToolsDialog);
        isoTesterButton->setFixedSize(250, 40);
        isoTesterButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(isoTesterButton, &QPushButton::clicked, this, [this, creatorToolsDialog]() {
            creatorToolsDialog->close(); // Close the dialog
            stackedWidget->setCurrentIndex(3); // Switch to Apex Iso Tester tab
        });
        dialogLayout->addWidget(isoTesterButton, 0, Qt::AlignCenter);

        // Create the "Apex Bootable Usb Creator" button
        QPushButton *usbButton = new QPushButton("Apex Bootable Usb Creator", creatorToolsDialog);
        usbButton->setFixedSize(250, 40);
        usbButton->setStyleSheet("background-color: teal; color: gold; font-size: 14px;");
        connect(usbButton, &QPushButton::clicked, this, [this, creatorToolsDialog]() {
            creatorToolsDialog->close(); // Close the dialog
            QWidget *usbTab = createUsbTab(); // Create the USB tab
            stackedWidget->addWidget(usbTab); // Add the USB tab to the stacked widget
            stackedWidget->setCurrentWidget(usbTab); // Switch to the USB tab
        });
        dialogLayout->addWidget(usbButton, 0, Qt::AlignCenter);

        // Show the dialog
        creatorToolsDialog->exec();
    }

    QWidget *createUsbTab() {
        QWidget *usbTab = new QWidget();
        QVBoxLayout *usbLayout = new QVBoxLayout(usbTab);
        ApexBootableUsbCreator *usbCreator = new ApexBootableUsbCreator(); // Create the USB creator widget
        usbLayout->addWidget(usbCreator);

        // Connect the backToMainRequested signal to switch back to the main page
        connect(usbCreator, &ApexBootableUsbCreator::backToMainRequested, this, [this, usbTab]() {
            stackedWidget->removeWidget(usbTab); // Remove the USB tab
            stackedWidget->setCurrentIndex(0);   // Switch to the main page
            delete usbTab;                       // Clean up the USB tab
        });

        return usbTab;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ISOCreator isoCreator;
    isoCreator.show();
    return app.exec();
}
