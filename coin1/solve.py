import time
from pwn import *

found = False

HOST = "pwnable.kr"
PORT = 9007
r= remote(HOST, PORT)

#initial banner and sleep
r.recv()
time.sleep(3)



def find_coin(N, C):
    
    print "N {}, C {}\n".format(N, C)
    left_half = range(0, int(N)//2)
    right_half = range(int(N)//2, int(N))

    # weigh left half
    left_str = ' '.join(str(v) for v in left_half)
    print "sending {}".format(left_str)
    r.sendline(left_str)
    left_weight = r.recvline()
    print "left weight: " + left_weight

    #weigh right half
    right_str = ' '.join(str(v) for v in right_half)
    print "sending {}".format(right_str)
    r.sendline(right_str)
    right_weight = r.recvline()
    print "right weight: " + right_weight

    # base cases
    if int(left_weight) == 9:
        print "[+] FOUND COUNTERFEIT at {}".format(left_weight)
        return left_str

    if int(right_weight) == 0:
        print "[+] FOUND COUNTERFEIT at {}".format(right_weight)
        return right_str

    # recursive cases
    if int(left_weight)%2 != 0:
        print "recurse left side"
        find_coin(0, int(N)//2)
    else:
        print "recurse right side"
        find_coin(int(N)//2, N)
    
def main():
    for i in range(100):
        # get coins and tries
        line = r.recvline().split()
        N = line[0].split("=")[1]
        C = line[1].split("=")[1]
        r.sendline(find_coin(N, C))
    r.recv()

if __name__ == '__main__':
    main()
