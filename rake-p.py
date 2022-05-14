import sys
import socket
import subprocess
import threading
import select
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

def readfile(filename):
    try:
        fd = open(filename, 'r')
    except:
        print("fail to read rakefile file")
        return 1
    
    #default port number
    port = None
    hosts = []
    action = []
    actions = []
    actionsetcount = 0
    linecount = 0
    
    for line in fd.readlines():
        
        if not (line.startswith("#") or line == "\n"):
            word_in_list = line[:-1].split()
            #print(line[:-1])
            #find the default port number
            if word_in_list[0] == "PORT":
                port = int(word_in_list[-1])
            #find the hosts
            elif word_in_list[0] == "HOSTS":
                for word in word_in_list[2:]:
                    hosts.append(word)
                        
            elif word_in_list[0].startswith("actionset"):
                actions.append(action)
                action = []
                actionsetcount += 1

            elif line.startswith("\t"):
                action.append(line[:-1])
            else:
                print("line {0} in {1} has no meaning, please modify {1}, and try later.".format(linecount, filename))
                return None
        linecount += 1

    actions.append(action)
    
    return port, hosts, actions

def execute(command):
    '''execute a command and return output and exit status'''
    ret = subprocess.run(command,shell=True)
    #print("output: {}".format(ret.stdout))
    #print("status: {}".format(ret.returncode))
    return ret.stdout, ret.returncode

def connect(host, port):
    client = socket.socket()
    try:
        client.connect((host, port))
        print("connected to {} at port {}".format(host, port))
    except:
        print("fail to connect a server")
        return 1
    message = "this is a message"
    '''
    quote_p = packet.make_packet("quote_ask", sys.getsizeof(message), message)
    
    type_len = len(quote_p.TYPE)
    data_len = len(quote_p.data)
    
    packed_packet = struct.pack("!{}si{}s".format(type_len, data_len), quote_p.TYPE, quote_p.size, quote_p.data);
    
    client.send(packed_packet)
    '''
    client.send(message.encode())
    print("messaged sent")
    message = client.recv(1024)
    print("{} bytes message received, message is: {}".format(sys.getsizeof(message), message.decode()))
    client.close()
    #print("one thread exited")
    return 0
    

def host_check(host_str, default_port):
    if ":" in host_str:
        host_port = host_str.split(":")
        host = host_port[0]
        port = int(host_port[1])
    else:
        host = host_str
        port = default_port
    
    if host == "localhost":
        host = socket.gethostname()
    #print("host is : {}, port is : {}".format(host, port))
    return host, port

def main(argv):
    argc = len(argv)

    if argc == 1:
        print("'rakefile' file name is required")
        return 1
    elif argc > 2:
        print("only one parameter allowed")
        return 1
    else:
        try:
            port, hosts, actions = readfile(argv[1])
        except:
            return 1
        #for ele in actions:
            #print(ele)
        
    if len(hosts) != 10:
        for host in hosts:
            cur_host, cur_port = host_check(host, port)
            threading.Thread(target=connect, args=(cur_host, cur_port)).start()
            #print("one thread started")
    '''
    for action in actions:
        for command in action:
            execute(command)
    return 0
    '''
    
if __name__ == "__main__":
    main(sys.argv)