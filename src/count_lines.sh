#!/bin/sh
find . -name '*.h' | xargs wc -l
find . -name '*.cpp' | xargs wc -l