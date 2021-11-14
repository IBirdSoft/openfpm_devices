#! /bin/bash

hostname=$(hostname)
branch=$3

echo "Machine: $hostname"
echo "Branch: $branch"

if [ x"$hostname" == x"cifarm-centos-node.mpi-cbg.de"  ]; then
        echo "CentOS node"
        source /opt/rh/devtoolset-8/enable
	export PATH="$HOME/openfpm_dependencies/openfpm_pdata/$branch/CMAKE/bin:$PATH"
fi

if [ x"$hostname" == x"cifarm-ubuntu-node"  ]; then
        echo "Ubuntu node"
        export PATH="/opt/bin:$PATH"
	rm -rf $HOME/openfpm_dependencies/openfpm_devices/BOOST
fi

mkdir src/config


if [ ! -d $HOME/openfpm_dependencies/openfpm_devices/BOOST ]; then
        if [ x"$hostname" == x"cifarm-mac-node" ]; then
                echo "Compiling for OSX"
                ./install_BOOST.sh $HOME/openfpm_dependencies/openfpm_devices/ 4 clang
        else
                echo "Compiling for Linux"
                ./install_BOOST.sh $HOME/openfpm_dependencies/openfpm_devices 4 gcc
        fi
fi

sh ./autogen.sh
sh ./configure --with-boost=$HOME/openfpm_dependencies/openfpm_devices/BOOST --enable-cuda-on-cpu

make VERBOSE=1


