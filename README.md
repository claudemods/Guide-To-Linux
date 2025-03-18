<p align="center">
<img src="https://i.postimg.cc/JhMRf2RZ/claudemods-03-17-2025.gif">	



changing passwords, usernames, homefolder,

to change your password
use command sudo passwd "username" e.g sudo passwd root
enter your password

change your username, and home folder
simply login to root account
usermod -l "newusername" "oldusername"


setup wifi in konsole 
to get a wifi list 
use command nmcli d wifi 

to connect to wifi
nmcli d wifi connect "BSSID" password "your password'
example full command 'fake credentials" nmcli d wifi connect 2E:FB:FA:B9:82:94 password tttodayjunior
