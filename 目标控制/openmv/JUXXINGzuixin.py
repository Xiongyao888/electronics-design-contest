import sensor, image, time, math
from pid import PID
from pyb import UART
from nei import inner_rect_vertices

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=6000)
clock = time.clock()

localx = 0
localy = 0

threshold_index = 0 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(9, 70, 16, 54, 3, 35), # generic_red_thresholds
              (30, 100, -64, -8, -32, 32), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0)] # generic_blue_thresholds

red_week   = (0, 84, 12, 79, -32, 72)
red_strong = (60, 88, 7, 26, -2, 18)  #a = 18 b = 28

red_week   = (0, 36, 13, 67, -59, 44)
red_strong = (70, 100, 12, 45, -13, 10)

#b = 35

# 确保a和b的值是整数类型
#a = int(a)
#b = int(b)


juxing_x = PID(p=1, i=0.000, d=0)
juxing_y = PID(p=1, i=0.000, d=0)

err_x             = 0                    #x本次误差
err_y             = 0                    #y本次误差


# 用于保存每次识别的色块信息
blobs_list = []
#串口输出结果
import ustruct
uart = UART(3,115200)
uart.init(115200, bits = 8, parity = None, stop = 1)
def sending_data(cx,cy,cz,cw):
    global uart;
    data = ustruct.pack("<bbbbbb",
                   0xFF,
                   int(cx),
                   int(cy),
                   int(cz),
                   int(cw),
                   0xFE)
    uart.write(data);


# 定义感兴趣区域的位置和大小
roi_= (21, 11, 114, 107)

roi_h = (0, 0, 0, 0)

# 用于计数检测到的矩形数量
rect_count = 0
# 用于累加矩形顶点的坐标
sum_x1, sum_y1, sum_x2, sum_y2, sum_x3, sum_y3, sum_x4, sum_y4 = 0, 0, 0, 0, 0, 0, 0, 0
# 用于保存四次 x1 坐标的值
x1_values = []
y1_values = []
x2_values = []
y2_values = []
x3_values = []
y3_values = []
x4_values = []
y4_values = []

# 检测矩形标志位
flag = 0
flaag = 0

flag1 = 0
flag2 = 0
flag3 = 0
flag4 = 0
flag5 = 0

xx = 0

# 定义一个变量，用于保存上一个检测到的色块的中心位置横向和纵向坐标
prev_cx, prev_cy = None, None

# 最终识别到的坐标矩形坐标值
jx1,jy1,jx2,jy2,jx3,jy3,jx4,jy4 = 0,0,0,0,0,0,0,0

# 分成的小段数量
num_segments = 20
i = 0

# 距离判别阈值
ddd = 2

# 左右 1为负 零为正
zx, zy = 0, 0

flagtime = 0

shibie = 3

fflag = 1

while True:
    if uart.any() and fflag == 0:   # 判断是否有数据可读
        data = uart.read(1)   # 读取1字节数据
        data1 = uart.read(1)   # 读取1字节数据
        data1 = uart.read(1)   # 读取1字节数据
        data1 = uart.read(1)   # 读取1字节数据
        data1 = uart.read(1)   # 读取1字节数据
        data1 = uart.read(1)   # 读取1字节数据
        if data == b'\x15' and fflag == 0:
            fflag = 1
            data = 0
            print(66)
    elif fflag == 1 :
        clock.tick()
        img = sensor.snapshot()

        # 下面的`threshold`应设置为足够高的值，以滤除在图像中检测到的具有
        # 低边缘幅度的噪声矩形。最适用与背景形成鲜明对比的矩形。
        if flag == 0 :
            for r in img.find_rects( threshold = 5000):
                # 获取矩形的四个顶点坐标
                corners = r.corners()

                # 检查矩形是否在指定ROI内
                #if roi_x <= min(corners[0][0], corners[1][0], corners[2][0], corners[3][0]) <= roi_x + roi_w and \
                #        roi_y <= min(corners[0][1], corners[1][1], corners[2][1], corners[3][1]) <= roi_y + roi_h:
                img.draw_rectangle(r.rect(), color=(255, 0, 0))
                for p in corners:
                    img.draw_circle(p[0], p[1], 5, color=(0, 255, 0))
                    #print("Corner: X={}, Y={}".format(p[0], p[1]))

                # 累加矩形顶点的坐标
                sum_x1 += corners[0][0]
                sum_y1 += corners[0][1]
                sum_x2 += corners[1][0]
                sum_y2 += corners[1][1]
                sum_x3 += corners[2][0]
                sum_y3 += corners[2][1]
                sum_x4 += corners[3][0]
                sum_y4 += corners[3][1]
                # 增加矩形计数器
                rect_count += 1
                #print(rect_count)
                # 保存 x1 坐标的值
                x1_values.append(corners[0][0])
                y1_values.append(corners[0][1])
                x2_values.append(corners[1][0])
                y2_values.append(corners[1][1])
                x3_values.append(corners[2][0])
                y3_values.append(corners[2][1])
                x4_values.append(corners[3][0])
                y4_values.append(corners[3][1])

                time.sleep_ms(100)

                if rect_count == shibie:
                    break
            # 检测到四次矩形后，计算平均值并输出
            if rect_count == shibie:
                rect_count = 0
                rect_count = 0
                rect_count = 0
                rect_count = 0
                rect_count = 0
                rect_count = 0
                rect_count = 0
                rect_count = 0
                # 计算四次 x1 坐标的极差并输出
                x1_range = max(x1_values) - min(x1_values)
                y1_range = max(y1_values) - min(y1_values)
                x2_range = max(x2_values) - min(x2_values)
                y2_range = max(y2_values) - min(y2_values)
                x3_range = max(x3_values) - min(x3_values)
                y3_range = max(y3_values) - min(y3_values)
                x4_range = max(x4_values) - min(x4_values)
                y4_range = max(y4_values) - min(y4_values)
                '''
                print("X1 Range:", x1_range)
                print("Y1 Range:", y1_range)
                print("X2 Range:", x2_range)
                print("Y2 Range:", y2_range)
                print("X3 Range:", x3_range)
                print("Y3 Range:", y3_range)
                print("X4 Range:", x4_range)
                print("Y4 Range:", y4_range)
                '''

                jc = max(x1_range,y1_range,x2_range,y2_range,x3_range,y3_range,x4_range,y4_range)

                if jc <= 2 :
                    avg_x1 = sum_x1 // shibie
                    avg_y1 = sum_y1 // shibie
                    avg_x2 = sum_x2 // shibie
                    avg_y2 = sum_y2 // shibie
                    avg_x3 = sum_x3 // shibie
                    avg_y3 = sum_y3 // shibie
                    avg_x4 = sum_x4 // shibie
                    avg_y4 = sum_y4 // shibie
                    print("Average Corners: (X1={}, Y1={}), (X2={}, Y2={}), (X3={}, Y3={}), (X4={}, Y4={})".format(
                        avg_x1, avg_y1, avg_x2, avg_y2, avg_x3, avg_y3, avg_x4, avg_y4
                    ))
                    width = 2.0
                    jx1,jy1,jx4,jy4,jx3,jy3,jx2,jy2 = inner_rect_vertices(avg_x1, avg_y1, avg_x2, avg_y2, avg_x3, avg_y3, avg_x4, avg_y4)
                    print("Average Corners: (X1={}, Y1={}), (X2={}, Y2={}), (X3={}, Y3={}), (X4={}, Y4={})".format(
                        jx1, jy1, jx2, jy2, jx3, jy3, jx4, jy4
                    ))
                    flag = 1
                    sensor.set_pixformat(sensor.RGB565)
                    sensor.set_framesize(sensor.QVGA)
                    jx1 *= 2
                    jy1 *= 2
                    jx2 *= 2
                    jy2 *= 2
                    jx3 *= 2
                    jy3 *= 2
                    jx4 *= 2
                    jy4 *= 2
                    print("Average Corners: (X1={}, Y1={}), (X2={}, Y2={}), (X3={}, Y3={}), (X4={}, Y4={})".format(
                        jx1, jy1, jx2, jy2, jx3, jy3, jx4, jy4
                    ))
                    time.sleep_ms(100)

                else :
                    print('wu cha guo da')
                    time.sleep_ms(100)

                time.sleep_ms(50)
                # 清空 x1 坐标的列表和重置计数器和累加值
                x1_values.clear()
                y1_values.clear()
                x2_values.clear()
                y2_values.clear()
                x3_values.clear()
                y3_values.clear()
                x4_values.clear()
                y4_values.clear()

                rect_count = 0
                sum_x1, sum_y1, sum_x2, sum_y2, sum_x3, sum_y3, sum_x4, sum_y4 = 0, 0, 0, 0, 0, 0, 0, 0
        elif flag == 1 :
            '''
            roi_h = (round(min(jx1, jx2, jx3, jx4) - 10), round(min(jy1, jy2, jy3, jy4) - 6), round(max(jx1, jx2, jx3, jx4) - min(jx1, jx2, jx3, jx4) + 20), round(max(jy1, jy2, jy3, jy4) - min(jy1, jy2, jy3, jy4) + 12))

            for blob in img.find_blobs([thresholds[threshold_index]], roi = roi_h , pixels_threshold=10, area_threshold=10, merge=True):
                # 滤除错误识别的条件：限制横向和纵向跳变
                #if prev_cx is not None and prev_cy is not None and (abs(blob.cx() - prev_cx) > 13 or abs(blob.cy() - prev_cy) > 13):
                   # print("错误识别，横向或纵向跳变过大，忽略该色块")
                   # continue

                # 将每次识别的色块信息添加到列表中
                blobs_list.append(blob)
            if len(blobs_list) >= 2:
                # 更新 prev_cx 和 prev_cy
                avg_x = sum(blob.cx() for blob in blobs_list) // len(blobs_list)
                avg_y = sum(blob.cy() for blob in blobs_list) // len(blobs_list)
                prev_cx, prev_cy = avg_x, avg_y

                # These values are stable all the time.
                # img.draw_rectangle(blob.rect())
                img.draw_cross(avg_x, avg_y)
                # Note - the blob rotation is unique to 0-180 only.
                img.draw_keypoints([(avg_x, avg_y, int(math.degrees(blob.rotation())))], size=20)

                # 输出中心位置坐标
                #print("中心位置坐标：X={}, Y={}".format(blob.cx(), blob.cy()))
            '''



            img.draw_cross(160,109,size=2)
            blob_week = img.find_blobs([red_week], pixels_threshold=23, area_threshold=23, merge=True)
            blob_strong = img.find_blobs([red_strong], pixels_threshold=35, area_threshold=35, merge=True)
            if blob_strong:
                for b in blob_strong:
                    tmp=img.draw_rectangle(b[0:4])
                    tmp=img.draw_cross(b[5], b[6])
                    c=img.get_pixel(b[5], b[6])
                    localx=b[5]
                    localy=b[6]
                    print(int(localx),int(localy))
            elif blob_week:
                for b in blob_week:
                    tmp=img.draw_rectangle(b[0:4])
                    tmp=img.draw_cross(b[5], b[6])
                    c=img.get_pixel(b[5], b[6])
                    localx=b[5]
                    localy=b[6]
                    print(int(localx),int(localy))



            if flagtime == 0 :
                jx = jx1
                jy = jy1

            if abs(localx - jx1) <= ddd and abs(localy - jy1) <= ddd and flag1 == 0:
                flagtime = 1
                flag1 = 1
                i = 0
                dis_x = jx2 - jx1
                dis_y = jy2 - jy1
                distas = math.sqrt(dis_x**2 + dis_y**2)
                segment_length = distas / num_segments
                dx = (jx2 - jx1) / num_segments
                dy = (jy2 - jy1) / num_segments
                jx = jx1 + dx
                jy = jy1 + dy
            elif abs(localx - jx2) <= ddd and abs(localy - jy2) <= ddd and flag2 == 0:
                flag2 = 1
                i = 0
                dis_x = jx3 - jx2
                dis_y = jy3 - jy2
                distas = math.sqrt(dis_x**2 + dis_y**2)
                segment_length = distas / num_segments
                dx = (jx3 - jx2) / num_segments
                dy = (jy3 - jy2) / num_segments
                jx = jx2 + dx
                jy = jy2 + dy
            elif abs(localx - jx3) <= ddd and abs(localy - jy3) <= ddd and flag3 == 0:
                flag3 = 1
                i = 0
                dis_x = jx4 - jx3
                dis_y = jy4 - jy3
                distas = math.sqrt(dis_x**2 + dis_y**2)
                segment_length = distas / num_segments
                dx = (jx4 - jx3) / num_segments
                dy = (jy4 - jy3) / num_segments
                jx = jx3 + dx
                jy = jy3 + dy
            elif abs(localx - jx4) <= ddd and abs(localy - jy4) <= ddd and flag4 == 0:
                flag4 = 1
                flaag = 1
                i = 0
                dis_x = jx1 - jx4
                dis_y = jy1 - jy4
                distas = math.sqrt(dis_x**2 + dis_y**2)
                segment_length = distas / num_segments
                dx = (jx1 - jx4) / num_segments
                dy = (jy1 - jy4) / num_segments
                jx = jx4 + dx
                jy = jy4 + dy


            #print(flagtime)

            err_x = localx - jx        #偏移量
            err_y = localy - jy
            speed_x = juxing_x.get_pid(err_x,1.2)
            speed_y = juxing_y.get_pid(err_y,1.2)


            #小段目标检测
            if abs(localx - jx) <= ddd and abs(localy - jy) <= ddd and i <= num_segments - 1 :
                jx += dx
                jy += dy
                i += 1
                if flaag == 1 :
                    xx += 1
            print(xx)


            print(speed_x, speed_y)
            print("激光位置坐标：X={}, Y={}".format(localx, localy))



            print("i:", i)
            print(jx1, jy1)
            print("目标位置坐标：X={}, Y={}".format(jx, jy))



            if xx == num_segments :
                speed_x = 0
                speed_y = 0
                sending_data(3,6,6,6)
                flag = 0
                flaag = 0
                flag1 = 0
                flag2 = 0
                flag3 = 0
                flag4 = 0
                flag5 = 0
                xx = 0
                fflag = 0


            #print("：X={}, Y={}".format(int(speed_x), int(speed_y)))
            if speed_x < 0 :
                speed_x *= -1
                zx = 1
            elif speed_x >= 0 :
                zx = 2
            if speed_y < 0 :
                speed_y *= -1
                zy = 1
            elif speed_y >= 0 :
                zy = 2
            #print(speed_x,speed_y)
            #print(int(zx),int(speed_x),int(zy),int(speed_y))

            time.sleep_ms(20)
            sending_data(zx,speed_x,zy,speed_y)
            # 将下面这行代码移出if块
            blobs_list.clear()

