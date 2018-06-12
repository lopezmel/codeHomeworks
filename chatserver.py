#!/usr/bin/python
#server

import socket
import sys
import signal
import time
import threading
import re

#error checking 
if(len(sys.argv) != 2):
        print "usage: ./chatserver.py port"
        sys.exit(1)

port = int (sys.argv[1])

#creating global mutex and var
mutex = threading.Lock()


#exit gracefully 
def signalHandler(signal, frame):

        print ' Pressed signal'

        #exit gracefully
        sys.exit(0)


#recive messages 
#sinal.pause()
def th(y):

        while True:

                st = y.recv(1024)



try:

        s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind(('127.0.0.1', port))

        #create an empty dictinary 
        d = {}

        #create empty list 
        threads = []

        #print "dictionay before threads", d    

        while True:
                print "server: waiting for connection..."
                s.listen(5) #backlog 5

                #register signal handler 
                signal.signal(signal.SIGINT, signalHandler)
                (conn, addr) = s.accept()
                print "server: connected to", addr

                #span threads
                t = threading.Thread(target=th, args=(conn,))
                t.start()
                threads.append(t)

        #wait for threads to finish executing and join 
        for th in threads:
                th.join()


        #close connections 
        s.close()
        conn.close()

#error 
except Exception as err:
        print err

