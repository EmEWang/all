

# LINK.c  cc   COMPILE.c  cc -c
PROG := main
SRCS := $(PROG).c
AAA=AAA
BBB+=BBB

$(PROG): $(SRCS:.c=.o)
	$(LINK.c) $^ -o $@

sinclude $(SRCS:.c=.d)

# $(:=) performs a string replacement.
# $@ is the name of the file being generated (the target).
# So $(@:%.o=%.d) is the name of the file, with the .o extension changed to .d.
# 其实 $@  就是 $(@)  也就是说 @ 才是变量 $@ 就是使用变量
%.o: %.c
	gcc -MM -MP -MT $@ -MF $(@:.o=.d) $<
	$(COMPILE.c) $< -o $@

test:
	$(info LINK.c:$(LINK.c))
	$(info COMPILE.c:$(COMPILE.c))
	$(info AAA:$(AAA))
	$(info BBB:$(BBB))
	$(info CFLAGS:$(CFLAGS))
	$(info CPPFLAGS:$(CPPFLAGS))
	$(info CXXFLAGS:$(CXXFLAGS))
	$(info LDFLAGS:$(LDFLAGS))
clean:
	-rm *.o *.d $(PROG)