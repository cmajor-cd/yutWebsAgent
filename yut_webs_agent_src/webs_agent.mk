# ------- 工作说明 ------ 
# MK文件会在build过程中会做以下两步操作：
# 1. build.h 将'webs_agent_goahead_cust.mk' copy到 ./goahead_src/projects 目录下并改名为makefile。以保持goahead的makefile架构不变。
# 2. build.sh 再调用 make webs_agent.mk 进行最终的编译。
# 采用此方法主要是兼容 goahead mk文件的规则，避免过多改动 goahead的结构。
# 整个makefile的基础目录是=> ./webs_agent_src
# -----------------------

# #################################################
#  以下为继承于 goAhead 的编译宏定义和编译开关
# ---- 用于覆盖goAhead MK定义的控制信息
# 1.TODO // please modify the parameters by your platform!!
#ARCH ?=arm
ARCH                  ?= $(shell uname -m | sed 's/i.86/x86/;s/x86_64/x64/;s/arm.*/arm/;s/mips.*/mips/')
#CC := arm-fsl-linux-gnueabi-gcc
CC    = gcc

BUILD = $(shell pwd)/../build

ME_COM_COMPILER       ?= 1
ME_COM_LIB            ?= 1
ME_COM_MATRIXSSL      ?= 0
ME_COM_MBEDTLS        ?= 1
ME_COM_NANOSSL        ?= 0
ME_COM_OPENSSL        ?= 0
ME_COM_OSDEP          ?= 1
# ME_COM_SSL            ?= 1
ME_COM_SSL            ?= 0
ME_COM_VXWORKS        ?= 0

ME_COM_OPENSSL_PATH   ?= "/path/to/openssl"

ifeq ($(ME_COM_LIB),1)
    ME_COM_COMPILER := 1
endif
ifeq ($(ME_COM_MBEDTLS),1)
    ME_COM_SSL := 1
endif
ifeq ($(ME_COM_OPENSSL),1)
    ME_COM_SSL := 1
endif

CFLAGS                += -fPIC -fstack-protector --param=ssp-buffer-size=4 -Wformat -Wformat-security -Wl,-z,relro,-z,now -Wl,--as-needed -Wl,--no-copy-dt-needed-entries -Wl,-z,noexecstatck -Wl,-z,noexecheap -w
DFLAGS                += -D_REENTRANT -DPIC $(patsubst %,-D%,$(filter ME_%,$(MAKEFLAGS))) -DME_COM_COMPILER=$(ME_COM_COMPILER) -DME_COM_LIB=$(ME_COM_LIB) -DME_COM_MATRIXSSL=$(ME_COM_MATRIXSSL) -DME_COM_MBEDTLS=$(ME_COM_MBEDTLS) -DME_COM_NANOSSL=$(ME_COM_NANOSSL) -DME_COM_OPENSSL=$(ME_COM_OPENSSL) -DME_COM_OSDEP=$(ME_COM_OSDEP) -DME_COM_SSL=$(ME_COM_SSL) -DME_COM_VXWORKS=$(ME_COM_VXWORKS) 
IFLAGS                += "-I$(BUILD)/inc"
LDFLAGS               += '-rdynamic' '-Wl,--enable-new-dtags' '-Wl,-rpath,$$ORIGIN/'
LIBPATHS              += -L$(BUILD)/bin
LIBS                  += -lrt -ldl -lpthread -lm

DEBUG                 = release
# DEBUG                 = debug
CFLAGS-debug          ?= -g
DFLAGS-debug          = -DME_DEBUG=1
LDFLAGS-debug         ?= -g
DFLAGS-release        = -DME_DEBUG=0
CFLAGS-release        ?= -O2
LDFLAGS-release       ?= 
CFLAGS                += $(CFLAGS-$(DEBUG))
DFLAGS                += $(DFLAGS-$(DEBUG))
LDFLAGS               += $(LDFLAGS-$(DEBUG))

TARGETS               += $(BUILD)/bin/yut_webs_agent.bin


# export for all sun makefiles
export ARCH CC BUILD CFLAGS DFLAGS IFLAGS LDFLAGS LIBPATHS LIBS DEBUG CFLAGS-debug DFLAGS-debug LDFLAGS-debug DFLAGS-release CFLAGS-release LDFLAGS-release TARGETS ME_COM_COMPILER ME_COM_LIB ME_COM_MATRIXSSL ME_COM_MBEDTLS ME_COM_NANOSSL ME_COM_OPENSSL ME_COM_OSDEP ME_COM_SSL ME_COM_VXWORKS

ifndef SHOW
.SILENT:
endif

all build compile: prepare $(TARGETS)

.PHONY: prepare

prepare:
	@echo "=>[Info] Use "make SHOW=1" to trace executed commands."
	@[ ! -x $(BUILD)/bin ] && mkdir -p $(BUILD)/bin; true
	@[ ! -x $(BUILD)/inc ] && mkdir -p $(BUILD)/inc; true
	@[ ! -x $(BUILD)/obj ] && mkdir -p $(BUILD)/obj; true
	@echo '=>[Info] Create the dir named build '

clean:
# 	rm -f $(BUILD)/obj/*.o $(BUILD)/obj/*.so $(BUILD)/obj/*.a $(BUILD)/obj/*.bin
# completed_clean: clean
	rm -fr $(BUILD)

# build the subdir to webs_agent.a
SUBDIR_webs_agent_list += $(shell ls -d */)
SUBDIR_webs_agent_h_list = $(shell find $(SUBDIR_webs_agent_list) -name '*.h') #调用shell命令在当前目录的子目录中查找名字为 *.c 的所有文件
subdir_webs_agent:
	@echo '=>SUBDIR_webs_agent_list Copy *.h of all subdir into build/inc'
		mkdir -p "$(BUILD)/inc"
	cp $(SUBDIR_webs_agent_h_list) $(BUILD)/inc/

	@echo '=>SUBDIR_webs_agent_list = $(SUBDIR_webs_agent_list)'
	for dir in $(SUBDIR_webs_agent_list); do\
		$(MAKE) -C $$dir; \
	done

# build the submodules
# 2. TODO //please add your libs or other modules dir name into this deps.
LIBS_3rd = ../libs
MODULES_LIST += $(LIBS_3rd)

# GOAHEAD_DIR = ../goahead_src
goahead_src_projects_dir="../goahead_src/projects"
MODULES_LIST += $(goahead_src_projects_dir)
submodules:
	@echo '=>MODULES_LIST = $(MODULES_LIST)'
	for dir in $(MODULES_LIST); do\
		$(MAKE) -C $$dir; \
	done

# #################################################
# # ---- websAgent自身基础配置信息
# # 
# # ---- 准备websAgent自己的源文件信息
WEBSAGENT_SRC_H = $(wildcard ./*.h)
# # OBJ_CC = $(patsubst %.c, %.o, $(SRC_CC))

# # ----- copy *.h to $(BUILD)/inc
$(BUILD)/inc/websagent_main_h: $(WEBSAGENT_SRC_H)
	@echo '=>[Copy] websagent_main header files:$(WEBSAGENT_SRC_H)'
	mkdir -p "$(BUILD)/inc"
	cp $(WEBSAGENT_SRC_H) $(BUILD)/inc/

# # ----- compile websAgent .o files ---
# DEPS_yut_main_1 += $(BUILD)/inc/goahead.h
# DEPS_yut_main_1 += $(BUILD)/inc/js.h
DEPS_yut_main_1 += $(BUILD)/inc/websagent_main_h

$(BUILD)/obj/webs_agent_main.o: $(DEPS_yut_main_1)
	@echo '=>[Compile] $(BUILD)/obj/yut_webs_agent.o'
	$(CC) -c -o $(BUILD)/obj/webs_agent_main.o $(CFLAGS) $(DFLAGS) -D_FILE_OFFSET_BITS=64 -D_FILE_OFFSET_BITS=64 -DMBEDTLS_USER_CONFIG_FILE=\"embedtls.h\" -DME_COM_OPENSSL_PATH=$(ME_COM_OPENSSL_PATH) $(IFLAGS) "-I$(ME_COM_OPENSSL_PATH)/include" webs_agent_main.c

# #----- link to exe bin ---
DEPS_yut_main_x += submodules
DEPS_yut_main_x += subdir_webs_agent
DEPS_yut_main_x += $(BUILD)/obj/webs_agent_main.o

# -----以 .o和.a的顺序请特别注意，否则link会有问题。
# 3. TODO //please add your libs or other modules .o / .a name into this deps.
OBJS_yut_main_x += $(BUILD)/obj/webs_agent_main.o
OBJS_yut_main_x += $(BUILD)/obj/webs_agent_api.a
OBJS_yut_main_x += $(BUILD)/obj/webs_agent_hal.a
OBJS_yut_main_x += $(BUILD)/obj/libs_3rd.a
OBJS_yut_main_x += $(BUILD)/bin/libgo.so
# OBJS_yut_main_x += $(BUILD)/obj/.install-certs-modified

ifeq ($(ME_COM_MBEDTLS),1)
    LIBS_yut_main_x += -lmbedtls
endif
ifeq ($(ME_COM_MBEDTLS),1)
    LIBS_yut_main_x += -lgoahead-mbedtls
endif
ifeq ($(ME_COM_MBEDTLS),1)
    LIBS_yut_main_x += -lmbedtls
endif
ifeq ($(ME_COM_OPENSSL),1)
    LIBS_yut_main_x += -lgoahead-openssl
endif
ifeq ($(ME_COM_OPENSSL),1)
ifeq ($(ME_COM_SSL),1)
    LIBS_yut_main_x += -lssl
    LIBPATHS_yut_main_x += -L"$(ME_COM_OPENSSL_PATH)"
endif
endif
ifeq ($(ME_COM_OPENSSL),1)
    LIBS_yut_main_x += -lcrypto
    LIBPATHS_yut_main_x += -L"$(ME_COM_OPENSSL_PATH)"
endif
LIBS_yut_main_x += -lgo
ifeq ($(ME_COM_OPENSSL),1)
    LIBS_yut_main_x += -lgoahead-openssl
endif
ifeq ($(ME_COM_MBEDTLS),1)
    LIBS_yut_main_x += -lgoahead-mbedtls
endif

$(BUILD)/bin/yut_webs_agent.bin: $(DEPS_yut_main_x)
	@echo '=>[Link] $(BUILD)/bin/yut_webs_agent.bin'
	# $(CC) -o $(BUILD)/bin/yut_webs_agent.bin $(OBJS_yut_main_x)
	$(CC) -o $(BUILD)/bin/yut_webs_agent.bin $(LDFLAGS) $(LIBPATHS) $(LIBPATHS_yut_main_x) $(LIBS_yut_main_x) $(LIBS) $(OBJS_yut_main_x)

