<div align="center">

  <h1>First, Watch This Video from Chris Titus Tech</h1>
  <p>He shares many useful tips in this video:</p>
  <a href="https://youtu.be/u0CIrKkBung?si=X7u6aIUhP7jTYLAA">Chris Titus Tech Video</a>
  <p>Please support him if you can!</p>

</div>

<div align="center">
  <pre>
please remove the quotes "" from commands 
they are hypothetical

System Commands For Updating

Arch Updating

Update Package List
  sudo pacman -Sy

Update All Installed Packages
sudo pacman -Syu

Reboot Your System before next steps

Clean Old Packages
sudo pacman -Scc

Ubuntu/Debian

Update Package List
sudo apt update

Update All Installed Packages
sudo apt full-upgrade

Reboot Your System Before Next Steps

Clean Old Packages
sudo apt-get clean

Auto Remove Unused Packages
sudo apt autoremove
  </pre>
</div>

<div align="center">
  <pre>
Changing Passwords, Usernames, Home Folder, and Adding to Group

To Change Your Password
sudo passwd "username"
Example: sudo passwd "root"

Change Username and Home Folder
Log in to the root account.
Change Username:
usermod -l "newusername" "oldusername"

Change Home Folder:
sudo usermod -d /home/"yournewusername" -m "yournewusername"

Add User to Group:
sudo usermod -aG "groupname" "username"
  </pre>
</div>

<div align="center">
  <pre>
Setup Wi-Fi in Konsole

To Get a Wi-Fi List:
nmcli d wifi

To Connect to Wi-Fi:
nmcli d wifi connect "BSSID" password "yourpassword"
Example (fake credentials):
nmcli d wifi connect 2E:FB:FA:B9:82:94 password "tttodayjunior"
  </pre>
</div>

<div align="center">
  <pre>
Other Common Linux Commands And Steps For Arch, Ubuntu And Debian
  </pre>
</div>

<div align="center">
  <pre>
Guide To Setting Up Arch, Ubuntu , Debian To Compile C++ Applications

Arch Needed Packages To Compile Qt6 Applications
sudo -S base-devel qt6-base qt6-tools

Files Need To Compile C++
main.cpp main.pro

Other Things That Can Be Used
.h files to add different functions within the project 
resources.qrc to embed other files

Ubuntu/Debian Packages To Compile Qt6 Applications
sudo apt install build-essential qt6-base-dev

Files Need To Compile C++
main.cpp main.pro

Other Things That Can Be Used
.h files to add different functions within the project 
resources.qrc to embed other files
  </pre>
</div>

<div align="center">
  <pre>
Example Files For .pro And resources.qrc

example .pro
# Project name
TARGET = apexisocreatorgui

# Required Qt modules
QT += core gui widgets

# Source files
SOURCES += main.cpp
HEADERS += squashfs.h
HEADERS += usb.h
HEADERS += isocreator.h
HEADERS += setupscripts.h


# C++ standard
CONFIG += c++23

RESOURCES += resources.qrc


example resources.qrc
<RCC>
    <qresource prefix="/">
        <file>images/ApexBrowser.png</file>
        <file>images/burn.png</file>
        <file>images/transfer-file.png</file>
        <file>images/usb.png</file>
        <file>images/machine.png</file>
        <file>images/pirate-ship.png</file>
    </qresource>
        <qresource prefix="/config">
            <file>scripts.zip</file>
        </qresource>
    </RCC>
  </pre>
</div>

<div align="center">
  <pre>
How To Compile The Qt6 Applications
qmake6 -makefile
make
  </pre>
</div>

<div align="center">
  <pre>
Everyday Use Tools for Arch, Ubuntu, Debian

Edit Text in Konsole
Install nano from your repos:
sudo pacman -S nano (Arch)
sudo apt install nano (Ubuntu/Debian)

Custom Application Manager
https://github.com/vinifmor/bauh

Custom DNS Manager
https://github.com/DnsChanger/dnsChanger-desktop

Application Store Website
www.pling.com
  </pre>
</div>
