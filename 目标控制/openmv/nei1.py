import math

# 定义中心点坐标
CEN_X = 74
CEN_Y = 82

# 归一化向量
def normalize_vector(vec):
    x, y = vec
    length = math.sqrt(x**2 + y**2)
    return (x / length, y / length)

# 计算两个向量的平均单位向量
def average_unit_vectors(u, v):
    u_x, u_y = u
    v_x, v_y = v
    w = (u_x + v_x, u_y + v_y)
    w_normalized = normalize_vector(w)
    return w_normalized

# 找到通过两点的线性函数
def find_linear_function(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    slope = (y2 - y1) / (x2 - x1)
    intercept = y1 - slope * x1
    def linear_function(x):
        return slope * x + intercept
    return linear_function

# 计算给定距离的点B的坐标
def calculate_point_b(ax, ay, ux, uy, d):
    bx = ax + ux * d
    by = ay + uy * d
    return bx, by

# 计算内矩形的顶点坐标
def inner_rect_verstices(x1, y1, x2, y2, x3, y3, x4, y4):
    # 计算每条边的向量和长度
    lgcen1 = [x1 - CEN_X, y1 - CEN_Y]
    lgcen2 = [x2 - CEN_X, y2 - CEN_Y]
    lgcen3 = [x3 - CEN_X, y3 - CEN_Y]
    lgcen4 = [x4 - CEN_X, y4 - CEN_Y]
    edge1 = [x2 - x1, y2 - y1]
    edge2 = [x3 - x2, y3 - y2]
    edge3 = [x4 - x3, y4 - y3]
    edge4 = [x1 - x4, y1 - y4]

    # 计算中心到每个顶点的距离
    longcentr1 = math.sqrt(lgcen1[0]**2 + lgcen1[1]**2)
    longcentr2 = math.sqrt(lgcen2[0]**2 + lgcen2[1]**2)
    longcentr3 = math.sqrt(lgcen3[0]**2 + lgcen3[1]**2)
    longcentr4 = math.sqrt(lgcen4[0]**2 + lgcen4[1]**2)

    # 计算每条边的宽度
    width1 = linear_func(longcentr1)
    width2 = linear_func(longcentr2)
    width3 = linear_func(longcentr3)
    width4 = linear_func(longcentr4)

    # 计算每条边的内边长
    edge1_norm = math.sqrt(edge1[0]**2 + edge1[1]**2)
    edge2_norm = math.sqrt(edge2[0]**2 + edge2[1]**2)
    edge3_norm = math.sqrt(edge3[0]**2 + edge3[1]**2)
    edge4_norm = math.sqrt(edge4[0]**2 + edge4[1]**2)
    neiedge1 = edge1_norm / 2 - width1
    neiedge2 = edge2_norm / 2 - width2
    neiedge3 = edge3_norm / 2 - width3
    neiedge4 = edge4_norm / 2 - width4

    # 计算内矩形的四条边的长度
    neiedge11 = ((edge1_norm + edge3_norm) / 2 - (width2 + width3)) / 2
    neiedge21 = ((edge2_norm + edge4_norm) / 2 - (width3 + width4)) / 2
    neiedge31 = ((edge3_norm + edge1_norm) / 2 - (width4 + width1)) / 2
    neiedge41 = ((edge4_norm + edge2_norm) / 2 - (width1 + width2)) / 2

    # 计算每条边的单位向量
    edge1_unit = [edge1[0] / edge1_norm, edge1[1] / edge1_norm]
    edge2_unit = [edge2[0] / edge2_norm, edge2[1] / edge2_norm]
    edge3_unit = [edge3[0] / edge3_norm, edge3[1] / edge3_norm]
    edge4_unit = [edge4[0] / edge4_norm, edge4[1] / edge4_norm]

    # 计算平行边的单位向量
    edge32_unit = [edge3_unit[0]*(-1),edge3_unit[1]*(-1)]
    edge42_unit = [edge4_unit[0]*(-1),edge4_unit[1]*(-1)]
    edge12_unit = [edge1_unit[0]*(-1),edge1_unit[1]*(-1)]
    edge22_unit = [edge2_unit[0]*(-1),edge2_unit[1]*(-1)]

    # 计算四个边的平均单位向量
    edge1_unit1 = average_unit_vectors(edge1_unit, edge32_unit)
    edge2_unit1 = average_unit_vectors(edge2_unit, edge42_unit)
    edge3_unit1 = average_unit_vectors(edge3_unit, edge12_unit)
    edge4_unit1 = average_unit_vectors(edge4_unit, edge22_unit)

    # 计算中心点的坐标
    center_x = (x1 + x2 + x3 + x4) / 4
    center_y = (y1 + y2 + y3 + y4) / 4

    # 设置起始点为中心点
    ax, ay = center_x, center_y

    # 设置x方向和y方向的单位向量，计算顶点1的坐标
    ux, uy = edge1_unit1[0], edge1_unit1[1]
    d = neiedge11
    bx1, by1 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx1, by1

    # 设置x方向和y方向的单位向量，计算顶点2的坐标
    ux, uy = edge2_unit[0]*-1, edge2_unit[1]*-1
    d = neiedge2
    inner_x1, inner_y1 = calculate_point_b(ax, ay, ux, uy, d)

    # 设置起始点为中心点
    ax, ay = center_x, center_y

    # 设置x方向和y方向的单位向量，计算顶点3的坐标
    ux, uy = edge2_unit1[0], edge2_unit1[1]
    d = neiedge21
    bx2, by2 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx2, by2

    # 设置x方向和y方向的单位向量，计算顶点4的坐标
    ux, uy = edge3_unit[0]*-1, edge3_unit[1]*-1
    d = neiedge3
    inner_x2, inner_y2 = calculate_point_b(ax, ay, ux, uy, d)

    # 设置起始点为中心点
    ax, ay = center_x, center_y

    # 设置x方向和y方向的单位向量，计算顶点5的坐标
    ux, uy = edge3_unit1[0], edge3_unit1[1]
    d = neiedge31
    bx3, by3 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx3, by3

    # 设置x方向和y方向的单位向量，计算顶点6的坐标
    ux, uy = edge4_unit[0]*-1, edge4_unit[1]*-1
    d = neiedge4
    inner_x3, inner_y3 = calculate_point_b(ax, ay, ux, uy, d)

    # 设置起始点为中心点
    ax, ay = center_x, center_y

    # 设置x方向和y方向的单位向量，计算顶点7的坐标
    ux, uy = edge4_unit1[0], edge4_unit1[1]
    d = neiedge41
    bx4, by4 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx4, by4

    # 设置x方向和y方向的单位向量，计算顶点8的坐标
    ux, uy = edge1_unit[0]*-1, edge1_unit[1]*-1
    d = neiedge1
    inner_x4, inner_y4 = calculate_point_b(ax, ay, ux, uy, d)

    # 返回内矩形顶点的坐标
    return inner_x1, inner_y1, inner_x2, inner_y2, inner_x3, inner_y3, inner_x4, inner_y4
