cat *.cc *.h | wc -l
if [[ -n $1 ]] && [[ $1 = "-v" ]]
then
    for fn in *.cc *.h; do
        wc -l $fn
    done
fi
