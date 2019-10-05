import cv2
import numpy as np


vid = cv2.VideoCapture("./IMG_3841.MOV")

frame_width=640
frame_height=480
fourcc = cv2.VideoWriter_fourcc(*'H264')#-1
out = cv2.VideoWriter("./birthday.avi",fourcc, 16, (frame_width,frame_height), True)

while True:
        
        ret, frame = vid.read()
        if ret==True:

                smallFrame = cv2.resize(frame, (frame_width,frame_height), interpolation=cv2.INTER_LINEAR)
                # cv2.imshow('original', smallFrame)
        #         cv2.imshow('edges', edges)         
                cv2.imshow('frame', smallFrame)  

                out.write(smallFrame)



                if cv2.waitKey(1) & 0xFF == ord('q'):
                        break
        else:
                break
        vid.release()
        out.release()
        cv2.destroyAllWindows()