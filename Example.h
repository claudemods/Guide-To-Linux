#ifndef SETUPSCRIPTS_H
#define SETUPSCRIPTS_H

#include <QFile>
#include <QByteArray>
#include <QProcess>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <unistd.h> // For chdir
#include <sys/stat.h> // For chmod

namespace fs = std::filesystem;

// ANSI escape codes for colors
constexpr auto SETUP_RED = "\033[38;2;255;0;0m";    // Red color (RGB: 255, 0, 0)
constexpr auto SETUP_GOLD = "\033[38;2;255;215;0m"; // Gold color (RGB: 255, 215, 0)
constexpr auto SETUP_NC = "\033[0m";                // No Color (reset)

class SetupScripts {
private:
    std::string install_location;

    // Helper function to format messages with color
    std::string format_message(const std::string& color, const std::string& message) {
        std::stringstream ss;
        ss << color << message << SETUP_NC;
        return ss.str();
    }

    // Function to execute a command and print its output in gold
    bool execute_gold(const std::string& command, bool exclude_gold = false, bool real_time = false) {
        if (real_time) {
            int status = system(command.c_str());
            if (status != 0) {
                std::cerr << format_message(SETUP_GOLD, "Error: Command failed: " + command + "\n");
                return false;
            }
            return true;
        } else {
            std::string result;
            char buffer[128];
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
            if (!pipe) {
                std::cerr << format_message(SETUP_GOLD, "Error: Failed to execute command: " + command + "\n");
                return false;
            }
            while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
                result += buffer;
            }
            if (exclude_gold) {
                std::cout << result;
            } else {
                std::cout << format_message(SETUP_GOLD, result);
            }
            return true;
        }
    }

    // Function to log messages (gold in terminal, default color in log file)
    void log_message(const std::string& message) {
        if (install_location.empty()) {
            std::cerr << format_message(SETUP_GOLD, "Error: install_location is not set.\n");
            exit(1);
        }
        std::string log_file = install_location + "/build-image-arch/.disk/Archprocess.txt";
        time_t now = time(nullptr);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        // Print to terminal in gold color
        std::cout << format_message(SETUP_GOLD, std::string(timestamp) + " - " + message + "\n");
        // Ensure the .disk directory exists before writing to the log file
        fs::create_directories(fs::path(log_file).parent_path());
        // Append to log file in default color
        std::ofstream log_stream(log_file, std::ios::app);
        if (log_stream.is_open()) {
            log_stream << std::string(timestamp) + " - " + message + "\n";
        } else {
            std::cerr << format_message(SETUP_GOLD, "Error: Failed to open log file: " + log_file + "\n");
        }
    }

    // Function to save installation location to files
    void save_installation_location(const std::string& location) {
        std::string image_location_file = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/Arch-Image-location.txt";
        fs::create_directories(fs::path(image_location_file).parent_path());
        std::ofstream image_stream(image_location_file);
        if (image_stream.is_open()) {
            image_stream << location << "/build-image-arch\n";
        } else {
            std::cerr << format_message(SETUP_GOLD, "Error: Failed to save installation location to " + image_location_file + "\n");
        }
        std::string clone_directory_file = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/CloneDirectory.txt";
        fs::create_directories(fs::path(clone_directory_file).parent_path());
        std::ofstream clone_stream(clone_directory_file);
        if (clone_stream.is_open()) {
            clone_stream << location << "\n";
        } else {
            std::cerr << format_message(SETUP_GOLD, "Error: Failed to save clone directory to " + clone_directory_file + "\n");
        }
    }

    // Function to read installation location from Arch-Image-location.txt
    std::string read_installation_location() {
        std::string image_location_file = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/Arch-Image-location.txt";
        if (!fs::exists(image_location_file)) {
            std::cerr << format_message(SETUP_GOLD, "Error: " + image_location_file + " not found. Please run option 1 first.\n");
            return "";
        }
        std::ifstream image_stream(image_location_file);
        std::string location;
        if (image_stream.is_open()) {
            std::getline(image_stream, location);
        }
        return location;
    }

    // Function to set permissions for a directory (editable and deletable by the user)
    void set_user_permissions(const std::string& path) {
        if (chmod(path.c_str(), 0755) != 0) { // 0755 = rwxr-xr-x
            log_message("Error: Failed to set permissions for " + path);
            exit(1);
        }
        log_message("Set permissions for " + path + " to 0755 (user editable/deletable)");
    }

public:
    // Function to install build-image-arch
    void install_build_image_arch() {
        std::cout << format_message(SETUP_GOLD, "Enter the location to install build-image-arch:\n");
        std::getline(std::cin, install_location);
        install_location = fs::absolute(install_location).string();

        if (install_location.empty()) {
            std::cerr << format_message(SETUP_GOLD, "Error: Installation location cannot be empty.\n");
            exit(1);
        }

        if (!fs::exists(install_location)) {
            std::cout << format_message(SETUP_GOLD, "Creating directory: " + install_location + "\n");
            fs::create_directories(install_location);
            set_user_permissions(install_location); // Ensure the directory is editable/deletable
        }

        if (chdir(install_location.c_str()) != 0) {
            std::cerr << format_message(SETUP_GOLD, "Error: Failed to change directory to " + install_location + "\n");
            exit(1);
        }

        if (fs::exists("build-image-arch")) {
            log_message("build-image-arch directory found in the current directory. Skipping download and extraction.");
        } else {
            std::cout << format_message(SETUP_GOLD, "Extracting embedded build-image-arch.zip...\n");

            // Load the embedded ZIP file from resources
            QFile zipResource(":/build-image-arch.zip");
            if (!zipResource.open(QIODevice::ReadOnly)) {
                log_message("Error: Failed to open embedded ZIP file.");
                exit(1);
            }

            QByteArray zipData = zipResource.readAll();
            zipResource.close();

            // Save the ZIP file to disk
            QString tempZipPath = QString::fromStdString(install_location) + "/download.zip";
            QFile tempZipFile(tempZipPath);
            if (!tempZipFile.open(QIODevice::WriteOnly)) {
                log_message("Error: Failed to create temporary ZIP file at " + tempZipPath.toStdString());
                exit(1);
            }
            tempZipFile.write(zipData);
            tempZipFile.close();

            // Unzip the file
            if (!execute_gold("unzip -q " + tempZipPath.toStdString() + " -d " + install_location, false, false)) {
                log_message("Error: Failed to extract build-image-arch.zip");
                exit(1);
            }

            // Remove the temporary ZIP file
            if (!QFile::remove(tempZipPath)) {
                log_message("Warning: Failed to remove temporary ZIP file at " + tempZipPath.toStdString());
            }

            set_user_permissions(install_location + "/build-image-arch"); // Ensure the directory is editable/deletable
        }

        save_installation_location(install_location);
    }

    // Function to download dependencies
    void download_dependencies() {
        std::cout << format_message(SETUP_GOLD, "Installing required packages...\n");
        std::vector<std::string> packages = {
            "arch-install-scripts", "bash-completion", "dosfstools", "erofs-utils", "findutils", "git", "grub", "jq", "libarchive",
            "libisoburn", "lsb-release", "lvm2", "mkinitcpio-archiso", "mkinitcpio-nfs-utils", "mtools", "nbd", "pacman-contrib",
            "parted", "procps-ng", "pv", "python", "rsync", "sshfs", "syslinux", "xdg-utils", "bash-completion",
            "zsh-completions", "kernel-modules-hook", "unzip", "nano"
        };
        std::string package_list;
        for (const auto& pkg : packages) {
            package_list += pkg + " ";
        }
        if (!execute_gold("sudo pacman -Sy --needed " + package_list)) {
            log_message("Error: Failed to install required packages");
            exit(1);
        }
        log_message("Required packages installed successfully.");

        // Ask if user wants to install optional dependencies
        std::cout << format_message(SETUP_GOLD, "Do you want to install optional dependencies (gnome-boxes, virt-manager)? (yes/no): ");
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes" || response == "y") {
            std::cout << format_message(SETUP_GOLD, "Installing optional packages...\n");
            if (!execute_gold("sudo pacman -Sy --needed gnome-boxes virt-manager")) {
                log_message("Error: Failed to install optional packages");
                exit(1);
            }
            log_message("Optional packages installed successfully.");
        } else {
            log_message("Skipping installation of optional packages.");
        }
    }

    // Function to copy vmlinuz and generate initramfs
    void copy_vmlinuz_and_generate_initramfs() {
        install_location = read_installation_location();
        if (install_location.empty()) {
            std::cerr << format_message(SETUP_GOLD, "Error: install_location is not set. Please run option 1 first.\n");
            return;
        }
        std::string live_location = install_location + "/live";

        // Check if the live folder exists and delete its contents if it does
        if (fs::exists(live_location)) {
            std::cout << format_message(SETUP_GOLD, "Cleaning up existing files in the live folder...\n");
            for (const auto& entry : fs::directory_iterator(live_location)) {
                try {
                    fs::remove_all(entry.path()); // Delete all files and subdirectories
                    log_message("Deleted: " + entry.path().string());
                } catch (const fs::filesystem_error& e) {
                    log_message("Error: Failed to delete " + entry.path().string() + ": " + e.what());
                    exit(1);
                }
            }
        } else {
            // Create the live folder if it doesn't exist
            fs::create_directories(live_location);
            set_user_permissions(live_location); // Ensure the directory is editable/deletable
            log_message("Created live folder: " + live_location);
        }

        // Copy all vmlinuz files from /boot to the live directory
        for (const auto& entry : fs::directory_iterator("/boot")) {
            if (entry.path().filename().string().find("vmlinuz") != std::string::npos) {
                try {
                    fs::copy(entry.path(), live_location / entry.path().filename());
                    log_message(entry.path().filename().string() + " copied successfully to " + live_location);
                } catch (const fs::filesystem_error& e) {
                    log_message("Error: Failed to copy " + entry.path().string() + ": " + e.what());
                    exit(1);
                }
            }
        }

        // Read live.conf from the Qt resource system
        QFile liveConfResource(":/config/live.conf");
        if (!liveConfResource.open(QIODevice::ReadOnly | QIODevice::Text)) {
            log_message("Error: Failed to open embedded live.conf resource");
            exit(1);
        }

        // Write the embedded live.conf to the live directory
        std::string live_conf = live_location + "/live.conf";
        QFile liveConfFile(QString::fromStdString(live_conf));
        if (!liveConfFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            log_message("Error: Failed to create live.conf in " + live_location);
            exit(1);
        }

        liveConfFile.write(liveConfResource.readAll());
        liveConfFile.close();
        liveConfResource.close();
        log_message("live.conf created successfully in " + live_location);

        // Generate initramfs using the specified mkinitcpio command
        std::cout << format_message(SETUP_GOLD, "Generating initramfs...\n");
        if (!execute_gold("sudo mkinitcpio -c " + live_conf + " -g " + live_location + "/initramfs-linux.img", false, true)) {
            log_message("Error: Failed to generate initramfs");
            exit(1);
        }
        log_message("initramfs generated successfully");
    }

    // Function to update ISOLinux configuration
    void update_isolinux_configuration() {
        install_location = read_installation_location();
        if (install_location.empty()) {
            std::cerr << format_message(SETUP_GOLD, "Error: install_location is not set. Please run option 1 first.\n");
            return;
        }
        std::string isolinux_cfg = install_location + "/isolinux/isolinux.cfg";
        if (fs::exists(isolinux_cfg)) {
            std::cout << format_message(SETUP_GOLD, "Opening ISOLinux configuration file in nano...\n");
            if (!execute_gold("nano " + isolinux_cfg, false, true)) {
                log_message("Error: Failed to open ISOLinux configuration file in nano");
                exit(1);
            }
            log_message("ISOLinux configuration file updated successfully");
        } else {
            log_message("Error: ISOLinux configuration file not found at " + isolinux_cfg);
        }
    }

    // Function to update GRUB configuration
    void update_grub_configuration() {
        install_location = read_installation_location();
        if (install_location.empty()) {
            std::cerr << format_message(SETUP_GOLD, "Error: install_location is not set. Please run option 1 first.\n");
            return;
        }
        std::string grub_cfg = install_location + "/boot/grub/grub.cfg";
        if (fs::exists(grub_cfg)) {
            std::cout << format_message(SETUP_GOLD, "Opening GRUB configuration file in nano...\n");
            if (!execute_gold("nano " + grub_cfg, false, true)) {
                log_message("Error: Failed to open GRUB configuration file in nano");
                exit(1);
            }
            log_message("GRUB configuration file updated successfully");
        } else {
            log_message("Error: GRUB configuration file not found at " + grub_cfg);
        }
    }

    // Function to save ISO name to a file
    void save_iso_name() {
        std::cout << format_message(SETUP_GOLD, "Enter the ISO name (e.g., my-custom-iso no characters like ' or + strictly - only):\n");
        std::string iso_name;
        std::getline(std::cin, iso_name);
        if (iso_name.empty() || iso_name.find('\'') != std::string::npos || iso_name.find('+') != std::string::npos) {
            std::cerr << format_message(SETUP_GOLD, "Error: ISO name cannot be empty or contain invalid characters (', +).\n");
            return;
        }
        std::string isoname_file = "/opt/Apex-Iso-Creator/Supported-Distros/Arch/Scripts/isoname.txt";
        fs::create_directories(fs::path(isoname_file).parent_path());
        std::ofstream iso_stream(isoname_file);
        if (iso_stream.is_open()) {
            iso_stream << iso_name << "\n";
            iso_stream.close();
            std::cout << format_message(SETUP_GOLD, "ISO name saved to " + isoname_file + "\n");
        } else {
            std::cerr << format_message(SETUP_GOLD, "Error: Failed to save ISO name to " + isoname_file + "\n");
        }
    }

    // Function to display the menu with red ASCII art and gold text
    void display_menu() {
        std::cout << SETUP_RED;
        std::cout << R"(
    ░█████╗░██╗░░░░░░█████╗░██╗░░░██╗██████╗░███████╗███╗░░░███╗░█████╗░██████╗░░██████╗
    ██╔══██╗██║░░░░░██╔══██╗██║░░░██║██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗██╔════╝
    ██║░░╚═╝██║░░░░░███████║██║░░░██║██║░░██║█████╗░░██╔████╔██║██║░░██║██║░░██║╚█████╗░
    ██║░░██╗██║░░░░░██╔══██║██║░░░██║██║░░██║██╔══╝░░██║╚██╔╝██║██║░░██║██║░░██║░╚═══██╗
    ╚█████╔╝███████╗██║░░██║╚██████╔╝██████╔╝███████╗██║░╚═╝░██║╚█████╔╝██████╔╝██████╔╝
    ░╚════╝░╚══════╝╚═╝░░░░░░╚═════╝░╚═════╝░╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═════╝░╚═════╝░
    )" << std::endl;
    std::cout << SETUP_NC;
    std::cout << format_message(SETUP_GOLD, "Apex Arch Iso Creator Setup Script v1.0 18-03-2025\n");
    std::cout << format_message(SETUP_GOLD, "=== Main Menu ===\n");
    std::cout << format_message(SETUP_GOLD, "1. Install Build-Image-Arch\n");
    std::cout << format_message(SETUP_GOLD, "2. Download Dependencies\n");
    std::cout << format_message(SETUP_GOLD, "3. Copy vmlinuz and Generate initramfs\n");
    std::cout << format_message(SETUP_GOLD, "4. Update ISOLinux configuration\n");
    std::cout << format_message(SETUP_GOLD, "5. Update GRUB configuration\n");
    std::cout << format_message(SETUP_GOLD, "6. Save ISO Name\n");
    std::cout << format_message(SETUP_GOLD, "7. Exit\n");
    }

    // Main menu
    void main_menu() {
        while (true) {
            display_menu();
            std::cout << format_message(SETUP_GOLD, "Enter your choice: ");
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            switch (choice) {
                case 1:
                    install_build_image_arch();
                    break;
                case 2:
                    download_dependencies();
                    break;
                case 3:
                    copy_vmlinuz_and_generate_initramfs();
                    break;
                case 4:
                    update_isolinux_configuration();
                    break;
                case 5:
                    update_grub_configuration();
                    break;
                case 6:
                    save_iso_name();
                    break;
                case 7:
                    std::cout << format_message(SETUP_GOLD, "Exiting...\n");
                    return;
                default:
                    std::cerr << format_message(SETUP_GOLD, "Invalid choice. Please try again.\n");
            }
        }
    }
};

#endif // SETUPSCRIPTS_H
