<?

// This would be where you put all your normal PHP code

print shell_exec("./get_page.pl '/pkg/webview/view_guilds.ecl?" . $_GET['guildid'] . "'");

?>

