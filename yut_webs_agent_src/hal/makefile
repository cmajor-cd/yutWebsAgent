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
# WEBSAGENT_HAL_OBJ_CC = $(patsubst %.c, %.o, $(WEBSAGENT_HAL_SRC_C))

# ----- copy *.h to ./$(BUILD)/inc
hal_h: $(WEBSAGENT_HAL_SRC_H)
	@echo '=>[Copy] WEBSAGENT_HAL header files: $(WEBSAGENT_HAL_SRC_H)'
	mkdir -p "$(BUILD)/inc"
	mkdir -p "$(BUILD)/bin"
	cp $(WEBSAGENT_HAL_SRC_H) $(BUILD)/inc/

#--- compile .o ---
# hal_o:
	# $(foreach item,$(WEBSAGENT_HAL_SRC_C),\
	# 	echo $(item);\
	# 	echo $(BUILD)/obj/$(patsubst %.c, %.o, $(item)) | sed 's/ //g';\
	# 	$(CC) -c $(item) -o $(BUILD)/obj/$(patsubst %.c, %.o, ${$(item)// //g}); \
	# )
# ---- hal.o ----
# DEPS_yut_hal_1 += hal_h
$(BUILD)/obj/hal.o: 
	@echo '=>[Compile] hal.o'
	$(CC) -c -o $(BUILD)/obj/hal.o $(CFLAGS) $(DFLAGS) $(IFLAGS) ./hal.c
# ---- hal.o ----
# DEPS_yut_hal_1 += hal_h
# $(BUILD)/obj/hal2.o: 
# 	@echo '=>[Compile] hal2.o'
# 	$(CC) -c -o $(BUILD)/obj/hal2.o $(CFLAGS) $(DFLAGS) $(IFLAGS) ./hal2.c
# ---- hal.o ----

###########################################################################
#  Compile webs_agent_hal.a                                               #
#                                                                         #
###########################################################################
DEPS_yut_hal_x += hal_h
DEPS_yut_hal_x += $(BUILD)/obj/hal.o
# DEPS_yut_hal_x += $(BUILD)/obj/hal2.o

$(BUILD)/obj/webs_agent_hal.a: $(DEPS_yut_hal_x)
	@echo '=>[Link] $(BUILD)/obj/webs_agent_hal.a'
	$(AR) -cr $(BUILD)/obj/webs_agent_hal.a "$(BUILD)/obj/hal.o" 
	# $(BUILD)/obj/hal2.o
