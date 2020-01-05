----------------------------------------------------------------------
 Remote Administrator for Win9X/WinNT
 Version: 1.1

 Copyright (c) 1999  by Dmitry Znosko
 Date: July 28 1999 
----------------------------------------------------------------------

----------------------------------------------------------------------
Radmin 
----------------------------------------------------------------------
Contents:

 * What is Radmin ?
  - What makes it different from other systems?
  - Features
 * System requirements
 * Installation
 * Radmin viewer command-line switches
 * Radmin server command-line switches
 * About testing 
 * FAQ 
 * Registration
 * How to contact me 

 
----------------------------------------------------------------------
 What is Radmin ?
----------------------------------------------------------------------
It is a remote access system, which  enables you to work on the remote computer,
from you own computer.                                                 
You will see a remote computer screen in the window of your computer or on the 
whole screen of your computer.
Your mouse and keyboard are transferred to the remote computer.
So, you can work with the remote computer, as if you are sitting in front of it.

The remote computer can be anywhere in the Internet or in your local network.

You don't need a fast network to work with the remote computer by using Radmin.

Even if you are connected via MODEM , you will reach a reasonable screen 
update speed (about 5-10 screen updates per second).

And if you are using LOCAL NETWORK you will reach a realtime update speed
(about 100 - 500 screen updates per second ).
Sometimes, if you use Radmin in a full-screen mode , you may just 
forget , that you are working on the REMOTE computer ! :)

Radmin consists of two parts:
1) A server, which generates a display.
2) A client (viewer), which actually draws the display on your screen. 

So, to get started with Radmin you must run a server, and then get 
connected with it through a client (viewer).

A current version of Radmin requires a TCP/IP connection between 
the server and the viewer.


----------------------------------------------------------------------
 What makes it different from other systems?
----------------------------------------------------------------------

The speed : All other remote control systems work much more slowly
than Radmin. 
For example, when I tested a famous program that is widely used, the VNC 
(Virtual Network Computing, AT&T product ),
I found out that Radmin works 150 times (!!!) faster than the VNC does.

The test was performed on this configuration:
Server: 800 X 600 65535 colors, OS - WindowsNT 4.0 Service pack 4
Client: 800 X 600 256   colors, OS - Windows95
Ethernet 10Mbit local network.

----------------------------------------------------------------------
 Features.
----------------------------------------------------------------------

+Run as Service
The Radmin server can work as SERVICE on WinNT and Win9X,
which allows you to logon and logoff the user remotely.

+Video hook driver technology is used
Radmin uses a video hook kernel mode driver on Windows NT to catch screen changes.
This allows to work on the remote computer with incredible 'realtime' update speed
(hundrends of screen updates per second).

+Full-screen mode
Windowed and full-screen view modes.
Full-screen mode allows you to see the remote screen  on the entire screen 
of your display.

+Telnet server
Additionally to screen sharing, Radmin provides a Telnet access 
to the remote computer, when its server runs on the Windows NT.

+Password protection
Access to a remote computer is controlled by a password. Radmin uses a 
challenge-response password authentication method, based on DES encryption.

+Optional encryption (DES-56bit) of all data streams. 
With encryption enabled, the perfomance will go down several times.

+IP filter. 
This feature allows access to the Radmin server only from specified 
IP addresses and subnets.

+Hi-resolution modes are supported by Radmin.
Display resolutions up to 2048 X 2048 X 32bit color are supported 
by Radmin. 


----------------------------------------------------------------------
 System requirements.
----------------------------------------------------------------------
No special requirements for hardware:
If you have Windows installed, the program will run.
It even runs on 386\8Mb RAM with Win95.

NOTE: the program will still operate successfully, when a display, a mouse and 
a keyboard are disconnected from the remote computer (but some computers do not
boot successfully, when a keyboard is not connected).

For all operation systems :
The computer must have TCP/IP installed.

Windows 95/98 :
Nothing special.

Windows NT 4.0 :
Service pack 4 or higher is required.
Administrator rights are required, if you want to install the service or 
the driver.


----------------------------------------------------------------------
 Installation.
----------------------------------------------------------------------
Before installation :
For all users:
Uninstall a previous version of Radmin, if it is present.

For WindowsNT users: 
*) If you want install the service or the driver, you  should  have 
   administrator rights.
*) If you want to use the Radmin server with a video hook driver
   you must uninstall any other Remote Control software , which uses 
   Video hook driver technology.
   Running more than one Video hook drivers together can lead 
   to a system crash while booting.
   If you have a problem while booting with the Radmin driver, you can 
   press repeatedly (5 times per sec) a key '1' while booting and 
   the Radmin driver will not load.


Installation:
1) Unpack installation files.
2) Run setup.exe from unpacked distribution.
3) Follow setup instructions.

After installation, the Radmin server or the Radmin client (viewer) can be 
started from Start menu.

You can also start from menu the Radmin Server setup , where you can :
set the Radmin Server to the automatic startup with Windows , 
set a password for the network access to a server.


----------------------------------------------------------------------
 Radmin viewer command-line switches
----------------------------------------------------------------------

Radmin viewer has command line options, which enable you to get connected 
to the host without using a phonebook.

Usage:   
 radmin.exe /connect:xxxxx:nnnn other_options

Examples: 
 radmin.exe /connect:server:1000 /fullscreen /encrypt
 radmin.exe /connect:10.0.0.100:4000 /telnet
 radmin.exe /connect:server /through:gate

Options:
 /connect:xxxxx:nnnn 
    specify an address and a port of the server. 
    This option is required for connection without a phonebook.

 /through:xxxxx:nnnn 
    specify an address and a port of the intermediate server

 /telnet 
    specify a telnet connection mode

 /fullscreen 
    specify to display remote screen in fullscreen mode

 /hicolor 
    specify a 65536 color format, while transferring via a network.

 /noinput 
    disable sending mouse and keyboard input to the remote computer

 /updates:nn 
    specify a maximum number of screen updates per second

 /encrypt  
    specify to encrypt data stream

 /? - shows help screen



----------------------------------------------------------------------
 Radmin server command-line switches
----------------------------------------------------------------------

  The Radmin server has several command line switches.
Normally, all settings can be set through installation process or 
by using 'Radmin server setup' and the user need not use any of the command 
line switches.

These switches are intended to be used by System Administrators.
Using these switches you can manually install\uninstall parts of Radmin,
such as the service and the driver, set a password and a port number.

r_server.exe <switches>

r_server switches :

 /setup - shows a dialog box in which you can install the service and the driver, 
          set a password, port number, IP filter and other options 
          for the server.
Example: r_server.exe /setup

 [/port:xxxx] [/pass:xxxxx] - if there are no other switches specified,
               except /port and /pass, r_server runs as the Radmin server, 
               with a password and a port from the a command line or 
               from the registry, if corresponding switch is not present.
Example: r_server.exe
Example: r_server.exe /pass:mypass
Example: r_server.exe /port:5505
Example: r_server.exe /port:3333 /pass:qwerty

 /save [/port:xxxx] [/pass:xxxxx] - saves the password and the port 
               in the default program settings in the registry. 
               If you do not specify the port or\and the password 
               using this option, the default port or\and the empty password 
               will be saved. 
Example: r_server.exe /port:5505 /pass:qwerty /save  
 This saves values of the port and password in the registry, these values will
 be used, when r_server.exe is executed without parameters (/pass or /port)
 in command line.
Example: r_server.exe /save
 This saves the default port and the empty password in the registry .

 /install    - install the service (Win95/98 or WinNT) and the driver (WinNT)
IMPORTANT NOTE: To be installed, the driver (raddrv.dll) must be
                placed in System32 directory, which is in your Windows directory.
Example: r_server.exe /install

 /uninstall  - uninstall the service and the driver, if present.
NOTE : Failure to remove the service usually indicates that it was not installed. 
Example: r_server.exe /uninstall

 /installservice    - install the service only (Win95/98 or WinNT)
Example: r_server.exe /install the service

 /uninstallservice  - uninstall the service only
NOTE : Failure to remove the service usually indicates that it was not installed. 
Example: r_server.exe /uninstall the service

 /installdrv  - to install the driver (works only in WinNT)
IMPORTANT NOTE: To be installed, the driver (raddrv.dll) must be
                placed in System32 directory, which is in your windows directory.
Example: r_server.exe /installdrv

 /uninstalldrv  - uninstall the driver only.
NOTE : Failure to remove the driver usually indicates that it was not installed. 
Example: r_server.exe /uninstalldrv

 /silence    - doesn't show 'error' or 'ok' message boxes,
               in /install, /uninstall or /save commands.

 /? - shows a help screen.

----------------------------------------------------------------------
 About testing 
----------------------------------------------------------------------
If you find that some part of Radmin crashes sometimes or works 
incorrectly, please, send me e-mail with your description of the problem.

In your report you must specify:
1) OS type on a server side (remote computer side).

2) OS type on a client side (viewer side).

3) Type of installation of the Radmin server 
   -   application
   -   service 
   -   service with driver (only on WinNT)

4) Which part of the Radmin system caused a problem 
   -   Client (Radmin.exe)
   -   Server (r_server.exe)
   -   Driver (raddrv.dll) (Only on WinNT)

5) Screen resolution and a color type of the screen on a client side
Example : 1024 X 768 X 65535 colors                      

6) Screen resolution and a color type of the screen on a server side
Example : 800 X 600 X 256 colors
 
8) If you have any problems with a video hook driver, please specify the model
   of your video card and the version and manufacturer of video drivers,
   which you are using (this information  can be found in 
   Display Properties from Control Panel)

9) Please specify a situation in which the problem occurs 
   (may be, the problem occurred when you did some specific actions ?).

10) Send all other information that, which is in your opinion , is related 
to the problem.

If I find your report useful, you will recieve a registration of 
this product FREE of charge.

Send your reports to e-mail: radmin@mail.ru


----------------------------------------------------------------------
 FAQ 
----------------------------------------------------------------------

Q:How can I send Ctrl-Alt-Del to the remote computer ?
Q:I can't connect to Radmin server. What can I do ?
Q:What is the 'Connect through host' option in the properties of the connection?
Q:How can I return from the full-screen mode to normal one ?
Q:How I can see statistics of the connection (updates per sec, bytes per sec).
Q:I obtain a high processor load on the remote computer,
  when I see its screen with the help of Radmin. How can I make it lower ?
Q:How can I speed up the Radmin in the remote screen mode? I use 
  a slow (modem) connection between computers.
Q:How can I speed up the Radmin in the remote screen mode? I use a fast 
  connection between computers.
Q:Telnet mode does not work, when the Radmin server is executed on the Win95/98.
Q:I can't see the remote screen, when the remote display is in full-screen text
  mode. Is it a bug ?
Q:How can I install the video hook driver on the WinNT ?
Q:I have a problem while running some console application via Radmin telnet 
  session. Applications do not work properly.  What can I do?


Q:How can I send Ctrl-Alt-Del to the remote computer ?
A:If you want to send Ctrl-Alt-Del key to a remote computer, use 
  'Send Ctrl-Alt-Del' entry from the RScreen window menu. 
  That feature will work only when the remote computer OS is WindowsNT and 
  the Radmin server runs as system service on the remote computer.

Q:I can't connect to Radmin server. What can I do ?
A:Test,if you can get connected with the remote host via TCP/IP:
  Type in the command prompt:
  ping remote_host_name
Ex: ping 10.0.0.1
Ex: ping myserver.mycompany.com
  Make sure, that radmin server runs on the remote computer.
  Make sure, that you are connecting to the port, which is equal to the port,
  on which the radmin server is waiting for the incoming connection.

Q:What is the 'Connect through host' option in the properties of the connection?
A:This enables you to get connected with the hosts, when there is no direct 
  TCP/IP connection with them, but some computer has direct TCP/IP connection 
  with them and to you. If you run the Radmin server on such a computer,
  you will be able to get connected through it with the target hosts. 
Ex: You have a local network without a direct connection to the Internet
  and the computer that has direct connection with the Internet and the 
  local network. If you install Radmin server in the that computer, you 
  will be able to get connected from the internet with the computers in the 
  local network. 

Q:How can I return from the full-screen mode to normal one ?
A:Just press F12. Using this key you can switch between normal and full-screen
  modes. if you want to send F12 key to a remote computer, use 'Send F12' entry
  from the RScreen window menu.

Q:How I can see statistics of the connection (updates per sec, bytes per sec).
A:Use 'Connection info' entry from the RScreen window menu.

Q:I obtain a high processor load on the remote computer,
  when I see its screen with the help of Radmin. How can I make it lower ?
A:Set 'max screen updates pes second' entry to the smaller value
  in the 'Options' dialog of the RScreen window menu.
  If your remote computer works under Win95/98 (or under WinNT, 
  without video hook driver installed) the Radmin server
  can cause a high processor load when the 'Maximum updates per second' 
  value is set to values bigger than 50.

Q:How can I speed up the Radmin in the remote screen mode? I use 
  a slow (modem) connection between computers.
A:To speed up, you can disable wallpaper on the remote computer.
  Also, make sure, that 'Strict to 256 colors' checkbox is checked in 
  the Options dialog of the RScreen window.
  If you are connected via modem you can't have update rates higher 
  than 10 times per second, just because a signal can't go from one 
  side to the other and return faster than 10 times per second (ping > 100ms).

Q:How can I speed up the Radmin in the remote screen mode? I use a fast 
  connection between computers.
A:If you use Win95/98 OS on the remote side,
  the speed depends on the screen resolution of the remote computer.
  So set a lower screen resolution on the remote computer.
  Besides, set a lower color format 8bpp (256 colors) or 16bpp (65536 colors),
  on some systems 8bpp faster, on some 16bpp.
  Make sure, that your update speed is not limited by the 
  'Maximum updates per second' field from the option dialog of the RScreen
  window.
  If you use WinNT on the remote side without the video hook driver
  installed, note that with the video hook driver Radmin works about 10 times 
  faster and uses much less processor time.

Q:Telnet mode does not work, when the Radmin server is executed on the Win95/98.
A:Yes, the Telnet access to Win95/98 is not supported , because of limitation 
  of the command.com - command prompt interpreter of the Win95/98.

Q:I can't see the remote screen, when the remote display is in full-screen text
  mode. Is it a bug ?
A:Currently, Radmin can't get screen changes, when the remote computer is 
  in the full-screen text mode. Drawing on the screen isn't performed 
  by GDI (Graphic Display Interface) when the remote computer is in such a mode.
  Windows works with full-screen text modes in an undocumented way,
  via video port driver.

Q:How can I install the video hook driver on the WinNT ?
A:If you did not install Radmin server as a system service in installation 
  process, you can do it from 'Radmin server setup': press the 'Install' button
  in the 'Radmin server setup' dialog.
  This installs the service and the driver on the your computer.

Q:I have a problem while running some console application via Radmin telnet 
  session. Applications do not work properly.  What can I do?
A:Some Win32 console applications use direct access to a console. 
  Such applications can't work via the telnet mode , because
  the telnet mode on server uses standart i\o streams to
  interact with the application. Just do not run such applications via 
  telnet. You can run such applications in RScreen mode.

----------------------------------------------------------------------
 Registration
----------------------------------------------------------------------
This is a shareware program.
You can see the LICENSE AGREEMENT in the file 'license.txt'.

Register, and you will have all benefits of Remote Administrator.
They are as follows:

 - Remove 30-day evaluation period.
 - All future versions of Remote Administrator - FREE.
 - Full e-mail support.

Registration fee is $25.

To register, visit the web site: 
 http://www.mtu-net.ru/radmin/

----------------------------------------------------------------------
 How to contact me 
----------------------------------------------------------------------

You can download a new version from 
http://www.mtu-net.ru/radmin/

You can contact me to e-mail: radmin@mail.ru

----------------------------------------------------------------------
                                         July 28 1999 
                                         Dmitry Znosko
