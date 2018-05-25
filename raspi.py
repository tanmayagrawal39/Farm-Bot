from firebase import firebase
import time as time
import threading
import serial
import cv2
import pyrebase

serial=serial.Serial("COM7",9600)


time.sleep(2)
serial.write('1'.encode())
print("1")
temp =int(25)
hum =int(0)
sun =int(0)
firebase = firebase.FirebaseApplication('https://cncproj-a880d.firebaseio.com/', None)


def checkTemp():
    print("temp :")
    time.sleep(2)
    serial.write("checkTemperature".encode())
    temp =serial.readline()
    temp=temp.decode()
    print(temp)
    firebase.put('/cnc/environment','/Temperature',temp)
    return temp


def checkHum():
    print("humidity :")
    time.sleep(2)
    serial.write("checkHumidity".encode())
    hum =serial.readline()
    hum=hum.decode()
    print(hum)
    firebase.put('/cnc/environment','/Humidity',hum)
    return hum

def checkSun():
    print("sunny :")
    time.sleep(2)
    serial.write("checkSun".encode())
    sun =serial.readline()
    sun=sun.decode()
    print(sun)
    firebase.put('/cnc/environment','/Sun',sun)
    return sun

def fuzzyLogic(sun,temp,hum):
    if int(sun) > 25:
        if int(temp)<25:
            return 150
        elif int(temp)< 32:
            return 90
        elif int(temp)<40:
            return 60
        elif int(temp)<50:
            return 30
        else:
            return 15
    return 180

def moveTo(x,y):
    time.sleep(1)
    print("Moving to:",x,y)
    serial.write("moveTo".encode());
    time.sleep(3)
    xx=str(x)
    serial.write(xx.encode())
    done=serial.readline()
    print(done.decode())
    time.sleep(2)
    xx=str(y)
    serial.write(xx.encode())
    done=serial.readline()
    print(done.decode())
    print("written")
    time.sleep(1)


    done=serial.readline()
    print(done.decode())

    done=serial.readline()
    print(done.decode())
    
    done=serial.readline()
    print(done.decode())
    video = cv2.VideoCapture(0)
    ret, im = video.read()
    #cv2.imshow("test picutre", im)
    cv2.imwrite("test1.jpg",im)
    video.release()
    

    config = {
    "apiKey": "AIzaSyAkRS3SPqdS2Jr4I4W_DKc7luoGpP33vQg",
    "authDomain": "sample-1886e.firebaseio.com",
    "databaseURL": "https://sample-1886e.firebaseio.com/",
    "storageBucket": "sample-1886e.appspot.com"
    }

    #print("here 1")
    firebase1 = pyrebase.initialize_app(config)
    #print("here 2")
    storage = firebase1.storage()
    #print("here 3")
    storage.child("example1.jpg").put(r"C:\Users\harsh\AppData\Local\Programs\Python\Python36\test1.jpg")
    serial.flush()
    #capture();
    return

def moveToAll():
    flag=int(1)
    for i in range(1,4):
        if flag==1:
            for j in range(1,4):
                moveTo(i,j)
            flag=0
        else:
            for j in range(3,0,-1):
                moveTo(i,j)
            flag=1
    
    return


temp= checkTemp()
hum= checkHum()
sun= checkSun()
print(temp,hum,sun)
time.sleep(1)
#bt=fuzzyLogic(sun,temp,hum)
#print(bt)
moveToAll()

time.sleep(2)

serial.write("moveToOrigin".encode())

temp =serial.readline()
temp=temp.decode()
print(temp)

serial.flush()
serial.close()
