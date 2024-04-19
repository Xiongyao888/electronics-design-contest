import math
CEN_X = 74
CEN_Y = 82
def normalize_vector(vec):
    x, y = vec
    length = math.sqrt(x**2 + y**2)
    return (x / length, y / length)
def average_unit_vectors(u, v):
    u_x, u_y = u
    v_x, v_y = v
    w = (u_x + v_x, u_y + v_y)
    w_normalized = normalize_vector(w)
    return w_normalized
u = (0.6, 0.8)
v = (0.65, 0.75)

point1 = (0, 0.1) #2.5 1.8
point2 = (50,0.1)
def find_linear_function(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    slope = (y2 - y1) / (x2 - x1)
    intercept = y1 - slope * x1
    def linear_function(x):
        return slope * x + intercept
    return linear_function
linear_func = find_linear_function(point1, point2)
x_value = 3
y_value = linear_func(x_value)
print(y_value)
def calculate_point_b(ax, ay, ux, uy, d):
    bx = ax + ux * d
    by = ay + uy * d
    return bx, by
def inner_rect_verstices(x1, y1, x2, y2, x3, y3, x4, y4):
    lgcen1 = [x1 - CEN_X, y1 - CEN_Y]
    lgcen2 = [x2 - CEN_X, y2 - CEN_Y]
    lgcen3 = [x3 - CEN_X, y3 - CEN_Y]
    lgcen4 = [x4 - CEN_X, y4 - CEN_Y]
    edge1 = [x2 - x1, y2 - y1]
    edge2 = [x3 - x2, y3 - y2]
    print(edge2)
    edge3 = [x4 - x3, y4 - y3]
    edge4 = [x1 - x4, y1 - y4]
    longcentr1 = math.sqrt(lgcen1[0]**2 + lgcen1[1]**2)
    longcentr2 = math.sqrt(lgcen2[0]**2 + lgcen2[1]**2)
    longcentr3 = math.sqrt(lgcen3[0]**2 + lgcen3[1]**2)
    longcentr4 = math.sqrt(lgcen4[0]**2 + lgcen4[1]**2)
    width1 = linear_func(longcentr1)
    print("width1:",width1)
    width2 = linear_func(longcentr2)
    print("width2:",width2)
    width3 = linear_func(longcentr3)
    print("width3:",width3)
    width4 = linear_func(longcentr4)
    edge1_norm = math.sqrt(edge1[0]**2 + edge1[1]**2)
    edge2_norm = math.sqrt(edge2[0]**2 + edge2[1]**2)
    edge3_norm = math.sqrt(edge3[0]**2 + edge3[1]**2)
    edge4_norm = math.sqrt(edge4[0]**2 + edge4[1]**2)
    neiedge1 = edge1_norm/2 - width1
    neiedge2 = edge2_norm/2 - width2
    neiedge3 = edge3_norm/2 - width3
    neiedge4 = edge4_norm/2 - width4
    neiedge11 = ((edge1_norm + edge3_norm)/2 - (width2+width3))/2
    print("neiedge11",neiedge11)
    neiedge21 = ((edge2_norm + edge4_norm)/2 - (width3+width4))/2
    neiedge31 = ((edge3_norm + edge1_norm)/2 - (width4+width1))/2
    neiedge41 = ((edge4_norm + edge2_norm)/2 - (width1+width2))/2
    edge1_unit = [edge1[0] / edge1_norm, edge1[1] / edge1_norm]
    print(edge1_unit)
    edge2_unit = [edge2[0] / edge2_norm, edge2[1] / edge2_norm]
    print(edge2_unit)
    edge3_unit = [edge3[0] / edge3_norm, edge3[1] / edge3_norm]
    edge4_unit = [edge4[0] / edge4_norm, edge4[1] / edge4_norm]
    edge32_unit = [edge3_unit[0]*(-1),edge3_unit[1]*(-1)]
    edge42_unit = [edge4_unit[0]*(-1),edge4_unit[1]*(-1)]
    edge12_unit = [edge1_unit[0]*(-1),edge1_unit[1]*(-1)]
    edge22_unit = [edge2_unit[0]*(-1),edge2_unit[1]*(-1)]
    edge1_unit1 = average_unit_vectors(edge1_unit, edge32_unit)
    edge2_unit1 = average_unit_vectors(edge2_unit, edge42_unit)
    edge3_unit1 = average_unit_vectors(edge3_unit, edge12_unit)
    edge4_unit1 = average_unit_vectors(edge4_unit, edge22_unit)
    center_x = (x1 + x2 + x3 + x4) / 4
    center_y = (y1 + y2 + y3 + y4) / 4
    ax, ay = center_x, center_y
    print(center_x,center_y)
    ux, uy = edge1_unit1[0], edge1_unit1[1]
    print(edge1_unit1[0],edge1_unit1[1])
    d =  neiedge11
    print(d)
    bx1, by1 = calculate_point_b(ax, ay, ux, uy, d)
    print(bx1,by1)
    ax, ay = bx1 , by1
    ux, uy = edge2_unit[0]*-1, edge2_unit[1]*-1
    d =  neiedge2
    inner_x1, inner_y1 = calculate_point_b(ax, ay, ux, uy, d)
    print(inner_x1,inner_y1)
    ax, ay = center_x, center_y
    ux, uy = edge2_unit1[0], edge2_unit1[1]
    d =  neiedge21
    bx2, by2 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx2 , by2
    ux, uy = edge3_unit[0]*-1, edge3_unit[1]*-1
    d =  neiedge3
    inner_x2, inner_y2 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = center_x, center_y
    ux, uy = edge3_unit1[0], edge3_unit1[1]
    d =  neiedge31
    bx3, by3 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx3 , by3
    ux, uy = edge4_unit[0]*-1, edge4_unit[1]*-1
    d =  neiedge4
    inner_x3, inner_y3 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = center_x, center_y
    ux, uy = edge4_unit1[0], edge4_unit1[1]
    d =  neiedge41
    bx4, by4 = calculate_point_b(ax, ay, ux, uy, d)
    ax, ay = bx4 , by4
    ux, uy = edge1_unit[0]*-1, edge1_unit[1]*-1
    d =  neiedge1
    inner_x4, inner_y4 = calculate_point_b(ax, ay, ux, uy, d)
    return inner_x1, inner_y1, inner_x2, inner_y2, inner_x3, inner_y3, inner_x4, inner_y4
