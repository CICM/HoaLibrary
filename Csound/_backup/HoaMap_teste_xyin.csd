cccccccccc
<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
; Audio out   Audio in    No messages
-odac           
-iadc     -d     ;;;RT audio I/O
; For Non-realtime ouput leave only the line below:
; -o FLjoy.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

; Demonstration of the flpanel opcode
; Horizontal click-dragging controls the frequency of the oscillator
; Vertical click-dragging controls the amplitude of the oscillator

sr = 48000
ksmps = 16
nchnls = 8
0dbfs  = 1

#include "Hoa3.inc"

FLpanel	"FLxyin", 400, 400, 10, 10, 3
FLpanelEnd
FLrun

cpuprc 1, 5


instr 1


  ; The x values are from 1 to 30.
  ixmin = 1
  ixmax = 2
  ; The y values are from 1 to 30.
  iymin = 1
  iymax = 2
  ; The initial values for X and Y are both 15.
  ixinit = 1
  iyinit = 1

  ; Get the values kx and ky using the xyin opcode.
  kx, ky, kinside FLxyin iymin, iymax, ixmin, ixmax, 10, 190, 10, 90




;kfreqx = gkfreqx
;ky = gky 
;kx = kfreqx - 2



kamod = 1
kfmod = p4
ksmod = p5

aSig	adsyn	kamod, kfmod, ksmod, "sonar.het"

;aSig oscil .5, 220, 1

kx portk kx, 0.5
ky portk ky, 0.5

ky = ky - 2 
kx = kx - 2 



aA, aB, aC, aD, aE, aF, aG HoaMap3 aSig, kx, ky

a1, a2, a3, a4, a5, a6, a7, a8 HoaDec3 aA, aB, aC, aD, aE, aF, aG

kg = .5


outch 1, a1*kg, 2, a2*kg, 3, a3*kg, 4, a4*kg, 5, a5*kg, 6, a6*kg, 7, a7*kg, 8, a8*kg


	endin


	instr 2


insnd   = 2
kamp2 = .8
kdens  = 50
kaoff  =  .10
kpoff  =  .10 
kgdur  = .02
imaxgdur =  .10
kpitch = 50000 

aT = 0
aU = 0
aV = 0
aW grain kamp2*0.4, kpitch*0.4, kdens*0.4, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0
aX grain kamp2*0.8, kpitch*0.10, kdens*0.4, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0
aY grain kamp2*0.6, kpitch*0.8, kdens*4, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0
aZ grain kamp2*0.2, kpitch*0.2, kdens*2, kaoff, kpoff, kgdur, insnd, 5, imaxgdur, 0.0


a1, a2, a3, a4, a5, a6, a7, a8 HoaDec3 aT, aU, aV, aW, aX, aY, aZ




outch 1, a1, 2, a2, 3, a3, 4, a4, 5, a5, 6, a6, 7, a7, 8, a8

	endin
	

</CsInstruments>
<CsScore>
f1 0 512 10 1
f2 0 16384 10 1   
f5  0 512  20 2 ; Hanning window 


i 2 1 60 

i 1 5  3  1 1
i 1 10 3  1 1
i 1 10 3  2 0.5
i 1 15 3  1 1
i 1 15 3  3 0.5
i 1 20 3  1 1
i 1 25 1  2 1
i 1 30 3  1 1
i 1 35 5 .3 1.5
i 1 40 2 .3 1.5
i 1 42 3 .3 1.5
i 1 48 5 .3 1.5


e

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
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
