
https://docs.python.org/zh-cn/3/library/index.html   # Python 标准库
https://www.runoob.com/python3/python3-tutorial.html # Python3教程
https://www.runoob.com/pandas/pandas-tutorial.html   # Pandas 教程

https://zhuanlan.zhihu.com/p/675323789               # 带你一步步调试CPython源码

ubuntu 安裝
python3 --version     # 检查是否存在
sudo apt-get update
sudo apt-get install python3
sudo apt-get install python3.8  # 指定版本
python3 --version     # 检查是否成功


sudo apt-get install python3-pandas   # Ubuntu python3安装pandas  -> /usr/lib/python3/dist-packages/pandas
sudo apt-get install python3-numpy    #



numpy.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
  1 功能
    生成一个指定大小，指定数据区间的均匀分布序列
  2 参数说明
    1 start：序列中数据的下界。
    2 end：序列中数据的上界。
    3 num：生成序列包含num个元素；其值默认为50。
    4 endpoint：取True时，序列包含最大值end；否则不包含；其值默认为True。
    5 retstep：该值取True时，生成的序列中显示间距；反正不显示；其值默认为false。
    6 dtype：数据类型，可以指定生成序列的数据类型；当为None时，根据其他输入推断数据类型。
    7 返回值：是一个数组。
  3 code
import numpy as np
print(np.linspace(1, 10))  # 说明参数num的值默认为50
print(np.linspace(1, 10, 10))    # 生成[1,10]之间元素个数为10的序列 endpoint默认为true,参数retstep默认为false
print(np.linspace(1, 10, 10, endpoint=False))   # 生成[1,10)之间元素个数为10的序列,设置参数retstep为true
print(np.linspace(1, 10, 10, dtype=int))  # 生成[1,10)之间元素个数为10的整数序列
  4 运行结果
# 参数num的值默认为50:
[ 1.          1.18367347  1.36734694  1.55102041  1.73469388  1.91836735
  2.10204082  2.28571429  2.46938776  2.65306122  2.83673469  3.02040816
  3.20408163  3.3877551   3.57142857  3.75510204  3.93877551  4.12244898
  4.30612245  4.48979592  4.67346939  4.85714286  5.04081633  5.2244898
  5.40816327  5.59183673  5.7755102   5.95918367  6.14285714  6.32653061
  6.51020408  6.69387755  6.87755102  7.06122449  7.24489796  7.42857143
  7.6122449   7.79591837  7.97959184  8.16326531  8.34693878  8.53061224
  8.71428571  8.89795918  9.08163265  9.26530612  9.44897959  9.63265306
  9.81632653 10.        ]
# 生成[1,10]之间元素个数为10的序列:
[ 1.  2.  3.  4.  5.  6.  7.  8.  9. 10.]
# 生成[1,10)之间元素个数为10的序列:
[1.  1.9 2.8 3.7 4.6 5.5 6.4 7.3 8.2 9.1]
# 生成[1,10)之间元素个数为10的整数序列:
[ 1  2  3  4  5  6  7  8  9 10]



