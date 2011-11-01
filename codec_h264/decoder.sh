rm -rf ../decode_sandbox
mkdir ../decode_sandbox
cp decoder.cfg ../decode_sandbox
cd ../decode_sandbox
mkfifo recv.264
mkfifo output.264
../codec_h264/ldecod &
../bin/recv $1 recv.264 &
mplayer output.264 -demuxer rawvideo -rawvideo qcif
cd ..
rm -rf ./decode_sandbox
