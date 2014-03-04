<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
; Audio out   Audio in
-odac           -iadc    ;;;RT audio I/O
; For Non-realtime ouput leave only the line below:
; -o pvspitch.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

sr = 48000
ksmps = 4800
nchnls = 4

/** UDO HoaEnc1 - ordre 1 **/

	opcode HoaEnc1, aaa, ak
	
setksmps 1

ain, kangle xin 

ah0  = ain * cos(0*kangle)
ah_1 = ain * sin(1*kangle)
ah1  = ain * cos(1*kangle)


xout ah0, ah_1, ah1

	endop

/** UDO HoaEnc1 - ordre 1 **/
/** UDO HoaDec1 - ordre 1 **/
	opcode HoaDec1, aaaa, aaa

setksmps 1

aX, aY, aZ xin

asig1 = 0.5
asig2 = 0.25

aA, aB, aC HoaEnc1 asig1, 0
aD, aE, aF HoaEnc1 asig1, 1.570796
aG, aH, aI HoaEnc1 asig1, 3.141592
aJ, aK, aL HoaEnc1 asig1, 4.712388

a1 = asig2*aX + aB*aY + aC*aZ
a2 = asig2*aX + aE*aY + aF*aZ
a3 = asig2*aX + aH*aY + aI*aZ
a4 = asig2*aX + aK*aY + aL*aZ

xout a1, a2, a3, a4 

	endop

/** UDO HoaDec1 - ordre 1 **/


giwave ftgen 0, 0, 4096, 10, 1, 0.5, 0.333, 0.25, 0.2, 0.1666 


instr 1 

ifftsize = 1024
iwtype = 1    /* cleaner with hanning window */

a1 inch 1 ;Realtime audio input
;a1   soundin "input.wav" ;Use this line for file input

fsig pvsanal   a1, ifftsize, ifftsize/4, ifftsize, iwtype
kfr, kamp pvspitch   fsig, 0.01


insnd   = 10 
ibasfrq = 44100 / ftlen(insnd) ; Use original sample rate of insnd file 

kdens  = 600
kaoff  =  .1
kpoff  =  .5 
kgdur  = .01
imaxgdur =  .5 

kdens = ((kamp * 100)/50000)
kpitch = ((kamp * 5000)/50000) 

aA  grain kamp, kpitch, kdens, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0 
aB  grain kamp, kpitch, kdens, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0 
aC  grain kamp, kpitch, kdens, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0 

a1, a2, a3, a4 HoaDec1 aA, aB, aC

outch 1, a1, 2, a2, 3, a3, 4, a4


printk 0, kdens

endin 


</CsInstruments>
<CsScore>
 
f5  0 512  20 2 ; Hanning window 
f10 0 16384 1  "beats.wav" 0 0 0 

i1 0 60
 
e 
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>434</x>
 <y>148</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
