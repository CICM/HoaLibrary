<CsoundSynthesizer>
<CsOptions>

--opcode-lib=OneSourceToStereo.dylib
-odac

-+rtaudio=PortAudio

</CsOptions>
<CsInstruments>
sr = 44100
kr = 4410


instr 1 

aordre = 1
asig oscil 500, 440, 1
aangle = 100

ka = 1
kb = 0
kc = 0
kd = 0
ke = 0
kf = 0
kg = 0

a1, a2 OneSourceToStereo asig, ka, kb

outs asig, asig

endin

</CsInstruments>
<CsScore>
f1 0 512 10 1

i 1 0 10

e 


</CsScore>
</CsoundSynthesizer>
