#!/bin/awk -f
# ./81.awk file
BEGIN {
    i=0

#    array
}

{if(i<5){
    print i,$0
    array[i+10]=$4    # 使用数组
    i++
    }
}

END {
    print "--- 原始 while"
    j=0
    while(j<i){         # 打印数组
        print j+10,array[j+10]
        j++
    }

    print "--- 原始 for"
    for(k in array)     # awk是关联数组。for…in循环输出时候，默认打印出来是无序数组
        print k,array[k]

#    print "--- asort 排序"
#    slen=asort(array,arrayb)
#    for(l in arrayb)
#        print l,array[l],array[l+10],arrayb[l]

    print "--- asorti 排序"
    slen=asorti(array,arrayb)
    for(l in arrayb)
        print l,arrayb[l]

# gun awk 出错  function asort never defined   -> sudo apt-get install gawk 解决
# https://stackoverflow.com/questions/39426524/awk-function-asorti-never-defined
# asort  是对数组的值进行排序，并且会丢掉原先键值；
# asorti 是对数组的键值进行排序，生成<序号，键值>关联数组。
#    for(i in a)
#        print i,a[i]        # **1 输出
#    slen=asort(a,b)  # 对数组a的值进行排序，把排序后的下标存入新生成的数组b中，丢弃数组a下标值，数组a的长度赋值给变量slen
#    for(i=1;i<=slen;i++)      # 数组的值是无法直接print，使用for循环取出数值的下标，输出排序后的数组b下标值及对应数值
#        print i","a[i]","b[i] # 此时a已经是空数组   **2 输出
#    slen=asorti(a,b)       # 对数组a的下标进行排序，并把排序后的下标存入新生成的数组b中，并把数组a的长度赋值给变量slen
#    for(i=1;i<=slen;i++)
#        print i"\t"b[i]"\t"a[b[i]]
# **1             **2              **3
# 78 90    ->     1  34      ->    1  12
# 12 34           2  45            2  23
# 23 45           3  90            3  78

}
