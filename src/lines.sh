#!/bin/bash
echo "Files: ";
find . -name *.h -o -name *.cpp | wc -l;
echo "Lines: ";
cat `find . -name "*.h" -o -name "*.cpp"` | wc -l;
