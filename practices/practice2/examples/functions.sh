#!/bin/sh
add() {
	echo $*
	echo $(($1+$2))
}
add 2 3
