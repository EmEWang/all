#! /bin/bash

inputnum=$#
help0(){
    echo "输入 -h 或 --help 查看更多信息"
}
help1(){
    echo "参数错误"
}
help2(){
    echo "说明: llvmcovtool 在指定的目录下 输出 html格式的覆盖率信息";
    echo "格式: llvmcovtool dir1 exe1 [dir2 exe2] ....";
    echo "参数: dirX 目标目录";
    echo "格式: exeX 执行文件";
    echo "备注: dirX exeX 需要成对出现";
    echo "示例: ./xxx.sh ~/coverage1 tar101 ~/coverage2 tar102";
}
verify(){
    if [[ ! -d $1 ]]
    then
        echo $1 不是目录
        exit 0
    fi

    if [[ ! -x $1/$2 ]]
    then
        echo $2 不是执行文件
        exit 0
    fi
    return 0
}

if [ $inputnum == 0 ]
then
    help0
    exit 0
fi

if [[  $inputnum > 0 && ( $1 == "-h" ||  $1 == "--help" ) ]]
then
    help2
    exit 0
fi

if [[  `expr $inputnum % 2 ` != 0 || $inputnum == 0 ]]
then
    help1
    help0
    exit 0
fi

index=1
args=(1 2)
for arg in $*
do
   args[index]=$arg
   let index+=1
done

 dir=
 exe=
for((i=1;i<=$inputnum;i+=2))
do
    dir=${args[i]}
    exe=${args[i+1]}
    verify $dir $exe
done

llvm=llvmcov_html
for((i=1;i<=$inputnum;i+=2))
do
    dir=${args[i]}
    exe=${args[i+1]}
    echo $dir $exe
    llvm-profdata merge -o $dir/target.profdata  $dir/default.profraw
    llvm-cov show $dir/$exe \
    --show-line-counts-or-regions  \
    --show-branches=count  \
    -instr-profile=$dir/target.profdata -format=html -output-dir=$dir/$llvm
done

echo 生成成功