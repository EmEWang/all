# 无限循环调用netstat       ./92.py > xxx.log 记录

import subprocess
import time
from datetime import datetime

def run_netstat():
    try:
        # 运行命令并捕获输出
        result = subprocess.run(['netstat', '-s', '--raw'], capture_output=True, text=True)

        # 在输出中查找包含 "drop" 的行
        drop_lines = [line for line in result.stdout.split('\n') if 'fragments dropped after timeout' in line.lower()]

        # 打印包含 "drop" 的行
        ts = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        for line in drop_lines:
            print(ts, line)

    except Exception as e:
        print(f"Error: {e}")

# 设置循环间隔（以秒为单位）
interval = 1

while True:
    run_netstat()
    time.sleep(interval)
