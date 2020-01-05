<%
 use http;
 use uo;
 use os;
 use cfgfile;

 include "../hasher";

 const MIN_NAME := 5;
 const MAX_NAME := 15;
 const MIN_PASS := 6;
 const MAX_PASS := 16;
 const MIN_ICQ := 5;
 const MAX_ICQ := 11;

 var acctname := QueryParam( "acctname" );
 var acctpass := QueryParam( "acctpass" );
 var acctpass2 := QueryParam( "acctpass2" );
 var acctemail := QueryParam( "acctemail" );
 var accticq := QueryParam( "accticq" );
 var acctip := QueryIP();
 var text := lower( acctemail );
 var splitted := SplitWords( text );
 var text2 := lower( acctname );
 var splitted2 := SplitWords( text2 );
 var text3 := lower( acctpass );
 var splitted3 := SplitWords( text3 );
 var text4 := lower( accticq );
 var splitted4 := SplitWords( text4 );
 var icqi := CInt( accticq );
 var icqnum := len( accticq );
 var namenum := len( acctname );
 var passnum := len( acctpass );
 var hashpass := hashing( acctpass );
%>

<html>
 <head>
  <LINK rel="stylesheet" href="TYPE THE PATH TO YOUR STYLESHEET HERE/style1.css">
  <title>POL HTTP Account Adder</title>
 </head>
 <body>
  <div class="header">
   <B>POL HTTP Account Adder</B>
  </div><HR><P>

  <%
  if( !acctname or !acctpass or !acctemail or !accticq )
   %>

    Please fill in all blanks.

   <%
  elseif( acctpass != acctpass2 )
   %>

    Passwords did not match.<P>Please ensure your Password matches the Confirmation.

   <%
  elseif( acctpass == acctname )
   %>

    Please use a Password that is different from your Account Name.

   <%
  elseif( splitted[2] or splitted2[2] or splitted3[2] or splitted4[2] )
   %>

    One of your entries contained spaces.<P>Please do not use spaces.

   <%
  elseif(( !icqi ) or ( MIN_ICQ > icqnum ) or ( MAX_ICQ < icqnum ))
   %>

    Please enter your correct Icq.

   <%
  elseif(( MIN_NAME > namenum ) or ( MAX_NAME < namenum ))
   %>

    Please use between 5 and 10 characters for your Account Name.

   <%
  elseif(( MIN_PASS > passnum ) or ( MAX_PASS < passnum ))
   %>

    Please use between 6 and 16 characters for your Password.

   <%
  elseif( !domain(text) )
   %>

    Please use a non-anonymous email.

   <%
  elseif( !text["@"] or !text["."] or !suffix(text) )
   %>

    Please enter your correct email.

   <%
  elseif( usedinfo( acctname, acctemail, accticq, acctip, hashpass ) )
   %>

    Sorry, one account per person.

   <%
  else
   while( acctname["+"] )
    acctname["+"] := " ";
   endwhile
   while( acctpass["+"] )
    acctpass["+"] := " ";
   endwhile
   var ret := CreateAccount( acctname, acctpass, 1 );
   var acct := FindAccount( acctname );
   acct.setprop( "password", hashpass );
   acct.setprop( "email", acctemail );
   acct.setprop( "icq", icqi );
   acct.setprop( "ip", acctip );
   if( ret = error )
    %>

     Sorry, account creation failed.<P>
     Error: <%=ret.errortext %>

    <%
   else
    %>

     Account added successfully.<P>
     Name : <%=acctname %>.<P>
     Password : <%=acctpass %>.<P>
     Email : <%=acctemail %>.<P>
     Icq : <%=icqi %>.<P><P><P>

    <%
   endif
  endif
  %>

  Please wait, you will be forwarded in 5 seconds.<P>
  Otherwise click <a href="index.ecl">here</a>.
 </body>
</html>

<%
 function domain( text )
  var cfgfile, element, propvalue, entry;
  cfgfile := ReadConfigFile( ":*:webacct" );
  element := FindConfigElem( cfgfile, "names" );
  propvalue := GetConfigStringArray( element, "dom" );
   foreach entry in propvalue
    if( text[entry] )
     return;
    else
     return 1;
    endif
   endforeach
  UnloadConfigFile( "webacct" );	
 endfunction

 function suffix( text )
  var cfgfile, element, propvalue, entry;
  cfgfile := ReadConfigFile( ":*:webacct" );
  element := FindConfigElem( cfgfile, "types" );
  propvalue := GetConfigStringArray( element, "suf" );
   foreach entry in propvalue
    if ( text[entry] )
     return 1;
    else
     return;
    endif
   endforeach
  UnloadConfigFile( "webacct" );	
 endfunction

function usedinfo( acctname, acctemail, accticq, acctip, hashpass )
 foreach acctname in ListAccounts()
  var acct := FindAccount( acctname );
  var email := acct.getprop( "email" );
  var icq := acct.getprop( "icq" );
  var ip := acct.getprop( "ip" );
  var passhash := acct.getprop( "password" );
  if( acctip == "192.168.0.42" )
   return;
  elseif( (acctemail == email) or (accticq == icq) or (acctip == ip) or (passhash == hashpass) )
   return 1;
  endif
 endforeach
endfunction
%>