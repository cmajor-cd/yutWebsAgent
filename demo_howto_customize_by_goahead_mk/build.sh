#!/bin/bash
goahead_src_dir="../goahead_src"
goahead_src_projects_dir="../goahead_src/projects"
build_dir="../build"
mk_filename="yut_webs_agentdemo.mk"

if [ ! -d $goahead_src_projects_dir ]; then
    echo "ERROR: " $goahead_src_projects_dir "is NOT exist!"
    exit 1
fi

sudo cp $mk_filename $goahead_src_projects_dir
cd $goahead_src_dir
sudo make -f projects/$mk_filename SHOW=1