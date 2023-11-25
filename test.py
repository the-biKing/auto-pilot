
#[  0  16 156] [ 34  40 241]
import numpy as np
import cv2 as cv
cv.namedWindow('image')
def nothing(x):
    pass
#cap = cv.VideoCapture("D:\Clauser__max\Videos\Captures/123132132.mp4")
cv.createTrackbar('Hue_Lower', 'image', 0, 179, nothing)
cv.createTrackbar('Hue_Upper', 'image', 0, 179, nothing)
cv.createTrackbar('Saturation_Lower', 'image', 0, 255, nothing)
cv.createTrackbar('Saturation_Upper', 'image', 0, 255, nothing)
cv.createTrackbar('Value_Lower', 'image', 0, 255, nothing)
cv.createTrackbar('Value_Upper', 'image', 0, 255, nothing)
'''
def getLines(image):
    lines = cv.HoughLinesP(image, 0.3, np.pi/180, 100, np.array([]), minLineLength=70, maxLineGap=20)
    return lines
def displayLines(image, lines):
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4) #converting to 1d array
            cv.line(image, (x1, y1), (x2, y2), (255, 0, 0), 10)
    return image
def getLineCoordinatesFromParameters(image, line_parameters):
    slope = line_parameters[0]
    intercept = line_parameters[1]
    y1 = image.shape[0]  # since line will always start from bottom of image
    y2 = int(y1 * (3.4 / 5))  # some random point at 3/5
    x1 = int((y1 - intercept) / slope)
    x2 = int((y2 - intercept) / slope)
    return np.array([x1, y1, x2, y2])
def getSmoothLines(image, lines):
    left_fit = []  # will hold m,c parameters for left side lines
    right_fit = []  # will hold m,c parameters for right side lines

    for line in lines:
        x1, y1, x2, y2 = line.reshape(4)
        parameters = np.polyfit((x1, x2), (y1, y2), 1)
        slope = parameters[0]
        intercept = parameters[1]

        if slope < 0:
            left_fit.append((slope, intercept))
        else:
            right_fit.append((slope, intercept))

    left_fit_average = np.average(left_fit, axis=0)
    right_fit_average = np.average(right_fit, axis=0)

    # now we have got m,c parameters for left and right line, we need to know x1,y1 x2,y2 parameters
    left_line = getLineCoordinatesFromParameters(image, left_fit_average)
    right_line = getLineCoordinatesFromParameters(image, right_fit_average)
    return np.array([left_line, right_line])
'''
frame = cv.imread('D:\Clauser__max\Desktop\新增資料夾\LT1.png',1)
while(True): 
    # Capture frame-by-frame
    cv.waitKey(1000)
    cv.imshow('line',frame)
    cv.waitKey(1000)
    #frame=cv.resize(frame,(896,504))   
    # Our operations on the frame come here
    # gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    hsv=cv.cvtColor(frame,cv.COLOR_BGR2HSV)
    frame=cv.resize(frame,(896,504))
    cv.line(hsv,(358,132),(107,344),(0,0,0),200)
    cv.line(hsv,(582,132),(895,344),(0,0,0),200)
    h_lower = cv.getTrackbarPos('Hue_Lower', 'image')
    h_upper = cv.getTrackbarPos('Hue_Upper', 'image')
    s_lower = cv.getTrackbarPos('Saturation_Lower', 'image')
    s_upper = cv.getTrackbarPos('Saturation_Upper', 'image')
    v_lower = cv.getTrackbarPos('Value_Lower', 'image')
    v_upper = cv.getTrackbarPos('Value_Upper', 'image')
    hsv = hsv[210:210+148, 290:290+455]
    hsv=cv.resize(hsv,(128,128))
    # Display the resulting frame
    hL=([ 19 ,  5 ,149])
    hU=([ 40  ,47 ,215])
    lower_range = np.array(h_lower,s_lower,v_lower)
    upper_range = np.array(h_upper,s_upper,v_upper)
    #lower_range = np.array(hL)
    #upper_range = np.array(hU)
    maskB=cv.inRange(hsv,lower_range,upper_range)
    print(lower_range,upper_range)
    
    #lines = getLines(maskB)
    #smooth_lines = getSmoothLines(frame, lines) 
    #image_with_smooth_lines = displayLines(frame, lines)
    cv.imshow('line',frame)
    cv.imshow('frame',maskB)
    cv.imshow('hsv',hsv)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
        
# When everything done, release the capture
cap.release()
cv.destroyAllWindows()
'''
import matplotlib. pyplot as plt
import numpy as np
import cv2 as cv 
cap = cv.VideoCapture("D:\Clauser__max\Videos\Captures/123132132.mp4")
while(True):
    ret, frame = cap.read() 
    cv.waitKey(10)
    frame=cv.resize(frame,(896,504))  
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    ret ,twofil=cv.threshold(gray,180,255,cv.THRESH_BINARY) 
    cv.namedWindow("image",0)
    cv.imshow("image",twofil)
    mask=np.zeros_like(twofil)
    mask=cv.fillPoly(mask,np.array([[[0,460], [580 , 480],[400 , 15], [330, 15 ]]]) , color=255 )

    mei=cv.bitwise_and(twofil,mask) 
    contours,hierarchy=cv.findContours(mei,cv.RETR_EXTERNAL,cv.CHAIN_APPROX_NONE)
    for i in range(len(contours)):
        area=cv.contourArea(contours[i])
        if area<2:
            cv.drawContours(mei,[contours[i]],0,0,-1)
    cv.namedWindow("mei",0)
    cv.resizeWindow("mei",1000,1200)
    points=[]
    for i in range(896):
        for j in range(504):
            if mei[i][j]!=0:
                mei[i][j]=[0,0,255]
                points.append([i,j])
    plt.imshow(gray)
    plt.show()
    cv.namedWindow("mask",0)
    cv.resizeWindow("mask",1000,1200)
    cv.imshow("mask",mask)
    cv.imshow("frame",frame)
    cv.imshow("mei",mei)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
'''