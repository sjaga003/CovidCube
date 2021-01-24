from gpiozero import LED, Button
startsignal = Button(4, pull_up = False)
finishsignal =LED(16)
wrongLED = LED(17)
rightLED = LED(27)
import time
def rightLEDon():
    rightLED.on()
    time.sleep(0.2)
    rightLED.off()
    
def wrongLEDon():
    wrongLED.on()
    time.sleep(0.2)
    wrongLED.off()
    
def Puzzle5():
    out = False
    First = True
    Second = True
    Third = True
    Fourth = True
    while not out:
        print("waiting")
        if(startsignal.is_pressed):    
            out = True
    while out:
        print("waiting2")
        fo = open("ID.txt")
        cardID = fo.readline()
        if cardID != "":
            if First:
                if cardID == "P1":
                    First = False
                    rightLEDon()
                else:
                    wrongLEDon()
            elif Second:
                if cardID == "P4":
                    Second = False
                    rightLEDon()
                else:
                    First = True
                    wrongLEDon()
            elif Third:
                if cardID == "P2":
                    Third = False
                    rightLEDon()
                else:
                    First = True
                    Second = True
                    wrongLEDon()
            elif Fourth:
                if cardID == "P3":
                    Fourth = False
                    rightLEDon()
                    finishsignal.on()
                    time.sleep(0.2)
                    finishsignal.off()
                    out = False
                else:
                    First = True
                    Second = True
                    Third = True
                    wrongLEDon()
        cardID = ""
        fo.close()
        fl = open("ID.txt","w")
        fl.close()

        
Puzzle5() 



    
    -