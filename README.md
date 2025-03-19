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





<div align="center">
  <h1>First, Watch This Video from Chris Titus Tech</h1>
  <p>He shares many useful tips in this video:</p>
  <a href="https://youtu.be/u0CIrKkBung?si=X7u6aIUhP7jTYLAA">Chris Titus Tech Video</a>
  <p>Please support him if you can!</p>
</div>

<div align="center">
  <h2>System Commands for Updating</h2>

  <h3>Arch Linux</h3>
  <p><strong>Update Package List</strong></p>
  <code>sudo pacman -Sy</code>

  <p><strong>Update All Installed Packages</strong></p>
  <code>sudo pacman -Syu</code>

  <p><strong>Reboot Your System Before Next Steps</strong></p>
  <code>sudo reboot</code>

  <p><strong>Clean Old Packages</strong></p>
  <code>sudo pacman -Scc</code>

  <h3>Ubuntu/Debian</h3>
  <p><strong>Update Package List</strong></p>
  <code>sudo apt update</code>

  <p><strong>Update All Installed Packages</strong></p>
  <code>sudo apt full-upgrade</code>

  <p><strong>Reboot Your System Before Next Steps</strong></p>
  <code>sudo reboot</code>

  <p><strong>Clean Old Packages</strong></p>
  <code>sudo apt-get clean</code>

  <p><strong>Auto Remove Unused Packages</strong></p>
  <code>sudo apt autoremove</code>
</div>

<div align="center">
  <h2>Changing Passwords, Usernames, Home Folder, and Adding to Group</h2>

  <p><strong>Change Your Password</strong></p>
  <code>sudo passwd username</code>
  <p>Example: <code>sudo passwd root</code></p>

  <p><strong>Change Username and Home Folder</strong></p>
  <p>1. Log in to the root account.</p>
  <p>2. Change username:</p>
  <code>usermod -l newusername oldusername</code>

  <p>3. Change home folder:</p>
  <code>sudo usermod -d /home/yournewusername -m yournewusername</code>

  <p><strong>Add User to Group</strong></p>
  <code>sudo usermod -aG groupname username</code>
</div>

<div align="center">
  <h2>Setup Wi-Fi in Konsole</h2>

  <p><strong>Get a Wi-Fi List</strong></p>
  <code>nmcli d wifi</code>

  <p><strong>Connect to Wi-Fi</strong></p>
  <code>nmcli d wifi connect BSSID password yourpassword</code>
  <p>Example (fake credentials):</p>
  <code>nmcli d wifi connect 2E:FB:FA:B9:82:94 password tttodayjunior</code>
</div>

<div align="center">
  <h2>Other Common Linux Commands and Steps for Arch, Ubuntu, and Debian</h2>
</div>

<div align="center">
  <h2>Guide to Setting Up Arch, Ubuntu, Debian to Compile C++ Applications</h2>

  <h3>Arch Needed Packages to Compile Qt6 Applications</h3>
  <code>sudo pacman -S base-devel qt6-base qt6-tools</code>

  <h3>Files Needed to Compile C++</h3>
  <p><code>main.cpp</code>, <code>main.pro</code></p>

  <h3>Other Things That Can Be Used</h3>
  <p><code>.h</code> files to add different functions within the project.</p>
  <p><code>resources.qrc</code> to embed other files.</p>

  <h3>Ubuntu/Debian Packages to Compile Qt6 Applications</h3>
  <code>sudo apt install build-essential qt6-base-dev</code>

  <h3>Files Needed to Compile C++</h3>
  <p><code>main.cpp</code>, <code>main.pro</code></p>

  <h3>Other Things That Can Be Used</h3>
  <p><code>.h</code> files to add different functions within the project.</p>
  <p><code>resources.qrc</code> to embed other files.</p>
</div>

<div align="center">
  <h2>Example Files for .pro and resources.qrc</h2>

  <h3>Example .pro File</h3>
  <pre>
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
  </pre>

  <h3>Example resources.qrc File</h3>
  <pre>
&lt;RCC&gt;
    &lt;qresource prefix="/"&gt;
        &lt;file&gt;images/ApexBrowser.png&lt;/file&gt;
        &lt;file&gt;images/burn.png&lt;/file&gt;
        &lt;file&gt;images/transfer-file.png&lt;/file&gt;
        &lt;file&gt;images/usb.png&lt;/file&gt;
        &lt;file&gt;images/machine.png&lt;/file&gt;
        &lt;file&gt;images/pirate-ship.png&lt;/file&gt;
    &lt;/qresource&gt;
    &lt;qresource prefix="/config"&gt;
        &lt;file&gt;scripts.zip&lt;/file&gt;
    &lt;/qresource&gt;
&lt;/RCC&gt;
  </pre>
</div>

<div align="center">
  <h2>How to Compile Qt6 Applications</h2>
  <code>qmake6 -makefile</code>
  <code>make</code>
</div>

<div align="center">
  <h2>Everyday Use Tools for Arch, Ubuntu, Debian</h2>

  <p><strong>Edit Text in Konsole</strong></p>
  <p>Install <code>nano</code> from your repos:</p>
  <code>sudo pacman -S nano</code> (Arch)
  <code>sudo apt install nano</code> (Ubuntu/Debian)

  <p><strong>Custom Application Manager</strong></p>
  <a href="https://github.com/vinifmor/bauh">bauh</a>

  <p><strong>Custom DNS Manager</strong></p>
  <a href="https://github.com/DnsChanger/dnsChanger-desktop">dnsChanger-desktop</a>

  <p><strong>Application Store Website</strong></p>
  <a href="https://www.pling.com">www.pling.com</a>
</div>
