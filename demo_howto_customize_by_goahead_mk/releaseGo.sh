#!/bin/bash
base_dir=$(dirname $(readlink -f "$0"))
rel_webs_bin_dir="../release/webserver"
rel_webs_root_dir="../release/webroot"
build_bin_dir="../build/bin"
build_webs_root_dir="./webroot"
build_bin_filename="yut_webs_agentdemo.bin"
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