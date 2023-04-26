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

# 优雅处理参数
{
    func1()
    {
        origin=$*
        while getopts ":n:ho::" optname
        do
            case "$optname" in
            "n")
                echo "参数数量[$#] 参数[$OPTARG] 位置[$OPTIND]"
                shift $(($OPTIND - 1))     # 从索引位置截取参数 赋给 $*
                echo remaining parameters=[$*]
                echo \$1=[$1]
                echo \$2=[$2]

                shift $((1))
                echo remaining parameters=[$*]
                echo \$1=[$1]
                echo \$2=[$2]
                ;;
            "h")
                echo "参数数量[$#] 参数[$OPTARG] 位置[$OPTIND]"
                ;;
            "o")
                echo "参数数量[$#] 参数[$OPTARG] 位置[$OPTIND]"
                ;;
            ":")
                echo "参数数量[$#] 参数[$OPTARG] 位置[$OPTIND]"
                ;;
            "?")
                echo "未知 $OPTARG"
                ;;
            *)
                echo "出错"
                ;;
            esac
        done
    }
    # func1 $*


    func2()
    {
        echo 原始参数=[$@]

        # -o或--options选项后面是可接受的短选项，
        # 如ab:c::，表示可接受的短选项为-a -b -c，其中-a选项不接参数，-b选项后必须接参数，-c选项的参数为可选的
        # -l或--long选项后面是可接受的长选项，用逗号分开，冒号的意义同短选项。
        # -n选项后接选项解析错误时提示的脚本名字
        # 格式
        # getopt optstring parameters
        # getopt [options] [--] optstring parameters
        # getopt [options] -o|--options optstring [options] [--] parameters
        # 第一部分是命令名。
        # 第二部分optstring（选项字符串），是这个命令解析的格式。
        # 第三部分parameters（getopt命令的参数），就是需要解析的内容。
        # 如果添加了双破折线，那么无轮后面是什么，都会作为参数而不是选项来处理
        #ARGS=`getopt -o ab:c:: --long along,blong:,clong:: -n "$0" -- "$@"`
        ARGS=`getopt -o ab:c:: --long along,blong:,clong:: -n "$0脚本参数错误" -- $@ `
        if [ $? != 0 ]; then
            echo "解析错误..."
            exit 1
        fi

        echo getopt处理后参数=$ARGS
        #将规范化后的命令行参数分配至位置参数（$1,$2,...)
        # eval 表示 将剩下的字符串拼接成一个命令并执行
        # set -- 表示 任何剩余的参数会被赋值给位置参数。如果没有剩余的参数，位置参数不会被设置。
        eval set -- "${ARGS}"
        echo 格式化后参数=$@

        while true
        do
            case "$1" in
                -a|--along)
                    echo "选项 a";
                    shift
                    ;;
                -b|--blong)
                    echo "选项 b, 参数 $2";
                    shift 2
                    ;;
                -c|--clong)
                    case "$2" in
                        "")
                            echo "选项 c, 没有参数";
                            shift 2
                            ;;
                        *)
                            echo "选项 c, 参数 $2";
                            shift 2;
                            ;;
                    esac
                    ;;
                --)
                    shift
                    break
                    ;;
                *)
                    echo "Internal error!"
                    exit 1
                    ;;
            esac
        done

        #处理剩余的参数
        echo 剩余的参数=[$@]
        # echo \$1=[$1]
        # echo \$2=[$2]
    }
    # ./0.sh -a -b 123 -czz --along --blong=bbb --clong --clong=xx
    # func2 $*
}

# 缺省值
{
    func1()
    {
        {
            name=1
            name2=2
            # echo [name:-xxx][${name:-xxx}];echo [name][${name}]
            # echo [name-xxx][${name-xxx}];echo [name][${name}]

            # echo [name=xxx][${name=xxx}];echo [name][${name}]
            # echo [name:=xxx]${name:=xxx};echo [name][${name}]

            # echo [name?xxx][${name?xxx}];echo [name][${name}]
            # echo [name:?xxx][${name:?xxx}];echo [name][${name}]

            # echo [name+xxx][${name+xxx}];echo [name][${name}]
            # echo [name:+xxx][${name:+xxx}];echo [name][${name}]

            # echo ${!nam*}
            # echo ${!nam@}

            # name=123456
            # echo [name:2][${name:2}]; echo [name][${name}]
            # echo [{name:2:2][${name:2:2}];echo [name][${name}]

            # name=123123
            # echo name/2/b--\>${name/2/b};echo [name][${name}]
            # echo name//2/b--\>${name//2/b};echo [name][${name}]

            # name=123123
            # echoname/#1/b--\>${name/#1/b};echo [name][${name}]
            # name=123123
            # echo name/%1/b--\>${name/%3/b};echo [name][${name}]

            # name=123123
            # echo name/1--\>${name/1};echo [name][${name}]
            # echo name//2--\>${name//2};echo [name][${name}]

            # name=1,2!3.123
            # echo name/[13]--\>${name/[[:punct:]]};echo [name][${name}]
            # echo name//[13]--\>${name//[[:punct:]]};echo [name][${name}]

            # name=123123
            # echo name/[13]--\>${name/*};echo [name][${name}]
            # echo name//[13]--\>${name//*};echo [name][${name}]

            # name=123123
            # echo name/[13]--\>${name/*/xx};echo [name][${name}]
            # echo name//[13]--\>${name//*/xx};echo [name][${name}]

            # name=a1234b1234c
            # echo -n [name#*23][${name#*23}];echo [name][${name}]
            # echo -n [name##*23][${name##*23}];echo [name][${name}]
            # echo -n [name%23*][${name%23*}];echo [name][${name}]
            # echo -n [name%%23*][${name%%23*}];echo [name][${name}]
        }

    }
    func1

    func2()
    {
        via1="\[\e]\n \055 \r \""
        via2='\[\e]\n \055 \r \" '

        echo  $via1
        echo  $via2

        var1=a
        var2=b

        var=1
        var0=var$var

# 变量的值作为新的变量名
        eval echo \${var$var}

        aa=25
        bb=aa
        echo \$$bb  #$aa 普通shell只对命令做一次解析
        eval echo \$$bb   #25
        # 执行过程：
        # 一次扫描时(同上)：$bb获取到了bb的值aa成功替换 ，替换后整个命令变成了
        # echo $aa
        # 第二次扫描时： 发现命令$aa ,执行替换获取到25，执行echo 25 ,输出 25
    }
    # func2


 }

}
