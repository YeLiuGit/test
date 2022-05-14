import socket
import sys
import time
import random
import struct
    
class Mypacket(object):
    class Struct(object):
        def __init__(self, header, data):
            self.TYPE = TYPE
            self.size = size
            self.data = data

    def make_packet(self, TYPR, size, data):
            return self.Struct(TYPE, size, data)

packet = Mypacket()
    
def main(argv):
    port = int(argv[1])
    server = socket.socket()
    host = socket.gethostname()
    print("hostname is {}".format(host))
    
    server.bind((host, port))
    server.listen(5)
    print("listening on port {}".format(port))
    while True:
        client,addr = server.accept()
        print("connect to {}".format(addr))
        
        
        message = client.recv(1024)
        print("{} bytes data received, message is: {}".format(sys.getsizeof(message), message.decode()))
        time.sleep(int(random.random() * 10))
        client.send(message)
        print("message returned back")
        #c.close
        #print("connection breaked")
        print("listening on port {}".format(port))
        
        
if __name__ == "__main__":
    main(sys.argv)
