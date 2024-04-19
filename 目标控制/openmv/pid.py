from pyb import millis  # 导入 millis 函数用于获取当前时间
from math import pi, isnan  # 导入 pi 常量和 isnan 函数用于检查是否为 NaN

class PID:
    _kp = _ki = _kd = _integrator = _imax = 0  # 初始化 PID 控制器的参数
    _last_error = _last_derivative = _last_t = 0  # 初始化 PID 控制器的状态
    _RC = 1 / (2 * pi * 20)  # RC 时间常数

    def __init__(self, p=0, i=0, d=0, imax=0):
        """PID 控制器初始化函数"""
        # 设置 PID 控制器的参数
        self._kp = float(p)  # 比例系数
        self._ki = float(i)  # 积分系数
        self._kd = float(d)  # 微分系数
        self._imax = abs(imax)  # 积分项最大值限制
        self._last_derivative = float('nan')  # 上一次的微分项

    def get_pid(self, error, scaler):
        """计算 PID 控制器的输出"""
        tnow = millis()  # 获取当前时间
        dt = tnow - self._last_t  # 计算时间间隔
        output = 0

        # 如果是第一次计算或者时间间隔过大，将时间间隔置为 0，并重置积分项
        if self._last_t == 0 or dt > 1000:
            dt = 0
            self.reset_I()

        self._last_t = tnow  # 更新上一次计算的时间

        delta_time = float(dt) / float(1000)  # 将时间间隔转换为秒
        output += error * self._kp  # 计算比例项

        # 计算微分项
        if abs(self._kd) > 0 and dt > 0:
            if isnan(self._last_derivative):
                derivative = 0
                self._last_derivative = 0
            else:
                derivative = (error - self._last_error) / delta_time
            derivative = self._last_derivative + \
                         ((delta_time / (self._RC + delta_time)) * \
                          (derivative - self._last_derivative))
            self._last_error = error
            self._last_derivative = derivative
            output += self._kd * derivative

        output *= scaler  # 缩放输出值

        # 计算积分项
        if abs(self._ki) > 0 and dt > 0:
            self._integrator += (error * self._ki) * scaler * delta_time
            if self._integrator < -self._imax:
                self._integrator = -self._imax
            elif self._integrator > self._imax:
                self._integrator = self._imax
            output += self._integrator

        return output

    def reset_I(self):
        """重置积分项"""
        self._integrator = 0
        self._last_derivative = float('nan')
