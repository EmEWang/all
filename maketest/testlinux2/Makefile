
tar=main
obj=$(subst .cpp,.o,$(wildcard *.cpp))
com=g++

${tar}:${obj}
	${com} -o ${tar} $^

# %.o:%.cpp
# 	${com} -o $@ -c $<

.PHONY:
clean:
	-rm  -f ${obj} ${tar}

.PHONY:
test:
	$(info "obj:${obj}")

