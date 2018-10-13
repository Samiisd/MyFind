#!/usr/bin/env bash

# -- Function definitions --
print_success(){
    [ $# -ne 1 ] && exit 1;
    printf "\e[32m%s\e[0m" "$1"
}

print_error(){
    [ $# -ne 1 ] && exit 1;
    printf "\e[31m%s\e[0m" "$1"
}

# -- Check arguments --
[ $# -ne 3 ] && echo "usage: $0 tests_dir to_test_bin log_dir" && exit 1;
[ ! -d "$1" ] && echo "'$1' is not a correct directory" && exit 1;
[ ! -x "$2" ] && echo "'$2' is not a correct executable" && exit 1;

# -- Creating the LOG folder --
if [ -d "$3" ]; then
    $(rm -r "$3")
fi

$(mkdir "$3")
[ $? -ne 0 ] && echo "Unable to create the log folder '$3'" && exit 1;

# -- Running tests --
nb_tests=0
nb_tests_failed=0

echo -e "\n-- Test suite --"
echo -e "Starting tests...\n"

for test_file in $(ls "$1")
do
    printf "> test [%d] ('%s') : " $nb_tests "$test_file"

    stdout_corr="$3/test_"$nb_tests"_correct_stdout"
    stdout_totest="$3/test_"$nb_tests"_totest_stdout"

    touch $stdout_corr
    touch $stdout_totest

    argument=$(cat "$1/$test_file")

    $(find $argument 1> $stdout_corr 2> /dev/null)
    $($2 $argument 1> $stdout_totest 2> /dev/null)

    stdout_log=$(diff "$stdout_corr" "$stdout_totest")

    if [ $? -ne 0 ]; then
        nb_tests_failed=$((nb_tests_failed + 1))
        print_error "FAILED"
        echo $stdout_log > "$3/log_stdout_$nb_tests"
    else
        print_success "OK"
        rm $stdout_corr $stdout_totest
    fi
    echo

    nb_tests=$((nb_tests + 1))
done

# -- Resume tests results --
echo
printf "Tests done  : %d\n" $nb_tests
printf "Tests failed: %d\n" $nb_tests_failed
printf "Tests passed: %d\n" $((nb_tests - nb_tests_failed))

if [ $nb_tests_failed -ne 0 ]; then
    print_error "Some tests failed, check logs to understand why..."
    echo
    exit 0
fi

$(rm -fr "$3")
print_success "All tests passed successfully!"
echo

exit 0;