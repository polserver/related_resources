/////////////////////////////////////////
// SelectAccount plug-in for GMtools!
//
// Author: Dougall (dougalloogle@yahoo.com)
// Thanks: Bishop - author of GMtools!
/////////////////////////////////////////
// Installing....
//
// 1. Add this include file to 
//      pol\pkg\tools\gmtools\textcmd\gm
// 2. Open gmtools\textcmd\gm\gmtools.src
//    in a text editor.
// 3. Under the other include statements add
//      include "selectAccount";
// 4. Find the function AccountListing
// 5. Before the commented out code add
//      return (SelectAccount(who));
// 6. Comment out the rest of the code
//    in this function. (for tidyness!)
// 7. Recompile gmtools and try it out!
//
/////////////////////////////////////////
//
// Notes:
// - Accounts are grouped together into
//   groups and a group can then be selected.
// - Once the group has been selected you
//   can select the actual account you want
//   from that group.
// - Should theoretically be able to cope
//   with tens of thousands of accounts!
//
/////////////////////////////////////////
// TODO: 
// - Sort accounts without case sensitivity
//
/////////////////////////////////////////

const ACCOUNTS_PER_GROUP    := 200; // how many accounts are grouped together in each account group.
const ACCOUNTS_PER_PAGE     := 25;  // how many accounts are displayed per select account page.
const ACCOUNTGROUPS_PER_PAGE:= 15;  // how many accountgroups are displayed per select account group page.

/////////////////////////////////////////

const LINE_HEIGHT:=20;
const BUTTON_OFFSET:=200;

/////////////////////////////////////////

function SelectAccount(who)
  var accounts:=ListAccounts();
  accounts.sort();
  var meta_pages:=1+Cint(len(accounts)/ACCOUNTS_PER_GROUP);
  if (meta_pages=1)
    return (Select_AccountGump(who,accounts,1));
  else
    var account;
    var display_page:=Select_AccountsGroup(who,accounts,meta_pages);
    while (display_page)
      account:=Select_AccountGump(who,accounts,display_page);
      if (!account)
        display_page:=Select_AccountsGroup(who,accounts,meta_pages);
      endif
    endwhile
    return (account);
  endif
endfunction

/////////////////////////////////////////

function Select_AccountGump(who,accounts,display_page)
  var start_i:=((display_page-1)*ACCOUNTS_PER_GROUP)+1;
  var end_i:=(display_page*ACCOUNTS_PER_GROUP);
  if (end_i>len(accounts))
    end_i:=len(accounts);
  endif
  var i;
  var display_accounts:=array;
  for (i:=start_i;i<=end_i;i:=i+1)
    if (accounts[i])
      display_accounts.append(accounts[i]);
    endif
  endfor
  var acct_buttons:=BUTTON_OFFSET;
  var this_layout:={
     "page 0",
     "resizepic 0 0 5100 300 "+(80+(ACCOUNTS_PER_PAGE*LINE_HEIGHT)),
     "gumppic 30 30 3001",
     "text 100 10 0 0" };
  var this_data:={"Select Account"};
  var build_page:=1;
  while (Build_SelectAccountPage(display_accounts,build_page,acct_buttons,this_layout,this_data))
    build_page:=build_page+1;
  endwhile
  var retval:=SendDialogGump(who,this_layout,this_data);
  for (i:=200;i<=acct_buttons;i:=i+1)
    if (retval[i+1])
      return (display_accounts[i-BUTTON_OFFSET]);
    endif
  endfor
  return 0;
endfunction

/////////////////////////////////////////

function Build_SelectAccountPage(byref display_accounts,byref build_page,byref acct_buttons,byref this_layout,byref this_data)
  var i,notfinished:=1;
  var start_i:=((build_page-1)*ACCOUNTS_PER_PAGE)+1;
  var end_i:=(build_page*ACCOUNTS_PER_PAGE);
  this_layout.append("page "+build_page);
  this_layout.append("text 265 10 0 "+len(this_data));
  this_data.append(build_page);
  if (build_page>1)
    this_layout.append("button 265 50 250 251 0 "+(build_page-1));
  endif
  if (end_i<len(display_accounts))
    this_layout.append("button 265 "+(40+(ACCOUNTS_PER_PAGE*LINE_HEIGHT))+" 252 253 0 "+(build_page+1));
  else
    end_i:=len(display_accounts);
    notfinished:=0;
  endif
  for (i:=start_i;i<=end_i;i:=i+1)
    if (len(display_accounts[i]))
      var y:=40+((i-start_i)*LINE_HEIGHT);
      this_layout.append("croppedtext 80 "+y+" 180 20 0 "+len(this_data));
      this_data.append(display_accounts[i]);
      this_layout.append("button 40 "+y+" 4005 4007 1 0 "+(i+BUTTON_OFFSET+1));
      acct_buttons:=acct_buttons+1;
    else
      break;
    endif
  endfor
  return notfinished;
endfunction

/////////////////////////////////////////

function Select_AccountsGroup(who,accounts,meta_pages)
  var this_layout:={
     "page 0",
     "resizepic 0 0 5100 300 "+(80+(ACCOUNTGROUPS_PER_PAGE*LINE_HEIGHT)),
     "gumppic 30 30 3001",
     "text 60 10 0 0",
     "page 1" };
  var this_data:={"Select Account Group"};
  var select_buttons:=array;
  var i;
  var pagei:=1;
  var pagecount:=1;
  for (i:=1;i<=meta_pages;i:=i+1)
    var y:=20+(pagei*LINE_HEIGHT);
    var show_first:=accounts[((i-1)*ACCOUNTS_PER_GROUP)+1];
    var show_last;
    if ((i*ACCOUNTS_PER_GROUP)<=len(accounts))
      show_last:=accounts[(i*ACCOUNTS_PER_GROUP)];
    else
      show_last:=accounts[len(accounts)];
    endif
    this_layout.append("croppedtext 80 "+y+" 70 20 0 "+len(this_data));
    this_data.append(show_first);
    this_layout.append("croppedtext 160 "+y+" 100 20 0 "+len(this_data));
    this_data.append("-> "+show_last);
    this_layout.append("button 40 "+y+" 4005 4007 1 0 "+(i+BUTTON_OFFSET));
    pagei:=pagei+1;
    if (pagei>=ACCOUNTGROUPS_PER_PAGE)
      pagei:=1;
      this_layout.append("text 265 10 0 "+len(this_data));
      this_data.append(pagecount);
      this_layout.append("button 265 "+(40+(ACCOUNTGROUPS_PER_PAGE*LINE_HEIGHT))+" 252 253 0 "+(pagecount+1));
      pagecount:=pagecount+1;
      this_layout.append("page "+pagecount);
      this_layout.append("button 265 50 250 251 0 "+(pagecount-1));
    endif
  endfor
  if (pagecount>1)
    this_layout.append("text 265 10 0 "+len(this_data));
    this_data.append(pagecount);
  endif
  var retval:=SendDialogGump(who,this_layout,this_data);
  for (i:=1;i<=meta_pages;i:=i+1)
    if (retval[(i+BUTTON_OFFSET)])
      return (i);
    endif
  endfor
  return 0;
endfunction

/////////////////////////////////////////
