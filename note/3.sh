#!/bin/bash

exec() {
    echo "$1"
    echo "$2"
    echo "$3"
#    echo "$1"
#    mkdir "$3"
#    cd "$3"
#    export LD_LIBRARY_PATH=../
#    sudo ../perf record -F 99 -p "$1" --call-graph dwarf sleep "$2" # 时间需要改
#    sudo ../perf script > out.unfold
#    sudo ../../FlameGraph/stackcollapse-perf.pl out.unfold > out.folded
#    sudo ../../FlameGraph/flamegraph.pl out.folded > "$3".svg
}

#exec "$*"
exec "$@" #"$@" "$@" #perf.sh  pid time filename