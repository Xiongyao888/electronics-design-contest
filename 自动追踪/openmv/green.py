import sensor
import image
import lcd
import time


from pyb import UART

uart = UART(3, 9600)


Flag            = 0
localx          = 0
localy          = 0

errx             = 0                    #本次误差
old_errx         = 0                    #上次误差

erry             = 0                    #本次误差
old_erry         = 0                    #上次误差

Kp              = 0.4                #PID比例系数
Kd              = 0.0                   #PID微分系数
flag            = 0                     #追逐停止标志位

Speedx           = 0                    #期望速度
Speed_leftx      = 0                    #左轮速度
Speed_rightx     = 0                    #右轮速度

Speedy           = 0                    #期望速度
Speed_lefty      = 0                    #左轮速度
Speed_righty     = 0                    #右轮速度

px1              = 0
px2              = 0
px3              = 0
px4              = 0
px5              = 0
px6              = 0
px7              = 0
px8              = 0

py1              = 0
py2              = 0
py3              = 0
py4              = 0
py5              = 0
py6              = 0
py7              = 0
py8              = 0

pxaverage        = 0
pyaverage        = 0

pxmax            = 20
pymax            = 20

px               =[0,0,0,0,0,0,0,0]
py               =[0,0,0,0,0,0,0,0]

def sending_data(x,y,z,):                            #向单片机发送数据包
    global uart;
    FH = bytearray([0x2C,0x12,x,y,z,0x5B])
    uart.write(FH);

lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)                  #彩色模式
sensor.set_framesize(sensor.QVGA)                    #320x240
sensor.skip_frames(10) # 跳过10帧，使新设置生效

red_week   = (0, 84, 12, 79, -32, 72)
red_strong = (60, 88, 7, 26, -2, 18)

while True:
    img=sensor.snapshot()
    img.draw_cross(160,109,size=2)


    blob_week = img.find_blobs([red_week], pixels_threshold=18, area_threshold=18, merge=True)
    blob_strong = img.find_blobs([red_strong], pixels_threshold=28, area_threshold=28, merge=True)

    if blob_strong:
        for b in blob_strong:
            tmp=img.draw_rectangle(b[0:4])      #画外框
            tmp=img.draw_cross(b[5], b[6])      #画出中心十字
            c=img.get_pixel(b[5], b[6])

            #PID计算
            localx=b[5]                                    #外框中心x坐标
            localy=b[6]                                    #外框中心y坐标

            px8 = px7
            px7 = px6
            px6 = px5
            px5 = px4
            px4 = px3
            px3 = px2
            px2 = px1
            px1 = localx

            py8 = py7
            py7 = py6
            py6 = py5
            py5 = py4
            py4 = py3
            py3 = py2
            py2 = py1
            py1 = localy

            px  = [px1,px2,px3,px4,px5,px6,px7,px8]
            py  = [py1,py2,py3,py4,py5,py6,py7,py8]

            pxaverage = (px1+ px2+ px3+ px4 +px5+ px6+ px7+ px8)/8
            pyaverage = (py1+ py2+ py3+ py4 +py5+ py6+ py7+ py8)/8

            for i in range(8):
                if px[i]>(pxaverage+pxmax):
                    px[i] = pxaverage
                if px[i]<(pxaverage-pxmax):
                    px[i] = pxaverage

            for i in range(8):
                if py[i]>(pyaverage+pymax):
                    py[i] = pyaverage
                if py[i]<(pyaverage-pymax):
                    py[i] = pyaverage

            pxaverage = (px[0]+px[1]+px[2]+px[3]+px[4]+px[5]+px[6]+px[7])/8
            pyaverage = (py[0]+py[1]+py[2]+py[3]+py[4]+py[5]+py[6]+py[7])/8

            errx=pxaverage-160                       #偏移量
            Speed_rightx = Speedx - (Kp*errx+Kd*(errx-old_errx))
            Speed_leftx  = Speedx + (Kp*errx+Kd*(errx-old_errx))
            old_errx = errx

            erry=pyaverage-109                       #偏移量
            Speed_righty = Speedy - (Kp*erry+Kd*(erry-old_erry))
            Speed_lefty  = Speedy + (Kp*erry+Kd*(erry-old_erry))
            old_erry = erry



    elif blob_week:
        for b in blob_week:
            tmp=img.draw_rectangle(b[0:4])      #画外框
            tmp=img.draw_cross(b[5], b[6])      #画出中心十字
            c=img.get_pixel(b[5], b[6])

           #PID计算
            localx=b[5]                                    #外框中心x坐标
            localy=b[6]                                    #外框中心y坐标

            px8 = px7
            px7 = px6
            px6 = px5
            px5 = px4
            px4 = px3
            px3 = px2
            px2 = px1
            px1 = localx

            py8 = py7
            py7 = py6
            py6 = py5
            py5 = py4
            py4 = py3
            py3 = py2
            py2 = py1
            py1 = localy

            px  = [px1,px2,px3,px4,px5,px6,px7,px8]
            py  = [py1,py2,py3,py4,py5,py6,py7,py8]

            pxaverage = (px1+ px2+ px3+ px4 +px5+ px6+ px7+ px8)/8
            pyaverage = (py1+ py2+ py3+ py4 +py5+ py6+ py7+ py8)/8

            for i in range(8):
                if px[i]>(pxaverage+pxmax):
                    px[i] = pxaverage
                if px[i]<(pxaverage-pxmax):
                    px[i] = pxaverage

            for i in range(8):
                if py[i]>(pyaverage+pymax):
                    py[i] = pyaverage
                if py[i]<(pyaverage-pymax):
                    py[i] = pyaverage

            pxaverage = (px[0]+px[1]+px[2]+px[3]+px[4]+px[5]+px[6]+px[7])/8
            pyaverage = (py[0]+py[1]+py[2]+py[3]+py[4]+py[5]+py[6]+py[7])/8

            errx=pxaverage-160                      #偏移量
            Speed_rightx = Speedx - (Kp*errx+Kd*(errx-old_errx))
            Speed_leftx  = Speedx + (Kp*errx+Kd*(errx-old_errx))
            old_errx = errx

            erry=pyaverage-109                       #偏移量
            Speed_righty = Speedy - (Kp*erry+Kd*(erry-old_erry))
            Speed_lefty  = Speedy + (Kp*erry+Kd*(erry-old_erry))
            old_erry = erry

    lcd.display(img)

    print(int(localx),int(localy),int(Speed_leftx),int(Speed_righty))

    sending_data(int(localx),int(Speed_leftx),int(Speed_righty))
