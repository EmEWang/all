

dirtmp=tmp
# dirinc=module1/inc module2/inc module3/inc module4/inc
dirinc=$(shell find module*/inc -type d)
dirsrc1=module1/src
dirsrc2=module2/src
dirsrc3=module3/src
dirsrc4=module4/src
# dirsrc=$(dirsrc1) $(dirsrc2) $(dirsrc3) $(dirsrc4) .
dirsrc=$(shell find module*/src -type d) .
#objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard *.cpp $(dirsrc1)/*.cpp  $(dirsrc2)/*.cpp))))
objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp,$(dirsrc))))))

subdirs=testlinux1 testlinux2 profilecpu profileheap profilemalloc
subdirs2=testlinux3#这部分需要进入目录 因为会获取当前目录

# SO_LIBS=-ldl -pthread -lrt
SO_LIBS=-ldl -pthread
target=$(dirtmp)/main

vpath %.h $(dirinc)
# vpath %.cpp $(dirsrc1)
# vpath %.cpp $(dirsrc2)
# vpath %.cpp $(dirsrc3)
# vpath %.cpp $(dirsrc4)
# vpath %.cpp .
vpath %.cpp $(dirsrc)
CFLAGS+=$(addprefix -I, $(dirinc))
#override CXXFLAGS+=-fno-elide-constructors -std=c++17 -rdynamic -g
override CXXFLAGS+=-fno-elide-constructors -std=c++2a -rdynamic -g -fconcepts
# override CXXFLAGS+=-std=c++2a -rdynamic -g

.PHONEY:
all:$(target)
	@for dir in ${subdirs}; do \
		make -C $${dir}; \
	done

	@for dir in ${subdirs2}; do \
		cd $${dir} && make; \
	done

	./$(target)

$(target):$(objs)
	g++ -o $@  $(CXXFLAGS)  $^ $(SO_LIBS)

$(objs):$(dirtmp)/%.o:%.cpp
	$(info $$@:$@  $$<:$<  $$^:$^ $$*:$* )
	g++ -o $@ $(CFLAGS) $(CXXFLAGS) -c $<



CPPFLAGS+=-I./
CPPFLAGS+=$(addprefix -I, $(dirinc))
$(dirtmp)/%.d: %.cpp
	@set -e; rm -f $@; \
	g++ -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(dirtmp)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

alldfile = $(patsubst %.o,%.d,$(objs))
include $(alldfile)


.PHONEY:
dir:
	-mkdir -p $(dirtmp)

.PHONEY:
clean:
	-rm -f $(objs) $(target) $(addsuffix *, $(alldfile)) test_file.txt
#	-rm -rf $(dirtmp)
#	@echo subdirs=${subdirs}
#	@for dir in ${subdirs}; do \
#		echo dir0=${dir}; \
#		echo dir1=$($dir); \
#		echo dir2=$$; \
#		echo dir3=$$(dir); \
#		make -C $${dir} clean; \
#	done
	@for dir in ${subdirs}; do \
		echo $${dir}; \
		make -C $${dir} clean ; \
	done

	@for dir in ${subdirs2}; do \
		echo $${dir}; \
		cd $${dir} && make clean ; \
	done

.PHONEY:
test:
	$(info $(objs) objs)
	$(info $(CFLAGS) CFLAGS)
	$(info $(CPPFLAGS) CPPFLAGS)
	$(info $(CXXFLAGS) CXXFLAGS)
	$(info $(addsuffix /*.cpp, $(dirsrc)) dirsrc)
	$(info $(alldfile) alldfile)
	$(info $(dirinc) dirinc)
