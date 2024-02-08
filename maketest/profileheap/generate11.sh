#! /bin/bash
# 自动生成 jeprof 结果 svg
# 参数分别为
# jeprof       路径
# app          应用
# prefix       日志前缀
# step         步长
# output       输出目录 文件格式 为 app+index[-index]
# division     输出文件区分


jeprof=$1
app=$2
prefix=$3
out=$4         # path
num=10           # 111
startindex=0
#endindex=118
#endindex=$(($(ls ${prefix}* | wc -l)-1))
endindex=$(($(find $(dirname ${prefix}) -type f -name "$(basename ${prefix})*" | wc -l)-1))
span=$(($endindex-$startindex))
out_name=$(basename $app)

#${jeprof} --svg ${app} ${prefix} > ${output}.svg
#mkdir -p ${output}

for((i=0;i<=num;i++))
{
  moment[i]=$(($span*i/$num+$startindex))
#   echo cur $i is ${moment[$i]}
}

for((i=0;i<=num;i++))
{
  ${jeprof} --svg ${app} ${prefix}.${moment[$i]}.i${moment[$i]}.heap > ${out}/${out_name}.moment.[$startindex-$endindex][${moment[$i]}]_index_${i}.svg
  ${jeprof} --text ${app} ${prefix}.${moment[$i]}.i${moment[$i]}.heap > ${out}/${out_name}.moment.[$startindex-$endindex][${moment[$i]}]_index_${i}.txt
  #echo ${jeprof} -- ${app} -- ${prefix}.${moment[$i]}.i${moment[$i]}.heap -- ${out}/${out_name}.moment.[$startindex-$endindex][moment[$i]].svg
}

for((i=1;i<=num;i++))
{
  j=$((i-1))
  ${jeprof} --svg ${app} --base=${prefix}.${moment[$j]}.i${moment[$j]}.heap ${prefix}.${moment[$i]}.i${moment[$i]}.heap > ${out}/${out_name}.diff.[$startindex-$endindex][${moment[$j]}-${moment[$i]}]_index_${j}.svg
  ${jeprof} --text ${app} --base=${prefix}.${moment[$j]}.i${moment[$j]}.heap ${prefix}.${moment[$i]}.i${moment[$i]}.heap > ${out}/${out_name}.diff.[$startindex-$endindex][${moment[$j]}-${moment[$i]}]_index_${j}.txt

  #echo ${jeprof} -- ${app} -- ${prefix}.${moment[$j]}.i${moment[$j]}.heap  ${prefix}.${moment[$i]}.i${moment[$i]}.heap ${out}/${out_name}.diff.[$startindex-$endindex][${moment[$j]}-${moment[$i]}].svg
}






