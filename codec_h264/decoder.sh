rm -rf ../decode_sandbox
mkdir ../decode_sandbox
cp decoder.cfg ../decode_sandbox
cp ldecod ../decode_sandbox
cd ../decode_sandbox
mkfifo recv.264
mkfifo output.yuv
./ldecod &
../bin/recv $1 recv.264 &
mplayer output.yuv -demuxer rawvideo -rawvideo qcif
cd ..
rm -rf ./decode_sandbox
