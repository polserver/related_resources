<%
 use uo;
 use http;
%>

<html>
 <head>
  <LINK rel="stylesheet" href="TYPE THE PATH TO YOUR STYLESHEET HERE/style1.css">
  <title>POL HTTP Account Adder</title>
 </head>
 <body>
  <div class="header">
   <B>POL HTTP Account Adder</B>
  </div><HR>
  <P>
   <form method=GET action=webacct.ecl>
    Account Name: <P><INPUT name=acctname style=HEIGHT: 22px; WIDTH: 158px><P>
    Account Password: <P><INPUT name=acctpass style=HEIGHT: 22px; WIDTH: 158px><P>
    Confirm Password: <P><INPUT name=acctpass2 style=HEIGHT: 22px; WIDTH: 158px><P>
    Account Email: <P><INPUT name=acctemail style=HEIGHT: 22px; WIDTH: 158px><P>
    Account Icq: <P><INPUT name=accticq style=HEIGHT: 22px; WIDTH: 158px><P>
    <INPUT id=submit1 name=submit1 type=submit value=Submit>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <INPUT id=reset1 name=reset1 type=reset value=Reset>
   </form>
  </P>
 </body>
</html>