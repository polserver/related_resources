These are example .php files that you can use to include the .ecl scripts from your POL server from your normal webserver. If you have a newer version of .php you can use the scripts from the non-cgi folder but if you have older PHP that can't do cross-server includes you'll have to use the stuff from the cgi folder. The cgi method is a little slower and harder to install but they should both work and I have used both.


Installation of non-cgi:
First open view.inc and change the $pol_url variable to the URL of your POL webserver. Next, copy all of the files in the directory (should be 4) to your webserver and make sure they're all in the same folder. Now just follow the rest of the instructions in the readme file that came with the package to configure the scripts to link to these .php files and not the .ecl files.



Installation of cgi:
Open the .pl (perl) file and edit the $host variable to the URL of your POL webserver. Next, copy all of the files in that directory (should be 4) to your webserver. After that, chmod 755 the .pl file and then read the readme file that came with the package to configure the scripts to link to these .php files and not the .ecl files.

For those of you who don't know what chmod is, it just means to telnet or ssh to your webserver, go to the directory with the .pl file and type this line:
chmod 755 get_page.pl

If you can't telnet or ssh to your webserver then use your FTP (you DO have ftp access right?) client to set permissions on the file so that the owner can read write and execute, group and read and execute and user can read and execute.

That should work...



-tekproxy@yahoo.com