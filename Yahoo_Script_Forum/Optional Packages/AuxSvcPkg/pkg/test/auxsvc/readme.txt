Install this package somewhere.
Restart POL
telnet to 127.0.0.1, port 5009
type "i4"<enter>
  ( you've just sent a packed integer, value 4, to the aux control script)

console displays:
event: struct{ type = "recv", value = 4 }


your telnet session displays:
a2:S8:responset2:S4:typeS4:recvS5:valuei4

