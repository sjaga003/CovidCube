import getch
from gpiozero import LED, Button
import time


count = 0
pwd = "57613"
led1 = LED(17)
led2 = LED(27)
led3 = LED(22)
led4 = LED(5)
led5 = LED(6)
ledR = LED(23)
finishSignal = LED(16)
startSignal = Button(4, pull_up=False)

while(count != 5):
    print("outside")
    if(startSignal.is_pressed):
        #startSignal.wait_for_press()
        while(count != 5):
            print("inside")
            val = getch.getch()
            if(val != pwd[count]):
                print("Mistake")
                count = 0
                led5.off()
                led4.off()
                led3.off()
                led2.off()
                led1.off()
                flash = 0
                while(flash != 4):
                    ledR.toggle()
                    time.sleep(0.1)
                    flash = flash + 1
                ledR.off()
            else:
                count = count + 1
                print("correct")
            if (count == 1) and not(led1.is_lit):
                led1.on()
            elif (count == 2) and not(led2.is_lit):
                led2.on()
            elif (count == 3) and not(led3.is_lit):
                led3.on()
            elif (count == 4) and not(led4.is_lit):
                led4.on()
            elif (count == 5) and not(led5.is_lit):
                led5.on()

print("Completed puzzle")
time.sleep(3)
finishSignal.on()
time.sleep(0.5)
finishSignal.off()
