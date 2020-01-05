<?

// This would be where you put all your normal PHP code

print shell_exec("./get_page.pl '/pkg/webview/view_chars.ecl?" . $_SERVER['argv'][0] . "'");

?>
