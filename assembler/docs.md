

Emitted Assembly Layout


.bss uninit memory

buffer: 256 (label buffer reserve 256 bytes)

.data initialized memory

  sub-directives
  .ascii (null terminated ascii string)
  .word (16-bit integer) (can init arrays like this 1,2,3,4 produces 8 bytes as an array)

myVar: .ascii "Hello World\0"
myVar2: .word 5
myVar3: .word 1,2,3,4,5


.text (program code)
