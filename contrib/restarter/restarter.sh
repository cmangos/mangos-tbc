#! /bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $DIR
cd $DIR
echo "run\n" > gdbcommands
echo "shell echo -e \"SERVERCRASHEVENT\"        " >> gdbcommands
echo "shell echo -e \"\nCRASH ON\" `date`       " >> gdbcommands
echo "info program                              " >> gdbcommands
echo "shell echo -e \"\nBACKTRACE\n\"           " >> gdbcommands
echo "bt                                        " >> gdbcommands
echo "shell echo -e \"\nBACKTRACE FULL\n\"      " >> gdbcommands
echo "bt full                                   " >> gdbcommands
echo "shell echo -e \"\nTHREADS\n\"             " >> gdbcommands
echo "info threads                              " >> gdbcommands
echo "shell echo -e \"\nTHREADS BACKTRACE\n\"   " >> gdbcommands
echo "thread apply all bt full                  " >> gdbcommands
chmod +x gdbcommands
while :
do
    echo "starting mangosd";
    #./mangosd
    mkdir -p crashes
    gdb mangosd --batch -x gdbcommands | tee crashes/current
    FILE=$(date +%s)
    sed -i '1,/SERVERCRASHEVENT/d' crashes/current
    mv crashes/current crashes/$FILE".crash"
    find crashes/ -name '*.crash' -and -size -10k -delete
    echo "mangosd stopped";
    sleep 1
done
