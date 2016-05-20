cat src/* shaders/* | wc -l
if [[ -n $1 ]] && [[ $1 = "-v" ]]
then
    for fn in src/* shaders/*; do
        wc -l $fn
    done
fi
