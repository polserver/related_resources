#!/usr/bin/perl -w
# 
# I suck with Perl. It's just a quick hack. Forgive me.
# Last Modified: 06/13/04
#

use strict;
use Net::HTTP;

# CHANGE THIS HERE.
my $host = "http://myhost.com:5002";

my $page = $ARGV[0];
if ($ARGV[1]) {
	$page .= $page + $ARGV[1];
}

my $s = Net::HTTP->new(Host => $host) or die($!);
$s->keep_alive;
$s->write_request(GET => $page, 'Connection' => "keep-alive");
my ($code, $mess, %h) = $s->read_response_headers;

while ($code == 200) {
	if (lc(substr($h{"Content-Type"}, 0, length("text/html"))) ne "text/html") {
		return;
	}

	my $buf;
	my $n = $s->read_entity_body($buf, $h{"Content-Length"});
	die "read failed: $!" unless defined $n;
	last unless $n;
	print $buf;
}
