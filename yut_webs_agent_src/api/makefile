###########################################################################
# Makefile                                                                #
# Copyright (c) 20018 by webs_agent Project.  All rights reserved.        #
#                                                                         #
###########################################################################

# Please add used api' compile, link, and other make commands into here.
# 
all build compile: $(BUILD)/obj/webs_agent_api.a

# ---- hal file list ++++
WEBSAGENT_API_SRC_H = $(wildcard *.h)
WEBSAGENT_API_SRC_C = $(wildcard *.c)
# WEBSAGENT_APP_OBJ_CC = $(patsubst %.c, %.o, $(WEBSAGENT_API_SRC_C))

# ----- copy *.h to ./$(BUILD)/inc
api_h: $(WEBSAGENT_API_SRC_H)
	@echo '=>[Copy] WEBSAGENT_API header files: $(WEBSAGENT_API_SRC_H)'
	mkdir -p "$(BUILD)/inc"
	mkdir -p "$(BUILD)/bin"
	cp $(WEBSAGENT_API_SRC_H) $(BUILD)/inc/

#--- compile .o ---
# app_o:
	# $(foreach item,$(WEBSAGENT_API_SRC_C),\
	# 	echo $(item);\
	# 	echo $(BUILD)/obj/$(patsubst %.c, %.o, $(item)) | sed 's/ //g';\
	# 	$(CC) -c $(item) -o $(BUILD)/obj/$(patsubst %.c, %.o, ${$(item)// //g}); \
	# )
# ---- api.o ----
# DEPS_yut_hal_1 += hal_h
$(BUILD)/obj/api.o: 
	@echo '=>[Compile] api.o'
	$(CC) -c -o $(BUILD)/obj/api.o $(CFLAGS) $(DFLAGS) $(IFLAGS) ./api.c
# ---- api.o ----

###########################################################################
#  Compile webs_agent_api.a                                               #
#                                                                         #
###########################################################################
DEPS_yut_hal_x += api_h
DEPS_yut_hal_x += $(BUILD)/obj/api.o

$(BUILD)/obj/webs_agent_api.a: $(DEPS_yut_hal_x)
	@echo '=>[Link] $(BUILD)/obj/webs_agent_api.a'
	$(AR) -cr $(BUILD)/obj/webs_agent_api.a $(BUILD)/obj/api.o
