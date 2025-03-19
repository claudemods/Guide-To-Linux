<p align="center">
<img src="https://i.postimg.cc/7LwstxCz/me.webp">	



<div align="center">
Guide To Linux

  
<div align="center">
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

I have also tested games like "Skull and Bones" by Ubisoft before their release—I like to get involved.

Since I am a game mod creator, music creator, and now a software engineer,
I have a lot of free time on my hands after putting my game mod updates on hold.

I’ve made tons of scripts and applications for Linux, and I wish to help others with what I’ve learned.

Below, you’ll find many useful tutorials for Linux,
including application building and complex Bash commands that everyday users might not know.

More to come—I will update this soon!
  </pre>
</div>

<div align="center">

  <h1>First, Watch This Video from Chris Titus Tech</h1>
  <p>He shares many useful tips in this video:</p>
  <a href="https://youtu.be/u0CIrKkBung?si=X7u6aIUhP7jTYLAA">Chris Titus Tech's Video</a>
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


Example Files For .cpp .pro And resources.qrc

<a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.cpp">Example main.cpp</a>
<a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.pro">Example main.pro</a>
<a href="https://github.com/claudemods/Guide-To-Linux/blob/main/example.qrc">Example resources.qrc</a>


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
