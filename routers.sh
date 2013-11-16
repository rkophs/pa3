rm -rf *log.txt
cp init.txt initA.txt;
cp init.txt initB.txt;
cp init.txt initC.txt;
cp init.txt initD.txt;
cp init.txt initE.txt;
cp init.txt initF.txt;

./router A alog.txt initA.txt 45 &
./router B blog.txt initB.txt &
./router C clog.txt initC.txt &
./router D dlog.txt initD.txt &
./router E elog.txt initE.txt &
./router F flog.txt initF.txt &

