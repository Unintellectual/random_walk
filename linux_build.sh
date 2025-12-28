
#!/bin/sh

set -xe

clang random_walk.c -o random_walk -ggdb -I/usr/include -I/usr/local/include -std=c99 -Os -flto -Wall -Wextra -Wpedantic -L/usr/local/lib -lraylib -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
