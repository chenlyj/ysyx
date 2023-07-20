import subprocess

# 定义要执行的命令列表
commands = [
    './ex17_ex db.dat c 10 20',
    './ex17_ex db.dat s 5 zed zed@',
    './ex17_ex db.dat s 8 xiaoming xiaoming@',
    "./ex17_ex db.dat g 5 ",
    "./ex17_ex db.dat f zed "
    # 在此添加更多命令...
]

# 遍历命令列表并逐个执行
for cmd in commands:
    print(f'Running command: {cmd}')
    try:
        # 执行命令并等待其完成
        subprocess.run(cmd, shell=True, check=True)
        print('Command executed successfully')
    except subprocess.CalledProcessError as e:
        # 命令执行失败，输出错误信息并终止脚本
        print(f'Command failed with exit code {e.returncode}')
        print(e.output)
        break
