#! /bin/bash
# 测试shell

# 函数使用
{
    # 全局变量方式 外部以 $? 捕获返回值 和 使用全局变量
    g_ret=
    func1()
    {
        g_ret=xxx
        return 123
    }
    func1 1 2 3
    func1_ret=$?             #取上个函数的返回值
    # echo $func1_ret
    # echo $g_ret

    # 内部 以 $? 返回 外部捕获方式
    func2()
    {
        echo xx1
        echo xx2
        return $?
    }
    func2_ret=`func2 1 2 3`        #捕获 下同
    func2_ret2=$(func2 1 2 3)
    # echo $func2_ret
    # echo $func2_ret2

    # 传入的参数 类似于 脚本传参
    func3()
    {
        # $* 与 $@ 区别：
        # 相同点：都是引用所有参数。
        # 不同点：只有在双引号中体现出来。假设在脚本运行时写了三个参数 1、2、3，则 " * " 等价于 "1 2 3"（传递了一个参数），
        #   而 "@" 等价于 "1" "2" "3"（传递了三个参数）。
        echo "执行的文件名：$0";
        echo "第一个参数为：$1";
        echo "第二个参数为：$2";
        echo "参数的个数为：$#";
        echo "所有的参数为：$*"; #以一个单字符串显示所有向脚本传递的参数。如"$*"用「"」括起来的情况、以"$1 $2 … $n"的形式输出所有参数。
        echo "所有的参数为："$*"";
        echo "所有的参数为：$@"; #与$*相同，但是使用时加引号，并在引号中返回每个参数。如"$@"用「"」括起来的情况、以"$1" "$2" … "$n" 的形式输出所有参数。
        echo "所有的参数为："$@"";
        echo "当前进程ID号为：$$";
        echo "后台运行的最后一个进程的ID号为：$!";
        echo "显示Shell使用的当前选项，与set命令功能相同为：$-";
        echo "显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误为：$?";

        echo "-- \"\$*\" 演示 ---"
        for i in "$*"; do
            echo $i
        done

        echo "-- \"\$@\" 演示 ---"
        for i in "$@"; do
            echo $i
        done
    }

    # func3 param1 param2 param3
}

# 数组
{
    func1(){
        declare -A site=(["A"]="A.a" ["B"]="B.b" ["C"]="C.c")  #关联数组
        array=(1 2 3)              #普通数组

        echo ${array[0]}           #第一个元素
        echo ${array[*]}           #全部元素
        echo ${!array[*]}          #元素的索引
        echo ${#array[*]}          #数组的数量  下同
        echo ${site["A"]}
        echo ${site[*]}
        echo ${!site[*]}
        echo ${#site[*]}

        array2=(3 4 5)
        array3=(${array[*]} ${array2[*]})   #数组拼接 普通数组和关联数组不能拼接
        echo ${array3[*]}

        unset site["A"]            #删除元素
        echo ${site[*]}
    }
    # func1
}

# 比较
{
    # 字符串比较
    fuc1(){
        str1=xxx
        str2=sss
        str3=
        if [ $str1 \> $str2 ]
        then
            echo "str1>str2"
        fi;

        if [ $str1 ]
        then
            echo "str1 not null"
        fi;

        if [ -z $str3 ]
        then
            echo "str3 null"
        fi;
    }
    # fuc1

    # 逻辑判断
    a=10
    b=20
    fuc2(){
        if [[  $a > 0 && $b > 0  ]]
        then
            echo "[[  $a > 0 && $b > 0  ]]"
        fi

        if [ $a -gt 0 -a $b -gt 0  ]
        then
            echo "[ $a -gt 0 -a $b -gt 0  ]"
        fi

        if [[ !($a -gt 30) ]]
        then
            echo "[[ !($a -gt 30) ]]"
        fi
    }
    # fuc2
}

# 数学
{
    func1()
    {
        # (())
        {
            ((a=10+10))
            ((b=a-1))
            echo $a
            echo $b
        }
        {
            a=$((10+10))
            b=$((a-1))
            echo $a
            echo $b
        }
        {
            a=10
            b=5
            if ((a>7 && b==5))
            then
                echo "((a>7 && b==5))"
            fi

            echo $((a+10))
            echo $((a=3+5, b=a+10))
        }
        {
            a=10
            echo $((a++))
            echo $a

            a=10
            echo $((++a))
            echo $a

            a=10
            echo $((--a))
            echo $a

            a=10
            echo $((a--))
            echo $a

        }
        # let
        {
            a=10
            b=100
            let a+=10 b+=200
            echo $a $b
        }
        # expr
        {
            m=5
            n=`expr $m + 10`
            echo $n
        }
        # bc
        {
            echo "5+3" | bc
            echo "(2+6)*3.1" | bc
        }
    }
    # func1
}

# 字符串
{
    func1()
    {
        string=abc:def:f:g
        echo ${string: 1 :2}
        echo ${string: 1}
        echo ${string: 0-3 :2}
        echo ${string: 0-3 }
        echo ${string#*:}
        echo ${string##*:}
        echo ${string%:*}
        echo ${string%%:*}
    }
    # func1
}
