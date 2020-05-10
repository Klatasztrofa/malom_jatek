#/bin/bash

done_str=" -- \e[1m\e[32mdone\e[0m\n"
fail_str=" -- \e[1m\e[31mFAIL\e[0m\n"

if [[ -z $1 ]]; then
    printf "main missing\n"
    exit 1
fi

if [[ ! -d obj ]]; then
    mkdir obj
fi

compiler_return=0
build_fail=false
if [[ $@ =~ "debug" ]]; then
    g++ -g $1 src/*.cpp -Wshadow -Wall -Iinclude -lgraphics -lSDL -lSDL_ttf
    compiler_return=$?
else
    link=false
    for f in src/*.cpp; do
        if [[ $f =~ .*/(.*).cpp ]]; then
            fname=${f%.*} # cut everything after dot
            fname=${fname##*/} # cut everything before slash

            obj_file="obj/$fname.o"
            hdr_file="include/$fname.*"
            build=false
            if [[ -f $obj_file ]]; then
                src_date=$(stat -c %y $f)
                hdr_date=$(stat -c %y $hdr_file)
                obj_date=$(stat -c %y $obj_file)

                if [[ $src_date > $obj_date || $hdr_date > $obj_date ]]; then
                    build=true
                    link=true
                fi
                if [[ $@ =~ "clean" ]]; then
                    build=true
                    link=true
                fi
            else
                build=true
                link=true
            fi

            if [[ $build = true ]]; then
                printf "building \e[1m$fname\e[0m"
                g++ -c $f -o$obj_file -Iinclude
                compiler_return=$?

                if [[ $compiler_return = 0 ]]; then
                    printf "$done_str"
                else
                    printf "$fail_str"
                    build_fail=true
                fi
            fi
        fi
    done

    out_date=$(stat -c %y ./a.out)
    main_date=$(stat -c %y $1)

    if [[ $main_date > $out_date ]]; then
        link=true
    fi

    if [[ $build_fail = false &&  $link = true && $compiler_return = 0 ]]; then
        printf "linking"
        g++ $1 obj/*.o -Iinclude -lgraphics -lSDL -lSDL_ttf
        compiler_return=$?
        if [[ $compiler_return = 0 ]]; then
            printf "$done_str"
        else
            printf "$fail_str"
        fi
    fi
fi

if [[ $build_fail = false && $compiler_return = 0 ]]; then
    if [[ $@ =~ "go" ]]; then
        ./a.out --release
    fi
fi