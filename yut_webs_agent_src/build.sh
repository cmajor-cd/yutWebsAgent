#!/bin/bash
webs_agent_src_dir="../yut_webs_agent_src"
# goahead_src_dir="../goahead_src"
goahead_src_projects_dir="../goahead_src/projects"
# build_dir="../build"
mk_filename_main="webs_agent.mk"
mk_filename_goahead="webs_agent_gohead_cust.mk"

if [ ! -d $goahead_src_projects_dir ]; then
    echo "ERROR: " $goahead_src_projects_dir "is NOT exist!"
    exit 1
fi

sudo cp $mk_filename_goahead $goahead_src_projects_dir/makefile
# cd $goahead_src_dir
# sudo make -f projects/$mk_filename SHOW=1
# cd $webs_agent_src_dir
sudo make -f $mk_filename_main
