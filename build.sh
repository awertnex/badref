#!/bin/bash

SOURCE='src/'
MAIN='main.c'
CHILDREN=''
CFLAGS='-Wall -Wextra'
LIBS='-lraylib -lm'
OUT='badref'

set -xe

if [ "$1" == "test" ]; then
	MAIN='test.c'
	OUT='test'
fi

pushd $SOURCE
time gcc $MAIN $CHILDREN $CFLAGS $LIBS -o $OUT &&
mv $OUT ../
popd
