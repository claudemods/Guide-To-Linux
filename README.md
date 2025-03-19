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



More To Come i Will Update This More Soon....
  

```




<p align="center">
  <img src="https://i.postimg.cc/7LwstxCz/me.webp">
</p>

<div align="center">
  <h1>Guide To Linux</h1>
  
  <pre>
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



More To Come i Will Update This More Soon....
  </pre>
</div>

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

auto remove unused packages
sudo apt autoremove
  </pre>
</div>

<div align="center">
  <pre>
changing passwords, usernames, homefolder, add to group

to change your password
use command sudo passwd "username"
e.g sudo passwd "root"

change your username, and home folder
simply login to root account
 change username
usermod -l "newusername" "oldusername"

change home folder
sudo usermod -d /home/"yournewusername" -m "yournewusername"

add user to group
sudo usermod -aG "groupname" "username"
  </pre>
</div>

<div align="center">
  <pre>
setup wifi in konsole 

to get a wifi list 
use command nmcli d wifi 

to connect to wifi
nmcli d wifi connect "BSSID" password "yourpassword"
example full command 'fake credentials'
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
Guide To Setting Up Arch, Ubuntu , Debian To Compile Cpp Applications

Arch Needed Packages To Compile Qt6 Applications
sudo -S base-devel qt6-base qt6-tools

Files Need To Compile Cpp
main.cpp main.pro

Other Things That Can Be Used
.h files to add different functions within the project 
resources.qrc to embedded other files


Ubuntu/Debian Packages To Compile Qt6 Applications
sudo apt install build-essentials qt6-base-dev

Files Need To Compile Cpp
main.cpp main.pro

Other Things That Can Be Used
.h files to add different functions within the project 
resources.qrc to embedded other files
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
Every day use tools for Arch, Ubuntu, Debian

edit text in konsole
install nano from your repos

custom application manager
https://github.com/vinifmor/bauh

custom dns manager
https://github.com/DnsChanger/dnsChanger-desktop

application store website
www.pling.com
  </pre>
</div>
