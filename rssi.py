import os
import sys

def rssi_x1():
    value = "0"
    os.system('hcitool rssi 50:77:05:C4:90:35 > rssi.txt')
    #$os.system('date')
    with open("rssi.txt", "r") as infile:
        for line in infile:
            output = (line.split("RSSI return value: ")[1][0])
            value = output
            print(output)
        infile.close()
    return value

def rssi_n(n):
    vals = []
    for a in range(n):
        vals.append(rssi_x1())
    
    pos = 0
    for x in vals:
        if(x == "-"):
            pos += 1
    
    if(pos >= n * .7): #at least 70% pass rate; false positives 30% or less
        return True, float(pos)/n * 100
    return False, float(pos)/n * 100

def rssi_cont():
    vals = []
    n = 200
    for a in range(n):
        vals.append(rssi_x1())
        
    pos = 0
    for x in vals:
        if(x == "-"):
            pos += 1
    
    if(pos >= n * .7): #at least 70% pass rate; false positives 30% or less
        return True, float(pos)/n * 100
    print("Too close! Trying again...")
    return rssi_cont()

#result, confidence = rssi_n(int(sys.argv[1]))
def main():
    result, confidence = rssi_cont()
    if(result):
        print("6 feet apart!")
    else:
        print("Too close!")
    print(str(confidence) + "% success rate!")
