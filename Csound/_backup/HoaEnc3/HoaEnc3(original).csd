<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>


/** UDO HoaEnc3 - ordre 3 **/

opcode HoaEnc3, aaaaaaa, ak
ain, kangle xin

ah0 init 0
ah0 = ain * cos(0*kangle)

ahn1 init 0
ahn1 = ain * sin(-1*kangle)

ahn init 0
ah1 = ain * cos(1*kangle)

ahn2 init 0
ahn2 = ain * sin(-2*kangle)

ah2 init 0
ah2 = ain * cos(2*kangle)

ahn3 init 0
ahn3 = ain * sin(-3*kangle)

ah3 init 0
ah3 = ain * cos(3*kangle)


xout ah0, ahn1, ah1, ahn2, ah2, ahn3, ah3

endop

/** UDO HoaEnc3 - ordre 3 **/


instr 1

kangle = 0.7853

a1 oscil 1000, 400, 1

a1, a2, a3, a4, a5, a6, a7 HoaEnc3 a1, kangle

outch 1, a1, 2, a2, 3, a3, 4, a4, 5, a5, 6, a6, 7, a7

endin



</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 30
e


</CsScore>
</CsoundSynthesizer>