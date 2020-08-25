import bluetooth
from gpiozero import LED, Button
import time
import rssi
#import os

server_socket=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
button = Button(2)
led = LED(17)
ard = Button(27)

port = 1
server_socket.bind(("",port))
server_socket.listen(1)
count = 0 
client_socket,address = server_socket.accept()
print("Accepted connection from ", address)
val = 0

override = True
while 1:
 #print("Starting Puzzle 1")
 #os.system('python3 rssi.py') #This call will continue recursively until successful, returning 1
 #if(val == 0):
  #   val = rssi.rssi_cont()
   #  if(val == True):
    #     print("Puzzle 1 complete!")
    
 if ard.is_pressed:
     print("Recieved signal from arduino")
 if button.is_pressed or override:
    print("Button pressed..")
    led.on()
    if count == 0:
      client_socket.send("puzzle1_start")
      print("Sent puzzle1_start")
      rssi.main()
    elif count == 1:
      override = False
      client_socket.send("puzzle2_start")
      print("Sent puzzle2_start")
    elif count == 2:
      client_socket.send("puzzle3_start")
      print("Sent puzzle3_start")
    elif count == 3:
      client_socket.send("puzzle4_start")
      print("Sent puzzle4_start")
    elif count == 4:
      client_socket.send("puzzle5_start")
      print("Sent puzzle5_start")
    elif count == 5:
      client_socket.send("completed")
      print("Sent completed")
    count = count + 1
    time.sleep(0.5)
# data = client_socket.recv(1024)
 #print("Received: ", data.decode())

client_socket.close()
server_socket.close()
