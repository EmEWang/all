


dirsrc1=.
dirsrc=$(dirsrc1)
#objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard *.cpp $(dirsrc1)/*.cpp  $(dirsrc2)/*.cpp))))
#objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp,$(dirsrc))))))
objs=$(basename $(wildcard $(addsuffix /*.cpp,$(dirsrc))))

all:
	$(info objs: $(objs) )




clean:
	rm -f $(objs)

