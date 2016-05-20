cat src/*.cc src/*.h | wc -l
if [[ -n $1 ]] && [[ $1 = "-v" ]]
then
    for fn in src/*.cc src/*.h; do
        wc -l $fn
    done
fi
