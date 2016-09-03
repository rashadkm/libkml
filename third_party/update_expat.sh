#!/bin/sh
VERSION=2.1.0
CURDIR="$1"
echo $CURDIR
rm -fr expat* && mkdir $CURDIR/expat
wget http://downloads.sourceforge.net/project/expat/expat/$VERSION/expat-$VERSION.tar.gz  -O $CURDIR/expat-$VERSION.tar.gz
tar xvf $CURDIR/expat-$VERSION.tar.gz
cp -r $CURDIR/expat-$VERSION $CURDIR/expat/
rm -fr $CURDIR/expat-*

