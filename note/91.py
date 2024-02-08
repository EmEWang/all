#!/usr/bin/python3
##  #! /usr/bin/env python3  # 这个也可以




import matplotlib.pyplot as plt
import numpy as np

def printmsg():
    print ("Hello, Python!")


def drawline():
    x = np.linspace(-1,1,50)
    y = 2*x + 1
    y2 = x**2

    plt.plot(x,y)
    plt.plot(x,y2)
    plt.show()

def drawline2():
    x = np.linspace(-1,1,50)
    y = 2*x + 1
    y2 = x**2

    plt.figure()
    plt.plot(x,y)
    plt.figure(num=3,figsize=(8,5))
    plt.plot(x,y2)
    plt.show()

def drawline3():
    # 显示中文
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus']=False

    x = np.linspace(-3,3,50)
    y1 = 2*x - 1
    y2 = x**2

    # 一张图
    plt.figure()
    plt.plot(x,y1,label='Linear function')
    plt.plot(x,y2,label='Quadratic function',color="red",linewidth=1.0,linestyle='-.')

    # 限制x,y轴的范围，设置标签
    plt.xlim((-2,3))
    plt.ylim((-2,8))
    plt.xlabel("x")
    plt.ylabel("y")

    # 更换下标
    new_ticks = np.linspace(-2,3,11)
    plt.xticks(new_ticks)
    plt.yticks(range(5), ['cat', 'fish', 'dog$', 'tom', 'jerry'])

    # 移动x,y轴位置
    # gca = "get current axis"
    ax = plt.gca()
    ax.spines['right'].set_color('none') # 右边框设置成无颜色
    ax.spines['top'].set_color('none') # 上边框设置成无颜色
    ax.xaxis.set_ticks_position('bottom') # x轴用下边框代替，默认是这样
    ax.yaxis.set_ticks_position('left') # y轴用左边的边框代替，默认是这样
    # ax.spines['bottom'].set_color('red') # x轴颜色为红色
    ax.spines['bottom'].set_position(('data',0)) # x轴在y轴，０的位置
    ax.spines['left'].set_position(('data',0)) # y轴在x轴，０的位置


    # annotation 注释，我们注释在交点
    # emm,我手算出来，暂时没考虑样自动计算
    # 这个略微有点复杂，用的时候，google下就好
    x0 = 1
    y0 = 2*x0 -1
    plt.scatter(x0,y0,color='green') # 画一个点
    plt.plot([x0,x0],[y0,0],color='green',linestyle='--') # 画一条虚线
    plt.annotate('intersection is (%d,%d)' % (x0,y0),
                    xy=(x0,y0),xytext=(x0+0.5,y0-0.5),xycoords='data',
                    arrowprops=dict(arrowstyle='->', connectionstyle="arc3,rad=.2"))

    # plt.text(0,-2,'unused text.')

    # 设置透明度
    l = len(ax.get_xticklabels()) + len(ax.get_yticklabels())
    i = 0
    for label in ax.get_xticklabels() + ax.get_yticklabels():
        i+=1
    #     # label.set_fontsize(16) # 设置标签字体大小
    #     label.set_bbox(dict(facecolor='white', edgecolor='None', alpha=0.65 )) # 设置标签填充色 边框色 透明度
        label.set_bbox(dict(facecolor='blue', edgecolor='None', alpha=(++i)/(l*2) )) # 设置标签填充色 边框色 透明度

    plt.legend(loc='best')  # 设置图例位置
    plt.show()

def drawline4():#柱状图
    n = 12
    X = np.arange(n)
    Y1 = (1-X/n)*np.random.uniform(0.5,1.0,n)
    Y1 = (1-X/n)*np.random.uniform(0.5,1.0,n)

    # 由于返回值，进过提取是str，操作小数位数不方便，外面提前处理好
    p1 = plt.bar(X,np.round(Y1,2),width=0.8,facecolor='deeppink',label='uniform')

    def autolabel(rects):
        """Attach a text label above each bar in *rects*, displaying its height."""
        for rect in rects:
            height = rect.get_height()
            plt.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

    # 为什么有两个hight
    def add_labels(rects):
        for rect in rects:
            height = rect.get_height()
            plt.text(rect.get_x() + rect.get_width()/2,height,height, ha='center', va='bottom')
            rect.set_edgecolor('white')

    # add_labels(p1)
    autolabel(p1)

    plt.legend(loc='best')
    plt.show()


def drawline5():#散点图
    n = 1024
    X = np.random.normal(0,1,1024) # 正态分布
    Y = np.random.normal(0,1,1024)
    T = np.arctan2(X,Y) # for color

    plt.xlim(-1.5,1.5)
    plt.ylim(-1.5,1.5)
    plt.xticks(())
    plt.yticks(())

    plt.scatter(X,Y,c=T,alpha=0.65)
    plt.show()

def f(x,y):
    # the height function
    return (1-x/2+x**5+y**3)*np.exp(-x**2-y**2)

def drawline6():#等高线
    n = 256
    x = np.linspace(-3,3,n)
    y = np.linspace(-3,3,n)
    X,Y = np.meshgrid(x,y)

    # use plt.contourf to filling fontous
    plt.contourf(X,Y,f(X,Y),8,alpha=0.75,cmap=plt.cm.hot)

    # use plt.contour to add contour lines
    C = plt.contour(X,Y,f(X,Y),8,color='black',linewidt=0.5)

    # add lable
    # 这个label比以前的好加
    plt.clabel(C,inline=True,fontsize=10)

    plt.xticks(())
    plt.yticks(())
    plt.show()


if __name__ == "__main__":
    drawline6()
