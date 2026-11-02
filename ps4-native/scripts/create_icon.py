#!/usr/bin/env python3
import struct, zlib, os
os.makedirs("sce_sys", exist_ok=True)
W=H=512
rows=[]
for y in range(H):
    row=bytearray([0])
    for x in range(W):
        # Deep navy-to-violet diagonal gradient.
        t=(x+y)/(W+H)
        r=int(8+30*t); g=int(12+15*t); b=int(28+70*t)
        # Neon frame.
        if x<16 or x>=W-16 or y<16 or y>=H-16:
            r,g,b=116,84,255
        # Stylized C mark.
        dx=x-256; dy=y-256
        d=(dx*dx+dy*dy)**0.5
        ang=__import__('math').atan2(dy,dx)
        if 116<d<174 and not (-0.78<ang<0.78):
            r,g,b=244,247,255
        # Small cyan accent bar.
        if 190<y<210 and 160<x<352:
            r,g,b=55,215,225
        row.extend((r,g,b))
    rows.append(bytes(row))
def chunk(kind,data):
    return struct.pack(">I",len(data))+kind+data+struct.pack(">I",zlib.crc32(kind+data)&0xffffffff)
raw=b"".join(rows)
png=b"\x89PNG\r\n\x1a\n"+chunk(b"IHDR",struct.pack(">2I5B",W,H,8,2,0,0,0))+chunk(b"IDAT",zlib.compress(raw,9))+chunk(b"IEND",b"")
open("sce_sys/icon0.png","wb").write(png)
