###########################################################################
# Makefile                                                                #
# Copyright (c) 20018 by FQR Project.  All rights reserved.               #
#                                                                         #
#   This file is the Makefile for the libs which are used by FQR project. #
#                                                                         #
###########################################################################

# Please add used libs' compile, link, and other make commands into here.
# ######  Libs_3rd ##########
# 
all build compile: $(BUILD)/obj/libs_3rd.a

# ---- cJSON lib BEGIN ++++
cJSON_DIR_NAME = cJSON
# cJSON_SRC_H = $(wildcard $(LIBS_3rd)/$(cJSON_DIR_NAME)/*.h)
cJSON_SRC_H += $(cJSON_DIR_NAME)/cJSON.h
# OBJ_CC = $(patsubst %.c, %.o, $(SRC_CC))

# ----- copy *.h to $(BUILD)/inc
cJSON_h: $(cJSON_SRC_H)
	@echo '=>[Copy] cJSON lib header files.'
	mkdir -p "$(BUILD)/inc"
	cp $(cJSON_SRC_H) $(BUILD)/inc/

#--- compile cJSON.o ---
# DEPS_yut_cjson_2 += $(BUILD)/inc/cJSON.h
$(BUILD)/obj/cJSON.o: # $(cJSON_DIR_NAME)/cJSON.c $(DEPS_yut_cjson_2)
	@echo '=>[Compile] $(BUILD)/obj/cJSON.o'
	$(CC) -c -o $(BUILD)/obj/cJSON.o $(CFLAGS) $(DFLAGS) -D_FILE_OFFSET_BITS=64 -D_FILE_OFFSET_BITS=64 -DMBEDTLS_USER_CONFIG_FILE=\"embedtls.h\" -DME_COM_OPENSSL_PATH=$(ME_COM_OPENSSL_PATH) $(IFLAGS) "-I$(ME_COM_OPENSSL_PATH)/include" $(cJSON_DIR_NAME)/cJSON.c
# ---- cJSON lib END ----

###########################################################################
#  Compile libs_3rd.a                                                     #
#   it's used by 'webs_agent_goahead_cust.mak' to build 'webs_agent.bin'  #
###########################################################################
DEPS_yut_libs_3rd_x += cJSON_h
DEPS_yut_libs_3rd_x += $(BUILD)/obj/cJSON.o

$(BUILD)/obj/libs_3rd.a: $(DEPS_yut_libs_3rd_x)
	@echo '=>[Link] $(BUILD)/obj/libs_3rd.a'
	$(AR) -cr $(BUILD)/obj/libs_3rd.a "$(BUILD)/obj/cJSON.o"
