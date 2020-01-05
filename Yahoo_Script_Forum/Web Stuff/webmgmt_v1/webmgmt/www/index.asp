<%
 use uo;
 use http;
%>

<html>
 <head>
  <LINK rel="stylesheet" href="TYPE THE PATH TO YOUR STYLESHEET HERE/style1.css">
  <title>POL Secure HTTP Login</title>
 </head>
 <body>
  <div class="header">
   <B>POL Secure HTTP Login</B>
  </div><HR>
  <P>
   <form method=GET action=login.ecl>
    Account Name: <P><INPUT name=acctname style="HEIGHT: 22px; WIDTH: 158px"><P>
    Account Password: <P><INPUT name=acctpass style="HEIGHT: 22px; WIDTH: 158px"><P>
    <INPUT id=submit1 name=submit1 type=submit value=Submit>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <INPUT id=reset1 name=reset1 type=reset value=Reset><P>
   </form>
   <form method=GET action=acctadd.ecl>
    <INPUT id=submit1 name=submit1 type=submit value=&nbsp;&nbsp;Create_Account&nbsp;&nbsp;>
   </form>
  </P>
 </body>
</html>