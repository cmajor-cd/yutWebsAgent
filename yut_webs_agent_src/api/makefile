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
WEBSAGENT_API_OBJS = $(patsubst %.c, %.o, $(WEBSAGENT_API_SRC_C))

# ----- copy *.h to ./$(BUILD)/inc
api_h: $(WEBSAGENT_API_SRC_H)
	@echo '=>[Copy] WEBSAGENT_API header files: $(WEBSAGENT_API_SRC_H)'
	mkdir -p "$(BUILD)/inc"
	mkdir -p "$(BUILD)/bin"
	cp $(WEBSAGENT_API_SRC_H) $(BUILD)/inc/

#--- compile .o ---
api_o: api_h
	@echo '=>[Compile] WEBSAGENT_API O files: $(WEBSAGENT_API_OBJS)'
	$(foreach item,$(WEBSAGENT_API_OBJS),\
		$(CC) -c -o $(BUILD)/obj/$(item)  $(CFLAGS) $(DFLAGS) $(IFLAGS) $(patsubst %.o, %.c, $(item)) ; \
	)

###########################################################################
#  Compile webs_agent_api.a                                               #
#                                                                         #
###########################################################################
DEPS_yut_api_x := $(foreach item,$(WEBSAGENT_API_OBJS),\
		$(BUILD)/obj/$(item)\
	)

$(BUILD)/obj/webs_agent_api.a: api_o
	@echo '=>[Build] $(BUILD)/obj/webs_agent_api.a'
	$(AR) -cr $(BUILD)/obj/webs_agent_api.a $(DEPS_yut_api_x) 
