#!/usr/bin/env bash
autoreconf -i
automake -a
(cd extern/gl3w && python gl3w_gen.py)
./configure
