

dirtmp=tmp
dirinc=module1/inc module2/inc
dirsrc1=module1/src
dirsrc2=module2/src
dirsrc=$(dirsrc1) $(dirsrc2) .
#objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard *.cpp $(dirsrc1)/*.cpp  $(dirsrc2)/*.cpp))))
objs=$(addprefix $(dirtmp)/,$(notdir $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp,$(dirsrc))))))

# SO_LIBS=-ldl -pthread -lrt
SO_LIBS=-ldl
target=$(dirtmp)/main

vpath %.h $(dirinc)
vpath %.cpp $(dirsrc1)
vpath %.cpp $(dirsrc2)
vpath %.cpp .
CFLAGS+=$(addprefix -I, $(dirinc))
override CXXFLAGS+=-fno-elide-constructors -std=c++17 -rdynamic -g

.PHONEY:
all:$(target)
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
	mkdir -p $(dirtmp)

.PHONEY:
clean:
	-rm $(objs) $(target) $(addsuffix *, $(alldfile))
#	-rm -rf $(dirtmp)

.PHONEY:
test:
	$(info $(objs) objs)
	$(info $(CFLAGS) CFLAGS)
	$(info $(CPPFLAGS) CPPFLAGS)
	$(info $(CXXFLAGS) CXXFLAGS)
	$(info $(addsuffix /*.cpp, $(dirsrc)) dirsrc)
	$(info $(alldfile) alldfile)
