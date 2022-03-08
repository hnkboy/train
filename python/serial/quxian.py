import matplotlib.pyplot as plt
import matplotlib.font_manager as font_manager
import numpy as np

#横坐标100个点
POINTS = 100
sin_list = [0] * POINTS   
indx = 0
 
fig, ax = plt.subplots()
#设置横纵范围
ax.set_ylim([-2, 2])   
ax.set_xlim([0, POINTS])
ax.set_autoscale_on(False)
#设置刻度
ax.set_xticks(range(0, 100, 10))
ax.set_yticks(range(-20, 20, 1))
ax.grid(True)
 
line_sin, = ax.plot(range(POINTS), sin_list, label='Sin() output', color='cornflowerblue')
ax.legend(loc='upper center', ncol=4, prop=font_manager.FontProperties(size=10))
 

def sin_output(ax):
    global indx, sin_list, line_sin
    if indx == 20:
        indx = 0
    indx += 1
 
    sin_list = sin_list[1:] + [(indx / 10)]
    line_sin.set_ydata(sin_list)
    ax.draw_artist(line_sin)
    ax.figure.canvas.draw()
 
 
timer = fig.canvas.new_timer(interval=100)
timer.add_callback(sin_output, ax)
timer.start()
plt.show()