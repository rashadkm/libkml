#!/bin/sh
THIS_FILE=$(readlink -f "$0")
CURDIR=$(dirname "$THIS_FILE")
cd $CURDIR
VERSION=1.61.0
VER=1_61_0
rm -fr boost* && mkdir $CURDIR/boost
wget http://downloads.sourceforge.net/project/boost/boost/$VERSION/boost_$VER.zip  -O $CURDIR/boost_$VER.zip
unzip -q $CURDIR/boost_$VER.zip
cp -r $CURDIR/boost_$VER/boost/smart_ptr $CURDIR/boost/
cp $CURDIR/boost_$VER/boost/shared_ptr.hpp $CURDIR/boost/
rm -fr $CURDIR/boost_$VER*

. ./update_expat.sh "$CURDIR"
. ./update_uriparser.sh "$CURDIR"
