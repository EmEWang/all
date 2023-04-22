####################################################
# Generic makefile 
# for compiling and linking C++ projects on Linux 
# Author: George Foot  Modified:Jackie Lee
#################################################### 

SOLUTIONDIR = ..
BASE_INCLUDE=
#../../base/include
# 输出文件名
OUTPUT_NAME= stltest
OUTPUT_PATH= ..
RULE_PATH = ..

# 库文件名
LIBS :=
#MXTranslate mxcomlib NNMlib mxdbvar MxHandlePool  TableVar  ServerData  DbWork  Bslib HttpProtocol liclib bsapi chen uuid ssl crypto json pthread dl rt

# 头文件目录 
INCLUDES:= ./
#			$(BASE_INCLUDE)/port2linux \
#			$(BASE_INCLUDE)/chen \
#			$(BASE_INCLUDE) \
#			$(BASE_INCLUDE)/Http \
#			$(BASE_INCLUDE)/bsapi \
#			$(BASE_INCLUDE)/mxcomlib \
#			$(BASE_INCLUDE)/MxHandlePool \
#			$(BASE_INCLUDE)/mxdbvar \
#			$(SOLUTIONDIR)/ServerData \
#			$(SOLUTIONDIR)/DbWork \
#			$(SOLUTIONDIR)/UtilCode \
#			$(BASE_INCLUDE)/TabelVar \
#			$(SOLUTIONDIR)/NNMLib \
#			$(SOLUTIONDIR)/WpsRun_LibXlsxWriter \
#			$(SOLUTIONDIR)/ErrorCode \
#			$(SOLUTIONDIR)/liclib \
#			$(SOLUTIONDIR) \
#			./

# 除了当前目录外，其他的源代码文件目录
SRCDIR:=  
		  
# 除了当前目录外，其他的源代码文件
SRCFILES :=      

#    
# # Now alter any implicit rules' variables if you like, e.g.:   
include $(RULE_PATH)/Makefile.rule


CFLAGS   +=  -DMIDRUN_EXPORTS -DNETFLOW_DEBUG   

#$(EXECUTABLE) : $(OBJS) 
$(EXECUTABLE) :
	@echo EXECUTABLE=#$(EXECUTABLE)#
	@echo OBJS=#$(OBJS)#
	@echo INCLUDES=#$(INCLUDES)#
	@echo BASE_INCLUDE=#$(BASE_INCLUDE)#
	@echo SOLUTIONDIR=#$(SOLUTIONDIR)#
	@echo SRCDIR=#$(SRCDIR)#
	@echo CFLAGS=#$(CFLAGS)#
	@echo CPPFLAGS=#$(CPPFLAGS)#
	@echo RELEASE=#${RELEASE}#
	@echo BITS=#${BITS}#
	@echo CENTOS=#${CENTOS}#
	@echo CC=#${CC}#
	@echo CROSS_COMPILE=#${CROSS_COMPILE}#
#	ar	rcs	$(EXECUTABLE) $(OBJS)     
#	$(CC) -Wl,-R./ -o $(EXECUTABLE) -shared -fPIC -rdynamic $(LASAN) -ldl $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
#	$(CC) -o $(EXECUTABLE) -rdynamic -ldl  $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))  
#	$(CC) -o $(EXECUTABLE) -rdynamic -ldl $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))      
#	$(CC) -o $(EXECUTABLE) -shared -fPIC $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
