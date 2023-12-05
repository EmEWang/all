#Makefile: recursive subdirs
# make RELEASE=0 BITS=32：32位的debug版。
# make RELEASE=0 BITS=64：64位的debug版。
# make RELEASE=1 BITS=32：32位的release版。
# make RELEASE=1 BITS=64：64位的release版。

# args
RELEASE=1
BITS=64
CENTOS=7
label=
# CENTOS =6
# [args] 生成模式. 0代表debug模式, 1代表release模式. make RELEASE=1.

SUBDIRS = stlTest \
#		SynDBConfig\
#		SysDb\
#		SearchDevice \


export


.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)
	@echo SUBDIRS=#$(SUBDIRS)#

$(SUBDIRS):
#	make -C $@ RELEASE=${RELEASE} BITS=${BITS} CENTOS=${CENTOS}
	make -C $@ $(label)

clean :
	@for dir in ${SUBDIRS}; do \
	      echo dir1=$($dir); \
	      echo dir1=$$; \
	      echo dir2=$$(dir); \
        make -C $$dir clean; \
    done



clean2 :
	@for dir in ${SUBDIRS}; do echo $dir;   echo $$dir; done
