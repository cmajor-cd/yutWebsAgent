###########################################################################
# Makefile                                                                #
# Copyright (c) 20018 by webs_agent Project.  All rights reserved.               #
#                                                                         #
###########################################################################

# Please add used hal' compile, link, and other make commands into here.
# 
all build compile: $(BUILD)/obj/webs_agent_hal.a

# ---- hal file list ++++
WEBSAGENT_HAL_SRC_H = $(wildcard *.h)
WEBSAGENT_HAL_SRC_C = $(wildcard *.c)
WEBSAGENT_HAL_OBJS = $(patsubst %.c, %.o, $(WEBSAGENT_HAL_SRC_C))

# ----- copy *.h to ./$(BUILD)/inc
hal_h: $(WEBSAGENT_HAL_SRC_H)
#	@echo '=>[Copy] WEBSAGENT_HAL header files: $(WEBSAGENT_HAL_SRC_H)'
	mkdir -p "$(BUILD)/inc"
	mkdir -p "$(BUILD)/bin"
	cp $(WEBSAGENT_HAL_SRC_H) $(BUILD)/inc/

#--- compile .o ---
hal_o: hal_h
#	@echo '=>[Compile] WEBSAGENT_HAL O files: $(WEBSAGENT_HAL_OBJS)'
	$(foreach item,$(WEBSAGENT_HAL_OBJS),\
		$(CC) -c -o $(BUILD)/obj/$(item)  $(CFLAGS) $(DFLAGS) $(IFLAGS) $(patsubst %.o, %.c, $(item)) ; \
	)
#		$(CC) -c $(patsubst %.o, %.c, $(item)) -o $(BUILD)/obj/$(item); 

###########################################################################
#  Compile webs_agent_hal.a                                               #
#                                                                         #
###########################################################################
DEPS_yut_hal_x := $(foreach item,$(WEBSAGENT_HAL_OBJS),\
		$(BUILD)/obj/$(item)\
	)

$(BUILD)/obj/webs_agent_hal.a: hal_o
	@echo '=>[Build] $(BUILD)/obj/webs_agent_hal.a'
	$(AR) -cr $(BUILD)/obj/webs_agent_hal.a $(DEPS_yut_hal_x) 
