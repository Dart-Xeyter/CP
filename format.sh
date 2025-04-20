#!/bin/bash

### find -name "*.cpp" | sort -g | xargs ./format.sh > ICPC.tex
# cat ICPC_algorithms.txt | xargs ./format.sh > ICPC.tex
# ./format.sh ICPC_algorithms.txt >> ICPC.tex

# geometry -> points
# math -> pow, factor
# graph -> LCA, DO (HLD)

echo "\documentclass[a4paper, 10pt]{article}
\usepackage[a4paper, left=3mm, right=3mm, top=19mm, bottom=6mm]{geometry}
\usepackage[utf8]{inputenc}
\usepackage[english, russian]{babel}
\usepackage{indentfirst}
\usepackage{amsmath, amsfonts, amssymb}
\usepackage{graphicx}
\usepackage{listings}

\usepackage{fancyhdr}
\pagestyle{fancy}
\fancyhead{}
\fancyhead[LO]{~~~MIPT (Gorbunov, Porai, Savvateev)}
\fancyhead[RO]{Page \thepage\;of 50~~~}
\fancyfoot{}
\begin{document}
\begin{center}
"

while [[ $# > 0 ]]
do
    name=$1
    file_name=$(basename $name)
    read -r -d "." short_name <<< $(echo $file_name)
    right_name=$(echo $short_name | sed -E "s/_/\\\\_/g")
    echo "\section*{$right_name}"

    readarray lines < $name
    len=${#lines[*]}
    (( len-- ))

    echo "\begin{verbatim}"
    for ind in ${!lines[*]}
    do
        if [[ $ind != $len ]]
        then
            printf "|    %s" "${lines[$ind]}"
        fi
    done
    echo "\end{verbatim}"
    echo

    shift 1
done

echo "\end{center}
\end{document}"
