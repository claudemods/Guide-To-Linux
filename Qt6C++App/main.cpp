#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextBrowser>

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Guide To Linux");
        resize(1000, 800);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);

        // Create scroll area
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::NoFrame);

        // Create text browser with HTML content
        QTextBrowser *textBrowser = new QTextBrowser(this);
        textBrowser->setOpenExternalLinks(true);
        textBrowser->setHtml(R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Guide To Linux</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1000px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .center {
            text-align: center;
        }
        img {
            max-width: 100%;
            height: auto;
            border-radius: 8px;
            margin: 20px 0;
        }
        pre {
            background-color: #f8f8f8;
            padding: 15px;
            border-radius: 5px;
            overflow-x: auto;
            white-space: pre-wrap;
            word-wrap: break-word;
        }
        h1, h2 {
            color: #2c3e50;
        }
        h1 {
            font-size: 1.8em;
            margin-top: 30px;
            border-bottom: 2px solid #4a6fa5;
            padding-bottom: 5px;
        }
        h2 {
            font-size: 1.5em;
            margin-top: 25px;
        }
        a {
            color: #2980b9;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
        .command {
            background-color: #2d2d2d;
            color: #f8f8f2;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: monospace;
        }
        .note {
            background-color: #fff3d4;
            padding: 10px;
            border-left: 4px solid #f0ad4e;
            margin: 15px 0;
        }
        </style>
        </head>
        <body>
        <div class="center">
        <img src="" alt="Profile Image">
        </div>

        <div class="center">
        <h1>Guide To Linux</h1>
        </div>

        <div class="center">
        <pre>
        History of Myself: Aaron Douglas D'souza

        I am 28 years old, originally from London in the UK, though I now live in Manchester.

        I hate the words "Noob" or "Newbie," but I was once a new Linux user. I started using Nobara around September 2023.
        From there, I began creating a custom taskbar, which can be seen in the project link below:
        Though the original color was burgundy and it was called "SpitFire."

        Project Link: <a href="https://github.com/claudemods/ApexKLGE-Minimal">ApexKLGE-Minimal</a>

        More photos of my old projects can be found here:
        <a href="https://www.claudemods.co.uk/distributions/theme-photos">Theme Photos</a>

        I was originally an advanced Windows user who enjoyed testing betas and development builds.
        In fact, I tested Windows 8/8.1/10/11 before their official releases and was testing KDE Plasma 6 before it came out.

        I have also tested games like "Skull and Bones" by Ubisoft before their release. I like to get involved.

        Since I am a game mod creator, music creator, and now a software engineer,
        I have a lot of free time on my hands after putting my game mod updates on hold.

        I've made tons of scripts and applications for Linux, and I wish to help others with what I've learned.

        Below, you'll find many useful tutorials for Linux,
        including application building and complex Bash commands that everyday users might not know.

        More to come I will update this soon!
        </pre>
        </div>

        <div class="center">
        <h1>First, Watch This Video from Chris Titus Tech</h1>
        <p>He shares many useful tips in this video:</p>
        <a href="https://youtu.be/u0CIrKkBung?si=X7u6aIUhP7jTYLAA">Chris Titus Tech's Video</a>
        <p>Please support him if you can!</p>
        </div>

        <div class="center">
        <pre>
        <h1>System Commands For Updating</h1>

        <div class="note">Please remove the quotes "" from commands - they are hypothetical</div>

        <h2>Arch Updating</h2>

        Update Package List
        <span class="command">sudo pacman -Sy</span>

        Update All Installed Packages
        <span class="command">sudo pacman -Syu</span>

        Reboot Your System before next steps

        Clean Old Packages
        <span class="command">sudo pacman -Scc</span>


        <h2>Ubuntu/Debian Updating</h2>

        Update Package List
        <span class="command">sudo apt update</span>

        Update All Installed Packages
        <span class="command">sudo apt full-upgrade</span>

        Reboot Your System Before Next Steps

        Clean Old Packages
        <span class="command">sudo apt-get clean</span>

        Auto Remove Unused Packages
        <span class="command">sudo apt autoremove</span>
        </pre>
        </div>

        <div class="center">
        <pre>
        <h1>Changing Passwords, Usernames, Home Folder, Adding to Group</h1>

        To Change Your Password
        <span class="command">sudo passwd username</span>
        Example: <span class="command">sudo passwd root</span>

        Change Username and Home Folder
        Log in to the root account.
        Change Username:
        <span class="command">sudo usermod -l newusername oldusername</span>
        Example: <span class="command">sudo usermod -l apex manowar</span>

        Change Home Folder:
        <span class="command">sudo usermod -d /home/yournewusername -m yournewusername</span>
        Example: <span class="command">sudo usermod -d /home/apex -m apex</span>

        Add User to Group:
        <span class="command">sudo usermod -aG groupname username</span>
        Example: <span class="command">sudo usermod -aG arch apex</span>
        </pre>
        </div>

        <div class="center">
        <pre>
        <h1>Setup Wi-Fi in Konsole</h1>

        To Get a Wi-Fi List:
        <span class="command">nmcli d wifi</span>

        To Connect to Wi-Fi:
        <span class="command">nmcli d wifi connect BSSID password yourpassword</span>
        Example (fake credentials):
        <span class="command">nmcli d wifi connect 2E:FB:FA:B9:82:94 password tttodayjunior</span>
        </pre>
        </div>

        <div class="center">
        <pre>
        <h1>Complex Linux Commands, For Arch, Ubuntu, Debian</h1>
        Install your drivers for your PC
        <span class="command">sudo apt install ubuntu-drivers-common</span>
        <span class="command">sudo ubuntu-drivers autoinstall</span>
        </pre>
        </div>

        <div class="center">
        <pre>
        <h1>Guide For Arch, Ubuntu, Debian To Compile C++ Applications</h1>

        <h2>Arch Needed Packages To Compile Qt6 Applications</h2>

        <span class="command">sudo -S base-devel qt6-base qt6-tools</span>

        Files Need To Compile C++
        main.cpp main.pro

        Other Things That Can Be Used
        .h files to add different functions within the project
        resources.qrc to embed other files

        <h2>Ubuntu/Debian Packages To Compile Qt6 Applications</h2>

        <span class="command">sudo apt install build-essential qt6-base-dev</span>
        </pre>
        </div>

        <div class="center">
        <h1>Example Files For .cpp .pro And resources.qrc</h1>
        <a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.cpp">Example main.cpp</a><br>
        <a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.h">Example backend.h</a><br>
        <a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.pro">Example main.pro</a><br>
        <a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.qrc">Example resources.qrc</a>
        </div>

        <div class="center">
        <pre>
        <h1>Everyday Use Tools for Arch, Ubuntu, Debian</h1>

        Edit Text in Konsole
        Install nano from your repos:
        <span class="command">sudo pacman -S nano</span> (Arch)
        <span class="command">sudo apt install nano</span> (Ubuntu/Debian)

        Custom Application Manager
        <a href="https://github.com/vinifmor/bauh">bauh</a>

        Custom DNS Manager
        <a href="https://github.com/DnsChanger/dnsChanger-desktop">dnsChanger-desktop</a>

        Application Store Website
        <a href="https://www.pling.com">www.pling.com</a>

        KSystemlog
        <a href="https://apps.kde.org/en-gb/ksystemlog/">KSystemlog</a>

        scrcpy
        <a href="https://github.com/Genymobile/scrcpy">scrcpy</a>

        spectacle
        <a href="https://apps.kde.org/en-gb/spectacle/">spectacle</a>

        ark
        <a href="https://apps.kde.org/en-gb/ark/">ark</a>

        file manager
        <a href="https://apps.kde.org/en-gb/dolphin/">dolphin</a>

        dolphin service menus for arch
        <a href="https://www.pling.com/p/2160116">Dolphin Service Menus</a>

        custom windows menu
        <a href="https://github.com/claudemods/11menu">11menu</a>

        hide files in dolphin
        <a href="https://github.com/claudemods/hideitems">hideitems</a>

        open dolphin as root
        <a href="https://github.com/claudemods/Dolphin-As-Root-Plasma-5-and-Plasma-6">Dolphin As Root</a>

        stacer
        <a href="https://appimage.github.io/Stacer/">Stacer</a>

        create arch isos with script
        <a href="https://www.pling.com/p/2261487">Arch ISO Script</a>

        create arch isos with gui application
        <a href="https://flatpak.opendesktop.org/p/2262634">Arch ISO GUI</a>

        Create Docker Containers From Cloned Linux Systems
        <a href="https://github.com/claudemods/ACCU">ACCU</a>

        view and edit html
        <a href="https://github.com/claudemods/apex-htmlviewer">apex-htmlviewer</a>

        custom decentralized browser
        <a href="https://github.com/claudemods/ApexBrowserAppImage">ApexBrowser</a>

        setup bottles for games
        <a href="https://github.com/claudemods/Custom-Bottle-For-Gamers">Custom Bottle For Gamers</a>

        custom arch installer gui
        <a href="https://github.com/claudemods/ApexArchInstallerAppImage">ApexArchInstaller</a>

        custom arch btrfs installer script
        <a href="https://github.com/claudemods/Apex-InstallerBtrfs">Apex-InstallerBtrfs</a>

        create arch bootable usb
        <a href="https://github.com/claudemods/ApexBootableUsbAppimage">ApexBootableUsb</a>
        </pre>
        </div>
        </body>
        </html>
        )");

        scrollArea->setWidget(textBrowser);
        mainLayout->addWidget(scrollArea);
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
