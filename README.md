<p align="center">
<img src="https://i.postimg.cc/7LwstxCz/me.webp">	



<div align="center">
Guide To Linux

  
```

 History Of My Self Aaron Douglas D'souza Im 28 From London In The Uk Though I Live In Manchester Now

I Hate The Word Noob or Newbie But i Was Once A New Linux User I Started Using Nobara
                 Around September 2023 time 

from There I Started Making A Custom Taskbar which Can Be Seen In This Project Link Below
Though The Original Colour Was Bungundy And Called SpitFire
Project Link https://github.com/claudemods/ApexKLGE-Minimal

More Photos Of My Old Projects https://www.claudemods.co.uk/distributions/theme-photos

I Was Originally A Advanced Windows User I Like To Test Betas/Devs
I Infact Tested Windows 8/8.1/10/11 Before They Came Out And Was Testing Kde Plasma 6 Before It Came Out

I Have Also Tested Skull And Bones By Ubisoft Before It Came Out I Like To Get Involved

Since Im A Game Mod Creator/Music Creator And Now A Software Engineer

I Have Alot Of Time On My Hands From Not Having A Job Since Putting My Game Mod Updates On Hold 

Ive Made Tones Of Scripts And Applications Linux Based And I wish To Help Others From What Ive Learnt

Find Below Many Useful Tutorials For Linux
Including Application Building And Complex Bash Commands Every Day Users Would Not Know



More To Come i Will Update This More Soon.
  
```

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


TARGET = apexisocreatorgui


QT += core gui widgets

SOURCES += main.cpp
HEADERS += squashfs.h
HEADERS += usb.h
HEADERS += isocreator.h
HEADERS += setupscripts.h


CONFIG += c++23

RESOURCES += resources.qrc


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
