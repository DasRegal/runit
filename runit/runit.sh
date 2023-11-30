#!/bin/bash

RUNIT_VERSION=1.1V

INC_FILE_NAME=includes
EXE_FILE=runit_exe
RUNIT_PATH=$(pwd)
PRJ_PATH="$RUNIT_PATH/.."
SPEC_DIR="$PRJ_PATH/spec"

function print_usage {
    echo "Usage: ./runit.sh [options]"
    echo "type: './runit.sh --help' for more"
}

function print_version {
    echo "RUnit Test framework $RUNIT_VERSION"
}

function print_help {
    echo "Usage: ./runit.sh [options]"
    echo "available options:"
    echo "  -h, --help"
    echo "      prints this page"
    echo "  -v, --verbose"
    echo "      be verbose"
    echo "  -V, --version"
    echo "      print program version"
    echo ""
}

VERBOSE_MODE=

for key in "$@"
do
case $key in
    --help|-h)
        print_help
        exit 0
        ;;
    --version|-V)
        print_version
        exit 0
        ;;
    --verbose|-v)
        VERBOSE_MODE=1
        ;;
    *)
        echo "Invalid option."
        print_usage
        exit 1
        ;;
esac
done

echo "RUnit $RUNIT_VERSION"

if [ ! -d $SPEC_DIR ]
then
    echo
    echo "[RUnit] Error: \`$SPEC_DIR\` directory does not exists."
    exit 1
fi

if [ -f $INC_FILE_NAME ]
then
    rm $INC_FILE_NAME
fi
touch $INC_FILE_NAME

if [ -z "$INC_FILES" ]
then
    INC_FILES=`ls $SPEC_DIR/*`
fi

SRC=""
for eachfile in $INC_FILES
do
    echo "#include \"$eachfile\"" >> $INC_FILE_NAME
    INC_SRC=$(cat $eachfile | grep -Ei 'source\(\".*"\)' | grep -oEi '\".*\"' | grep -oEi '[^"]*' | tr '\n' ' ')
    if [ ! -z "$INC_SRC" ]
    then
        SRC="$SRC $PRJ_PATH/$INC_SRC"
    fi
done

COMPILE_CMD="gcc $RUNIT_PATH/runit.c $SRC -o $RUNIT_PATH/$EXE_FILE -DTEST_MDB"

if [ "$VERBOSE_MODE" ]
then
    echo
    echo $COMPILE_CMD
    echo
fi

$COMPILE_CMD

if [ -f $RUNIT_PATH/$EXE_FILE ]
then
    $RUNIT_PATH/$EXE_FILE
else
    echo
    echo "[RUnit] Error: compile error."
    exit 1
fi

if [ -f $INC_FILE_NAME ]
then
    rm $EXE_FILE
    rm $INC_FILE_NAME
else
    echo
    echo "[RUnit] Error: compile error."
    exit 1
fi
