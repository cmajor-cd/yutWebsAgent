#!/bin/bash
base_dir=$(dirname $(readlink -f "$0"))
rel_webs_bin_dir="../release/webserver"
rel_webs_root_dir="../release/webroot"
build_bin_dir="../build/bin"
# webs_agent TODO: change the web src to YOUR DIR NAME!
build_webs_root_dir="../yut_webs_agent_websrc"
build_bin_filename="yut_webs_agent.bin"
goahead_src_dir="../goahead_src"

if [ ! -d $rel_webs_bin_dir ]; then
    sudo mkdir -p $rel_webs_bin_dir
fi

if [ ! -d $rel_webs_root_dir ]; then
    sudo mkdir -p $rel_webs_root_dir
fi

sudo cp $build_bin_dir/{self.crt,self.key,libgo.so,*.bin} $rel_webs_bin_dir
sudo cp $goahead_src_dir/src/{auth.txt,route.txt} $rel_webs_bin_dir
sudo cp -r $build_webs_root_dir/* $rel_webs_root_dir

sudo $rel_webs_bin_dir/$build_bin_filename -v --home $rel_webs_bin_dir $base_dir/$rel_webs_root_dir 0.0.0.0:8080