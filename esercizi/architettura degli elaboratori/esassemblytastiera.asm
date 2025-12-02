(START)
@SCREEN // 16348
D=A
@i
M=D // i punta a 1a word della mappa
(LOOP) // while(true)
@i
D=M
@24575 // ultima word della mappa
D=A-D // D=24575-i
@START
D;JLT // (**) se D<0 ricomincia
@KBD
D=M
@COLORANERO
D;JNE // salta se un tasto è premuto
@i
D=M
A=D
M=0 // MEM[i]=00...0 (bianco)
@CONTINUE
0;JMP
(COLORANERO)
@i
D=M
A=D
M=-1 // MEM[i]=11...1 (nero)
(CONTINUE)
@i
M=M+1 // i++: prossimo indirizzo
@LOOP
0;JMP