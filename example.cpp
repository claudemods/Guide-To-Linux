#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>
#include "Squashfs.h" // Include the SquashFS header file
#include "IsoCreator.h" // Include the ISO creator header file
#include "SetupScripts.h" // Include the Setup Scripts header file

// Qt includes for QRC resource handling
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Function to set text color using ANSI escape codes
void setColor(const std::string &color) {
    std::cout << color;
}

// Function to check if a file exists
bool fileExists(const std::string &filePath) {
    std::ifstream file(filePath);
    return file.good();
}

// Function to print the contents of a file
void printFileContents(const std::string &filePath, const std::string &message) {
    if (fileExists(filePath)) {
        setColor("\033[32m"); // Green color
        std::cout << message << "\n";
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    } else {
        setColor("\033[31m"); // Red color
        std::cout << message << "\n";
    }
    setColor("\033[0m"); // Reset color
}

// Function to print the status of vmlinuz and initramfs files
void printVmlinuzInitramfsStatus() {
    std::string vmlinuzFilePath = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/vmlinuz-init-time-generated.txt";
    std::string imageLocationFilePath = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/Arch-Image-location.txt";
    if (fileExists(vmlinuzFilePath)) {
        setColor("\033[32m"); // Green color
        std::ifstream vmlinuzFile(vmlinuzFilePath);
        std::string dateTime;
        if (std::getline(vmlinuzFile, dateTime)) {
            size_t atPos = dateTime.find("at: ");
            if (atPos != std::string::npos) {
                std::string extractedDateTime = dateTime.substr(atPos + 4); // Extract everything after "at: "
                std::cout << "Vmlinuz And Initramfs Copied/Generated " << extractedDateTime << "\n";
            } else {
                std::cout << "Vmlinuz And Initramfs Copied/Generated " << dateTime << "\n";
            }
        }
    } else {
        if (fileExists(imageLocationFilePath)) {
            setColor("\033[32m"); // Green color
            std::cout << "Copy And Generate vmlinuz and Initramfs With Option 3\n";
        } else {
            setColor("\033[31m"); // Red color
            std::cout << "Copy And Generate vmlinuz and Initramfs With Option 3\n";
        }
    }
    setColor("\033[0m"); // Reset color
}

// Function to clear the screen while keeping the ASCII art and title visible
void clearScreenWithHeader() {
    system("clear"); // Linux-specific command to clear the terminal
    setColor("\033[31m"); // Red color
    std::cout << R"(
░█████╗░██╗░░░░░░█████╗░██║░░░██╗██████╗░███████╗███╗░░░███╗░█████╗░██████╗░░██████╗
██╔══██╗██║░░░░░██╔══██╗██║░░░██║██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗██╔════╝
██║░░╚═╝██║░░░░░███████║██║░░░██║██║░░██║█████╗░░██╔████╔██║██║░░██║██║░░██║╚█████╗░
██║░░██╗██║░░░░░██╔══██║██║░░░██║██║░░██║██╔══╝░░██║╚██╔╝██║██║░░██║██║░░██║░╚═══██╗
╚█████╔╝███████╗██║░░██║╚██████╔╝██████╔╝███████╗██║░╚═╝░██║╚█████╔╝██████╔╝██████╔╝
░╚════╝░╚══════╝╚═╝░░░░░░╚═════╝░╚═════╝░╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═════╝░╚═════╝░
)" << std::endl;

setColor("\033[38;2;255;215;0m"); // Gold color
std::cout << "Hello, welcome to Apex Arch Iso Creator v1.01 Build 18-03-2025\n\n";
std::cout << "Sailing the 7 seas like Penguin's Eggs, Remastersys, Refracta, Systemback, and father Knoppix!\n\n";

auto now = std::time(nullptr);
auto localTime = *std::localtime(&now);
std::cout << "Date and Time: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";

FILE* pipe = popen("df -h / | awk 'NR==2 {print $3, $4}'", "r");
if (pipe) {
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    std::istringstream iss(result);
    std::string usedSize, availableSize;
    iss >> usedSize >> availableSize;
    std::cout << "Used System Space: " << usedSize << "\n";
    std::cout << "Available System Space: " << availableSize << "\n\n";
} else {
    std::cout << "Failed to retrieve filesystem information.\n\n";
}

std::string imageLocationFilePath = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/Arch-Image-location.txt";
if (fileExists(imageLocationFilePath)) {
    setColor("\033[32m"); // Green color
    std::ifstream imageLocationFile(imageLocationFilePath);
    std::string imageLocation;
    while (std::getline(imageLocationFile, imageLocation)) {
        std::cout << "Current Build Image Location By Choice: " << imageLocation << "\n";
    }
} else {
    setColor("\033[31m"); // Red color
    std::cout << "Build Image Not Found, press option 3 to download and save Build Image.\n";
}

std::string isoNameFilePath = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/isoname.txt";
if (fileExists(isoNameFilePath)) {
    setColor("\033[32m"); // Green color
    std::ifstream isoNameFile(isoNameFilePath);
    std::string isoName;
    while (std::getline(isoNameFile, isoName)) {
        std::cout << "Current Iso Name By Choice: " << isoName << "\n";
    }
} else {
    setColor("\033[31m"); // Red color
    std::cout << "Iso Name Not Found, press option 3 to create ISO name.\n";
}

printVmlinuzInitramfsStatus();

setColor("\033[38;2;255;215;0m"); // Gold color
std::cout << "Apex Arch Iso Creator v1.0 Main Menu\n\n";
setColor("\033[0m"); // Reset color
}

// Function to download and display the news file
void downloadAndDisplayNews() {
    if (fileExists("news.txt")) {
        if (std::remove("news.txt") != 0) {
            setColor("\033[31m");
            std::cout << "Failed to delete existing new.txt file!\n";
            setColor("\033[0m");
            return;
        }
    }
    std::string url = "https://sourceforge.net/projects/claudemods/files/App-Backend/claudemods-iso-creator-tools/ApexArchIsoCreator/ArchNews/readme.txt/download";
    std::string command = "eval 'printf \"\\e[38;2;255;215;0m\"; wget -O news.txt \"" + url + "\" && cat news.txt; printf \"\\e[0m\"'";
    system(command.c_str());
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Function to display the main menu
void displayMenu() {
    clearScreenWithHeader();
    setColor("\033[38;2;255;215;0m");
    std::cout << "1. Claudemods Iso Script News\n";
    std::cout << "2. Guide\n"; // New option
    std::cout << "3. Download Updates\n";
    std::cout << "4. Setup Scripts\n";
    std::cout << "5. Creator Tools\n";
    std::cout << "6. Exit\n"; // Shifted Exit to option 6
    std::cout << "\nEnter your choice: ";
    setColor("\033[0m");
}

// Function to display the Setup Scripts sub-menu
void displaySetupScriptsMenu() {
    clearScreenWithHeader();
    setColor("\033[38;2;255;215;0m");
    std::cout << "=== Setup Scripts ===\n\n";
    std::cout << "1. Manual Setup Script\n";
    std::cout << "2. Back to Main Menu\n"; // Removed the automatic option
    std::cout << "\nEnter your choice: ";
    setColor("\033[0m");
}

// Function to handle Setup Scripts sub-menu options
void handleSetupScriptsMenu() {
    int choice;
    SetupScripts setupScripts; // Create an instance of the SetupScripts class
    while (true) {
        displaySetupScriptsMenu();
        std::cin >> choice;
        setColor("\033[38;2;255;215;0m");
        switch (choice) {
            case 1:
                std::cout << "\nRunning Manual Setup Script...\n";
                setupScripts.main_menu(); // Use the SetupScripts class to handle the setup
                break;
            case 2:
                return; // Go back to the main menu
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
                break;
        }
        setColor("\033[0m");
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}

// Function to display the Creator Tools sub-menu
void displayCreatorToolsMenu() {
    clearScreenWithHeader();
    setColor("\033[38;2;255;215;0m");
    std::cout << "=== Creator Tools ===\n\n";
    std::cout << "1. Claudemods SquashFS Creator\n";
    std::cout << "2. Claudemods ISO Creator\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "\nEnter your choice: ";
    setColor("\033[0m");
}

// Function to handle Creator Tools sub-menu options
void handleCreatorToolsMenu() {
    int choice;
    while (true) {
        displayCreatorToolsMenu();
        std::cin >> choice;
        setColor("\033[38;2;255;215;0m");
        switch (choice) {
            case 1:
                std::cout << "\nRunning Apex SquashFS Creator...\n";
                runSquashFSTools(); // Call the SquashFS tools function from Squashfs.h
                break;
            case 2:
                std::cout << "\nRunning Apex ISO Creator...\n";
                iso_creator_menu(); // Call the ISO creator menu function from IsoCreator.h
                break;
            case 3:
                return;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
                break;
        }
        setColor("\033[0m");
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}

// Function to display the contents of Guide.txt (embedded via QRC)
void displayGuide() {
    QFile guideFile(":/Guide.txt");
    if (!guideFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Failed to open Guide.txt!\n";
        return;
    }

    QTextStream in(&guideFile);
    while (!in.atEnd()) {
        std::cout << in.readLine().toStdString() << "\n";
    }

    guideFile.close();
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Function to handle main menu options
void handleMenuOption(int choice) {
    setColor("\033[38;2;255;215;0m");
    switch (choice) {
        case 1:
            downloadAndDisplayNews();
            break;
        case 2: // New option to display Guide.txt
            displayGuide();
            break;
        case 3:
        {
            std::string url = "https://www.pling.com/p/2261487/";
            std::string command = "xdg-open " + url; // Open the URL in the default browser
            system(command.c_str());
            std::cout << "\nOpening update page in your default browser...\n";
        }
        break;
        case 4:
            handleSetupScriptsMenu();
            break;
        case 5:
            handleCreatorToolsMenu();
            break;
        case 6: // Updated exit option
            std::cout << "\nExiting...\n";
            exit(0);
        default:
            std::cout << "\nInvalid choice! Please try again.\n";
            break;
    }
    setColor("\033[0m");
}

int main() {
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;
        handleMenuOption(choice);
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
    return 0;
}
