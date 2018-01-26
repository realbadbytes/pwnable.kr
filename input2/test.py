from pwn import *

args = []
args.extend(range(1,99))
args[65] = "\x00"
args[66] = "\x20\x0a\x0d"

args2 = " A "*99
r = process('./input2', args2, shell=True)

print r.recvline()
print r.recvline()
print r.recvline()
