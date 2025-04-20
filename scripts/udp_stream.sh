#!/bin/bash
# udp_stream_lowlat.sh

WIDTH="600"
HEIGHT="400"
FPS="25"
TARGET_IP="192.168.86.29"   # your Mac’s IP
PORT="5000"

echo "Ultra‑low‑latency UDP → udp://${TARGET_IP}:${PORT}"

ffmpeg \
  -f v4l2 \
    -input_format mjpeg \
    -video_size ${WIDTH}x${HEIGHT} \
    -framerate ${FPS} \
    -i /dev/video1 \
  \
  -fflags nobuffer \
  -flags low_delay \
  -probesize 32 \
  -analyzeduration 0 \
  \
  -c:v libx264 \
    -preset superfast \
    -tune zerolatency \
    -x264opts "intra-refresh=1:keyint=${FPS}:vbv-bufsize=$((800000/${FPS}))" \
    -b:v 800k \
  \
  -f mpegts \
    "udp://${TARGET_IP}:${PORT}?pkt_size=1316"
