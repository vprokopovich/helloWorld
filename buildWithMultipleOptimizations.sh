#!/bin/bash

flags=( O0 O1 O2 O3 )

for i in "${flags[@]}"
do
   :
   # do whatever on $i

   cd solutions
   export OPTIMIZATION_FLAG="-${i}"
   cmake ./../src
   cmake --build . --target measures
   output="linux${OPTIMIZATION_FLAG}.csv"
   ../products/bin/measures > ${output}
   cd ..
done
