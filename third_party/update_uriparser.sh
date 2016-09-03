#!/bin/sh
VERSION=0.8.4
CURDIR="$1"
rm -fr uriparser* && mkdir $CURDIR/uriparser
wget https://downloads.sourceforge.net/project/uriparser/Sources/$VERSION/uriparser-$VERSION.zip  -O $CURDIR/uriparser-$VERSION.zip
unzip -q uriparser-$VERSION.zip
cp -r $CURDIR/uriparser-$VERSION/* $CURDIR/uriparser/
rm -fr $CURDIR/uriparser-*

