<%
 use http;
 use uo;
 use os;
 
 include "../hasher";

 var name := QueryParam( "acctname" );
 var pass := QueryParam( "acctpass" );
 var ip := QueryIP();
%>

<html>
 <head>

 <%
 var acct := FindAccount( name );
 var acctip := acct.getprop( "ip" );
 var checkpass := passcheck( pass, name );
 var isgm, charnum;
 if( (acctip == ip) and (acct.name == name) and (checkpass == 1) )
  for counter := 1 to 5
   var player := acct.GetCharacter( counter );
   if( player.cmdlevel )
    charnum := counter;
    print( "GM " + player.name + " has logged into the web interface." );
    isgm := 1;
   endif
  endfor
  if( isgm == 1 );
   %>

   <META http-equiv="refresh" content="0; URL=/pkg/webmgmt/gm/index.ecl?acctname=<%=name %>&char=<%=charnum %>">
  </head>
  <body>

   <%
  else
   %>

   <META http-equiv="refresh" content="0; URL=/pkg/webmgmt/player/index.ecl?acctname=<%=name %>">
  </head>
  <body>

   <%
  endif
 elseif( (acctip == ip) and (acct.name == name) )
  %>

   <META http-equiv="refresh" content="5; URL=index.ecl">
   <LINK rel="stylesheet" href="TYPE THE PATH TO YOUR STYLESHEET HERE/style1.css">
   <title>POL HTTP Login Manager</title>
  </head>
  <body>
   <div class="header">
    <B>POL HTTP Login Manager</B>
   </div><HR><P>
   I'm sorry, but you must have entered your password incorrectly.<P>
   Please wait, you will be forwarded in 5 seconds.<P>
   Otherwise click <a href="index.ecl">here</a>.

  <%
 else
  %>

   <LINK rel="stylesheet" href="TYPE THE PATH TO YOUR STYLESHEET HERE/style1.css">
   <title>POL HTTP Login Manager</title>
  </head>
  <body>
   <div class="header">
    <B>POL HTTP Login Manager</B>
   </div><HR><P>
   I'm sorry, but you must have an account .<P>
   If you have an account please log into the game server to ensure the account is active, then <a href="index.ecl">try again</a>.<P>
   If you need to set up an account, please click <a href="acctadd.ecl">here</a>.

  <%
 endif
 %>

 </body>
</html>