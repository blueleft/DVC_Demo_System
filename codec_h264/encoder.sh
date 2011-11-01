rm -rf ../encode_sandbox
mkdir ../encode_sandbox
cd ../encode_sandbox
mkfifo input.yuv
mkfifo encode.264
x264 input.yuv --input-res 176x144 -o encode.264 &
../bin/sender encode.264 &
../bin/camera input.yuv 
cd ..
rm -rf ./encode_sandbox
